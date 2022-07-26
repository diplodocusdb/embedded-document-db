/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "EmbeddedDocumentDBErrorCategory.hpp"
#include "XMLTreeDBNodeImpl.hpp"
#include "XMLTreeDBImpl.hpp"
#include <boost/date_time.hpp>
#include <Ishiko/Time.hpp>

using namespace Ishiko;

namespace DiplodocusDB
{

XMLTreeDBNodeImpl::XMLTreeDBNodeImpl(XMLTreeDBNodeImpl* parent, pugi::xml_node node)
    : TreeDBNodeImpl(node.name()), m_parent(parent), m_node(node)
{
}

XMLTreeDBNodeImpl::~XMLTreeDBNodeImpl()
{
}

bool XMLTreeDBNodeImpl::isRoot() const
{
    return (m_parent == nullptr);
}

XMLTreeDBNode XMLTreeDBNodeImpl::parent(Ishiko::Error& error)
{
    XMLTreeDBNode result;
    if (m_parent)
    {
        result = XMLTreeDBNode(m_parent->shared_from_this());
    }
    return result;
}

std::vector<XMLTreeDBNode> XMLTreeDBNodeImpl::childNodes(Ishiko::Error& error)
{
    std::vector<XMLTreeDBNode> result;
    loadChildren(error);
    for (std::shared_ptr<XMLTreeDBNodeImpl>& child : m_children)
    {
        result.push_back(XMLTreeDBNode(child));
    }
    return result;
}

XMLTreeDBNode XMLTreeDBNodeImpl::child(const std::string& name, Ishiko::Error& error)
{
    XMLTreeDBNode result;

    loadChildren(error);
    for (std::shared_ptr<XMLTreeDBNodeImpl>& child : m_children)
    {
        if (child->name() == name)
        {
            result = XMLTreeDBNode(child);
            break;
        }
    }

    return result;
}

XMLTreeDBNode XMLTreeDBNodeImpl::previousSibling(Ishiko::Error& error)
{
    XMLTreeDBNode result;
    return result;
}

XMLTreeDBNode XMLTreeDBNodeImpl::previousSibling(const std::string& name, Ishiko::Error& error)
{
    XMLTreeDBNode result;
    return result;
}

XMLTreeDBNode XMLTreeDBNodeImpl::nextSibling(Ishiko::Error& error)
{
    XMLTreeDBNode result;

    if (m_parent)
    {
        for (size_t i = 0; i < m_parent->m_children.size(); ++i)
        {
            if (m_parent->m_children[i].get() == this)
            {
                ++i;
                if (i < m_parent->m_children.size())
                {
                    result = XMLTreeDBNode(m_parent->m_children[i]);
                }
                break;
            }
        }
    }

    return result;
}

XMLTreeDBNode XMLTreeDBNodeImpl::nextSibling(const std::string& name, Ishiko::Error& error)
{
    // TODO
    XMLTreeDBNode result;
    return result;
}

XMLTreeDBNode XMLTreeDBNodeImpl::insertChildNode(size_t index, const std::string& name, const Value& value,
    Ishiko::Error& error)
{
    pugi::xml_node newNode = m_node.append_child(name.c_str());
    std::shared_ptr<XMLTreeDBNodeImpl> newNodeImpl = std::make_shared<XMLTreeDBNodeImpl>(this, newNode);
    newNodeImpl->value() = value;
    m_children.push_back(newNodeImpl);
    return XMLTreeDBNode(newNodeImpl);
}

XMLTreeDBNode XMLTreeDBNodeImpl::appendChildNode(const std::string& name, const Value& value, Ishiko::Error& error)
{
    pugi::xml_node newNode = m_node.append_child(name.c_str());
    std::shared_ptr<XMLTreeDBNodeImpl> newNodeImpl = std::make_shared<XMLTreeDBNodeImpl>(this, newNode);
    newNodeImpl->value() = value;
    m_children.push_back(newNodeImpl);
    return XMLTreeDBNode(newNodeImpl);
}

XMLTreeDBNode XMLTreeDBNodeImpl::setChildNode(const std::string& name, const Value& value, Ishiko::Error& error)
{
    XMLTreeDBNode result;

    loadChildren(error);
    for (size_t i = 0; i < m_children.size(); ++i)
    {
        if (m_children[i]->name() == name)
        {
            result = XMLTreeDBNode(m_children[i]);
            m_children[i]->value() = value;
            break;
        }
    }
    if (!result)
    {
        pugi::xml_node newNode = m_node.append_child(name.c_str());
        std::shared_ptr<XMLTreeDBNodeImpl> newNodeImpl = std::make_shared<XMLTreeDBNodeImpl>(this, newNode);
        newNodeImpl->value() = value;
        m_children.push_back(newNodeImpl);
        result = XMLTreeDBNode(newNodeImpl);
    }

    return result;
}

size_t XMLTreeDBNodeImpl::removeChildNode(const std::string& name, Ishiko::Error& error)
{
    return false;
}

size_t XMLTreeDBNodeImpl::removeAllChildNodes(Ishiko::Error& error)
{
    loadChildren(error);
    for (std::shared_ptr<XMLTreeDBNodeImpl>& child : m_children)
    {
        m_node.remove_child(child->m_node);
    }

    size_t result = m_children.size();
    m_children.clear();
    return result;
}

void XMLTreeDBNodeImpl::updateValue()
{
    // Remove any current data
    pugi::xml_node pcdataNode = m_node.first_child();
    if (pcdataNode.type() == pugi::node_pcdata)
    {
        m_node.remove_child(pcdataNode);
    }
    pugi::xml_node valueNode = m_node.child("data");
    if (valueNode)
    {
        m_node.remove_child(valueNode);
    }

    // Set the new data
    const Value& v = value();
    switch (v.type().primitiveType())
    {
    case PrimitiveDataType::null:
        // The data type of a node is null by default. If we didn't do that
        // then all the intermediate nodes without any value would have a
        // data-type attribute which would be cumbersome to write manually.
        m_node.remove_attribute("data-type");
        break;

    case PrimitiveDataType::unsignedInt64bit:
    {
        pugi::xml_attribute attributeNode = m_node.attribute("data-type");
        if (attributeNode)
        {
            attributeNode.set_value("unsigned-int-64bits");
        }
        else
        {
            m_node.append_attribute("data-type").set_value("unsigned-int-64bits");
        }
        if (m_children.empty())
        {
            pugi::xml_node pcdataNode = m_node.first_child();
            if (!pcdataNode || (pcdataNode.type() != pugi::node_pcdata))
            {
                pcdataNode = m_node.prepend_child(pugi::node_pcdata);
            }
            pcdataNode.set_value(std::to_string(v.asUnsignedInt64()).c_str());
        }
        else
        {
            pugi::xml_node valueNode = m_node.prepend_child("data");
            valueNode.append_child(pugi::node_pcdata).set_value(std::to_string(v.asUnsignedInt64()).c_str());
        }
    }
    break;

    case PrimitiveDataType::IEEE754Binary64:
        {
            pugi::xml_attribute attributeNode = m_node.attribute("data-type");
            if (attributeNode)
            {
                attributeNode.set_value("ieee-754-binary64");
            }
            else
            {
                m_node.append_attribute("data-type").set_value("ieee-754-binary64");
            }
            std::stringstream value;
            value << std::fixed << std::setprecision(8) << v.asDouble();
            if (m_children.empty())
            {
                pugi::xml_node pcdataNode = m_node.first_child();
                if (!pcdataNode || (pcdataNode.type() != pugi::node_pcdata))
                {
                    pcdataNode = m_node.prepend_child(pugi::node_pcdata);
                }
                pcdataNode.set_value(value.str().c_str());
            }
            else
            {
                pugi::xml_node valueNode = m_node.prepend_child("data");
                valueNode.append_child(pugi::node_pcdata).set_value(value.str().c_str());
            }
        }
        break;

    case PrimitiveDataType::unicodeString:
        {
            pugi::xml_attribute attributeNode = m_node.attribute("data-type");
            if (attributeNode)
            {
                attributeNode.set_value("unicode-string");
            }
            else
            {
                m_node.append_attribute("data-type").set_value("unicode-string");
            }
            if (m_children.empty())
            {
                pugi::xml_node pcdataNode = m_node.first_child();
                if (!pcdataNode || (pcdataNode.type() != pugi::node_pcdata))
                {
                    pcdataNode = m_node.prepend_child(pugi::node_pcdata);
                }
                pcdataNode.set_value(v.asUTF8String().c_str());
            }
            else
            {
                pugi::xml_node valueNode = m_node.prepend_child("data");
                valueNode.append_child(pugi::node_pcdata).set_value(v.asUTF8String().c_str());
            }
        }
        break;

    case PrimitiveDataType::date:
        {
            pugi::xml_attribute attributeNode = m_node.attribute("data-type");
            if (attributeNode)
            {
                attributeNode.set_value("date");
            }
            else
            {
                m_node.append_attribute("data-type").set_value("date");
            }


            if (m_children.empty())
            {
                pugi::xml_node pcdataNode = m_node.first_child();
                if (!pcdataNode || (pcdataNode.type() != pugi::node_pcdata))
                {
                    pcdataNode = m_node.prepend_child(pugi::node_pcdata);
                }
                pcdataNode.set_value(Date(v.asDate()).toISO8601String().c_str());
            }
            else
            {
                pugi::xml_node valueNode = m_node.prepend_child("data");
                valueNode.append_child(pugi::node_pcdata).set_value(Date(v.asDate()).toISO8601String().c_str());
            }
        }
        break;

    default:
        // TODO
        throw 0;
    }
     
    for (size_t i = 0; i < m_children.size(); ++i)
    {
        m_children[i]->updateValue();
    }
}

void XMLTreeDBNodeImpl::loadChildren(Ishiko::Error& error)
{
    if (m_children.empty())
    {
        pugi::xml_node childNode = m_node.first_child();
        while (childNode)
        {
            std::shared_ptr<XMLTreeDBNodeImpl> newNode = std::make_shared<XMLTreeDBNodeImpl>(this, childNode);
            pugi::xml_attribute dataTypeAttribute = childNode.attribute("data-type");
            if (dataTypeAttribute)
            {
                if (strcmp(dataTypeAttribute.as_string(), "null") == 0)
                {
                    m_children.push_back(newNode);
                }
                else if (strcmp(dataTypeAttribute.as_string(), "unsigned-int-64bits") == 0)
                {
                    // TODO: more robust decoding
                    newNode->value().setUnsignedInt64(atoi(childNode.child_value()));
                    m_children.push_back(newNode);
                }
                else if (strcmp(dataTypeAttribute.as_string(), "ieee-754-binary64") == 0)
                {
                    // TODO: more robust decoding
                    newNode->value().setDouble(atof(childNode.child_value()));
                    m_children.push_back(newNode);
                }
                else if (strcmp(dataTypeAttribute.as_string(), "date") == 0)
                {
                    // TODO: more robust decoding
                    newNode->value().setDate(boost::gregorian::from_string(childNode.child_value()));
                    m_children.push_back(newNode);
                }
                else if (strcmp(dataTypeAttribute.as_string(), "unicode-string") == 0)
                {
                    newNode->value().setUTF8String(childNode.child_value());
                    m_children.push_back(newNode);
                }
                else
                {
                    Fail(error, EmbeddedDocumentDBErrorCategory::eGeneric,
                        "Unknown data type encountered while loading child node", __FILE__, __LINE__);
                }
            }
            else
            {
                // No data-type attribute is equivalent to null
                m_children.push_back(newNode);
            }
            childNode = childNode.next_sibling();
        }
    }
}

}

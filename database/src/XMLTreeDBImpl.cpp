/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "EmbeddedDocumentDBErrorCategory.hpp"
#include "TreeDBTransaction.hpp"
#include "XMLTreeDBImpl.hpp"
#include "XMLTreeDBNodeImpl.hpp"
#include <fstream>

namespace DiplodocusDB
{

static const char* rootElementName = "diplodocusdb-xmltreedb";

void XMLTreeDBImpl::create(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_path = path;
    pugi::xml_node rootNode = m_document.append_child(rootElementName);
    if (rootNode)
    {
        m_root = XMLTreeDBNode(std::make_shared<XMLTreeDBNodeImpl>(nullptr, rootNode));

        std::ofstream file(m_path.string());
        m_document.save(file);
    }
}

void XMLTreeDBImpl::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_path = path;
    pugi::xml_parse_result result = m_document.load_file(m_path.string().c_str());
    if (!result)
    {
        // TODO: better error
        Fail(error, EmbeddedDocumentDBErrorCategory::Value::generic_error, "Failed to open file", __FILE__, __LINE__);
    }
    m_root = XMLTreeDBNode(std::make_shared<XMLTreeDBNodeImpl>(nullptr, m_document.child(rootElementName)));
}

void XMLTreeDBImpl::close()
{
    std::ofstream file(m_path.string());
    m_document.save(file, "  ");
}

XMLTreeDBNode& XMLTreeDBImpl::root()
{
    return m_root;
}

Value XMLTreeDBImpl::value(XMLTreeDBNode& node, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    return nodeImpl.value();
}

Value XMLTreeDBImpl::value(XMLTreeDBNode& node, const DataType& type, Ishiko::Error& error)
{
    Value result;
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    if (nodeImpl.value().type() == type)
    {
        result = nodeImpl.value();
    }
    return result;
}

Value XMLTreeDBImpl::childValue(XMLTreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    Value result;
    XMLTreeDBNode childNode = child(parent, name, error);
    if (!error)
    {
        result = value(childNode, error);
    }
    return result;
}

Value XMLTreeDBImpl::childValue(XMLTreeDBNode& parent, const std::string& name, const DataType& type,
    Ishiko::Error& error)
{
    Value result;
    XMLTreeDBNode childNode = child(parent, name, error);
    if (!error)
    {
        result = value(childNode, type, error);
    }
    return result;
}

XMLTreeDBNode XMLTreeDBImpl::parent(XMLTreeDBNode& node, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    return nodeImpl.parent(error);
}

std::vector<XMLTreeDBNode> XMLTreeDBImpl::childNodes(XMLTreeDBNode& parent, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    return parentNodeImpl.childNodes(error);
}

XMLTreeDBNode XMLTreeDBImpl::child(XMLTreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    return parentNodeImpl.child(name, error);
}

XMLTreeDBNode XMLTreeDBImpl::previousSibling(XMLTreeDBNode& node, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    return nodeImpl.previousSibling(error);
}

XMLTreeDBNode XMLTreeDBImpl::previousSibling(XMLTreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    return nodeImpl.previousSibling(name, error);
}

XMLTreeDBNode XMLTreeDBImpl::nextSibling(XMLTreeDBNode& node, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    return nodeImpl.nextSibling(error);
}

XMLTreeDBNode XMLTreeDBImpl::nextSibling(XMLTreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    return nodeImpl.nextSibling(name, error);
}

void XMLTreeDBImpl::setValue(XMLTreeDBNode& node, const Value& value, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    nodeImpl.value() = value;
    commitNode(nodeImpl, error);
}

XMLTreeDBNode XMLTreeDBImpl::insertChildNode(XMLTreeDBNode& parent, size_t index, const std::string& name,
    Ishiko::Error& error)
{
    Value value;
    return insertChildNode(parent, index, name, value, error);
}

XMLTreeDBNode XMLTreeDBImpl::insertChildNode(XMLTreeDBNode& parent, size_t index, const std::string& name,
    const Value& value, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    XMLTreeDBNode result = parentNodeImpl.insertChildNode(index, name, value, error);
    commitNode(parentNodeImpl, error);
    return result;
}

XMLTreeDBNode XMLTreeDBImpl::appendChildNode(XMLTreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    Value value;
    return appendChildNode(parent, name, value, error);
}

XMLTreeDBNode XMLTreeDBImpl::appendChildNode(XMLTreeDBNode& parent, const std::string& name, const Value& value,
    Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    XMLTreeDBNode result = parentNodeImpl.appendChildNode(name, value, error);
    commitNode(parentNodeImpl, error);
    return result;
}

XMLTreeDBNode XMLTreeDBImpl::setChildNode(XMLTreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    Value value;
    return setChildNode(parent, name, value, error);
}

XMLTreeDBNode XMLTreeDBImpl::setChildNode(XMLTreeDBNode& parent, const std::string& name, const Value& value,
    Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    XMLTreeDBNode result = parentNodeImpl.setChildNode(name, value, error);
    commitNode(parentNodeImpl, error);
    return result;
}

size_t XMLTreeDBImpl::removeChildNode(XMLTreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    size_t result = parentNodeImpl.removeChildNode(name, error);
    commitNode(parentNodeImpl, error);
    return result;
}

size_t XMLTreeDBImpl::removeAllChildNodes(XMLTreeDBNode& parent, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    size_t result = parentNodeImpl.removeAllChildNodes(error);
    //commitNode(parentNodeImpl, error);
    return result;
}

void XMLTreeDBImpl::commitNode(XMLTreeDBNodeImpl& node, Ishiko::Error& error)
{
    node.updateValue();
}

}

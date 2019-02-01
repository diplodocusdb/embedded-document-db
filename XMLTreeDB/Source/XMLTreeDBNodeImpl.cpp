/*
    Copyright (c) 2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "XMLTreeDBNodeImpl.h"
#include "XMLTreeDBImpl.h"

namespace DiplodocusDB
{

XMLTreeDBNodeImpl::XMLTreeDBNodeImpl(std::shared_ptr<XMLTreeDBImpl> db, XMLTreeDBNodeImpl* parent, pugi::xml_node node)
    : TreeDBNodeImpl(node.name()), m_db(db), m_parent(parent), m_node(node)
{
}

XMLTreeDBNodeImpl::~XMLTreeDBNodeImpl()
{
}

bool XMLTreeDBNodeImpl::isRoot() const
{
    return (m_parent == nullptr);
}

TreeDBNode XMLTreeDBNodeImpl::parent(Ishiko::Error& error)
{
    TreeDBNode result;
    if (m_parent)
    {
        result = TreeDBNode(m_parent->shared_from_this());
    }
    return result;
}

void XMLTreeDBNodeImpl::children(std::vector<TreeDBNode>& children, Ishiko::Error& error)
{
    loadChildren(error);
    for (std::shared_ptr<XMLTreeDBNodeImpl>& child : m_children)
    {
        children.push_back(TreeDBNode(child));
    }
}

TreeDBNode XMLTreeDBNodeImpl::child(const TreeDBKey& key, Ishiko::Error& error)
{
    TreeDBNode result;

    loadChildren(error);
    for (std::shared_ptr<XMLTreeDBNodeImpl>& child : m_children)
    {
        if (child->key() == key)
        {
            result = TreeDBNode(child);
            break;
        }
    }

    return result;
}

TreeDBNode XMLTreeDBNodeImpl::previousSibling(Ishiko::Error& error)
{
    TreeDBNode result;
    return result;
}

TreeDBNode XMLTreeDBNodeImpl::previousSibling(const TreeDBKey& key, Ishiko::Error& error)
{
    TreeDBNode result;
    return result;
}

TreeDBNode XMLTreeDBNodeImpl::nextSibling(Ishiko::Error& error)
{
    TreeDBNode result;
    pugi::xml_node sibling = m_node.next_sibling();
    if (sibling)
    {
        result = TreeDBNode(std::make_shared<XMLTreeDBNodeImpl>(m_db, m_parent, sibling));
    }
    return result;
}

TreeDBNode XMLTreeDBNodeImpl::nextSibling(const TreeDBKey& key, Ishiko::Error& error)
{
    TreeDBNode result;
    return result;
}

TreeDBNode XMLTreeDBNodeImpl::insert(const TreeDBKey& key, size_t index)
{
    pugi::xml_node newNode = m_node.append_child(key.value().c_str());
    m_children.push_back(std::make_shared<XMLTreeDBNodeImpl>(m_db, this, newNode));
    return TreeDBNode(m_children.back());
}

TreeDBNode XMLTreeDBNodeImpl::insertBefore(const TreeDBKey& key, TreeDBNode& child)
{
    TreeDBNode result;
    return result;
}

TreeDBNode XMLTreeDBNodeImpl::insertAfter(const TreeDBKey& key, TreeDBNode& child)
{
    TreeDBNode result;
    return result;
}

TreeDBNode XMLTreeDBNodeImpl::append(const TreeDBKey& key)
{
    pugi::xml_node newNode = m_node.append_child(key.value().c_str());
    m_children.push_back(std::make_shared<XMLTreeDBNodeImpl>(m_db, this, newNode));
    return TreeDBNode(m_children.back());
}

TreeDBNode XMLTreeDBNodeImpl::set(const TreeDBKey& key)
{
    pugi::xml_node existingNode = m_node.child(key.value().c_str());
    if (existingNode)
    {
        // TODO : we need to load the children else we are going to have the same
        // node represented by different XMLTreeDBNodeImpl instance
        return TreeDBNode(std::make_shared<XMLTreeDBNodeImpl>(m_db, this, existingNode));
    }
    else
    {
        pugi::xml_node newNode = m_node.append_child(key.value().c_str());
        m_children.push_back(std::make_shared<XMLTreeDBNodeImpl>(m_db, this, newNode));
        return TreeDBNode(m_children.back());
    }
}

bool XMLTreeDBNodeImpl::remove(const TreeDBKey& key, Ishiko::Error& error)
{
    return false;
}

void XMLTreeDBNodeImpl::commit(Ishiko::Error& error)
{
    m_db->commitNode(*this, error);
}

void XMLTreeDBNodeImpl::updateValue()
{
    const TreeDBValue& v = value();
    if (v.type() == EPrimitiveDataType::eNULL)
    {
        pugi::xml_attribute attributeNode = m_node.attribute("data-type");
        if (attributeNode)
        {
            attributeNode.set_value("null");
        }
        else
        {
            m_node.append_attribute("data-type").set_value("null");
        }
    }
    else if (v.type() != EPrimitiveDataType::eNULL)
    {
        pugi::xml_attribute attributeNode = m_node.attribute("data-type");
        if (attributeNode)
        {
            attributeNode.set_value("utf8string");
        }
        else
        {
            m_node.append_attribute("data-type").set_value("utf8string");
        }
        m_node.text().set(v.asString().c_str());
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
            std::shared_ptr<XMLTreeDBNodeImpl> newNode = std::make_shared<XMLTreeDBNodeImpl>(m_db, this, childNode);
            pugi::xml_attribute dataTypeAttribute = childNode.attribute("data-type");
            if (dataTypeAttribute)
            {
                if (strcmp(dataTypeAttribute.as_string(), "null") == 0)
                {
                    m_children.push_back(newNode);
                }
                else if (strcmp(dataTypeAttribute.as_string(), "utf8string") == 0)
                {
                    newNode->value().setString(childNode.child_value());
                    m_children.push_back(newNode);
                }
                else
                {
                    error = -1;
                }
            }
            else
            {
                error = -1;
            }
            childNode = childNode.next_sibling();
        }
    }
}

}

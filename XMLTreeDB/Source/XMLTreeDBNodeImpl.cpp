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

XMLTreeDBNodeImpl::XMLTreeDBNodeImpl(std::shared_ptr<XMLTreeDBImpl> db, pugi::xml_node node)
    : m_db(db), m_node(node)
{
}

XMLTreeDBNodeImpl::~XMLTreeDBNodeImpl()
{
}

bool XMLTreeDBNodeImpl::isRoot() const
{
    return true;
}

TreeDBNode XMLTreeDBNodeImpl::parent(Ishiko::Error& error)
{
    TreeDBNode result;
    return result;
}

void XMLTreeDBNodeImpl::children(std::vector<TreeDBNode>& children, Ishiko::Error& error)
{
}

TreeDBNode XMLTreeDBNodeImpl::child(const TreeDBKey& key, Ishiko::Error& error)
{
    TreeDBNode result;
    pugi::xml_node childNode = m_node.child(key.value().c_str());
    if (childNode)
    {
        pugi::xml_attribute dataTypeAttribute = childNode.attribute("data-type");
        if (dataTypeAttribute)
        {
            if (strcmp(dataTypeAttribute.as_string(), "null") == 0)
            {
                result = TreeDBNode(std::make_shared<XMLTreeDBNodeImpl>(m_db, childNode));
            }
            else if (strcmp(dataTypeAttribute.as_string(), "utf8string") == 0)
            {
                result = TreeDBNode(std::make_shared<XMLTreeDBNodeImpl>(m_db, childNode));
                result.value().setString(childNode.child_value());
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
    }
    else
    {
        error = -1;
    }

    return result;
}

TreeDBNode XMLTreeDBNodeImpl::insert(const TreeDBKey& key, size_t index)
{
    pugi::xml_node newNode = m_node.append_child(key.value().c_str());
    return TreeDBNode(std::make_shared<XMLTreeDBNodeImpl>(m_db, newNode));
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
    return TreeDBNode(std::make_shared<XMLTreeDBNodeImpl>(m_db, newNode));
}

bool XMLTreeDBNodeImpl::remove(const TreeDBKey& key, Ishiko::Error& error)
{
    return false;
}

void XMLTreeDBNodeImpl::commit(Ishiko::Error& error)
{
    const TreeDBValue& v = value();
    if (v.type() == EPrimitiveDataType::eNULL)
    {
        m_node.append_attribute("data-type").set_value("null");
    }
    else if (v.type() != EPrimitiveDataType::eNULL)
    {
        m_node.append_attribute("data-type").set_value("utf8string");
        m_node.append_child(pugi::node_pcdata).set_value(v.asString().c_str());
    }
    m_db->commitNode(*this, error);
}

}

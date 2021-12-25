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

#include "XMLTreeDB.h"
#include "XMLTreeDBImpl.h"

namespace DiplodocusDB
{

XMLTreeDB::XMLTreeDB()
    : m_impl(std::make_shared<XMLTreeDBImpl>())
{
}

XMLTreeDB::~XMLTreeDB()
{
}

void XMLTreeDB::create(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_impl->create(path, error);
}

void XMLTreeDB::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_impl->open(path, error);
}

void XMLTreeDB::close()
{
    m_impl->close();
}

TreeDBNode& XMLTreeDB::root()
{
    return m_impl->root();
}

TreeDBValue XMLTreeDB::value(TreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->value(node, error);
}

TreeDBValue XMLTreeDB::value(TreeDBNode& node, const DataType& type, Ishiko::Error& error)
{
    return m_impl->value(node, type, error);
}

TreeDBValue XMLTreeDB::childValue(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->childValue(parent, name, error);
}

TreeDBValue XMLTreeDB::childValue(TreeDBNode& parent, const std::string& name, const DataType& type,
    Ishiko::Error& error)
{
    return m_impl->childValue(parent, name, type, error);
}

TreeDBNode XMLTreeDB::parent(TreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->parent(node, error);
}

std::vector<TreeDBNode> XMLTreeDB::childNodes(TreeDBNode& parent, Ishiko::Error& error)
{
    return m_impl->childNodes(parent, error);
}

TreeDBNode XMLTreeDB::child(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->child(parent, name, error);
}

TreeDBNode XMLTreeDB::previousSibling(TreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->previousSibling(node, error);
}

TreeDBNode XMLTreeDB::previousSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    return m_impl->previousSibling(node, name, error);
}

TreeDBNode XMLTreeDB::nextSibling(TreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->nextSibling(node, error);
}

TreeDBNode XMLTreeDB::nextSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    return m_impl->nextSibling(node, name, error);
}

void XMLTreeDB::traverse(TreeDBNode& node, ETreeTraversalOrder order, void (*callback)(TreeDB& db, TreeDBNode& node),
    void* callbackData)
{
    return m_impl->traverse(node, order, callback, callbackData);
}

TreeDBTransaction XMLTreeDB::createTransaction(Ishiko::Error& error)
{
    return m_impl->createTransaction(error);
}

void XMLTreeDB::commitTransaction(TreeDBTransaction& transaction, Ishiko::Error& error)
{
    return m_impl->commitTransaction(transaction, error);
}

void XMLTreeDB::rollbackTransaction(TreeDBTransaction& transaction)
{
    return m_impl->rollbackTransaction(transaction);
}

void XMLTreeDB::setValue(TreeDBNode& node, const TreeDBValue& value, Ishiko::Error& error)
{
    m_impl->setValue(node, value, error);
}

TreeDBNode XMLTreeDB::insertChildNode(TreeDBNode& parent, size_t index, const std::string& name, Ishiko::Error& error)
{
    return m_impl->insertChildNode(parent, index, name, error);
}

TreeDBNode XMLTreeDB::insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
    const TreeDBValue& value, Ishiko::Error& error)
{
    return m_impl->insertChildNode(parent, index, name, value, error);
}

TreeDBNode XMLTreeDB::insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
    Ishiko::Error& error)
{
    return m_impl->insertChildNodeBefore(parent, nextChild, name, error);
}

TreeDBNode XMLTreeDB::insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
    const TreeDBValue& value, Ishiko::Error& error)
{
    return m_impl->insertChildNodeBefore(parent, nextChild, name, value, error);
}

TreeDBNode XMLTreeDB::insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
    Ishiko::Error& error)
{
    return m_impl->insertChildNodeAfter(parent, previousChild, name, error);
}

TreeDBNode XMLTreeDB::insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
    const TreeDBValue& value, Ishiko::Error& error)
{
    return m_impl->insertChildNodeAfter(parent, previousChild, name, value, error);
}

TreeDBNode XMLTreeDB::appendChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->appendChildNode(parent, name, error);
}

TreeDBNode XMLTreeDB::appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent, const std::string& name,
    Ishiko::Error& error)
{
    return m_impl->appendChildNode(transaction, parent, name, error);
}

TreeDBNode XMLTreeDB::appendChildNode(TreeDBNode& parent, const std::string& name, const TreeDBValue& value,
    Ishiko::Error& error)
{
    return m_impl->appendChildNode(parent, name, value, error);
}

TreeDBNode XMLTreeDB::appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent, const std::string& name,
    const TreeDBValue& value, Ishiko::Error& error)
{
    return m_impl->appendChildNode(transaction, parent, name, value, error);
}

TreeDBNode XMLTreeDB::setChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->setChildNode(parent, name, error);
}

TreeDBNode XMLTreeDB::setChildNode(TreeDBNode& parent, const std::string& name, const TreeDBValue& value,
    Ishiko::Error& error)
{
    return m_impl->setChildNode(parent, name, value, error);
}

size_t XMLTreeDB::removeChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->removeChildNode(parent, name, error);
}

size_t XMLTreeDB::removeAllChildNodes(TreeDBNode& parent, Ishiko::Error& error)
{
    return m_impl->removeAllChildNodes(parent, error);
}

}

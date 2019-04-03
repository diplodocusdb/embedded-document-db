/*
    Copyright (c) 2018 Xavier Leclercq

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

#include "EmbeddedTreeDB.h"
#include "EmbeddedTreeDBImpl.h"

namespace DiplodocusDB
{

EmbeddedTreeDB::EmbeddedTreeDB()
    : m_impl(std::make_shared<EmbeddedTreeDBImpl>())
{
}

EmbeddedTreeDB::~EmbeddedTreeDB()
{
}

void EmbeddedTreeDB::create(const boost::filesystem::path& path,
                            Ishiko::Error& error)
{
    m_impl->create(path, error);
}

void EmbeddedTreeDB::open(const boost::filesystem::path& path,
                          Ishiko::Error& error)
{
    m_impl->open(path, error);
}

void EmbeddedTreeDB::close()
{
    m_impl->close();
}

TreeDBNode& EmbeddedTreeDB::root()
{
    return m_impl->root();
}

TreeDBNode EmbeddedTreeDB::parent(TreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->parent(node, error);
}

std::vector<TreeDBNode> EmbeddedTreeDB::childNodes(TreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->childNodes(node, error);
}

TreeDBNode EmbeddedTreeDB::child(TreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    return m_impl->child(node, name, error);
}

TreeDBNode EmbeddedTreeDB::previousSibling(TreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->previousSibling(node, error);
}

TreeDBNode EmbeddedTreeDB::previousSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    return m_impl->previousSibling(node, name, error);
}

TreeDBNode EmbeddedTreeDB::nextSibling(TreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->nextSibling(node, error);
}

TreeDBNode EmbeddedTreeDB::nextSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    return m_impl->nextSibling(node, name, error);
}

TreeDBTransaction EmbeddedTreeDB::createTransaction()
{
    return m_impl->createTransaction();
}

TreeDBTransaction EmbeddedTreeDB::commitTransaction(TreeDBTransaction& transaction)
{
    return m_impl->commitTransaction(transaction);
}

TreeDBTransaction EmbeddedTreeDB::rollbackTransaction(TreeDBTransaction& transaction)
{
    return m_impl->rollbackTransaction(transaction);
}

void EmbeddedTreeDB::setValue(TreeDBNode& node, const TreeDBValue& value, Ishiko::Error& error)
{
    m_impl->setValue(node, value, error);
}

TreeDBNode EmbeddedTreeDB::insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
    Ishiko::Error& error)
{
    return m_impl->insertChildNode(parent, index, name, error);
}

TreeDBNode EmbeddedTreeDB::insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
    const TreeDBValue& value, Ishiko::Error& error)
{
    return m_impl->insertChildNode(parent, index, name, value, error);
}

TreeDBNode EmbeddedTreeDB::insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
    Ishiko::Error& error)
{
    return m_impl->insertChildNodeBefore(parent, nextChild, name, error);
}

TreeDBNode EmbeddedTreeDB::insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
    const TreeDBValue& value, Ishiko::Error& error)
{
    return m_impl->insertChildNodeBefore(parent, nextChild, name, value, error);
}

TreeDBNode EmbeddedTreeDB::insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
    Ishiko::Error& error)
{
    return m_impl->insertChildNodeAfter(parent, previousChild, name, error);
}

TreeDBNode EmbeddedTreeDB::insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
    const TreeDBValue& value, Ishiko::Error& error)
{
    return m_impl->insertChildNodeAfter(parent, previousChild, name, value, error);
}

TreeDBNode EmbeddedTreeDB::appendChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->appendChildNode(parent, name, error);
}

TreeDBNode EmbeddedTreeDB::appendChildNode(TreeDBNode& parent, const std::string& name, const TreeDBValue& value,
    Ishiko::Error& error)
{
    return m_impl->appendChildNode(parent, name, value, error);
}

TreeDBNode EmbeddedTreeDB::setChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->setChildNode(parent, name, error);
}

TreeDBNode EmbeddedTreeDB::setChildNode(TreeDBNode& parent, const std::string& name, const TreeDBValue& value,
    Ishiko::Error& error)
{
    return m_impl->setChildNode(parent, name, value, error);
}

size_t EmbeddedTreeDB::removeChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->removeChildNode(parent, name, error);
}

size_t EmbeddedTreeDB::removeAllChildNodes(TreeDBNode& parent, Ishiko::Error& error)
{
    return m_impl->removeAllChildNodes(parent, error);
}

}

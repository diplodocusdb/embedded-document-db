/*
    Copyright (c) 2018-2019 Xavier Leclercq

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

#include "EmbeddedTreeDBImpl.h"
#include "EmbeddedTreeDBNodeImpl.h"

namespace DiplodocusDB
{

EmbeddedTreeDBImpl::EmbeddedTreeDBImpl()
{
}

EmbeddedTreeDBImpl::~EmbeddedTreeDBImpl()
{
}

void EmbeddedTreeDBImpl::create(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_masterFile.create(path, error);
    if (!error)
    {
        m_root = TreeDBNode(std::make_shared<EmbeddedTreeDBNodeImpl>("/", m_masterFile.rootNodePosition(), RecordMarker(PageRepositoryPosition(0, 0))));
    }
}

void EmbeddedTreeDBImpl::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_masterFile.open(path, error);
    if (!error)
    {
        m_root = TreeDBNode(std::make_shared<EmbeddedTreeDBNodeImpl>("/", m_masterFile.rootNodePosition(), RecordMarker(PageRepositoryPosition(0, 0))));
    }
}

void EmbeddedTreeDBImpl::close()
{
    m_masterFile.close();
}

TreeDBNode& EmbeddedTreeDBImpl::root()
{
    return m_root;
}

TreeDBNode EmbeddedTreeDBImpl::parent(TreeDBNode& node, Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

void EmbeddedTreeDBImpl::setValue(TreeDBNode& node, const TreeDBValue& value, Ishiko::Error& error)
{
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*node.impl());
    nodeImpl.value() = value;
    commitNode(nodeImpl, error);
}

TreeDBNode EmbeddedTreeDBImpl::insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
    Ishiko::Error& error)
{   
    TreeDBValue value;
    return insertChildNode(parent, index, name, value, error);
}

TreeDBNode EmbeddedTreeDBImpl::insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
    const TreeDBValue& value, Ishiko::Error& error)
{
    TreeDBNode result = appendNode(name);
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;
    commitNode(nodeImpl, error);
    return result;
}

TreeDBNode EmbeddedTreeDBImpl::insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild,
    const std::string& name, Ishiko::Error& error)
{
    TreeDBValue value;
    return insertChildNodeBefore(parent, nextChild, name, value, error);
}

TreeDBNode EmbeddedTreeDBImpl::insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild,
    const std::string& name, const TreeDBValue& value, Ishiko::Error& error)
{
    // TODO : does this work?
    TreeDBNode result = insertNode(name, static_cast<EmbeddedTreeDBNodeImpl&>(*nextChild.impl()).marker());
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;
    commitNode(nodeImpl, error);
    return result;
}

TreeDBNode EmbeddedTreeDBImpl::insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild,
    const std::string& name, Ishiko::Error& error)
{
    TreeDBValue value;
    return insertChildNodeAfter(parent, previousChild, name, value, error);
}

TreeDBNode EmbeddedTreeDBImpl::insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild,
    const std::string& name, const TreeDBValue& value, Ishiko::Error& error)
{
    // TODO : does this work?
    TreeDBNode result = insertNode(name, static_cast<EmbeddedTreeDBNodeImpl&>(*previousChild.impl()).marker());
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;
    commitNode(nodeImpl, error);
    return result;
}

TreeDBNode EmbeddedTreeDBImpl::appendChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    TreeDBValue value;
    return appendChildNode(parent, name, value, error);
}

TreeDBNode EmbeddedTreeDBImpl::appendChildNode(TreeDBNode& parent, const std::string& name, const TreeDBValue& value,
    Ishiko::Error& error)
{
    TreeDBNode result = appendNode(name);
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;
    commitNode(nodeImpl, error);
    return result;
}

TreeDBNode EmbeddedTreeDBImpl::setChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    TreeDBValue value;
    return setChildNode(parent, name, value, error);
}

TreeDBNode EmbeddedTreeDBImpl::setChildNode(TreeDBNode& parent, const std::string& name, const TreeDBValue& value,
    Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

size_t EmbeddedTreeDBImpl::removeChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    // TODO
    return 0;
}

TreeDBNode EmbeddedTreeDBImpl::getNode(const TreeDBKey& key, Ishiko::Error& error)
{
    std::shared_ptr<EmbeddedTreeDBNodeImpl> temp = std::make_shared<EmbeddedTreeDBNodeImpl>(key,
        PageRepositoryPosition(0, 0), PageRepositoryPosition(0, 0));
    bool found = m_masterFile.findNode(key, *temp, error);
    return TreeDBNode(temp);
}

TreeDBNode EmbeddedTreeDBImpl::insertNode(const std::string& name, const RecordMarker& marker)
{
    return m_uncommittedNodes.createNode(name, marker);
}

TreeDBNode EmbeddedTreeDBImpl::appendNode(const TreeDBKey& key)
{
    return m_uncommittedNodes.createNode(key, m_masterFile.dataEndPosition());
}

bool EmbeddedTreeDBImpl::removeNode(const TreeDBKey& key,
                                    Ishiko::Error& error)
{
    return m_masterFile.removeNode(key, error);
}

size_t EmbeddedTreeDBImpl::removeAllChildNodes(TreeDBNode& parent, Ishiko::Error& error)
{
    // TODO
    return 0;
}

void EmbeddedTreeDBImpl::commitNode(const EmbeddedTreeDBNodeImpl& node, Ishiko::Error& error)
{
    m_masterFile.addNode(node, error);
}

}

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
#include "EmbeddedTreeDBTransactionImpl.h"

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
        m_root = TreeDBNode(std::make_shared<EmbeddedTreeDBNodeImpl>(NodeID(0), NodeID(1), "/"));
    }
}

void EmbeddedTreeDBImpl::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_masterFile.open(path, error);
    if (!error)
    {
        m_root = TreeDBNode(std::make_shared<EmbeddedTreeDBNodeImpl>(NodeID(0), NodeID(1), "/"));
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

std::vector<TreeDBNode> EmbeddedTreeDBImpl::childNodes(TreeDBNode& parent, Ishiko::Error& error)
{
    // TODO
    std::vector<TreeDBNode> result;
    return result;
}

TreeDBNode EmbeddedTreeDBImpl::child(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    TreeDBNode result;

    EmbeddedTreeDBNodeImpl& parentNodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*parent.impl());
    SiblingNodesRecordGroup siblingNodesRecordGroup;
    bool found = m_masterFile.findSiblingNodesRecordGroup(parentNodeImpl.nodeID(), siblingNodesRecordGroup, error);
    if (!error && found)
    {
        EmbeddedTreeDBNodeImpl node;
        found = siblingNodesRecordGroup.find(name, node);
        if (found)
        {
            // TODO : this doesn't work because we take a copy of the node so modifications will casuse
            // inconsistencies
            result = TreeDBNode(std::make_shared<EmbeddedTreeDBNodeImpl>(node));
        }
    }

    return result;
}

TreeDBNode EmbeddedTreeDBImpl::previousSibling(TreeDBNode& node, Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

TreeDBNode EmbeddedTreeDBImpl::previousSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

TreeDBNode EmbeddedTreeDBImpl::nextSibling(TreeDBNode& node, Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

TreeDBNode EmbeddedTreeDBImpl::nextSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

void EmbeddedTreeDBImpl::traverse(TreeDBNode& node, ETreeTraversalOrder order,
    void (*callback)(TreeDB& db, TreeDBNode& node), void* callbackData)
{
    // TODO
}

TreeDBTransaction EmbeddedTreeDBImpl::createTransaction()
{
    // TODO
    return TreeDBTransaction(std::make_shared<EmbeddedTreeDBTransactionImpl>());
}

TreeDBTransaction EmbeddedTreeDBImpl::commitTransaction(TreeDBTransaction& transaction)
{
    // TODO
    return TreeDBTransaction(std::make_shared<EmbeddedTreeDBTransactionImpl>());
}

TreeDBTransaction EmbeddedTreeDBImpl::rollbackTransaction(TreeDBTransaction& transaction)
{
    // TODO
    return TreeDBTransaction(std::make_shared<EmbeddedTreeDBTransactionImpl>());
}

void EmbeddedTreeDBImpl::setValue(TreeDBNode& node, const TreeDBValue& value, Ishiko::Error& error)
{
    // TODO : this can't be working, it re-adds the node, surely that creates duplicate nodes
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*node.impl());
    nodeImpl.value() = value;
    SiblingNodesRecordGroup siblings(nodeImpl);
    m_masterFile.addSiblingNodesRecordGroup(siblings, error);
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
    // TODO : doesn't work if there are already child nodes on this node
    EmbeddedTreeDBNodeImpl& parentNodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*parent.impl());
    TreeDBNode result = appendNode(parentNodeImpl.parentNodeID(), name);
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;
    SiblingNodesRecordGroup siblings(nodeImpl);
    m_masterFile.addSiblingNodesRecordGroup(siblings, error);
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
    // TODO : doesn't work if there are already child nodes on this node
    EmbeddedTreeDBNodeImpl& parentNodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*parent.impl());
    TreeDBNode result = insertNode(parentNodeImpl.parentNodeID(), name);
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;
    SiblingNodesRecordGroup siblings(nodeImpl);
    m_masterFile.addSiblingNodesRecordGroup(siblings, error);
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
    // TODO : doesn't work if there are already child nodes on this node
    EmbeddedTreeDBNodeImpl& parentNodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*parent.impl());
    TreeDBNode result = insertNode(parentNodeImpl.parentNodeID(), name);
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;
    SiblingNodesRecordGroup siblings(nodeImpl);
    m_masterFile.addSiblingNodesRecordGroup(siblings, error);
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
    // TODO : doesn't work if there are already child nodes on this node
    EmbeddedTreeDBNodeImpl& parentNodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*parent.impl());
    TreeDBNode result = appendNode(parentNodeImpl.parentNodeID(), name);
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;
    SiblingNodesRecordGroup siblings(nodeImpl);
    m_masterFile.addSiblingNodesRecordGroup(siblings, error);
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

size_t EmbeddedTreeDBImpl::removeAllChildNodes(TreeDBNode& parent, Ishiko::Error& error)
{
    // TODO
    return 0;
}

TreeDBNode EmbeddedTreeDBImpl::insertNode(const NodeID& parentNodeID, const std::string& name)
{
    return m_uncommittedNodes.createNode(parentNodeID, name);
}

TreeDBNode EmbeddedTreeDBImpl::appendNode(const NodeID& parentNodeID, const std::string& name)
{
    return m_uncommittedNodes.createNode(parentNodeID, name);
}

}

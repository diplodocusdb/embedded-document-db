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
    m_cachedRecordFiles.createMasterFile(path, error);
    if (!error)
    {
        m_root = TreeDBNode(std::make_shared<EmbeddedTreeDBNodeImpl>(NodeID(0), NodeID(1), "/"));
    }
}

void EmbeddedTreeDBImpl::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_cachedRecordFiles.openMasterFile(path, error);
    if (!error)
    {
        m_root = TreeDBNode(std::make_shared<EmbeddedTreeDBNodeImpl>(NodeID(0), NodeID(1), "/"));
    }
}

void EmbeddedTreeDBImpl::close()
{
    m_cachedRecordFiles.close();
}

TreeDBNode& EmbeddedTreeDBImpl::root()
{
    return m_root;
}

TreeDBValue EmbeddedTreeDBImpl::value(TreeDBNode& node, Ishiko::Error& error)
{
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*node.impl());
    return nodeImpl.value();
}

TreeDBValue EmbeddedTreeDBImpl::value(TreeDBNode& node, const DataType& type, Ishiko::Error& error)
{
    TreeDBValue result;
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*node.impl());
    if (nodeImpl.value().type() == type)
    {
        result = nodeImpl.value();
    }
    return result;
}

TreeDBValue EmbeddedTreeDBImpl::childValue(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    TreeDBValue result;
    TreeDBNode childNode = child(parent, name, error);
    if (!error)
    {
        result = value(childNode, error);
    }
    return result;
}

TreeDBValue EmbeddedTreeDBImpl::childValue(TreeDBNode& parent, const std::string& name, const DataType& type,
    Ishiko::Error& error)
{
    TreeDBValue result;
    TreeDBNode childNode = child(parent, name, error);
    if (!error)
    {
        result = value(childNode, type, error);
    }
    return result;
}

TreeDBNode EmbeddedTreeDBImpl::parent(TreeDBNode& node, Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

std::vector<TreeDBNode> EmbeddedTreeDBImpl::childNodes(TreeDBNode& parent, Ishiko::Error& error)
{
    std::vector<TreeDBNode> result;

    EmbeddedTreeDBNodeImpl& parentNodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*parent.impl());
    std::shared_ptr<SiblingNodesRecordGroup> siblingNodesRecordGroup;
    bool found = m_cachedRecordFiles.findSiblingNodesRecordGroup(parentNodeImpl.nodeID(), siblingNodesRecordGroup,
        error);
    if (!error && found)
    {
        // TODO: use iterator, also need to check the impact of copying these things around
        for (size_t i = 0; i < siblingNodesRecordGroup->size(); ++i)
        {
            // TODO: this looks pretty horrible conversion wise
            result.push_back(TreeDBNode(std::make_shared<EmbeddedTreeDBNodeImpl>((*siblingNodesRecordGroup)[i])));
        }
    }

    return result;
}

TreeDBNode EmbeddedTreeDBImpl::child(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    TreeDBNode result;

    EmbeddedTreeDBNodeImpl& parentNodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*parent.impl());
    std::shared_ptr<SiblingNodesRecordGroup> siblingNodesRecordGroup;
    bool found = m_cachedRecordFiles.findSiblingNodesRecordGroup(parentNodeImpl.nodeID(), siblingNodesRecordGroup,
        error);
    if (!error && found)
    {
        EmbeddedTreeDBNodeImpl node;
        found = siblingNodesRecordGroup->find(name, node);
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

TreeDBTransaction EmbeddedTreeDBImpl::createTransaction(Ishiko::Error& error)
{
    return TreeDBTransaction(std::make_shared<EmbeddedTreeDBTransactionImpl>());
}

void EmbeddedTreeDBImpl::commitTransaction(TreeDBTransaction& transaction, Ishiko::Error& error)
{
    EmbeddedTreeDBTransactionImpl& transactionImpl = static_cast<EmbeddedTreeDBTransactionImpl&>(*transaction.impl());
    transactionImpl.commit(m_cachedRecordFiles, error);
}

void EmbeddedTreeDBImpl::rollbackTransaction(TreeDBTransaction& transaction)
{
    EmbeddedTreeDBTransactionImpl& transactionImpl = static_cast<EmbeddedTreeDBTransactionImpl&>(*transaction.impl());
    transactionImpl.rollback();
}

void EmbeddedTreeDBImpl::setValue(TreeDBNode& node, const TreeDBValue& value, Ishiko::Error& error)
{
    // TODO : this can't be working, it re-adds the node, surely that creates duplicate nodes
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*node.impl());
    nodeImpl.value() = value;
    SiblingNodesRecordGroup siblings(nodeImpl);
    m_cachedRecordFiles.addSiblingNodesRecordGroup(siblings, error);
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
    TreeDBNode result = TreeDBNode(std::make_shared<EmbeddedTreeDBNodeImpl>(parentNodeImpl.nodeID(), NodeID(0), name));
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;
    SiblingNodesRecordGroup siblings(nodeImpl);
    m_cachedRecordFiles.addSiblingNodesRecordGroup(siblings, error);
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
    TreeDBNode result = TreeDBNode(std::make_shared<EmbeddedTreeDBNodeImpl>(parentNodeImpl.nodeID(), NodeID(0), name));
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;
    SiblingNodesRecordGroup siblings(nodeImpl);
    m_cachedRecordFiles.addSiblingNodesRecordGroup(siblings, error);
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
    TreeDBNode result = TreeDBNode(std::make_shared<EmbeddedTreeDBNodeImpl>(parentNodeImpl.nodeID(), NodeID(0), name));
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;
    SiblingNodesRecordGroup siblings(nodeImpl);
    m_cachedRecordFiles.addSiblingNodesRecordGroup(siblings, error);
    return result;
}

TreeDBNode EmbeddedTreeDBImpl::appendChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    TreeDBValue value;
    return appendChildNode(parent, name, value, error);
}

TreeDBNode EmbeddedTreeDBImpl::appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent,
    const std::string& name, Ishiko::Error& error)
{
    TreeDBValue value;
    return appendChildNode(transaction, parent, name, value, error);
}

TreeDBNode EmbeddedTreeDBImpl::appendChildNode(TreeDBNode& parent, const std::string& name, const TreeDBValue& value,
    Ishiko::Error& error)
{
    TreeDBNode result;

    EmbeddedTreeDBNodeImpl& parentNodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*parent.impl());
    result = TreeDBNode(std::make_shared<EmbeddedTreeDBNodeImpl>(parentNodeImpl.nodeID(), NodeID(0), name));
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;

    std::shared_ptr<SiblingNodesRecordGroup> existingSiblingNodesRecordGroup;
    bool found = m_cachedRecordFiles.findSiblingNodesRecordGroup(parentNodeImpl.nodeID(),
        existingSiblingNodesRecordGroup, error);
    if (!error)
    {
        if (found)
        {
            // TODO
            existingSiblingNodesRecordGroup->push_back(nodeImpl);
            m_cachedRecordFiles.updateSiblingNodesRecordGroup(*existingSiblingNodesRecordGroup, error);
        }
        else
        {
            SiblingNodesRecordGroup siblings(nodeImpl);
            m_cachedRecordFiles.addSiblingNodesRecordGroup(siblings, error);
        }
    }

    return result;
}

TreeDBNode EmbeddedTreeDBImpl::appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent,
    const std::string& name, const TreeDBValue& value, Ishiko::Error& error)
{
    EmbeddedTreeDBTransactionImpl& transactionImpl = static_cast<EmbeddedTreeDBTransactionImpl&>(*transaction.impl());
    return transactionImpl.appendChildNode(m_cachedRecordFiles, parent, name, value, error);
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

}

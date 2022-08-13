/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "EmbeddedDocumentDBImpl.hpp"
#include "EmbeddedDocumentDBNodeImpl.hpp"
#include "EmbeddedTreeDBTransactionImpl.h"

using namespace DiplodocusDB;

EmbeddedDocumentDBImpl::EmbeddedDocumentDBImpl()
{
}

EmbeddedDocumentDBImpl::~EmbeddedDocumentDBImpl()
{
}

void EmbeddedDocumentDBImpl::create(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_storageEngine.createMasterFile(path, error);
    if (!error)
    {
        m_root = TreeDBNode(
            std::make_shared<EmbeddedDocumentDBNodeImpl>(EDDBImpl::NodeID{0}, EDDBImpl::NodeID{1}, "/"));
    }
}

void EmbeddedDocumentDBImpl::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_storageEngine.openMasterFile(path, error);
    if (!error)
    {
        m_root = TreeDBNode(
            std::make_shared<EmbeddedDocumentDBNodeImpl>(EDDBImpl::NodeID{0}, EDDBImpl::NodeID{1}, "/"));
    }
}

void EmbeddedDocumentDBImpl::close()
{
    m_storageEngine.close();
}

TreeDBNode& EmbeddedDocumentDBImpl::root()
{
    return m_root;
}

Value EmbeddedDocumentDBImpl::value(TreeDBNode& node, Ishiko::Error& error)
{
    EmbeddedDocumentDBNodeImpl& nodeImpl = static_cast<EmbeddedDocumentDBNodeImpl&>(*node.impl());
    return nodeImpl.value();
}

Value EmbeddedDocumentDBImpl::value(TreeDBNode& node, const DataType& type, Ishiko::Error& error)
{
    Value result;
    EmbeddedDocumentDBNodeImpl& nodeImpl = static_cast<EmbeddedDocumentDBNodeImpl&>(*node.impl());
    if (nodeImpl.value().type() == type)
    {
        result = nodeImpl.value();
    }
    return result;
}

Value EmbeddedDocumentDBImpl::childValue(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    Value result;
    TreeDBNode childNode = child(parent, name, error);
    if (!error)
    {
        result = value(childNode, error);
    }
    return result;
}

Value EmbeddedDocumentDBImpl::childValue(TreeDBNode& parent, const std::string& name, const DataType& type,
    Ishiko::Error& error)
{
    Value result;
    TreeDBNode childNode = child(parent, name, error);
    if (!error)
    {
        result = value(childNode, type, error);
    }
    return result;
}

TreeDBNode EmbeddedDocumentDBImpl::parent(TreeDBNode& node, Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

std::vector<TreeDBNode> EmbeddedDocumentDBImpl::childNodes(TreeDBNode& parent, Ishiko::Error& error)
{
    std::vector<TreeDBNode> result;

    EmbeddedDocumentDBNodeImpl& parentNodeImpl = static_cast<EmbeddedDocumentDBNodeImpl&>(*parent.impl());
    std::shared_ptr<EDDBImpl::SiblingNodesRecordGroup> siblingNodesRecordGroup;
    bool found = m_storageEngine.findSiblingNodesRecordGroup(parentNodeImpl.nodeID(), siblingNodesRecordGroup,
        error);
    if (!error && found)
    {
        // TODO: use iterator, also need to check the impact of copying these things around
        for (size_t i = 0; i < siblingNodesRecordGroup->size(); ++i)
        {
            // TODO: this looks pretty horrible conversion wise
            result.push_back(TreeDBNode(std::make_shared<EmbeddedDocumentDBNodeImpl>(siblingNodesRecordGroup->parentNodeID(), (*siblingNodesRecordGroup)[i])));
        }
    }

    return result;
}

TreeDBNode EmbeddedDocumentDBImpl::child(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    TreeDBNode result;

    EmbeddedDocumentDBNodeImpl& parentNodeImpl = static_cast<EmbeddedDocumentDBNodeImpl&>(*parent.impl());
    std::shared_ptr<EDDBImpl::SiblingNodesRecordGroup> siblingNodesRecordGroup;
    bool found = m_storageEngine.findSiblingNodesRecordGroup(parentNodeImpl.nodeID(), siblingNodesRecordGroup,
        error);
    if (!error && found)
    {
        EDDBImpl::SiblingNodeRecordGroup node;
        found = siblingNodesRecordGroup->find(name, node);
        if (found)
        {
            // TODO : this doesn't work because we take a copy of the node so modifications will casuse
            // inconsistencies
            result = TreeDBNode(std::make_shared<EmbeddedDocumentDBNodeImpl>(siblingNodesRecordGroup->parentNodeID(), node));
        }
    }

    return result;
}

TreeDBNode EmbeddedDocumentDBImpl::previousSibling(TreeDBNode& node, Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

TreeDBNode EmbeddedDocumentDBImpl::previousSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

TreeDBNode EmbeddedDocumentDBImpl::nextSibling(TreeDBNode& node, Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

TreeDBNode EmbeddedDocumentDBImpl::nextSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

void EmbeddedDocumentDBImpl::traverse(TreeDBNode& node, ETreeTraversalOrder order,
    void (*callback)(TreeDB& db, TreeDBNode& node), void* callbackData)
{
    // TODO
}

TreeDBTransaction EmbeddedDocumentDBImpl::createTransaction(Ishiko::Error& error)
{
    return TreeDBTransaction(std::make_shared<EmbeddedTreeDBTransactionImpl>());
}

void EmbeddedDocumentDBImpl::commitTransaction(TreeDBTransaction& transaction, Ishiko::Error& error)
{
    EmbeddedTreeDBTransactionImpl& transactionImpl = static_cast<EmbeddedTreeDBTransactionImpl&>(*transaction.impl());
    transactionImpl.commit(m_storageEngine, error);
}

void EmbeddedDocumentDBImpl::rollbackTransaction(TreeDBTransaction& transaction)
{
    EmbeddedTreeDBTransactionImpl& transactionImpl = static_cast<EmbeddedTreeDBTransactionImpl&>(*transaction.impl());
    transactionImpl.rollback();
}

void EmbeddedDocumentDBImpl::setValue(TreeDBNode& node, const Value& value, Ishiko::Error& error)
{
    // TODO : this can't be working, it re-adds the node, surely that creates duplicate nodes
    EmbeddedDocumentDBNodeImpl& nodeImpl = static_cast<EmbeddedDocumentDBNodeImpl&>(*node.impl());
    EDDBImpl::SiblingNodesRecordGroup siblings(nodeImpl.parentNodeID(),
        EDDBImpl::SiblingNodeRecordGroup(nodeImpl.name(), value, nodeImpl.nodeID()));
    m_storageEngine.addSiblingNodesRecordGroup(siblings, error);
}

TreeDBNode EmbeddedDocumentDBImpl::insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
    Ishiko::Error& error)
{   
    Value value;
    return insertChildNode(parent, index, name, value, error);
}

TreeDBNode EmbeddedDocumentDBImpl::insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
    const Value& value, Ishiko::Error& error)
{
    // TODO : doesn't work if there are already child nodes on this node
    EmbeddedDocumentDBNodeImpl& parentNodeImpl = static_cast<EmbeddedDocumentDBNodeImpl&>(*parent.impl());
    TreeDBNode result =
        TreeDBNode(std::make_shared<EmbeddedDocumentDBNodeImpl>(parentNodeImpl.nodeID(), EDDBImpl::NodeID{0}, name));
    EmbeddedDocumentDBNodeImpl& nodeImpl = static_cast<EmbeddedDocumentDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;
    EDDBImpl::SiblingNodesRecordGroup siblings(nodeImpl.parentNodeID(),
        EDDBImpl::SiblingNodeRecordGroup(nodeImpl.name(), nodeImpl.value(), nodeImpl.nodeID()));
    m_storageEngine.addSiblingNodesRecordGroup(siblings, error);
    return result;
}

TreeDBNode EmbeddedDocumentDBImpl::insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild,
    const std::string& name, Ishiko::Error& error)
{
    Value value;
    return insertChildNodeBefore(parent, nextChild, name, value, error);
}

TreeDBNode EmbeddedDocumentDBImpl::insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild,
    const std::string& name, const Value& value, Ishiko::Error& error)
{
    // TODO : does this work?
    // TODO : doesn't work if there are already child nodes on this node
    EmbeddedDocumentDBNodeImpl& parentNodeImpl = static_cast<EmbeddedDocumentDBNodeImpl&>(*parent.impl());
    TreeDBNode result =
        TreeDBNode(std::make_shared<EmbeddedDocumentDBNodeImpl>(parentNodeImpl.nodeID(), EDDBImpl::NodeID{0}, name));
    EmbeddedDocumentDBNodeImpl& nodeImpl = static_cast<EmbeddedDocumentDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;
    EDDBImpl::SiblingNodesRecordGroup siblings(nodeImpl.parentNodeID(),
        EDDBImpl::SiblingNodeRecordGroup(nodeImpl.name(), nodeImpl.value(), nodeImpl.nodeID()));
    m_storageEngine.addSiblingNodesRecordGroup(siblings, error);
    return result;
}

TreeDBNode EmbeddedDocumentDBImpl::insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild,
    const std::string& name, Ishiko::Error& error)
{
    Value value;
    return insertChildNodeAfter(parent, previousChild, name, value, error);
}

TreeDBNode EmbeddedDocumentDBImpl::insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild,
    const std::string& name, const Value& value, Ishiko::Error& error)
{
    // TODO : does this work?
    // TODO : doesn't work if there are already child nodes on this node
    EmbeddedDocumentDBNodeImpl& parentNodeImpl = static_cast<EmbeddedDocumentDBNodeImpl&>(*parent.impl());
    TreeDBNode result =
        TreeDBNode(std::make_shared<EmbeddedDocumentDBNodeImpl>(parentNodeImpl.nodeID(), EDDBImpl::NodeID{0}, name));
    EmbeddedDocumentDBNodeImpl& nodeImpl = static_cast<EmbeddedDocumentDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;
    EDDBImpl::SiblingNodesRecordGroup siblings(nodeImpl.parentNodeID(),
        EDDBImpl::SiblingNodeRecordGroup(nodeImpl.name(), nodeImpl.value(), nodeImpl.nodeID()));
    m_storageEngine.addSiblingNodesRecordGroup(siblings, error);
    return result;
}

TreeDBNode EmbeddedDocumentDBImpl::appendChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    Value value;
    return appendChildNode(parent, name, value, error);
}

TreeDBNode EmbeddedDocumentDBImpl::appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent,
    const std::string& name, Ishiko::Error& error)
{
    Value value;
    return appendChildNode(transaction, parent, name, value, error);
}

TreeDBNode EmbeddedDocumentDBImpl::appendChildNode(TreeDBNode& parent, const std::string& name, const Value& value,
    Ishiko::Error& error)
{
    TreeDBNode result;

    EmbeddedDocumentDBNodeImpl& parentNodeImpl = static_cast<EmbeddedDocumentDBNodeImpl&>(*parent.impl());
    result = TreeDBNode(
        std::make_shared<EmbeddedDocumentDBNodeImpl>(parentNodeImpl.nodeID(), EDDBImpl::NodeID{0}, name));
    EmbeddedDocumentDBNodeImpl& nodeImpl = static_cast<EmbeddedDocumentDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;

    std::shared_ptr<EDDBImpl::SiblingNodesRecordGroup> existingSiblingNodesRecordGroup;
    bool found = m_storageEngine.findSiblingNodesRecordGroup(parentNodeImpl.nodeID(),
        existingSiblingNodesRecordGroup, error);
    if (!error)
    {
        if (found)
        {
            // TODO
            existingSiblingNodesRecordGroup->push_back(
                EDDBImpl::SiblingNodeRecordGroup(nodeImpl.name(), nodeImpl.value(), nodeImpl.nodeID()));
            m_storageEngine.updateSiblingNodesRecordGroup(*existingSiblingNodesRecordGroup, error);
        }
        else
        {
            EDDBImpl::SiblingNodesRecordGroup siblings(parentNodeImpl.nodeID(),
                EDDBImpl::SiblingNodeRecordGroup(nodeImpl.name(), nodeImpl.value(), nodeImpl.nodeID()));
            m_storageEngine.addSiblingNodesRecordGroup(siblings, error);
        }
    }

    return result;
}

TreeDBNode EmbeddedDocumentDBImpl::appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent,
    const std::string& name, const Value& value, Ishiko::Error& error)
{
    EmbeddedTreeDBTransactionImpl& transactionImpl = static_cast<EmbeddedTreeDBTransactionImpl&>(*transaction.impl());
    return transactionImpl.appendChildNode(m_storageEngine, parent, name, value, error);
}

TreeDBNode EmbeddedDocumentDBImpl::setChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    Value value;
    return setChildNode(parent, name, value, error);
}

TreeDBNode EmbeddedDocumentDBImpl::setChildNode(TreeDBNode& parent, const std::string& name, const Value& value,
    Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

size_t EmbeddedDocumentDBImpl::removeChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    // TODO
    return 0;
}

size_t EmbeddedDocumentDBImpl::removeAllChildNodes(TreeDBNode& parent, Ishiko::Error& error)
{
    // TODO
    return 0;
}

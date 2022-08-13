/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "EmbeddedDocumentDBNodeImpl.hpp"
#include "EmbeddedDocumentDBImpl.hpp"

using namespace DiplodocusDB;

EmbeddedDocumentDBNodeImpl::EmbeddedDocumentDBNodeImpl()
    : m_name("/")
{
}

EmbeddedDocumentDBNodeImpl::EmbeddedDocumentDBNodeImpl(const EDDBImpl::NodeID& parentNodeID,
    const EDDBImpl::NodeID& nodeID, const std::string& name)
    : m_name(name), m_parentNodeID(parentNodeID), m_nodeID(nodeID)
{
}

EmbeddedDocumentDBNodeImpl::EmbeddedDocumentDBNodeImpl(const EDDBImpl::NodeID& parentNodeID,
    const EDDBImpl::SiblingNodeRecordGroup& node)
    : m_name(node.name()), m_value(node.value()), m_parentNodeID(parentNodeID), m_nodeID(node.nodeID())
{
}

const std::string& EmbeddedDocumentDBNodeImpl::name() const
{
    return m_name;
}

const Value& EmbeddedDocumentDBNodeImpl::value() const
{
    return m_value;
}

Value& EmbeddedDocumentDBNodeImpl::value()
{
    return m_value;
}

bool EmbeddedDocumentDBNodeImpl::isRoot() const
{
    return (m_name == "/");
}

const EDDBImpl::NodeID& EmbeddedDocumentDBNodeImpl::parentNodeID() const
{
    return m_parentNodeID;
}

const EDDBImpl::NodeID& EmbeddedDocumentDBNodeImpl::nodeID() const
{
    return m_nodeID;
}

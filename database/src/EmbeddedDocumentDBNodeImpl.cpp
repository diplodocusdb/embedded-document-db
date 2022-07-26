/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "EmbeddedDocumentDBNodeImpl.hpp"
#include "EmbeddedDocumentDBImpl.hpp"

namespace DiplodocusDB
{

EmbeddedTreeDBNodeImpl::EmbeddedTreeDBNodeImpl()
    : m_name("/")
{
}

EmbeddedTreeDBNodeImpl::EmbeddedTreeDBNodeImpl(const NodeID& parentNodeID, const NodeID& nodeID,
    const std::string& name)
    : m_name(name), m_parentNodeID(parentNodeID), m_nodeID(nodeID)
{
}

const std::string& EmbeddedTreeDBNodeImpl::name() const
{
    return m_name;
}

const Value& EmbeddedTreeDBNodeImpl::value() const
{
    return m_value;
}

Value& EmbeddedTreeDBNodeImpl::value()
{
    return m_value;
}

bool EmbeddedTreeDBNodeImpl::isRoot() const
{
    return (name() == "/");
}

const NodeID& EmbeddedTreeDBNodeImpl::parentNodeID() const
{
    return m_parentNodeID;
}

const NodeID& EmbeddedTreeDBNodeImpl::nodeID() const
{
    return m_nodeID;
}

}

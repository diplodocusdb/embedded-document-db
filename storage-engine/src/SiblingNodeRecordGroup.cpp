/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "SiblingNodeRecordGroup.hpp"

using namespace DiplodocusDB;

SiblingNodeRecordGroup::SiblingNodeRecordGroup()
{
}

SiblingNodeRecordGroup::SiblingNodeRecordGroup(std::string name, NodeID nodeID)
    : m_name(std::move(name)), m_nodeID(std::move(nodeID))
{
}

SiblingNodeRecordGroup::SiblingNodeRecordGroup(std::string name, Value value, NodeID nodeID)
    : m_name(std::move(name)), m_value(std::move(value)), m_nodeID(std::move(nodeID))
{
}

const std::string& SiblingNodeRecordGroup::name() const
{
    return m_name;
}

const Value& SiblingNodeRecordGroup::value() const
{
    return m_value;
}

Value& SiblingNodeRecordGroup::value()
{
    return m_value;
}

bool SiblingNodeRecordGroup::isRoot() const
{
    return (m_name == "/");
}

const NodeID& SiblingNodeRecordGroup::nodeID() const
{
    return m_nodeID;
}

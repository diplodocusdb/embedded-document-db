/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "NodeID.hpp"

using namespace DiplodocusDB::EDDBImpl;

NodeID::NodeID()
    : m_value(0)
{
}

NodeID::NodeID(size_t value)
    : m_value(value)
{
}

bool NodeID::isNull() const
{
    return (m_value == 0);
}

bool NodeID::operator==(const NodeID& other) const
{
    return (m_value == other.m_value);
}

bool NodeID::operator!=(const NodeID& other) const
{
    return (m_value != other.m_value);
}

bool NodeID::operator<(const NodeID& other) const
{
    return (m_value < other.m_value);
}

bool NodeID::operator>(const NodeID& other) const
{
    return (m_value > other.m_value);
}

void NodeID::read(PhysicalStorage::PageRepositoryReader& reader, Ishiko::Error& error)
{
    m_value = reader.readLEB128(error);
}

void NodeID::write(PhysicalStorage::PageRepositoryWriter& writer, Ishiko::Error& error) const
{
    writer.writeLEB128(m_value, error);
}

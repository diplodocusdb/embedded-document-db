/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "SiblingNodesRecordGroup.hpp"
#include "Record.hpp"

using namespace DiplodocusDB::EDDBImpl;

SiblingNodesRecordGroup::SiblingNodesRecordGroup(const NodeID& parentNodeID)
    : m_parentNodeID(parentNodeID)
{
}

SiblingNodesRecordGroup::SiblingNodesRecordGroup(const NodeID& parentNodeID, const SiblingNodeRecordGroup& node)
    : m_parentNodeID(parentNodeID)
{
    m_siblings.emplace_back(node);
}

const NodeID& SiblingNodesRecordGroup::parentNodeID() const
{
    return m_parentNodeID;
}

const SiblingNodeRecordGroup& SiblingNodesRecordGroup::operator[](size_t pos) const
{
    return m_siblings[pos];
}

size_t SiblingNodesRecordGroup::size() const noexcept
{
    return m_siblings.size();
}

void SiblingNodesRecordGroup::push_back(const SiblingNodeRecordGroup& value)
{
    m_siblings.push_back(value);
}

bool SiblingNodesRecordGroup::find(const std::string& name, SiblingNodeRecordGroup& node)
{
    bool result = false;
    for (const SiblingNodeRecordGroup& n : m_siblings)
    {
        if (n.name() == name)
        {
            node = n;
            result = true;
            break;
        }
    }
    return result;
}

void SiblingNodesRecordGroup::readWithoutType(PhysicalStorage::PageRepositoryReader& reader, Ishiko::Error& error)
{
    Record nextRecord(Record::ERecordType::eInvalid);
    while (true)
    {
        nextRecord.read(reader, error);
        if (error)
        {
            return;
        }
        if (nextRecord.type() == Record::ERecordType::eSiblingNodesEnd)
        {
            break;
        }
        else
        {
            if (nextRecord.type() == Record::ERecordType::eParentNodeID)
            {
                m_parentNodeID = nextRecord.asNodeID();
            }
            else if (nextRecord.type() == Record::ERecordType::eNodeName)
            {
                m_siblings.emplace_back(nextRecord.asString(), Value(), NodeID(0));
            }
            else if (nextRecord.type() == Record::ERecordType::eInlineValue)
            {
                m_siblings.back().value() = nextRecord.asValue();
            }
        }
    }
}

void SiblingNodesRecordGroup::write(PhysicalStorage::PageRepositoryWriter& writer, Ishiko::Error& error) const
{
    Record nodeStartRecord(Record::ERecordType::eSiblingNodesStart);
    nodeStartRecord.write(writer, error);
    if (error)
    {
        return;
    }

    if (!m_parentNodeID.isNull())
    {
        Record parentRecord(Record::ERecordType::eParentNodeID, m_parentNodeID);
        parentRecord.write(writer, error);
        if (error)
        {
            return;
        }
    }

    for (const SiblingNodeRecordGroup& node : m_siblings)
    {
        writeNode(writer, node, error);
        if (error)
        {
            return;
        }
    }

    Record nodeEndRecord(Record::ERecordType::eSiblingNodesEnd);
    nodeEndRecord.write(writer, error);
}

void SiblingNodesRecordGroup::writeNode(PhysicalStorage::PageRepositoryWriter& writer,
    const SiblingNodeRecordGroup& node, Ishiko::Error& error)
{
    if (node.isRoot())
    {
        Record nameRecord(node.name());
        nameRecord.write(writer, error);
        if (error)
        {
            return;
        }
    }
    else
    {
        Record nameRecord(node.name());
        nameRecord.write(writer, error);
        if (error)
        {
            return;
        }

        if (!node.nodeID().isNull())
        {
            Record idRecord(Record::ERecordType::eNodeID, node.nodeID());
            idRecord.write(writer, error);
            if (error)
            {
                return;
            }
        }
    }

    if (node.value().type() != DataType(PrimitiveDataType::null))
    {
        Record record(Record::ERecordType::eInlineValue, node.value());
        record.write(writer, error);
        if (error)
        {
            return;
        }
    }
}

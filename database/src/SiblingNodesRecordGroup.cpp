/*
    Copyright (c) 2019-2022 Xavier Leclercq

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

#include "SiblingNodesRecordGroup.h"
#include <DiplodocusDB/EmbeddedDocumentDB/StorageEngine.hpp>

namespace DiplodocusDB
{

SiblingNodesRecordGroup::SiblingNodesRecordGroup(const NodeID& parentNodeID)
    : m_parentNodeID(parentNodeID)
{
}

SiblingNodesRecordGroup::SiblingNodesRecordGroup(const EmbeddedDocumentDBNodeImpl& node)
{
    m_parentNodeID = node.parentNodeID();
    m_siblings.emplace_back(node);
}

const NodeID& SiblingNodesRecordGroup::parentNodeID() const
{
    return m_parentNodeID;
}

const EmbeddedDocumentDBNodeImpl& SiblingNodesRecordGroup::operator[](size_t pos) const
{
    return m_siblings[pos];
}

size_t SiblingNodesRecordGroup::size() const noexcept
{
    return m_siblings.size();
}

void SiblingNodesRecordGroup::push_back(const EmbeddedDocumentDBNodeImpl& value)
{
    if (m_siblings.size() == 0)
    {
        m_parentNodeID = value.parentNodeID();
    }
    m_siblings.push_back(value);
}

bool SiblingNodesRecordGroup::find(const std::string& name, EmbeddedDocumentDBNodeImpl& node)
{
    bool result = false;
    for (EmbeddedDocumentDBNodeImpl n : m_siblings)
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

void SiblingNodesRecordGroup::readWithoutType(PageRepositoryReader& reader, Ishiko::Error& error)
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
                m_siblings.emplace_back(m_parentNodeID, NodeID(0), nextRecord.asString());
            }
            else if (nextRecord.type() == Record::ERecordType::eInlineValue)
            {
                m_siblings.back().value() = nextRecord.asValue();
            }
        }
    }
}

void SiblingNodesRecordGroup::write(PageRepositoryWriter& writer, Ishiko::Error& error) const
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

    for (const EmbeddedDocumentDBNodeImpl& node : m_siblings)
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

void SiblingNodesRecordGroup::writeNode(PageRepositoryWriter& writer, const EmbeddedDocumentDBNodeImpl& node,
    Ishiko::Error& error)
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

}

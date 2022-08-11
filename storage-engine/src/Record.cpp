/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "Record.hpp"
#include "EmbeddedDocumentDBStorageEngineErrorCategory.hpp"
#include "ValueCodec.hpp"

using namespace DiplodocusDB;

Record::Record(ERecordType type)
    : m_type(type)
{
}

Record::Record(ERecordType type, const NodeID& data)
    : m_type(type), m_data(data)
{
}

Record::Record(ERecordType type, const Value& data)
    : m_type(type), m_data(data)
{
}

Record::Record(const MasterFileMetadata& data)
    : m_type(ERecordType::eMasterFileMetadata), m_data(data)
{
}

Record::Record(const std::string& data)
    : m_type(ERecordType::eNodeName), m_data(data)
{
}

Record::ERecordType Record::type() const
{
    return m_type;
}

const NodeID& Record::asNodeID() const
{
    return boost::get<NodeID>(m_data);
}

const std::string& Record::asString() const
{
    return boost::get<std::string>(m_data);
}

const Value& Record::asValue() const
{
    return boost::get<Value>(m_data);
}

void Record::read(PageRepositoryReader& reader, Ishiko::Error& error)
{
    uint8_t type;
    reader.read((char*)&type, 1, error);
    if (error)
    {
        return;
    }

    m_type = (ERecordType)type;

    switch (m_type)
    {
    case ERecordType::eInvalid:
        // TODO : add details
        error.fail(EmbeddedDocumentDBStorageEngineErrorCategory::Get(), -1, "Invalid record type", __FILE__, __LINE__);
        break;

    case ERecordType::eMasterFileMetadata:
        m_data = MasterFileMetadata();
        boost::get<MasterFileMetadata>(m_data).read(reader, error);
        break;

    case ERecordType::eDataStart:
    case ERecordType::eDataEnd:
    case ERecordType::eSiblingNodesStart:
    case ERecordType::eSiblingNodesEnd:
        break;

    case ERecordType::eParentNodeID:
    case ERecordType::eNodeID:
    case ERecordType::ePersistentNodeID:
        m_data = NodeID();
        boost::get<NodeID>(m_data).read(reader, error);
        break;

    case ERecordType::eNodeName:
        m_data = ValueCodec::ReadString(reader, error);
        break;

    case ERecordType::eInlineValue:
        m_data = ValueCodec::ReadInlineValue(reader, error);
        break;

    default:
        // TODO : add details
        error.fail(EmbeddedDocumentDBStorageEngineErrorCategory::Get(), -1, "Invalid record type", __FILE__, __LINE__);
        break;
    }
}

void Record::write(PageRepositoryWriter& writer, Ishiko::Error& error) const
{
    uint8_t type = (uint8_t)m_type;
    writer.write((char*)&type, 1, error);
    switch (m_type)
    {
    case ERecordType::eMasterFileMetadata:
        boost::get<MasterFileMetadata>(m_data).write(writer, error);
        break;

    case ERecordType::eParentNodeID:
    case ERecordType::eNodeID:
    case ERecordType::ePersistentNodeID:
        boost::get<NodeID>(m_data).write(writer, error);
        break;

    case ERecordType::eNodeName:
        ValueCodec::WriteString(writer, boost::get<std::string>(m_data), error);
        break;

    case ERecordType::eInlineValue:
        ValueCodec::WriteInlineValue(writer, boost::get<Value>(m_data), error);
        break;
    }
}

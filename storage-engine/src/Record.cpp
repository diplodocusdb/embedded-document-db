/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "Record.hpp"
#include "StorageEngineErrorCategory.hpp"

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
        error.fail(-1, StorageEngineErrorCategory::Get(), "Invalid record type", __FILE__, __LINE__);
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
        m_data = readString(reader, error);
        break;

    case ERecordType::eInlineValue:
        m_data = readInlineValue(reader, error);
        break;

    default:
        // TODO : add details
        error.fail(-1, StorageEngineErrorCategory::Get(), "Invalid record type", __FILE__, __LINE__);
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
        writeString(writer, boost::get<std::string>(m_data), error);
        break;

    case ERecordType::eInlineValue:
        writeInlineValue(writer, boost::get<Value>(m_data), error);
        break;
    }
}

Value Record::readInlineValue(PageRepositoryReader& reader, Ishiko::Error& error)
{
    Value result;
    DataType type = readDataType(reader, error);
    if (!error)
    {
        switch (type.primitiveType())
        {
        case PrimitiveDataType::binary:
            result.setBinary(readString(reader, error));
            break;

        case PrimitiveDataType::boolean:
            result.setBoolean(readBoolean(reader, error));
            break;

        case PrimitiveDataType::unicodeString:
            result.setUTF8String(readString(reader, error));
            break;
        }
    }
    return result;
}

void Record::writeInlineValue(PageRepositoryWriter& writer, const Value& value, Ishiko::Error& error)
{
    writeDataType(writer, value.type(), error);
    if (!error)
    {
        switch (value.type().primitiveType())
        {
        case PrimitiveDataType::binary:
            writeString(writer, value.asBinary(), error);
            break;

        case PrimitiveDataType::boolean:
            writeBoolean(writer, value.asBoolean(), error);
            break;

        case PrimitiveDataType::unicodeString:
            writeString(writer, value.asUTF8String(), error);
            break;
        }
    }
}

DataType Record::readDataType(PageRepositoryReader& reader, Ishiko::Error& error)
{
    DataType result(PrimitiveDataType::null);
    char buffer;
    reader.read(&buffer, 1, error);
    if (!error)
    {
        result = DataType((PrimitiveDataType)(buffer & 0x3F), (DataTypeModifier)(buffer >> 6));
    }
    return result;
}

void Record::writeDataType(PageRepositoryWriter& writer, const DataType& dataType, Ishiko::Error& error)
{
    uint8_t primitiveType = (uint8_t)dataType.primitiveType();
    uint8_t typeModifier = (uint8_t)dataType.modifier();
    uint8_t type = ((primitiveType & 0x3F) | (typeModifier << 6));
    writer.write((char*)&type, 1, error);
}

bool Record::readBoolean(PageRepositoryReader& reader, Ishiko::Error& error)
{
    char data;
    reader.read(&data, 1, error);
    return data;
}

void Record::writeBoolean(PageRepositoryWriter& writer, bool data, Ishiko::Error& error)
{
    if (data)
    {
        writer.write("\x1", 1, error);
    }
    else
    {
        writer.write("\x0", 1, error);
    }
}

std::string Record::readString(PageRepositoryReader& reader, Ishiko::Error& error)
{
    std::string name;
    size_t size = reader.readLEB128(error);
    if (!error)
    {
        name.resize(size);
        reader.read(&name[0], size, error);
    }
    return name;
}

void Record::writeString(PageRepositoryWriter& writer, const std::string& data, Ishiko::Error& error)
{
    writer.writeLEB128(data.size(), error);
    if (!error)
    {
        writer.write(data.c_str(), data.size(), error);
    }
}

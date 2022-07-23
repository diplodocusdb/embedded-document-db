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

#include "Record.h"
#include "TreeDBErrorCategory.hpp"
#include "DiplodocusDB/PhysicalStorage/PageRepository/Page.h"

namespace DiplodocusDB
{

Record::Record(ERecordType type)
    : m_type(type)
{
}

Record::Record(ERecordType type, const NodeID& data)
    : m_type(type), m_data(data)
{
}

Record::Record(ERecordType type, const TreeDBValue& data)
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

const TreeDBValue& Record::asValue() const
{
    return boost::get<TreeDBValue>(m_data);
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
        error.fail(-1, TreeDBErrorCategory::Get(), "Invalid record type", __FILE__, __LINE__);
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
        error.fail(-1, TreeDBErrorCategory::Get(), "Invalid record type", __FILE__, __LINE__);
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
        writeInlineValue(writer, boost::get<TreeDBValue>(m_data), error);
        break;
    }
}

TreeDBValue Record::readInlineValue(PageRepositoryReader& reader, Ishiko::Error& error)
{
    TreeDBValue result;
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

void Record::writeInlineValue(PageRepositoryWriter& writer, const TreeDBValue& value, Ishiko::Error& error)
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

}

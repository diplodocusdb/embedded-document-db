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
#include "Utilities.h"
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
        error.fail(-1, "Invalid record type", __FILE__, __LINE__);
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
        m_data = readNodeName(reader, error);
        break;

    case ERecordType::eInlineValue:
        m_data = readInlineValue(reader, error);
        break;

    default:
        // TODO : add details
        error.fail(-1, "Invalid record type", __FILE__, __LINE__);
        break;
    }
}

void Record::write(PageRepositoryWriter& writer, Ishiko::Error& error) const
{
    uint8_t type = (uint8_t)m_type;
    writer.write((char*)&type, 1, error);
    switch (type)
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
        writeNodeName(writer, boost::get<std::string>(m_data), error);
        break;

    case ERecordType::eInlineValue:
        writeInlineValue(writer, boost::get<TreeDBValue>(m_data), error);
        break;
    }
}

std::string Record::readNodeName(PageRepositoryReader& reader, Ishiko::Error& error)
{
    std::string name;
    // TODO: this needs to decode LEB128
    uint8_t size;
    reader.read((char*)&size, 1, error);
    if (!error)
    {
        name.resize(size);
        reader.read(&name[0], size, error);
    }
    return name;
}

void Record::writeNodeName(PageRepositoryWriter& writer, const std::string& name, Ishiko::Error& error)
{
    char buffer[20];
    size_t n = Utilities::encodeLEB128(name.size(), buffer);
    writer.write(buffer, n, error);
    if (!error)
    {
        writer.write(name.c_str(), name.size(), error);
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
        case EPrimitiveDataType::eBoolean:
            char data;
            reader.read(&data, 1, error);
            result.setBoolean(data);
            break;

        case EPrimitiveDataType::eUTF8String:
            {
                // TODO: this needs to decode LEB128
                uint8_t size;
                reader.read((char*)&size, 1, error);
                if (!error)
                {
                    std::string data;
                    data.resize(size);
                    reader.read(&data[0], size, error);
                    result.setUTF8String(data);
                }
            }
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
        case EPrimitiveDataType::eBinary:
            {
                char buffer[20];
                size_t n = Utilities::encodeLEB128(value.asBinary().size(), buffer);
                writer.write(buffer, n, error);
                if (!error)
                {
                    writer.write(value.asUTF8String().c_str(), value.asBinary().size(), error);
                }
            }
            break;

        case EPrimitiveDataType::eBoolean:
            if (value.asBoolean())
            {
                writer.write("\x1", 1, error);
            }
            else
            {
                writer.write("\x0", 1, error);
            }
            break;

        case EPrimitiveDataType::eUTF8String:
            {
                char buffer[20];
                size_t n = Utilities::encodeLEB128(value.asUTF8String().size(), buffer);
                writer.write(buffer, n, error);
                if (!error)
                {
                    writer.write(value.asUTF8String().c_str(), value.asUTF8String().size(), error);
                }
            }
            break;
        }
    }
}

DataType Record::readDataType(PageRepositoryReader& reader, Ishiko::Error& error)
{
    DataType result(EPrimitiveDataType::eNULL);
    char buffer;
    reader.read(&buffer, 1, error);
    if (!error)
    {
        result = DataType((EPrimitiveDataType)(buffer & 0x3F), (EDataTypeModifier)(buffer >> 6));
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

}

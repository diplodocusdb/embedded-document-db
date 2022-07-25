/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "ValueCodec.hpp"

using namespace DiplodocusDB;

Value ValueCodec::ReadInlineValue(PageRepositoryReader& reader, Ishiko::Error& error)
{
    Value result;
    DataType type = ReadDataType(reader, error);
    if (!error)
    {
        switch (type.primitiveType())
        {
        case PrimitiveDataType::binary:
            result.setBinary(ReadString(reader, error));
            break;

        case PrimitiveDataType::boolean:
            result.setBoolean(ReadBoolean(reader, error));
            break;

        case PrimitiveDataType::unicodeString:
            result.setUTF8String(ReadString(reader, error));
            break;
        }
    }
    return result;
}

void ValueCodec::WriteInlineValue(PageRepositoryWriter& writer, const Value& value, Ishiko::Error& error)
{
    WriteDataType(writer, value.type(), error);
    if (!error)
    {
        switch (value.type().primitiveType())
        {
        case PrimitiveDataType::binary:
            WriteString(writer, value.asBinary(), error);
            break;

        case PrimitiveDataType::boolean:
            WriteBoolean(writer, value.asBoolean(), error);
            break;

        case PrimitiveDataType::unicodeString:
            WriteString(writer, value.asUTF8String(), error);
            break;
        }
    }
}

DataType ValueCodec::ReadDataType(PageRepositoryReader& reader, Ishiko::Error& error)
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

void ValueCodec::WriteDataType(PageRepositoryWriter& writer, const DataType& dataType, Ishiko::Error& error)
{
    uint8_t primitiveType = (uint8_t)dataType.primitiveType();
    uint8_t typeModifier = (uint8_t)dataType.modifier();
    uint8_t type = ((primitiveType & 0x3F) | (typeModifier << 6));
    writer.write((char*)&type, 1, error);
}

bool ValueCodec::ReadBoolean(PageRepositoryReader& reader, Ishiko::Error& error)
{
    char data;
    reader.read(&data, 1, error);
    return data;
}

void ValueCodec::WriteBoolean(PageRepositoryWriter& writer, bool data, Ishiko::Error& error)
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

std::string ValueCodec::ReadString(PageRepositoryReader& reader, Ishiko::Error& error)
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

void ValueCodec::WriteString(PageRepositoryWriter& writer, const std::string& data, Ishiko::Error& error)
{
    writer.writeLEB128(data.size(), error);
    if (!error)
    {
        writer.write(data.c_str(), data.size(), error);
    }
}

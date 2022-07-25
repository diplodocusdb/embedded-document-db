/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "ValueCodec.hpp"

using namespace DiplodocusDB;

Value ValueCodec::readInlineValue(PageRepositoryReader& reader, Ishiko::Error& error)
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

void ValueCodec::writeInlineValue(PageRepositoryWriter& writer, const Value& value, Ishiko::Error& error)
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

DataType ValueCodec::readDataType(PageRepositoryReader& reader, Ishiko::Error& error)
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

void ValueCodec::writeDataType(PageRepositoryWriter& writer, const DataType& dataType, Ishiko::Error& error)
{
    uint8_t primitiveType = (uint8_t)dataType.primitiveType();
    uint8_t typeModifier = (uint8_t)dataType.modifier();
    uint8_t type = ((primitiveType & 0x3F) | (typeModifier << 6));
    writer.write((char*)&type, 1, error);
}

bool ValueCodec::readBoolean(PageRepositoryReader& reader, Ishiko::Error& error)
{
    char data;
    reader.read(&data, 1, error);
    return data;
}

void ValueCodec::writeBoolean(PageRepositoryWriter& writer, bool data, Ishiko::Error& error)
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

std::string ValueCodec::readString(PageRepositoryReader& reader, Ishiko::Error& error)
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

void ValueCodec::writeString(PageRepositoryWriter& writer, const std::string& data, Ishiko::Error& error)
{
    writer.writeLEB128(data.size(), error);
    if (!error)
    {
        writer.write(data.c_str(), data.size(), error);
    }
}

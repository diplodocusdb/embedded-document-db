/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "ValueCodec.hpp"
#include <Ishiko/Memory.hpp>

using namespace DiplodocusDB;

Value ValueCodec::ReadInlineValue(PhysicalStorage::PageRepositoryReader& reader, Ishiko::Error& error)
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

void ValueCodec::WriteInlineValue(PhysicalStorage::PageRepositoryWriter& writer, const Value& value,
    Ishiko::Error& error)
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

DataType ValueCodec::ReadDataType(PhysicalStorage::PageRepositoryReader& reader, Ishiko::Error& error)
{
    DataType result(PrimitiveDataType::null);
    char buffer;
    reader.read(&buffer, 1, error);
    if (!error)
    {
        PrimitiveDataType primitiveType;
        switch (buffer & 0x3F)
        {
        case 0:
        case 1:
        case 2:
            primitiveType = (PrimitiveDataType)(buffer & 0x3F);
            break;

        case 18:
            primitiveType = PrimitiveDataType::unicodeString;

            // TODO: other values
        }
        result = DataType(primitiveType, (DataTypeModifier)(buffer >> 6));
    }
    return result;
}

void ValueCodec::WriteDataType(PhysicalStorage::PageRepositoryWriter& writer, const DataType& dataType,
    Ishiko::Error& error)
{
    Ishiko::Byte primitiveType;
    switch (dataType.primitiveType())
    {
    case PrimitiveDataType::null:
    case PrimitiveDataType::binary:
    case PrimitiveDataType::boolean:
        primitiveType = (Ishiko::Byte)dataType.primitiveType();
        break;

        // TODO
            /*
            PrimitiveDataType::int8bit
            PrimitiveDataType::int16bit
            PrimitiveDataType::int32bit
            PrimitiveDataType::int64bit
            PrimitiveDataType::intInfinite

            PrimitiveDataType::unsignedInt8bit
            PrimitiveDataType::unsignedInt16bit
            PrimitiveDataType::unsignedInt32bit
            PrimitiveDataType::unsignedInt64bit
            PrimitiveDataType::unsignedIntInfinite

            PrimitiveDataType::IEEE754Binary16
            PrimitiveDataType::IEEE754Binary32
            PrimitiveDataType::IEEE754Binary64
            PrimitiveDataType::IEEE754Binary128
            PrimitiveDataType::IEEE754Binary256
            */

    case PrimitiveDataType::unicodeString:
        primitiveType = 18;
        break;

        // TODO
                /*
            PrimitiveDataType::universalDateTime
            PrimitiveDataType::localDateTime
            PrimitiveDataType::date
            PrimitiveDataType::timeOfDay*/
    }
  
    uint8_t typeModifier = (uint8_t)dataType.modifier();
    uint8_t type = ((primitiveType & 0x3F) | (typeModifier << 6));
    writer.write((char*)&type, 1, error);
}

bool ValueCodec::ReadBoolean(PhysicalStorage::PageRepositoryReader& reader, Ishiko::Error& error)
{
    char data;
    reader.read(&data, 1, error);
    return data;
}

void ValueCodec::WriteBoolean(PhysicalStorage::PageRepositoryWriter& writer, bool data, Ishiko::Error& error)
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

std::string ValueCodec::ReadString(PhysicalStorage::PageRepositoryReader& reader, Ishiko::Error& error)
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

void ValueCodec::WriteString(PhysicalStorage::PageRepositoryWriter& writer, const std::string& data,
    Ishiko::Error& error)
{
    writer.writeLEB128(data.size(), error);
    if (!error)
    {
        writer.write(data.c_str(), data.size(), error);
    }
}

/*
    Copyright (c) 2018-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "TreeDBValue.h"

namespace DiplodocusDB
{

TreeDBValue::TreeDBValue()
    : m_type(PrimitiveDataType::null)
{
}

TreeDBValue TreeDBValue::Boolean(bool data)
{
    TreeDBValue result;
    result.setBoolean(data);
    return result;
}

TreeDBValue TreeDBValue::Int8(int8_t data)
{
    TreeDBValue result;
    result.setInt8(data);
    return result;
}

TreeDBValue TreeDBValue::Int16(int16_t data)
{
    TreeDBValue result;
    result.setInt16(data);
    return result;
}

TreeDBValue TreeDBValue::Int32(int32_t data)
{
    TreeDBValue result;
    result.setInt32(data);
    return result;
}

TreeDBValue TreeDBValue::Int64(int64_t data)
{
    TreeDBValue result;
    result.setInt64(data);
    return result;
}

TreeDBValue TreeDBValue::UTF8String(const std::string& data)
{
    TreeDBValue result;
    result.setUTF8String(data);
    return result;
}

TreeDBValue TreeDBValue::Binary(const std::string& data)
{
    TreeDBValue result;
    result.setBinary(data);
    return result;
}

const DataType& TreeDBValue::type() const
{
    return m_type;
}

bool TreeDBValue::asBoolean() const
{
    return boost::get<bool>(m_data);
}

int8_t TreeDBValue::asInt8() const
{
    return boost::get<int8_t>(m_data);
}

int16_t TreeDBValue::asInt16() const
{
    return boost::get<int16_t>(m_data);
}

int32_t TreeDBValue::asInt32() const
{
    return boost::get<int32_t>(m_data);
}

int64_t TreeDBValue::asInt64() const
{
    return boost::get<int64_t>(m_data);
}

const std::string& TreeDBValue::asUTF8String() const
{
    return boost::get<std::string>(m_data);
}

const std::string& TreeDBValue::asBinary() const
{
    return boost::get<std::string>(m_data);
}

bool TreeDBValue::operator ==(const TreeDBValue& other) const
{
    return ((m_type == other.m_type) && (m_data == other.m_data));
}

bool TreeDBValue::operator !=(const TreeDBValue& other) const
{
    return !(*this == other);
}

void TreeDBValue::setBoolean(bool data)
{
    m_type = PrimitiveDataType::boolean;
    m_data = data;
}

void TreeDBValue::setInt8(int8_t data)
{
    m_type = PrimitiveDataType::int8bit;
    m_data = data;
}

void TreeDBValue::setInt16(int16_t data)
{
    m_type = PrimitiveDataType::int16bit;
    m_data = data;
}

void TreeDBValue::setInt32(int32_t data)
{
    m_type = PrimitiveDataType::int32bit;
    m_data = data;
}

void TreeDBValue::setInt64(int64_t data)
{
    m_type = PrimitiveDataType::int64bit;
    m_data = data;
}

void TreeDBValue::setUTF8String(const std::string& data)
{
    m_type = PrimitiveDataType::unicodeString;
    m_data = data;
}

void TreeDBValue::setBinary(const std::string& data)
{
    m_type = PrimitiveDataType::binary;
    m_data = data;
}

}

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

#include "TreeDBValue.h"

namespace DiplodocusDB
{

TreeDBValue::TreeDBValue()
    : m_type(EPrimitiveDataType::eNULL)
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
    m_type = EPrimitiveDataType::eBoolean;
    m_data = data;
}

void TreeDBValue::setInt8(int8_t data)
{
    m_type = EPrimitiveDataType::eInt8;
    m_data = data;
}

void TreeDBValue::setInt16(int16_t data)
{
    m_type = EPrimitiveDataType::eInt16;
    m_data = data;
}

void TreeDBValue::setInt32(int32_t data)
{
    m_type = EPrimitiveDataType::eInt32;
    m_data = data;
}

void TreeDBValue::setInt64(int64_t data)
{
    m_type = EPrimitiveDataType::eInt64;
    m_data = data;
}

void TreeDBValue::setUTF8String(const std::string& data)
{
    m_type = EPrimitiveDataType::eUTF8String;
    m_data = data;
}

void TreeDBValue::setBinary(const std::string& data)
{
    m_type = EPrimitiveDataType::eBinary;
    m_data = data;
}

}

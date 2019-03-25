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

TreeDBValue TreeDBValue::Int32(int32_t value)
{
    TreeDBValue result;
    result.setInt32(value);
    return result;
}

TreeDBValue::~TreeDBValue()
{
}

const DataType& TreeDBValue::type() const
{
    return m_type;
}

int32_t TreeDBValue::asInt32() const
{
    return boost::any_cast<int32_t>(m_data);
}

const std::string& TreeDBValue::asUTF8String() const
{
    return boost::any_cast<const std::string&>(m_data);
}

void TreeDBValue::setInt32(int32_t value)
{
    m_type = EPrimitiveDataType::eInt32;
    m_data = value;
}

void TreeDBValue::setUTF8String(const std::string& value)
{
    m_type = EPrimitiveDataType::eUTF8String;
    m_data = value;
}

}

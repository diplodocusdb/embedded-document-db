/*
    Copyright (c) 2019 Xavier Leclercq

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

#include "NodeID.h"

namespace DiplodocusDB
{

NodeID::NodeID()
    : m_value(0)
{
}

NodeID::NodeID(size_t value)
    : m_value(value)
{
}

bool NodeID::isNull() const
{
    return (m_value == 0);
}

bool NodeID::operator==(const NodeID& other) const
{
    return (m_value == other.m_value);
}

bool NodeID::operator!=(const NodeID& other) const
{
    return (m_value != other.m_value);
}

bool NodeID::operator<(const NodeID& other) const
{
    return (m_value < other.m_value);
}

bool NodeID::operator>(const NodeID& other) const
{
    return (m_value > other.m_value);
}

void NodeID::read(PageRepositoryReader& reader, Ishiko::Error& error)
{
    m_value = reader.readLEB128(error);
}

void NodeID::write(PageRepositoryWriter& writer, Ishiko::Error& error) const
{
    writer.writeLEB128(m_value, error);
}

}
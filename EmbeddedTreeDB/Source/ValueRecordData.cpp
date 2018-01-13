/*
    Copyright (c) 2018 Xavier Leclercq

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

#include "ValueRecordData.h"

namespace DiplodocusDB
{

ValueRecordData::ValueRecordData()
    : RecordData(Record::ERecordType::eValue),
    m_type(EPrimitiveDataType::eNULL)
{
}

ValueRecordData::ValueRecordData(const TreeDBValue& value)
    : RecordData(Record::ERecordType::eValue),
    m_type(value.type()), m_buffer(value.asString())
{
}

ValueRecordData::~ValueRecordData()
{
}

size_t ValueRecordData::size() const
{
    return (8 + m_buffer.size());
}

void ValueRecordData::read(const char* buffer,
                           size_t recordDataSize)
{
}

void ValueRecordData::write(std::ostream& s,
                            Ishiko::Error& error) const
{
    writeDataType(s, error);
    if (!error)
    {
        s.write(m_buffer.c_str(), m_buffer.size());
    }
}

void ValueRecordData::writeDataType(std::ostream& s,
                                    Ishiko::Error& error) const
{
    uint32_t primitiveType = (uint32_t)m_type.primitiveType();
    s.write((char*)&primitiveType, 4);
    if (!s.good())
    {
        error = -1;
    }
    uint32_t modifier = (uint32_t)m_type.modifier();
    s.write((char*)&modifier, 4);
    if (!s.good())
    {
        error = -1;
    }
}

}

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
#include "Page.h"

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

const std::string& ValueRecordData::buffer() const
{
    return m_buffer;
}

size_t ValueRecordData::size() const
{
    return (2 + m_buffer.size());
}

void ValueRecordData::read(const char* buffer,
                           size_t recordDataSize)
{
    m_buffer.assign(buffer + 2, recordDataSize - 2);
}

void ValueRecordData::write(Page& page,
                            Ishiko::Error& error) const
{
    writeDataType(page, error);
    if (!error)
    {
        page.write(m_buffer.c_str(), m_buffer.size(), error);
    }
}

void ValueRecordData::writeDataType(Page& page,
                                    Ishiko::Error& error) const
{
    uint8_t type = (uint8_t)m_type.primitiveType();
    page.write((char*)&type, 1, error);
    if (!error)
    {
        uint8_t modifier = (uint8_t)m_type.modifier();
        page.write((char*)&modifier, 1, error);
    }
}

}

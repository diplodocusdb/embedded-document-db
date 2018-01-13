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

#include "KeyRecordData.h"

namespace DiplodocusDB
{

KeyRecordData::KeyRecordData()
    : RecordData(Record::ERecordType::eKey)
{
}

KeyRecordData::KeyRecordData(const TreeDBKey& key)
    : RecordData(Record::ERecordType::eKey), m_key(key.value())
{
}

KeyRecordData::~KeyRecordData()
{
}

size_t KeyRecordData::size() const
{
    return m_key.size();
}

void KeyRecordData::read(const char* buffer)
{
}

void KeyRecordData::write(std::ostream& s,
                          Ishiko::Error& error) const
{
    s.write(m_key.c_str(), m_key.size());
    if (!s.good())
    {
        error = -1;
    }
}

}

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

#include "Record.h"
#include "RecordData.h"

namespace DiplodocusDB
{

Record::Record()
{
}

Record::Record(std::shared_ptr<RecordData> data)
    : m_data(data)
{
}

Record::~Record()
{
}

size_t Record::size() const
{
    return (8 + m_data->size());
}

void Record::load(const char* buffer)
{
}

void Record::save(std::ostream& s,
                  Ishiko::Error& error) const
{
    uint32_t type = (uint32_t)m_data->type();
    s.write((char*)&type, 4);
    if (!s.good())
    {
        error = -1;
    }
    else
    {
        uint32_t size = m_data->size();
        s.write((char*)&size, 4);
        if (!s.good())
        {
            error = -1;
        }
        else
        {
            m_data->serialize(s, error);
        }
    }
}

}

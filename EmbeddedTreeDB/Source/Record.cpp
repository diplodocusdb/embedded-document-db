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
#include "MasterFileMetadata.h"
#include "KeyRecordData.h"
#include "StartOfPageRecordData.h"
#include "EndOfPageRecordData.h"

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

Record::ERecordType Record::type() const
{
    if (m_data)
    {
        return m_data->type();
    }
    else
    {
        return ERecordType::eInvalid;
    }
}

size_t Record::size() const
{
    return (8 + m_data->size());
}

RecordData* Record::data()
{
    return m_data.get();
}

void Record::read(const char* buffer,
                  Ishiko::Error& error)
{
    ERecordType type = (ERecordType)(*((uint32_t*)buffer));
    switch (type)
    {
    case ERecordType::eInvalid:
        error = -1;
        break;

    case ERecordType::eMasterFileMetadata:
        m_data = std::make_shared<MasterFileMetadata>();
        break;

    case ERecordType::eKey:
        m_data = std::make_shared<KeyRecordData>();
        break;

    case ERecordType::eStartOfPage:
        m_data = std::make_shared<StartOfPageRecordData>();
        break;

    case ERecordType::eEndOfPage:
        m_data = std::make_shared<EndOfPageRecordData>();
        break;

    default:
        error = -1;
        break;
    }
    
    if (!error)
    {
        uint32_t size = *((uint32_t*)(buffer + 4));
        m_data->read(buffer + 8, size);
    }
}

void Record::write(std::ostream& s,
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
            m_data->write(s, error);
        }
    }
}

}

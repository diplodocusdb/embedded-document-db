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
#include "DataStartRecordData.h"
#include "DataEndRecordData.h"
#include "KeyRecordData.h"
#include "ValueRecordData.h"
#include "Utilities.h"
#include "DiplodocusDB/PhysicalStorage/PageRepository/Page.h"

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
    size_t dataSize = m_data->size();
    return (1 + Utilities::encodeSize(dataSize, 0) + dataSize);
}

RecordData* Record::data()
{
    return m_data.get();
}

void Record::load(PageRepositoryReader& reader,
                  Ishiko::Error& error)
{
    uint8_t type;
    reader.read((char*)&type, 1, error);
    if (error)
    {
        return;
    }

    switch ((ERecordType)type)
    {
    case ERecordType::eInvalid:
        error = -1;
        break;

    case ERecordType::eMasterFileMetadata:
        m_data = std::make_shared<MasterFileMetadata>();
        break;

    case ERecordType::eDataStart:
        m_data = std::make_shared<DataStartRecordData>();
        break;

    case ERecordType::eDataEnd:
        m_data = std::make_shared<DataEndRecordData>();
        break;

    case ERecordType::eKey:
        m_data = std::make_shared<KeyRecordData>();
        break;

    case ERecordType::eValue:
        m_data = std::make_shared<ValueRecordData>();
        break;

    default:
        error = -1;
        break;
    }
    
    if (!error)
    {
        uint8_t size;
        reader.read((char*)&size, 1, error);
        if (!error)
        {
            m_data->load(reader, size, error);
        }
    }
}

void Record::save(PageRepositoryWriter& writer,
                  Ishiko::Error& error) const
{
    uint8_t type = (uint8_t)m_data->type();
    writer.write((char*)&type, 1, error);
    if (!error)
    {
        char buffer[20];
        size_t n = Utilities::encodeSize(m_data->size(), buffer);
        writer.write(buffer, n, error);
        if (!error)
        {
            m_data->save(writer, error);
        }
    }
}

}

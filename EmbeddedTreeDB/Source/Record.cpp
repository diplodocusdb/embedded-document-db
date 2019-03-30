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

#include "Record.h"
#include "RecordData.h"
#include "MasterFileMetadata.h"
#include "KeyRecordData.h"
#include "ValueRecordData.h"
#include "Utilities.h"
#include "DiplodocusDB/PhysicalStorage/PageRepository/Page.h"

namespace DiplodocusDB
{

Record::Record(ERecordType type)
    : m_type(type)
{
}

Record::Record(const MasterFileMetadata& data)
    : m_type(ERecordType::eMasterFileMetadata)
{
    m_data2 = data;
}

Record::Record(ERecordType type, std::shared_ptr<RecordData> data)
    : m_type(type), m_data(data)
{
}

Record::ERecordType Record::type() const
{
    return m_type;
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

void Record::read(PageRepositoryReader& reader, Ishiko::Error& error)
{
    uint8_t type;
    reader.read((char*)&type, 1, error);
    if (error)
    {
        return;
    }

    m_type = (ERecordType)type;

    switch (m_type)
    {
    case ERecordType::eInvalid:
        // TODO : add details
        error.fail(-1, "Invalid record type", __FILE__, __LINE__);
        break;

    case ERecordType::eMasterFileMetadata:
        {
            uint8_t size;
            reader.read((char*)&size, 1, error);
            if (!error)
            {
                m_data2 = MasterFileMetadata();
                boost::get<MasterFileMetadata>(m_data2).read(reader, size, error);
            }
        }
        break;

    case ERecordType::eDataStart:
    case ERecordType::eDataEnd:
    case ERecordType::eNodeStart:
    case ERecordType::eNodeEnd:
        break;

    case ERecordType::eNodeName:
        m_data = std::make_shared<KeyRecordData>();
        break;

    case ERecordType::eInlineValue:
        m_data = std::make_shared<ValueRecordData>();
        break;

    default:
        // TODO : add details
        error.fail(-1, "Invalid record type", __FILE__, __LINE__);
        break;
    }
    
    if (!error && m_data)
    {
        uint8_t size;
        reader.read((char*)&size, 1, error);
        if (!error)
        {
            m_data->load(reader, size, error);
        }
    }
}

void Record::write(PageRepositoryWriter& writer, Ishiko::Error& error) const
{
    uint8_t type = (uint8_t)m_type;
    writer.write((char*)&type, 1, error);
    if (!error && m_data)
    {
        char buffer[20];
        size_t n = Utilities::encodeSize(m_data->size(), buffer);
        writer.write(buffer, n, error);
        if (!error)
        {
            m_data->save(writer, error);
        }
    }
    switch (type)
    {
    case ERecordType::eMasterFileMetadata:
        {
            char buffer[20];
            size_t n = Utilities::encodeSize(boost::get<MasterFileMetadata>(m_data2).size(), buffer);
            writer.write(buffer, n, error);
            if (!error)
            {
                boost::get<MasterFileMetadata>(m_data2).write(writer, error);
            }
        }
        break;
    }
}

}

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

#include "MasterFile.h"
#include "EmbeddedTreeDBNodeImpl.h"
#include "DataStartRecordData.h"
#include "DataEndRecordData.h"
#include "KeyRecordData.h"
#include "ValueRecordData.h"

namespace DiplodocusDB
{

MasterFile::MasterFile()
    : m_metadata(std::make_shared<MasterFileMetadata>())
{
}

MasterFile::~MasterFile()
{
}

void MasterFile::create(const boost::filesystem::path& path,
                        Ishiko::Error& error)
{
    m_repository.create(path, error);
    if (!error)
    {
        std::shared_ptr<Page> page = m_repository.allocatePage(error);
        if (!error)
        {
            PageRepositoryWriter writer = m_repository.insert(page, 0, error);
            if (!error)
            {
                Record metadataRecord(m_metadata);
                metadataRecord.save(writer, error);
                if (!error)
                {
                    Record dataStartRecord(std::make_shared<DataStartRecordData>());
                    dataStartRecord.save(writer, error);
                    if (!error)
                    {
                        Record dataEndRecord(std::make_shared<DataEndRecordData>());
                        dataEndRecord.save(writer, error);
                        if (!error)
                        {
                            page->save(error);
                        }
                    }
                }
            }
        }
    }
}

void MasterFile::open(const boost::filesystem::path& path,
                      Ishiko::Error& error)
{
    m_repository.open(path, error);
}

void MasterFile::close()
{
    m_repository.close();
}

bool MasterFile::findNode(const TreeDBKey& key,
                          EmbeddedTreeDBNodeImpl& node,
                          Ishiko::Error& error)
{
    bool result = false;

    PageRepositoryReader reader = m_repository.read(0, 0, error);
    while (!result && !error)
    {
        Record record;
        record.load(reader, error);
        if (!error && (record.type() == Record::ERecordType::eKey))
        {
            if (static_cast<KeyRecordData*>(record.data())->key() == key.value())
            {
                Record valueRecord;
                valueRecord.load(reader, error);
                if (!error && (record.type() == Record::ERecordType::eValue))
                {
                    const std::string& value = static_cast<ValueRecordData*>(valueRecord.data())->buffer();
                    node.value().setString(value);
                }
                
                result = true;
            }
        }
    }

    return result;
}

void MasterFile::commitNode(const EmbeddedTreeDBNodeImpl& node,
                            Ishiko::Error& error)
{
    std::shared_ptr<Page> page = m_repository.page(0, error);
    if (!error)
    {
        PageRepositoryWriter writer = m_repository.insert(page, 0, error);
        if (!error)
        {
            std::shared_ptr<KeyRecordData> recordData = std::make_shared<KeyRecordData>(node.key());
            Record record(recordData);
            record.save(writer, error);

            if (!error)
            {
                if (node.value().type() != DataType(EPrimitiveDataType::eNULL))
                {
                    std::shared_ptr<ValueRecordData> recordData = std::make_shared<ValueRecordData>(node.value());
                    Record record(recordData);
                    record.save(writer, error);
                }

                if (!error)
                {
                    writer.save(error);
                }
            }
        }
    }
}

}

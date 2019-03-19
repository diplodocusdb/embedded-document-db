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

#include "MasterFile.h"
#include "EmbeddedTreeDBNodeImpl.h"
#include "KeyRecordData.h"
#include "ValueRecordData.h"

namespace DiplodocusDB
{

MasterFile::MasterFile()
    : m_metadata(std::make_shared<MasterFileMetadata>()),
    m_dataStartOffset(0), m_dataEndOffset(0)
{
}

MasterFile::~MasterFile()
{
}

void MasterFile::create(const boost::filesystem::path& path,
                        Ishiko::Error& error)
{
    m_repository.create(path, error);
    if (error)
    {
        return;
    }
    
    std::shared_ptr<Page> page = m_repository.allocatePage(error);
    if (error)
    {
        return;
    }
    
    PageRepositoryWriter writer = m_repository.insert(page, 0, error);
    if (error)
    {
        return;
    }

    Record metadataRecord(Record::ERecordType::eMasterFileMetadata, m_metadata);
    metadataRecord.save(writer, error);
    if (error)
    {
        return;
    }
    
    m_dataStartOffset = page->dataSize();
    Record dataStartRecord(Record::ERecordType::eDataStart);
    dataStartRecord.save(writer, error);
    if (error)
    {
        return;
    }
    
    createRootNode(writer, error);
    if (error)
    {
        return;
    }

    m_dataEndPage = page;
    m_dataEndOffset = page->dataSize();
    Record dataEndRecord(Record::ERecordType::eDataEnd);
    dataEndRecord.save(writer, error);
    if (error)
    {
        return;
    }
    
    page->save(error);
}

void MasterFile::open(const boost::filesystem::path& path,
                      Ishiko::Error& error)
{
    m_repository.open(path, error);
    m_dataStartOffset = 14;
    m_dataEndPage = m_repository.page(m_repository.pageCount() - 1, error);
    if (!error)
    {
        // Deduct 1 for the end of data record
        m_dataEndOffset = (m_dataEndPage->dataSize() - 1);
    }
}

void MasterFile::close()
{
    m_repository.close();
}

RecordMarker MasterFile::rootNodePosition() const
{
    return RecordMarker(PageRepositoryPosition(0, m_dataStartOffset + 1));
}

RecordMarker MasterFile::dataEndPosition() const
{
    return RecordMarker(PageRepositoryPosition(m_dataEndPage->index(), m_dataEndOffset));
}

bool MasterFile::findNode(const TreeDBKey& key,
                          EmbeddedTreeDBNodeImpl& node,
                          Ishiko::Error& error)
{
    bool result = false;

    PageRepositoryReader reader = m_repository.read(0, m_dataStartOffset + 1, error);
    while (!result && !error)
    {
        PageRepositoryPosition currentNodeStartPosition = reader.currentPosition();
        Record record(Record::ERecordType::eInvalid);
        record.load(reader, error);
        if (!error && (record.type() == Record::ERecordType::eKey))
        {
            if (static_cast<KeyRecordData*>(record.data())->key() == key.value())
            {
                Record valueRecord(Record::ERecordType::eValue);
                valueRecord.load(reader, error);
                if (!error)
                {
                    if (valueRecord.type() == Record::ERecordType::eValue)
                    {
                        const std::string& value = static_cast<ValueRecordData*>(valueRecord.data())->buffer();
                        node.value().setString(value);
                    }

                    node.setMarker(RecordMarker(currentNodeStartPosition));
                    result = true;
                }
            }
        }
    }

    return result;
}

void MasterFile::addNode(const EmbeddedTreeDBNodeImpl& node,
                         Ishiko::Error& error)
{
    PageRepositoryWriter writer = m_repository.insert(node.marker().position(), error);
    if (error)
    {
        return;
    }

    Record nodeStartRecord(Record::ERecordType::eNodeStart);
    nodeStartRecord.save(writer, error);
    if (error)
    {
        return;
    }

    std::shared_ptr<KeyRecordData> recordData = std::make_shared<KeyRecordData>(node.key());
    Record record(Record::ERecordType::eKey, recordData);
    record.save(writer, error);
    if (error)
    {
        return;
    }

    if (node.value().type() != DataType(EPrimitiveDataType::eNULL))
    {
        std::shared_ptr<ValueRecordData> recordData = std::make_shared<ValueRecordData>(node.value());
        Record record(Record::ERecordType::eValue, recordData);
        record.save(writer, error);
        if (error)
        {
            return;
        }
    }

    Record nodeEndRecord(Record::ERecordType::eNodeEnd);
    nodeEndRecord.save(writer, error);
    if (error)
    {
        return;
    }

    writer.save(error);
    if (error)
    {
        return;
    }

    m_dataEndPage = writer.currentPage();
    m_dataEndOffset = (m_dataEndPage->dataSize() - 1);
}

bool MasterFile::removeNode(const TreeDBKey& key,
                            Ishiko::Error& error)
{
    error.fail(-1);
    return false;
}

void MasterFile::createRootNode(PageRepositoryWriter& writer,
                                Ishiko::Error& error)
{
    Record nodeStartRecord(Record::ERecordType::eNodeStart);
    nodeStartRecord.save(writer, error);
    if (error)
    {
        return;
    }

    std::shared_ptr<KeyRecordData> recordData = std::make_shared<KeyRecordData>("/");
    Record record(Record::ERecordType::eKey, recordData);
    record.save(writer, error);
    if (error)
    {
        return;
    }

    Record nodeEndRecord(Record::ERecordType::eNodeEnd);
    nodeEndRecord.save(writer, error);
    if (error)
    {
        return;
    }
}

void MasterFile::findChildren()
{
}

}

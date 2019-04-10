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

namespace DiplodocusDB
{

MasterFile::MasterFile()
    : m_metadataRecord(MasterFileMetadata()), m_dataStartOffset(0), m_dataEndOffset(0)
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

    m_metadataRecord.write(writer, error);
    if (error)
    {
        return;
    }
    
    m_dataStartOffset = page->dataSize();
    Record dataStartRecord(Record::ERecordType::eDataStart);
    dataStartRecord.write(writer, error);
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
    dataEndRecord.write(writer, error);
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

bool MasterFile::findSiblingNodesRecordGroup(const NodeID& parentNodeID, SiblingNodesRecordGroup& siblingNodes,
    Ishiko::Error& error)
{
    bool result = false;

    PageRepositoryReader reader = m_repository.read(0, m_dataStartOffset + 1, error);
    while (!result && !error)
    {
        PageRepositoryPosition currentNodeStartPosition = reader.currentPosition();
        Record record(Record::ERecordType::eInvalid);
        record.read(reader, error);
        if (!error && (record.type() == Record::ERecordType::eNodeName))
        {
            /* TODO
            if (static_cast<KeyRecordData*>(record.data())->key() == key.value())
            {
                Record valueRecord(Record::ERecordType::eInlineValue);
                valueRecord.read(reader, error);
                if (!error)
                {
                    if (valueRecord.type() == Record::ERecordType::eInlineValue)
                    {
                        const std::string& value = static_cast<ValueRecordData*>(valueRecord.data())->buffer();
                        node.value().setUTF8String(value);
                    }

                    node.setMarker(RecordMarker(currentNodeStartPosition));
                    result = true;
                }
            }
            */
        }
    }

    return result;
}

void MasterFile::addSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error)
{
    PageRepositoryWriter writer = m_repository.insert(dataEndPosition().position(), error);
    if (error)
    {
        return;
    }

    siblingNodes.write(writer, error);
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

bool MasterFile::removeNode(const TreeDBKey& key, Ishiko::Error& error)
{
    error.fail(-1);
    return false;
}

void MasterFile::createRootNode(PageRepositoryWriter& writer, Ishiko::Error& error)
{
    Record nodeStartRecord(Record::ERecordType::eSiblingNodesStart);
    nodeStartRecord.write(writer, error);
    if (error)
    {
        return;
    }

    Record record("/");
    record.write(writer, error);
    if (error)
    {
        return;
    }

    Record nodeEndRecord(Record::ERecordType::eSiblingNodesEnd);
    nodeEndRecord.write(writer, error);
    if (error)
    {
        return;
    }
}

}

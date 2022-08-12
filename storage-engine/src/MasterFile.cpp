/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "MasterFile.hpp"
#include "MasterFileMetadata.hpp"
#include "EmbeddedDocumentDBStorageEngineErrorCategory.hpp"

using namespace DiplodocusDB;

MasterFile::MasterFile()
    : m_metadataRecord(MasterFileMetadata()), m_dataStartOffset(0), m_dataEndOffset(0)
{
}

void MasterFile::create(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_repository.create(path, error);
    if (error)
    {
        return;
    }
    
    std::shared_ptr<PhysicalStorage::Page> page = m_repository.allocatePage(error);
    if (error)
    {
        return;
    }
    
    PhysicalStorage::PageRepositoryWriter writer = m_repository.insert(page, 0, error);
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

    m_dataEndPageIndex = page->index();
    m_dataEndOffset = page->dataSize();
    Record dataEndRecord(Record::ERecordType::eDataEnd);
    dataEndRecord.write(writer, error);
    if (error)
    {
        return;
    }
    
    m_repository.save(*page, error);
}

void MasterFile::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_repository.open(path, error);
    m_dataStartOffset = 14;
    m_dataEndPageIndex = m_repository.pageCount() - 1;
    std::shared_ptr<PhysicalStorage::Page> dataEndPage = m_repository.page(m_dataEndPageIndex, error);
    if (!error)
    {
        // Deduct 1 for the end of data record
        m_dataEndOffset = (dataEndPage->dataSize() - 1);
    }
}

void MasterFile::close()
{
    m_repository.close();
}

RecordMarker MasterFile::rootNodePosition() const
{
    return RecordMarker(PhysicalStorage::PageRepositoryPosition(0, m_dataStartOffset + 1));
}

RecordMarker MasterFile::dataEndPosition() const
{
    return RecordMarker(PhysicalStorage::PageRepositoryPosition(m_dataEndPageIndex, m_dataEndOffset));
}

bool MasterFile::findSiblingNodesRecordGroup(const NodeID& parentNodeID, SiblingNodesRecordGroup& siblingNodes,
    Ishiko::Error& error)
{
    bool result = false;

    PhysicalStorage::PageRepositoryReader reader = m_repository.read(0, m_dataStartOffset + 1, error);
    while (!result && !error)
    {
        Record nextRecord(Record::ERecordType::eInvalid);
        nextRecord.read(reader, error);
        if (error)
        {
            break;
        }
        if (nextRecord.type() == Record::ERecordType::eSiblingNodesStart)
        {
            SiblingNodesRecordGroup siblingNodesRecordGroup;
            siblingNodesRecordGroup.readWithoutType(reader, error);
            if (error)
            {
                break;
            }
            if (siblingNodesRecordGroup.parentNodeID() == parentNodeID)
            {
                siblingNodes = siblingNodesRecordGroup;
                result = true;
                break;
            }
        }
        else if (nextRecord.type() == Record::ERecordType::eDataEnd)
        {
            break;
        }
        else
        {
            // TODO : more precise error
            error.fail(EmbeddedDocumentDBStorageEngineErrorCategory::Get(), -1, "TODO", __FILE__, __LINE__);
            break;
        }
    }

    return result;
}

void MasterFile::addSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error)
{
    PhysicalStorage::PageRepositoryWriter writer = m_repository.insert(dataEndPosition().position(), error);
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

    m_dataEndPageIndex = writer.currentPosition().page();
    m_dataEndOffset = writer.currentPosition().offset();
}

void MasterFile::updateSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error)
{
    // TODO
}

bool MasterFile::removeSiblingNodesRecordGroup(const NodeID& parentNodeID, Ishiko::Error& error)
{
    // TODO
    error.fail(EmbeddedDocumentDBStorageEngineErrorCategory::Get(), -1);
    return false;
}

void MasterFile::createRootNode(PhysicalStorage::PageRepositoryWriter& writer, Ishiko::Error& error)
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

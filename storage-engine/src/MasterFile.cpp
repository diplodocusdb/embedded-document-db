/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "MasterFile.hpp"
#include "MasterFileMetadata.hpp"
#include "StorageEngineErrorCategory.hpp"

using namespace DiplodocusDB;
using namespace DiplodocusDB::EDDBImpl;

MasterFile::MasterFile()
    : m_metadataRecord{MasterFileMetadata()}, m_dataStartOffset{0}, m_dataEndOffset{0}
{
}

void MasterFile::create(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_repository.create(path, error);
    if (error)
    {
        return;
    }
    
    RecordPage page = m_repository.allocatePage(error);
    if (error)
    {
        return;
    }
    
    RecordPageWorkingSet working_set{m_repository};
    working_set.add(page);
    RecordRepositoryWriter writer{working_set, page.number(), 0, error};
    if (error)
    {
        return;
    }

    m_metadataRecord.write(writer, error);
    if (error)
    {
        return;
    }
    
    m_dataStartOffset = page.dataSize();
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

    m_dataEndPageIndex = page.number();
    m_dataEndOffset = page.dataSize();
    Record dataEndRecord(Record::ERecordType::eDataEnd);
    dataEndRecord.write(writer, error);
    if (error)
    {
        return;
    }
    
    working_set.save(error);
}

void MasterFile::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_repository.open(path, error);
    m_dataStartOffset = 14;
    m_dataEndPageIndex = m_repository.pageCount() - 1;
    RecordPage dataEndPage = m_repository.page(m_dataEndPageIndex, error);
    if (!error)
    {
        // Deduct 1 for the end of data record
        m_dataEndOffset = (dataEndPage.dataSize() - 1);
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

void MasterFile::addSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error)
{
    RecordPage page = m_repository.page(dataEndPosition().position().page(), error);
    if (error)
    {
        return;
    }

    RecordPageWorkingSet working_set{m_repository};
    RecordRepositoryWriter writer{working_set, page.number(), dataEndPosition().position().offset(), error};
    if (error)
    {
        return;
    }

    siblingNodes.write(writer, error);
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
    error.fail(StorageEngineErrorCategory::Get(), -1);
    return false;
}

void MasterFile::createRootNode(RecordRepositoryWriter& writer, Ishiko::Error& error)
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

/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "StorageEngine.hpp"
#include "StorageEngineErrorCategory.hpp"

using namespace DiplodocusDB::EDDBImpl;

StorageEngine::StorageEngine()
    : m_working_set{m_master_file}
{
}

void StorageEngine::createMasterFile(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_master_file.create(path, error);
}

void StorageEngine::openMasterFile(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_master_file.open(path, error);
}

void StorageEngine::close()
{
    m_master_file.close();
}

bool StorageEngine::findSiblingNodesRecordGroup(const NodeID& parentNodeID,
    std::shared_ptr<SiblingNodesRecordGroup>& siblingNodes, Ishiko::Error& error)
{
    bool result = false;

    bool foundInCache = m_siblingNodesRecordGroupCache.find(parentNodeID, siblingNodes);
    if (foundInCache)
    {
        result = true;
    }
    else
    {
        std::shared_ptr<SiblingNodesRecordGroup> newCachedSiblingNodes = m_siblingNodesRecordGroupCache[parentNodeID];
        // TODO: 0 is for dataStartPosition, I think it doesn't matter that much, it's just that master file has the
        // metadata record at the start but even if we parse it doesn't matter
        bool foundInFiles = findSiblingNodesRecordGroup(m_working_set, 0, parentNodeID, *newCachedSiblingNodes, error);
        if (error)
        {
            result = false;
        }
        else if (foundInFiles)
        {
            siblingNodes = newCachedSiblingNodes;
            result = true;
        }
        else
        {
            // This should be a rare case as we should know which node IDs are unallocated and not even try to search
            // for them
            m_siblingNodesRecordGroupCache.erase(parentNodeID);
            result = false;
        }
    }

    return result;
}

bool StorageEngine::findSiblingNodesRecordGroup(RecordPageWorkingSet& repository, size_t dataStartOffset,
    const NodeID& parentNodeID, SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error)
{
    bool result = false;

    RecordRepositoryReader reader{repository, 0, dataStartOffset + 1, error};
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
            error.fail(StorageEngineErrorCategory::Get(), -1, "TODO", __FILE__, __LINE__);
            break;
        }
    }

    return result;
}

void StorageEngine::addSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error)
{
    m_master_file.addSiblingNodesRecordGroup(siblingNodes, error);
}

void StorageEngine::updateSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error)
{
    m_master_file.updateSiblingNodesRecordGroup(siblingNodes, error);
}

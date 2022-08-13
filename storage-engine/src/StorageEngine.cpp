/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "StorageEngine.hpp"

using namespace DiplodocusDB::EDDBImpl;

void StorageEngine::createMasterFile(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_recordFiles.createMasterFile(path, error);
}

void StorageEngine::openMasterFile(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_recordFiles.openMasterFile(path, error);
}

void StorageEngine::close()
{
    m_recordFiles.close();
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
        bool foundInFiles = m_recordFiles.findSiblingNodesRecordGroup(parentNodeID, *newCachedSiblingNodes, error);
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

void StorageEngine::addSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error)
{
    m_recordFiles.addSiblingNodesRecordGroup(siblingNodes, error);
}

void StorageEngine::updateSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error)
{
    m_recordFiles.updateSiblingNodesRecordGroup(siblingNodes, error);
}
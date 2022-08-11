/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_EMBEDDEDDOCUMENTDBSTORAGEENGINE_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_EMBEDDEDDOCUMENTDBSTORAGEENGINE_HPP_

#include "NodeID.hpp"
#include "RecordFilesSet.hpp"
#include "SiblingNodesRecordGroup.hpp"
#include "SiblingNodesRecordGroupCache.hpp"
#include <boost/filesystem.hpp>
#include <Ishiko/Errors.hpp>

namespace DiplodocusDB
{

class EmbeddedDocumentDBStorageEngine
{
public:
    void createMasterFile(const boost::filesystem::path& path, Ishiko::Error& error);
    void openMasterFile(const boost::filesystem::path& path, Ishiko::Error& error);
    void close();

    bool findSiblingNodesRecordGroup(const NodeID& parentNodeID,
        std::shared_ptr<SiblingNodesRecordGroup>& siblingNodes, Ishiko::Error& error);
    void addSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error);
    void updateSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error);

private:
    SiblingNodesRecordGroupCache m_siblingNodesRecordGroupCache;
    RecordFilesSet m_recordFiles;
};

}

#endif

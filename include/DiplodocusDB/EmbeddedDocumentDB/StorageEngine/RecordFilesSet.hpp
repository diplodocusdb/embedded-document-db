/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDFILESSET_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDFILESSET_HPP_

#include "MasterFile.hpp"
#include "NodeID.hpp"
#include "SiblingNodesRecordGroup.hpp"
#include <boost/filesystem.hpp>
#include <Ishiko/Errors.hpp>

namespace DiplodocusDB
{

class RecordFilesSet
{
public:
    void createMasterFile(const boost::filesystem::path& path, Ishiko::Error& error);
    void openMasterFile(const boost::filesystem::path& path, Ishiko::Error& error);
    void close();

    bool findSiblingNodesRecordGroup(const NodeID& parentNodeID, SiblingNodesRecordGroup& siblingNodes,
        Ishiko::Error& error);
    void addSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error);
    void updateSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error);

private:
    MasterFile m_masterFile;
};

}

#endif

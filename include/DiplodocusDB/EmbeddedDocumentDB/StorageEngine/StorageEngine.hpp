/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_STORAGEENGINE_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_STORAGEENGINE_HPP

#include "MasterFile.hpp"
#include "NodeID.hpp"
#include "SiblingNodesRecordGroup.hpp"
#include "SiblingNodesRecordGroupCache.hpp"
#include <boost/filesystem.hpp>
#include <Ishiko/Errors.hpp>

namespace DiplodocusDB
{
namespace EDDBImpl
{

class StorageEngine
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
    MasterFile m_master_file;
};

}
}

#endif

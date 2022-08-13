/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_SIBLINGNODESRECORDGROUPCACHE_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_SIBLINGNODESRECORDGROUPCACHE_HPP

#include "NodeID.hpp"
#include "SiblingNodesRecordGroup.hpp"
#include <map>
#include <memory>

namespace DiplodocusDB
{
namespace EDDBImpl
{

class SiblingNodesRecordGroupCache
{
public:
    bool find(const NodeID& key, std::shared_ptr<SiblingNodesRecordGroup>& siblingNodes);
    std::shared_ptr<SiblingNodesRecordGroup>& operator[](const NodeID& key);
    bool erase(const NodeID& key);

private:
    // TODO : it is not good enough for these to be shared pointers because if I remove them from the cache
    // and reload the same group in the cache again I have 1 group with 2 in-memory representations that can get
    // out of sync
    std::map<NodeID, std::shared_ptr<SiblingNodesRecordGroup>> m_groups;
};

}
}

#endif

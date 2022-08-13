/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "SiblingNodesRecordGroupCache.hpp"

using namespace DiplodocusDB::EDDBImpl;

bool SiblingNodesRecordGroupCache::find(const NodeID& key,
    std::shared_ptr<SiblingNodesRecordGroup>& siblingNodes)
{
    std::map<NodeID, std::shared_ptr<SiblingNodesRecordGroup>>::iterator it = m_groups.find(key);
    if (it != m_groups.end())
    {
        siblingNodes = it->second;
        return true;
    }
    else
    {
        return false;
    }
}

std::shared_ptr<SiblingNodesRecordGroup>& SiblingNodesRecordGroupCache::operator[](const NodeID& key)
{
    std::shared_ptr<SiblingNodesRecordGroup>& result = m_groups[key];
    if (!result)
    {
        result = std::make_shared<SiblingNodesRecordGroup>(key);
    }
    return result;
}

bool SiblingNodesRecordGroupCache::erase(const NodeID& key)
{
    return (m_groups.erase(key) > 0);
}

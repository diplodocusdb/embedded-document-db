/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_SIBLINGNODESRECORDGROUP_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_SIBLINGNODESRECORDGROUP_HPP_

#include "NodeID.hpp"
#include "SiblingNodeRecordGroup.hpp"
#include <DiplodocusDB/PhysicalStorage/PageRepository.hpp>
#include <Ishiko/Errors.hpp>
#include <string>
#include <vector>

namespace DiplodocusDB
{

/// A list of records storing sibling nodes.
/**
    This class represents a series of records used in the database to store the nodes that have the same parent.
*/
class SiblingNodesRecordGroup
{
public:
    SiblingNodesRecordGroup() = default;
    explicit SiblingNodesRecordGroup(const NodeID& parentNodeID);
    explicit SiblingNodesRecordGroup(const NodeID& parentNodeID, const SiblingNodeRecordGroup& node);

    const NodeID& parentNodeID() const;
    const SiblingNodeRecordGroup& operator[](size_t pos) const;
    /// Returns the number of sibling nodes in the record group.
    size_t size() const noexcept;
    void push_back(const SiblingNodeRecordGroup& value);
    bool find(const std::string& name, SiblingNodeRecordGroup& node);

    void readWithoutType(PageRepositoryReader& reader, Ishiko::Error& error);
    void write(PageRepositoryWriter& writer, Ishiko::Error& error) const;

private:
    static void writeNode(PageRepositoryWriter& writer, const SiblingNodeRecordGroup& node, Ishiko::Error& error);

private:
    NodeID m_parentNodeID;
    std::vector<SiblingNodeRecordGroup> m_siblings;
};

}

#endif

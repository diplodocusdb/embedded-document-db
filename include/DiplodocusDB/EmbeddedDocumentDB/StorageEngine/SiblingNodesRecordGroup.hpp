/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_SIBLINGNODESRECORDGROUP_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_SIBLINGNODESRECORDGROUP_HPP

#include "NodeID.hpp"
#include "RecordRepositoryReader.hpp"
#include "RecordRepositoryWriter.hpp"
#include "SiblingNodeRecordGroup.hpp"
#include <Ishiko/Errors.hpp>
#include <string>
#include <vector>

namespace DiplodocusDB
{
namespace EDDBImpl
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

    void readWithoutType(RecordRepositoryReader& reader, Ishiko::Error& error);
    void write(RecordRepositoryWriter& writer, Ishiko::Error& error) const;

private:
    static void writeNode(RecordRepositoryWriter& writer, const SiblingNodeRecordGroup& node, Ishiko::Error& error);

private:
    NodeID m_parentNodeID;
    std::vector<SiblingNodeRecordGroup> m_siblings;
};

}
}

#endif

/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_MASTERFILE_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_MASTERFILE_HPP

#include "NodeID.hpp"
#include "Record.hpp"
#include "RecordFile.hpp"
#include "RecordMarker.hpp"
#include "SiblingNodesRecordGroup.hpp"
#include <boost/filesystem/path.hpp>
#include <DiplodocusDB/PhysicalStorage.hpp>
#include <Ishiko/Errors.hpp>
#include <fstream>
#include <memory>

namespace DiplodocusDB
{
namespace EDDBImpl
{

/// The master file where the database contents are physically stored.
/**
    The master file's low level format is built on top of the PageFileRepository class. This is essentially a series of
    pages of fixed size stored in a file. These pages are used to stored a series of records.

    The records are organized as shown in the tables below. The records are listed in the order in which they appear in
    the file.

    Top level file organization
    ---------------------------

    Records              | Description
    -------------------- | ----------------------------------------
    Master File Metadata | Information about the master file itself
    Data Start           | Indicates the start of the section containing the data for the nodes stored in the database
    Data section records | See the Data Section organization table below
    Data End             | Indicates the end of the section started by the Data Start record

    Data Section organization
    -------------------------

    The Data Section contains a series of records describing the nodes of the database. These records are organized in
    groups. The Data Section may contain zero or more of these groups. Each group has the format described in the table
    below.

    Records                   | Description
    ------------------------- | -----------------------------
    Sibling Nodes Start       | Indicates the start of a series of nodes that have the same parent
    Parent Node ID (optional) | Specifies the ID of the parent for the nodes
    Node data records         | See the Node Data organization table below
    Sibling Nodes End         | Indicates the end of a series of nodes that have the same parent

    The Parent Node ID is only omitted for the root node which by definition has no parent.

    Node Data organization
    ----------------------

    The Node Data contains a series of records describing the nodes that have the same parent node i.e. siblings. These
    records are organized in groups. The Node Data contains one or more of these groups. Each group has the format
    described in the table below.

    Records                         | Description
    ------------------------------- | -----------------------------
    Node Name                       | The name of the node
    Node ID (optional)              | The ID of the node
    Inline Value (optional)         | The value of the node (directly inlined in the node)
    Partial Inline Value (optional) | The value of the node (partially inlined)
    Remote Value Marker (optional)  | A marker indicating the value of the node is stored in another record

    The Node ID record can be omitted if the node doesn't need an ID or its ID can be deduced without explicitly
    recording it in the file. For instance the root node always has ID 1 and nodes that do not have children and whose
    value is stored entirely inline may not need an ID.

    At most one of the Inline Value, Partial Inline Value or Remote Value Marker records can be present. If none are
    present it means the node has no associated value (the value has type NULL).

    @see PageFileRepository
*/
class MasterFile : public RecordFile
{
public:
    /// Constructor.
    MasterFile();

    void create(const boost::filesystem::path& path, Ishiko::Error& error);
    void open(const boost::filesystem::path& path, Ishiko::Error& error);
    void close();

    // TODO : seems unused
    RecordMarker rootNodePosition() const;
    // TODO : can be marked private. Remove?
    RecordMarker dataEndPosition() const;

    bool findSiblingNodesRecordGroup(const NodeID& parentNodeID, SiblingNodesRecordGroup& siblingNodes,
        Ishiko::Error& error);
    /// Adds a sibling nodes record group to the file.
    /**
        This is a low-level function used to write a new record group to the file. This function should not be called
        if a record group with the same parent node ID is already present in the database.

        @param siblingNodes The data to store in the master file.
        @param error The result of the operation.
    */
    void addSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error);
    /// Updates a sibling nodes record group.
    /**
        @param error The result of the operation.
    */
    void updateSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error);
    bool removeSiblingNodesRecordGroup(const NodeID& parentNodeID, Ishiko::Error& error);

private:
    static void createRootNode(PhysicalStorage::PageRepositoryWriter& writer, Ishiko::Error& error);

private:
    PhysicalStorage::PageFileRepository2 m_repository;
    Record m_metadataRecord;
    size_t m_dataStartOffset;
    size_t m_dataEndPageIndex;
    size_t m_dataEndOffset;
};

}
}

#endif

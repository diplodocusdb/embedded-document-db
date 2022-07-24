/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_NODEID_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_NODEID_HPP_

#include <DiplodocusDB/PhysicalStorage/PageRepository.hpp>
#include <Ishiko/Errors.hpp>

namespace DiplodocusDB
{

/// The ID of a node.
/**
    The ID of a node is unique within the database. However the ID of a node may change during the lifetime of the
    node. Not every node is assigned an ID at creation.

    The root node has ID with numeric value 1. The numeric value 0 signifies an invalid node ID or the absence of a
    node ID.
*/
class NodeID
{
public:
    /// Constructor.
    /**
        The default constructor creates a node ID with numeric value 0. This is an invalid node ID.
    */
    NodeID();
    explicit NodeID(size_t value);

    /// Checks whether the node ID is valid.
    /**
        Any ID with a value different from 0 is valid.
    */
    bool isNull() const;

    bool operator==(const NodeID& other) const;
    bool operator!=(const NodeID& other) const;
    bool operator<(const NodeID& other) const;
    bool operator>(const NodeID& other) const;

    void read(PageRepositoryReader& reader, Ishiko::Error& error);
    void write(PageRepositoryWriter& writer, Ishiko::Error& error) const;

private:
    size_t m_value;
};

}

#endif

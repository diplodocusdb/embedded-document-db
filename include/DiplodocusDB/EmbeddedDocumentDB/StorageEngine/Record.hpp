/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORD_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORD_HPP

#include "MasterFileMetadata.hpp"
#include "NodeID.hpp"
#include <boost/variant.hpp>
#include <DiplodocusDB/Core.hpp>
#include <DiplodocusDB/PhysicalStorage.hpp>
#include <Ishiko/Errors.hpp>
#include <memory>
#include <string>

namespace DiplodocusDB
{

/// A record in physical storage.
/**
    The data in the physical storage of an EmbeddedTreeDB is stored as a series of records.
*/
class Record
{
public:
    /// The type of the record.
    /**
        The values of this enumeration can't be changed as they are used as identifiers in the physical file.
    */
    enum class ERecordType
    {
        /// Invalid record. 
        eInvalid = 0,
        /// Master file metadata record.
        eMasterFileMetadata = 0x01,
        /// Start of data marker record.
        eDataStart = 0x02,
        /// End of data marker record.
        eDataEnd = 0x03,
        /// Start marker for a series of sibling nodes record.
        eSiblingNodesStart = 0x04,
        /// End marker for a series of sibling nodes record.
        eSiblingNodesEnd = 0x05,
        /// Parent node ID record.
        /**
            This record specifies the ID of the parent of the current node. This record is present in every node
            except the root node.
        */
        eParentNodeID = 0x06,
        /// Node name record.
        eNodeName = 0x07,
        /// Node ID record.
        /**
            Note that the ID is not guaranteed to be constant during the lifetime of the node.
        */
        eNodeID = 0x08,
        /// Persistent node ID record.
        /**
            The ePersistentNodeID record is used instead of the eNodeID record when the node ID must not change during
            the lifetime of the node.

            By default node IDs are not guaranteed to stay the same during the lifetime of the node. There are cases
            where the implementation may change the ID of a node (for instance during a database rebuild or to optimize
            disk usage).
        */
        ePersistentNodeID = 0x09,
        /// Start marker for a series of sibling nodes record that has been deleted.
        eDeletedSiblingNodesStart = 0x0C,
        /// Node name record for a node that has been deleted.
        eDeletedNodeName = 0x0F,
        /// Value record.
        /**
            In this case the value is stored directly in the record itself. This is in general
            more suitable for values that do not take up too much storage space.
        */
        eInlineValue = 0x10,
        /// Value record.
        /**
            In this case the first bytes of the value are stored directly in the record itself
            but subsequent bytes are stored in another record that will have to be fetched separately if the entire
            value is needed.

            This type of value record provides a performance compromise between eInlineValue and eRemoteValue.
        */
        ePartialInlineValue = 0x11,
        /// Record marking that there is a value but it is stored in another record.
        /**
            This record is used to distinguish between the case where there is no value at all and the case where the
            value is stored elsewhere.
        */
        eRemoteValueMarker = 0x12,
        /// A value record that is stored on its own.
        /**
            This kind of record will contain the ID of the node as well as the value. It is typically used for values
            that take up a large amount of storage space.
        */
        eRemoteValue = 0x13,
        /// A series of free bytes.
        /**
            This record is used to occupy space in the file. It can be used to fill the space left by deleted records.
            It is followed by a count of the number of free bytes.
        */
        eFreeBytes = 0xFD,
        /// A single free byte.
        /**
            This record is used to occupy space in the file. It can be used to fill the space left by deleted records.
        */
        eFreeByte = 0xFE,
        /// Reserved for future use.
        /**
            This is meant as a way to encode the record type over 2 bytes in the unlikely event we need more types than
            can be encoded on a single byte.
        */
        eExtension = 0xFF
    };

    Record(ERecordType type);
    Record(ERecordType type, const NodeID& data);
    Record(ERecordType type, const Value& data);
    Record(const MasterFileMetadata& data);
    Record(const std::string& data);

    ERecordType type() const;
    const NodeID& asNodeID() const;
    const std::string& asString() const;
    const Value& asValue() const;

    void read(PhysicalStorage::PageRepositoryReader& reader, Ishiko::Error& error);
    void write(PhysicalStorage::PageRepositoryWriter& writer, Ishiko::Error& error) const;

private:
    Record::ERecordType m_type;
    boost::variant<MasterFileMetadata, NodeID, std::string, Value> m_data;
};

}

#endif

/*
    Copyright (c) 2018-2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#ifndef _DIPLODOCUSDB_TREEDB_EMBEDDEDTREEDB_RECORD_H_
#define _DIPLODOCUSDB_TREEDB_EMBEDDEDTREEDB_RECORD_H_

#include "DiplodocusDB/PhysicalStorage/PageRepository/PageRepositoryReader.h"
#include "DiplodocusDB/PhysicalStorage/PageRepository/PageRepositoryWriter.h"
#include "Ishiko/Errors/Error.h"
#include <memory>

namespace DiplodocusDB
{

class RecordData;

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
        /// Start of node marker record.
        eNodeStart = 0x04,
        /// End of node marker record.
        eNodeEnd = 0x05,
        /// Parent node ID record.
        /**
            This record specifies the ID of the parent of the current node. This record is present in every node
            except the root node.
        */
        eParentNodeID = 0x06,
        /// Node name record.
        eNodeName = 0x07,
        /// Node ID record.
        eNodeID = 0x08,
        /// Value record.
        /**
            In this case the value is stored directly in the record itself. This is in general
            more suitable for values that do not take up too much storage space.
        */
        eInlineValue = 0x09,
        /// Value record.
        /**
            In this case the first bytes of the value are stored directly in the record itself
            but subsequent bytes are stored in another record that will have to be fetched separately if the entire
            value is needed.

            This type of value record provides a performance compromise between eInlineValue and eRemoteValue.
        */
        ePartialInlineValue = 0x10,
        /// Record marking that there is a value but it is stored in another record.
        /**
            This record is used to distinguish between the case where there is no value at all and the case where the
            value is stored elsewhere.
        */
        eRemoteValueMarker = 0x11,
        /// A value record that is stored on its own.
        /**
            This kind of record will contain the ID of the node as well as the value. It is typically used for values
            that take up a large amount of storage space.
        */
        eRemoteValue = 0x12
    };

    Record(ERecordType type);
    Record(ERecordType type, std::shared_ptr<RecordData> data);
    ~Record();

    ERecordType type() const;
    size_t size() const;
    RecordData* data();

    void load(PageRepositoryReader& reader, Ishiko::Error& error);
    void save(PageRepositoryWriter& writer, Ishiko::Error& error) const;

private:
    Record::ERecordType m_type;
    std::shared_ptr<RecordData> m_data;
};

}

#endif

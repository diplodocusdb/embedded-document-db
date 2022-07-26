/*
    Copyright (c) 2019-2022 Xavier Leclercq

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

#ifndef _DIPLODOCUSDB_TREEDB_EMBEDDEDTREEDB_SIBLINGNODESRECORDGROUP_H_
#define _DIPLODOCUSDB_TREEDB_EMBEDDEDTREEDB_SIBLINGNODESRECORDGROUP_H_

#include "EmbeddedDocumentDBNodeImpl.hpp"
#include "DiplodocusDB/PhysicalStorage/PageRepository/PageRepositoryWriter.h"
#include <DiplodocusDB/EmbeddedDocumentDB/StorageEngine.hpp>
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
    explicit SiblingNodesRecordGroup(const EmbeddedDocumentDBNodeImpl& node);

    const NodeID& parentNodeID() const;
    const EmbeddedDocumentDBNodeImpl& operator[](size_t pos) const;
    /// Returns the number of sibling nodes in the record group.
    size_t size() const noexcept;
    void push_back(const EmbeddedDocumentDBNodeImpl& value);
    bool find(const std::string& name, EmbeddedDocumentDBNodeImpl& node);

    void readWithoutType(PageRepositoryReader& reader, Ishiko::Error& error);
    void write(PageRepositoryWriter& writer, Ishiko::Error& error) const;

private:
    static void writeNode(PageRepositoryWriter& writer, const EmbeddedDocumentDBNodeImpl& node, Ishiko::Error& error);

private:
    NodeID m_parentNodeID;
    std::vector<EmbeddedDocumentDBNodeImpl> m_siblings;
};

}

#endif

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

#ifndef _DIPLODOCUSDB_TREEDB_EMBEDDEDTREEDB_SIBLINGNODESRECORDGROUPCACHE_H_
#define _DIPLODOCUSDB_TREEDB_EMBEDDEDTREEDB_SIBLINGNODESRECORDGROUPCACHE_H_

#include <DiplodocusDB/EmbeddedDocumentDB/StorageEngine.hpp>
#include <map>
#include <memory>

namespace DiplodocusDB
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

#endif

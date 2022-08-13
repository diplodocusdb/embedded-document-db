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

#ifndef _DIPLODOCUSDB_TREEDB_EMBEDDEDTREEDB_EMBEDDEDTREEDBTRANSACTIONIMPL_H_
#define _DIPLODOCUSDB_TREEDB_EMBEDDEDTREEDB_EMBEDDEDTREEDBTRANSACTIONIMPL_H_

#include "TreeDBTransactionImpl.hpp"
#include "TreeDBNode.hpp"
#include <DiplodocusDB/Core.hpp>
#include <DiplodocusDB/EmbeddedDocumentDB/StorageEngine.hpp>
#include <Ishiko/Errors.hpp>
#include <string>
#include <vector>
#include <memory>

namespace DiplodocusDB
{

class EmbeddedTreeDBTransactionImpl : public TreeDBTransactionImpl
{
public:
    TreeDBNode appendChildNode(EDDBImpl::StorageEngine& storageEngine, TreeDBNode& parent, const std::string& name,
        const Value& value, Ishiko::Error& error);

    void commit(EDDBImpl::StorageEngine& storageEngine, Ishiko::Error& error);
    void rollback();

private:
    enum EFindResult
    {
        eNotFound,
        eFoundInNew,
        eFoundInUpdated,
        eFoundInCache
    };
    EFindResult findSiblingNodesRecordGroup(EDDBImpl::StorageEngine& storageEngine,
        const EDDBImpl::NodeID& parentNodeID, std::shared_ptr<EDDBImpl::SiblingNodesRecordGroup>& siblingNodes,
        Ishiko::Error& error);

private:
    // TODO : see comments about using shared pointers in SiblingNodesRecordGroupCache, the same may apply here
    std::vector<std::shared_ptr<EDDBImpl::SiblingNodesRecordGroup>> m_newSiblingNodesRecordGroups;
    std::vector<std::shared_ptr<EDDBImpl::SiblingNodesRecordGroup>> m_updatedSiblingNodesRecordGroups;
};

}

#endif

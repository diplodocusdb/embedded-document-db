/*
    Copyright (c) 2019 Xavier Leclercq

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

#include "EmbeddedTreeDBTransactionImpl.h"
#include "EmbeddedTreeDBImpl.h"

namespace DiplodocusDB
{

TreeDBNode EmbeddedTreeDBTransactionImpl::appendChildNode(RecordFilesSet& recordFiles, TreeDBNode& parent,
    const std::string& name, const TreeDBValue& value, Ishiko::Error& error)
{
    TreeDBNode result;

    EmbeddedTreeDBNodeImpl& parentNodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*parent.impl());
    result = TreeDBNode(std::make_shared<EmbeddedTreeDBNodeImpl>(parentNodeImpl.nodeID(), NodeID(0), name));
    EmbeddedTreeDBNodeImpl& nodeImpl = static_cast<EmbeddedTreeDBNodeImpl&>(*result.impl());
    nodeImpl.value() = value;

    std::shared_ptr<SiblingNodesRecordGroup> existingSiblingNodesRecordGroup;
    bool found = findSiblingNodesRecordGroup(recordFiles, parentNodeImpl.nodeID(), existingSiblingNodesRecordGroup,
        error);
    if (!error)
    {
        if (found)
        {
            existingSiblingNodesRecordGroup->push_back(nodeImpl);
            
            // TODO : add to m_updated... unless already in it or in m_new..
        }
        else
        {
            m_newSiblingNodesRecordGroups.emplace_back(std::make_shared<SiblingNodesRecordGroup>(nodeImpl));
        }
    }

    return result;
}

void EmbeddedTreeDBTransactionImpl::commit(RecordFilesSet& recordFiles, Ishiko::Error& error)
{
    // TODO : updated siblings

    for (std::shared_ptr<SiblingNodesRecordGroup>& siblingNodes : m_newSiblingNodesRecordGroups)
    {
        recordFiles.addSiblingNodesRecordGroup(*siblingNodes, error);
        if (error)
        {
            break;
        }
    }
}

void EmbeddedTreeDBTransactionImpl::rollback()
{
    // TODO
}

bool EmbeddedTreeDBTransactionImpl::findSiblingNodesRecordGroup(RecordFilesSet& recordFiles,
    const NodeID& parentNodeID, std::shared_ptr<SiblingNodesRecordGroup>& siblingNodes, Ishiko::Error& error)
{
    for (std::shared_ptr<SiblingNodesRecordGroup>& group : m_newSiblingNodesRecordGroups)
    {
        if (group->parentNodeID() == parentNodeID)
        {
            siblingNodes = group;
            return true;
        }
    }
    for (std::shared_ptr<SiblingNodesRecordGroup>& group : m_updatedSiblingNodesRecordGroups)
    {
        if (group->parentNodeID() == parentNodeID)
        {
            siblingNodes = group;
            return true;
        }
    }
    // TODO : this should be cached
    siblingNodes = std::make_shared<SiblingNodesRecordGroup>(parentNodeID);
    return recordFiles.findSiblingNodesRecordGroup(parentNodeID, *siblingNodes, error);
}

}

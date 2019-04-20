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

#include "CachedRecordFilesSet.h"

namespace DiplodocusDB
{

void CachedRecordFilesSet::createMasterFile(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_recordFiles.createMasterFile(path, error);
}

void CachedRecordFilesSet::openMasterFile(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_recordFiles.openMasterFile(path, error);
}

void CachedRecordFilesSet::close()
{
    m_recordFiles.close();
}

bool CachedRecordFilesSet::findSiblingNodesRecordGroup(const NodeID& parentNodeID,
    SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error)
{
    return m_recordFiles.findSiblingNodesRecordGroup(parentNodeID, siblingNodes, error);
}

void CachedRecordFilesSet::addSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes,
    Ishiko::Error& error)
{
    m_recordFiles.addSiblingNodesRecordGroup(siblingNodes, error);
}

void CachedRecordFilesSet::updateSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes,
    Ishiko::Error& error)
{
    m_recordFiles.updateSiblingNodesRecordGroup(siblingNodes, error);
}

}

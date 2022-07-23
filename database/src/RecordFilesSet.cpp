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

#include "RecordFilesSet.h"

namespace DiplodocusDB
{

void RecordFilesSet::createMasterFile(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_masterFile.create(path, error);
}

void RecordFilesSet::openMasterFile(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_masterFile.open(path, error);
}

void RecordFilesSet::close()
{
    m_masterFile.close();
}

bool RecordFilesSet::findSiblingNodesRecordGroup(const NodeID& parentNodeID, SiblingNodesRecordGroup& siblingNodes,
    Ishiko::Error& error)
{
    return m_masterFile.findSiblingNodesRecordGroup(parentNodeID, siblingNodes, error);
}

void RecordFilesSet::addSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error)
{
    m_masterFile.addSiblingNodesRecordGroup(siblingNodes, error);
}

void RecordFilesSet::updateSiblingNodesRecordGroup(const SiblingNodesRecordGroup& siblingNodes, Ishiko::Error& error)
{
    m_masterFile.updateSiblingNodesRecordGroup(siblingNodes, error);
}

}

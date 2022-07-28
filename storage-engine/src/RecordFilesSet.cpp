/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "RecordFilesSet.hpp"

using namespace DiplodocusDB;

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

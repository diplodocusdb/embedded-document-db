/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "RecordMarker.hpp"

using namespace DiplodocusDB;
using namespace DiplodocusDB::EDDBImpl;

RecordMarker::RecordMarker(const PhysicalStorage::PageRepositoryPosition& pos)
    : m_position(pos)
{
}

RecordMarker::~RecordMarker()
{
}

const PhysicalStorage::PageRepositoryPosition& RecordMarker::position() const
{
    return m_position;
}

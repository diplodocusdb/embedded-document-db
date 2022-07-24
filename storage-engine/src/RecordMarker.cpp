/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "RecordMarker.hpp"

using namespace DiplodocusDB;

RecordMarker::RecordMarker(const PageRepositoryPosition& pos)
    : m_position(pos)
{
}

RecordMarker::~RecordMarker()
{
}

const PageRepositoryPosition& RecordMarker::position() const
{
    return m_position;
}

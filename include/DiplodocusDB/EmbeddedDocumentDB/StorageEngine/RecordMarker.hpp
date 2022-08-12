/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDMARKER_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDMARKER_HPP

#include "DiplodocusDB/PhysicalStorage.hpp"

namespace DiplodocusDB
{

class RecordMarker
{
public:
    RecordMarker(const PhysicalStorage::PageRepositoryPosition& pos);
    ~RecordMarker();

    const PhysicalStorage::PageRepositoryPosition& position() const;

private:
    PhysicalStorage::PageRepositoryPosition m_position;
};

}

#endif

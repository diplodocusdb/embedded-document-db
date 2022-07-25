/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDMARKER_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDMARKER_HPP_

#include "DiplodocusDB/PhysicalStorage/PageRepository/PageRepositoryPosition.h"

namespace DiplodocusDB
{

class RecordMarker
{
public:
    RecordMarker(const PageRepositoryPosition& pos);
    ~RecordMarker();

    const PageRepositoryPosition& position() const;

private:
    PageRepositoryPosition m_position;
};

}

#endif
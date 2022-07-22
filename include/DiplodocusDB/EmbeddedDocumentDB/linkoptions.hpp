/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_LINKOPTIONS_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_LINKOPTIONS_HPP_

#ifdef _DEBUG
#pragma comment(lib, "DiplodocusEmbeddedDocumentDB-d.lib")
#else
#pragma comment(lib, "DiplodocusEmbeddedDocumentDB.lib")
#endif

#include <DiplodocusDB/Core/linkoptions.hpp>

#endif

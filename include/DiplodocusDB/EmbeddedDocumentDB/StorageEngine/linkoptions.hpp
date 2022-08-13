/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_LINKOPTIONS_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_LINKOPTIONS_HPP

#ifdef _DEBUG
#pragma comment(lib, "DiplodocusEmbeddedDocumentDBStorageEngine-d.lib")
#else
#pragma comment(lib, "DiplodocusEmbeddedDocumentDBStorageEngine.lib")
#endif

#endif

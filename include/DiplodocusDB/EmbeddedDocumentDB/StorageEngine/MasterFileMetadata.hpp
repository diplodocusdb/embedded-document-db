/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_MASTERFILEMETADATA_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_MASTERFILEMETADATA_HPP_

#include <DiplodocusDB/Core.hpp>
#include <DiplodocusDB/PhysicalStorage/PageRepository.hpp>

namespace DiplodocusDB
{

class MasterFileMetadata
{
public:
    MasterFileMetadata();

    void read(PageRepositoryReader& reader, Ishiko::Error& error);
    void write(PageRepositoryWriter& writer, Ishiko::Error& error) const;

private:
    VersionNumber m_fileFormatVersion;
};

}

#endif

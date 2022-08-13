/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_MASTERFILEMETADATA_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_MASTERFILEMETADATA_HPP

#include <DiplodocusDB/Core.hpp>
#include <DiplodocusDB/PhysicalStorage.hpp>

namespace DiplodocusDB
{
namespace EDDBImpl
{

class MasterFileMetadata
{
public:
    MasterFileMetadata();

    void read(PhysicalStorage::PageRepositoryReader& reader, Ishiko::Error& error);
    void write(PhysicalStorage::PageRepositoryWriter& writer, Ishiko::Error& error) const;

private:
    VersionNumber m_fileFormatVersion;
};

}
}

#endif

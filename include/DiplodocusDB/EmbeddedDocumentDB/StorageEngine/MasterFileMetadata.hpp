/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_MASTERFILEMETADATA_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_MASTERFILEMETADATA_HPP

#include "RecordRepositoryReader.hpp"
#include "RecordRepositoryWriter.hpp"
#include <DiplodocusDB/Core.hpp>

namespace DiplodocusDB
{
namespace EDDBImpl
{

class MasterFileMetadata
{
public:
    MasterFileMetadata();

    void read(RecordRepositoryReader& reader, Ishiko::Error& error);
    void write(RecordRepositoryWriter& writer, Ishiko::Error& error) const;

private:
    VersionNumber m_fileFormatVersion;
};

}
}

#endif

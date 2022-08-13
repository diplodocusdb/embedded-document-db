/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "MasterFileMetadata.hpp"

using namespace DiplodocusDB::EDDBImpl;

MasterFileMetadata::MasterFileMetadata()
    : m_fileFormatVersion(1, 0, 0)
{
}

void MasterFileMetadata::read(PhysicalStorage::PageRepositoryReader& reader, Ishiko::Error& error)
{
    // TODO: this needs to decode LEB128
    uint8_t size;
    reader.read((char*)&size, 1, error);
    if (!error)
    {
        // TODO
        char buffer[12];
        reader.read(buffer, 12, error);
    }
}

void MasterFileMetadata::write(PhysicalStorage::PageRepositoryWriter& writer, Ishiko::Error& error) const
{
    writer.writeLEB128(12, error);
    if (!error)
    {
        for (unsigned int v : m_fileFormatVersion.value())
        {
            writer.write((char*)&v, 4, error);
            if (error)
            {
                break;
            }
        }
    }
}

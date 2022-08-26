/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDREPOSITORYREADER_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDREPOSITORYREADER_HPP

#include "RecordPage.hpp"
#include <DiplodocusDB/PhysicalStorage.hpp>
#include <Ishiko/Errors.hpp>
#include <memory>

namespace DiplodocusDB
{
namespace EDDBImpl
{

class RecordRepository;

class RecordRepositoryReader
{
public:
    RecordRepositoryReader(RecordRepository& repository, const RecordPage& startPage, size_t startOffset);
    RecordRepositoryReader(RecordRepository& repository, size_t start_page_number, size_t startOffset,
        Ishiko::Error& error);

    PhysicalStorage::PageRepositoryPosition currentPosition() const;

    void read(char* buffer, size_t n, Ishiko::Error& error);
    size_t readLEB128(Ishiko::Error& error);

private:
    RecordRepository& m_repository;
    RecordPage m_currentPage;
    size_t m_currentOffset;
};

}
}

#endif

/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/physical-storage/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDREPOSITORYREADER_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDREPOSITORYREADER_HPP

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
    RecordRepositoryReader(RecordRepository& repository, std::shared_ptr<Page2> startPage, size_t startOffset);

    PageRepositoryPosition currentPosition() const;

    void read(char* buffer, size_t n, Ishiko::Error& error);
    size_t readLEB128(Ishiko::Error& error);

private:
    PageFileRepository2& m_repository;
    std::shared_ptr<Page2> m_currentPage;
    size_t m_currentOffset;
};

}
}

#endif

/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDREPOSITORYREADER_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDREPOSITORYREADER_HPP

#include "RecordPage.hpp"
#include "RecordPageWorkingSet.hpp"
#include <DiplodocusDB/PhysicalStorage.hpp>
#include <Ishiko/Errors.hpp>
#include <memory>

namespace DiplodocusDB
{
namespace EDDBImpl
{

class RecordRepositoryReader
{
public:
    RecordRepositoryReader(RecordPageWorkingSet& working_set, size_t start_page_number, size_t startOffset,
        Ishiko::Error& error);

    PhysicalStorage::PageRepositoryPosition currentPosition() const;

    void read(char* buffer, size_t n, Ishiko::Error& error);
    size_t readLEB128(Ishiko::Error& error);

private:
    RecordPageWorkingSet& m_working_set;
    std::shared_ptr<RecordPage> m_currentPage;
    size_t m_currentOffset;
};

}
}

#endif

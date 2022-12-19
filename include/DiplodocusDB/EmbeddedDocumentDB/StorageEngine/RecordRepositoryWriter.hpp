/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDREPOSITORYWRITER_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDREPOSITORYWRITER_HPP

#include "RecordPage.hpp"
#include "RecordPageWorkingSet.hpp"
#include <DiplodocusDB/PhysicalStorage.hpp>
#include <Ishiko/Errors.hpp>
#include <set>
#include <memory>

namespace DiplodocusDB
{
namespace EDDBImpl
{

class RecordRepositoryWriter
{
public:
    RecordRepositoryWriter(RecordPageWorkingSet& working_set, size_t start_page_number, size_t start_offset,
        Ishiko::Error& error);
    
    PhysicalStorage::PageRepositoryPosition currentPosition() const;

    void write(const char* buffer, size_t bufferSize, Ishiko::Error& error);
    void writeLEB128(size_t value, Ishiko::Error& error);

private:
    RecordPageWorkingSet& m_working_set;
    std::shared_ptr<RecordPage> m_currentPage;
    size_t m_currentOffset;
};

}
}

#endif

/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDPAGEWORKINGSET_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDPAGEWORKINGSET_HPP

#include "RecordPage.hpp"
#include "RecordRepository.hpp"
#include <Ishiko/Errors.hpp>
#include <map>
#include <memory>

namespace DiplodocusDB
{
namespace EDDBImpl
{

class RecordPageWorkingSet
{
public:
    /// Constructor.
    RecordPageWorkingSet(RecordRepository& repository);

    std::shared_ptr<RecordPage> get(size_t page_number, Ishiko::Error& error);

    void add(const RecordPage& page);

    // TODO: not sure whether this should be on the working set or on a separate interface
    std::shared_ptr<RecordPage> insertPageAfter(RecordPage& page, Ishiko::Error& error);

    // TODO: not sure if this should be here or on the storage engine
    void save(Ishiko::Error& error);

private:
    class Entry
    {
    public:
        Entry(const RecordPage& page);
        Entry(RecordPage&& page);

        std::shared_ptr<RecordPage> m_page;
    };

    RecordRepository& m_repository;
    std::map<size_t, Entry> m_pages;
};

}
}

#endif

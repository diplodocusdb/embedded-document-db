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

private:
    class Entry
    {
    public:
        Entry(RecordPage&& page);

        std::shared_ptr<RecordPage> m_page;
    };

    RecordRepository& m_repository;
    std::map<size_t, Entry> m_pages;
};

}
}

#endif

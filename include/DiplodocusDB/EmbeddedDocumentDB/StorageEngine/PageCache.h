/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_PAGECACHE_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_PAGECACHE_HPP

#include "RecordPage.hpp"
#include <map>
#include <memory>

namespace DiplodocusDB
{
namespace EDDBImpl
{

/// An in-memory cache for the pages.
class PageCache
{
public:
    /// Constructor.
    PageCache() = default;

    bool get(size_t index, std::shared_ptr<RecordPage>& page);
    void set(std::shared_ptr<RecordPage>& page);

private:
    std::map<size_t, std::shared_ptr<RecordPage>> m_pages;
};

}
}

#endif

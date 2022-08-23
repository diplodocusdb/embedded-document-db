/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/physical-storage/blob/main/LICENSE.txt
*/

#include "PageCache.h"

using namespace DiplodocusDB::EDDBImpl;

bool PageCache::get(size_t index, std::shared_ptr<RecordPage>& page)
{
    std::map<size_t, std::shared_ptr<RecordPage>>::iterator it = m_pages.find(index);
    if (it != m_pages.end())
    {
        page = it->second;
        return true;
    }
    else
    {
        return false;
    }
}

void PageCache::set(std::shared_ptr<RecordPage>& page)
{
    m_pages[page->number()] = page;
}

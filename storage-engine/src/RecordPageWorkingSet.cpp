/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "RecordPageWorkingSet.hpp"

using namespace DiplodocusDB::EDDBImpl;

bool RecordPageWorkingSet::get(size_t index, std::shared_ptr<RecordPage>& page)
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

void RecordPageWorkingSet::set(std::shared_ptr<RecordPage>& page)
{
    m_pages[page->number()] = page;
}

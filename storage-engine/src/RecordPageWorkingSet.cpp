/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "RecordPageWorkingSet.hpp"

using namespace DiplodocusDB::EDDBImpl;

RecordPageWorkingSet::RecordPageWorkingSet(RecordRepository& repository)
    : m_repository{repository}
{
}

std::shared_ptr<RecordPage> RecordPageWorkingSet::get(size_t page_number, Ishiko::Error& error)
{
    std::map<size_t, Entry>::iterator it = m_pages.find(page_number);
    if (it != m_pages.end())
    {
        return it->second.m_page;
    }
    else
    {
        RecordPage page = m_repository.page(page_number, error);
        if (!error)
        {
            std::pair<std::map<size_t, Entry>::iterator, bool> r =
                m_pages.insert({page_number, Entry{std::move(page)}});
            return r.first->second.m_page;
        }
        else
        {
            return std::shared_ptr<RecordPage>();
        }
    }
}


void RecordPageWorkingSet::add(const RecordPage& page)
{
    // TODO: what if page already exists?
    m_pages.insert({page.number(), Entry{page}});
}

void RecordPageWorkingSet::save(Ishiko::Error& error)
{
    for (const std::pair<size_t, Entry>& item : m_pages)
    {
        m_repository.store(*item.second.m_page, error);
    }
}

RecordPageWorkingSet::Entry::Entry(const RecordPage& page)
    : m_page{std::make_shared<RecordPage>(page)}
{
}

RecordPageWorkingSet::Entry::Entry(RecordPage&& page)
    : m_page{std::make_shared<RecordPage>(std::move(page))}
{
}

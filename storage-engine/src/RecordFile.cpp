/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "RecordFile.hpp"

using namespace DiplodocusDB;
using namespace DiplodocusDB::EDDBImpl;

void RecordFile::create(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_page_file.create(path, error);
}

void RecordFile::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_page_file.open(path, error);
}

void RecordFile::close()
{
    m_page_file.close();
}

size_t RecordFile::pageCount()
{
    return m_page_file.pageCount();
}

RecordPage RecordFile::page(size_t index, Ishiko::Error& error)
{
    return RecordPage::Load(m_page_file.load(index, error));
}

RecordPage RecordFile::allocatePage(Ishiko::Error& error)
{
    return RecordPage::Create(m_page_file.allocatePage(error));
}

RecordPage RecordFile::insertPageAfter(RecordPage& page, Ishiko::Error& error)
{
    RecordPage new_page = RecordPage::Create(m_page_file.allocatePage(error));
    if (!error)
    {
        new_page.setNextPage(page.nextPage());
        page.setNextPage(new_page.number());
    }
    return new_page;
}

void RecordFile::store(RecordPage& page, Ishiko::Error& error)
{
    page.store(m_page_file, error);
}

RecordRepositoryWriter RecordFile::insert(const PhysicalStorage::PageRepositoryPosition& pos, Ishiko::Error& error)
{
    return insert(pos.page(), pos.offset(), error);
}

RecordRepositoryWriter RecordFile::insert(size_t startPage, size_t offset, Ishiko::Error& error)
{
    RecordPage p = page(startPage, error);
    return insert(p, offset, error);
}

RecordRepositoryWriter RecordFile::insert(RecordPage& startPage, size_t offset, Ishiko::Error& error)
{
    return RecordRepositoryWriter(*this, startPage, offset);
}

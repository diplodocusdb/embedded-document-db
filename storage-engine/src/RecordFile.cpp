/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/physical-storage/blob/main/LICENSE.txt
*/

#include "RecordFile.hpp"

using namespace DiplodocusDB;
using namespace DiplodocusDB::EDDBImpl;

void RecordFile::create(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_page_file_repository.create(path, error);
}

void RecordFile::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_page_file_repository.open(path, error);
}

void RecordFile::close()
{
    m_page_file_repository.close();
}

size_t RecordFile::pageCount()
{
    return m_page_file_repository.pageCount();
}

std::shared_ptr<PhysicalStorage::Page2> RecordFile::page(size_t index, Ishiko::Error& error)
{
    return m_page_file_repository.page(index, error);
}

std::shared_ptr<PhysicalStorage::Page2> RecordFile::allocatePage(Ishiko::Error& error)
{
    return m_page_file_repository.allocatePage(error);
}

std::shared_ptr<PhysicalStorage::Page2> RecordFile::insertPageAfter(PhysicalStorage::Page2& page, Ishiko::Error& error)
{
    std::shared_ptr<PhysicalStorage::Page2> newPage = m_page_file_repository.allocatePage(error);
    if (!error)
    {
        newPage->init();
        newPage->setNextPage(page.nextPage());
        page.setNextPage(newPage->number());
    }
    return newPage;
}

void RecordFile::store(const PhysicalStorage::Page2& page, Ishiko::Error& error)
{
    m_page_file_repository.store(page, error);
}

RecordRepositoryReader RecordFile::read(const PhysicalStorage::PageRepositoryPosition& pos, Ishiko::Error& error)
{
    return read(pos.page(), pos.offset(), error);
}

RecordRepositoryReader RecordFile::read(size_t startPage, size_t offset, Ishiko::Error& error)
{
    std::shared_ptr<PhysicalStorage::Page2> p = page(startPage, error);
    return read(p, offset, error);
}

RecordRepositoryReader RecordFile::read(std::shared_ptr<PhysicalStorage::Page2> startPage, size_t offset,
    Ishiko::Error& error)
{
    return RecordRepositoryReader(*this, startPage, offset);
}

RecordRepositoryWriter RecordFile::insert(const PhysicalStorage::PageRepositoryPosition& pos, Ishiko::Error& error)
{
    return insert(pos.page(), pos.offset(), error);
}

RecordRepositoryWriter RecordFile::insert(size_t startPage, size_t offset, Ishiko::Error& error)
{
    std::shared_ptr<PhysicalStorage::Page2> p = page(startPage, error);
    return insert(p, offset, error);
}

RecordRepositoryWriter RecordFile::insert(std::shared_ptr<PhysicalStorage::Page2> startPage, size_t offset,
    Ishiko::Error& error)
{
    return RecordRepositoryWriter(*this, startPage, offset);
}

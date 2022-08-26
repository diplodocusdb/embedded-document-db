/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "RecordPage.hpp"
#include "StorageEngineErrorCategory.hpp"
#include <Ishiko/Errors.hpp>
#include <Ishiko/IO.hpp>
#include <sstream>

using namespace DiplodocusDB::EDDBImpl;

RecordPage::RecordPage()
    : m_page{0}
{
}

RecordPage RecordPage::Create(PhysicalStorage::Page&& page)
{
    size_t available_space = (PhysicalStorage::Page::sm_size - sm_startMarkerSize - sm_endMarkerSize);
    RecordPage new_page{std::move(page), 0, available_space, 0};
    new_page.m_page.zero();
    return new_page;
}

RecordPage RecordPage::Load(PhysicalStorage::Page&& page)
{
    size_t data_size = *((uint16_t*)(page.data.data() + 6));
    size_t available_space = PhysicalStorage::Page::sm_size - sm_startMarkerSize - sm_endMarkerSize - data_size;
    size_t next_page = *((uint32_t*)(page.data.data() + sm_startMarkerSize + data_size + 2));
    return RecordPage{std::move(page), data_size, available_space, next_page};
}

void RecordPage::store(PhysicalStorage::PageRepository& repository, Ishiko::Error& error)
{
    Ishiko::Byte* data_begin = m_page.data.data();
    memcpy(data_begin, "\xF0\x06\x00\x00\x00\x00", 6);
    *((uint16_t*)(data_begin + 6)) = (uint16_t)m_dataSize;
    memcpy(data_begin + sm_startMarkerSize + m_dataSize, "\xF1\x06\x00\x00\x00\x00\x00\x00", 8);
    *((uint32_t*)(data_begin + sm_startMarkerSize + m_dataSize + 2)) = m_nextPage;

    repository.store(m_page, error);
}

size_t RecordPage::number() const
{
    return m_page.number;
}

size_t RecordPage::dataSize() const
{
    return m_dataSize;
}

size_t RecordPage::maxDataSize() const
{
    return (PhysicalStorage::Page::sm_size - sm_startMarkerSize - sm_endMarkerSize);
}

size_t RecordPage::availableSpace() const
{
    return m_availableSpace;
}

size_t RecordPage::nextPage() const
{
    return m_nextPage;
}

void RecordPage::setNextPage(size_t index)
{
    m_nextPage = index;
}

void RecordPage::get(char* buffer, size_t pos, size_t n, Ishiko::Error& error) const
{
    if ((pos + n) <= m_dataSize)
    {
        memcpy(buffer, m_page.data.data() + sm_startMarkerSize + pos, n);
    }
    else
    {
        std::stringstream message;
        message << "Page::get (m_index: " << m_page.number << ", pos:" << pos << ", n:" << n
            << ") exceeds data size (m_datasize: " << m_dataSize << ")";
        Fail(error, StorageEngineErrorCategory::Value::generic_error, message.str(), __FILE__, __LINE__);
    }
}

void RecordPage::insert(const char* buffer, size_t bufferSize, size_t pos, Ishiko::Error& error)
{
    if (bufferSize <= m_availableSpace)
    {
        char* p = (char*)(m_page.data.data() + sm_startMarkerSize);
        if (pos != m_dataSize)
        {
            memmove(p + pos + bufferSize, p + pos, (m_dataSize - pos));
        }
        memcpy(p + pos, buffer, bufferSize);
        m_dataSize += bufferSize;
        m_availableSpace -= bufferSize;
    }
    else
    {
        // TODO : add page details
        Fail(error, StorageEngineErrorCategory::Value::generic_error, "Failed to insert page", __FILE__, __LINE__);
    }
}

void RecordPage::erase(size_t pos, size_t n, Ishiko::Error& error)
{
    Ishiko::Byte* data_start = m_page.data.data();
    memmove(data_start + sm_startMarkerSize + pos, data_start + sm_startMarkerSize + pos + n,
        m_dataSize + sm_endMarkerSize - pos - n);
    memset(data_start + sm_startMarkerSize + m_dataSize + sm_endMarkerSize - n, 0, n);
    m_dataSize -= n;
    m_availableSpace += n;
}

void RecordPage::moveTo(size_t pos, size_t n, RecordPage& targetPage, Ishiko::Error& error)
{
    targetPage.insert((const char*)(m_page.data.data() + sm_startMarkerSize + pos), n, 0, error);
    if (!error)
    {
        erase(pos, n, error);
    }
}

RecordPage::RecordPage(PhysicalStorage::Page&& page, size_t data_size, size_t available_space, size_t next_page)
    : m_page{std::move(page)}, m_dataSize(data_size), m_availableSpace(available_space), m_nextPage(next_page)
{
}

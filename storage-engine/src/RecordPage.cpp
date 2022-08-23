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

RecordPage::RecordPage(size_t number)
    : m_page(number), m_dataSize(0),
    m_availableSpace(PhysicalStorage::Page::sm_size - sm_startMarkerSize - sm_endMarkerSize), m_nextPage(0)
{
}

void RecordPage::init()
{
    m_page.init();
}

size_t RecordPage::number() const
{
    return m_page.number();
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
        memcpy(buffer, m_page.buffer().data() + sm_startMarkerSize + pos, n);
    }
    else
    {
        std::stringstream message;
        message << "Page::get (m_index: " << m_page.number() << ", pos:" << pos << ", n:" << n
            << ") exceeds data size (m_datasize: " << m_dataSize << ")";
        Fail(error, StorageEngineErrorCategory::Value::generic_error, message.str(), __FILE__, __LINE__);
    }
}

void RecordPage::insert(const char* buffer, size_t bufferSize, size_t pos, Ishiko::Error& error)
{
    if (bufferSize <= m_availableSpace)
    {
        char* p = (char*)(m_page.buffer().data() + sm_startMarkerSize);
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
    memmove(m_page.buffer().data() + sm_startMarkerSize + pos, m_page.buffer().data() + sm_startMarkerSize + pos + n,
        m_dataSize + sm_endMarkerSize - pos - n);
    memset(m_page.buffer().data() + sm_startMarkerSize + m_dataSize + sm_endMarkerSize - n, 0, n);
    m_dataSize -= n;
    m_availableSpace += n;
}

void RecordPage::moveTo(size_t pos, size_t n, RecordPage& targetPage, Ishiko::Error& error)
{
    targetPage.insert((const char*)(m_page.buffer().data() + sm_startMarkerSize + pos), n, 0, error);
    if (!error)
    {
        erase(pos, n, error);
    }
}

void RecordPage::write(PhysicalStorage::PageFileRepository& repository, Ishiko::Error& error) const
{
    repository.m_file.setFilePointer(m_page.number() * PhysicalStorage::Page::sm_size);
    if (!error)
    {
        memcpy(m_page.buffer().data(), "\xF0\x06\x00\x00\x00\x00", 6);
        *((uint16_t*)(m_page.buffer().data() + 6)) = (uint16_t)m_dataSize;
        memcpy(m_page.buffer().data() + sm_startMarkerSize + m_dataSize, "\xF1\x06\x00\x00\x00\x00\x00\x00", 8);
        *((uint32_t*)(m_page.buffer().data() + sm_startMarkerSize + m_dataSize + 2)) = m_nextPage;
        
        repository.m_file.write((const char*)m_page.buffer().data(), PhysicalStorage::Page::sm_size, error);
    }
}

void RecordPage::read(PhysicalStorage::PageFileRepository& repository, Ishiko::Error& error)
{
    repository.m_file.setFilePointer(m_page.number() * PhysicalStorage::Page::sm_size);
    if (!error)
    {
        size_t read_count = repository.m_file.read(PhysicalStorage::Page::sm_size, (char*)m_page.buffer().data(),
            error);
        if (!error)
        {
            if (read_count == PhysicalStorage::Page::sm_size)
            {
                m_dataSize = *((uint16_t*)(m_page.buffer().data() + 6));
                m_availableSpace = PhysicalStorage::Page::sm_size - sm_startMarkerSize - sm_endMarkerSize - m_dataSize;

                uint32_t nextPage = *((uint32_t*)(m_page.buffer().data() + sm_startMarkerSize + m_dataSize + 2));
                m_nextPage = nextPage;
            }
            else
            {
                // TODO
                Fail(error, StorageEngineErrorCategory::Value::generic_error, "", __FILE__, __LINE__);
            }
        }
    }
}

/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "RecordRepositoryWriter.hpp"

using namespace DiplodocusDB;
using namespace DiplodocusDB::EDDBImpl;

RecordRepositoryWriter::RecordRepositoryWriter(RecordPageWorkingSet& working_set, size_t start_page_number,
    size_t start_offset, Ishiko::Error& error)
    : m_working_set(working_set), m_currentPage(m_working_set.get(start_page_number, error)),
    m_currentOffset(start_offset)
{
}

PhysicalStorage::PageRepositoryPosition RecordRepositoryWriter::currentPosition() const
{
    return PhysicalStorage::PageRepositoryPosition(m_currentPage->number(), m_currentOffset);
}

void RecordRepositoryWriter::write(const char* buffer, size_t bufferSize, Ishiko::Error& error)
{
    if ((m_currentOffset + bufferSize) <= m_currentPage->maxDataSize())
    {
        // The new data can fit in the current page. We may have to move
        // existing data though.
        size_t availableSpace = m_currentPage->availableSpace();
        if (bufferSize <= availableSpace)
        {
            // The new data can fit in the current page without moving any
            // data.
            m_currentPage->insert(buffer, bufferSize, m_currentOffset, error);
            if (!error)
            {
                m_currentOffset += bufferSize;
            }
            // TODO: mark dirty
            //m_updatedPages.insert(m_currentPage);
        }
        else
        {
            // We need to move some data to a new page
            size_t nextPageIndex = m_currentPage->nextPage();
            std::shared_ptr<RecordPage> newPage;
            if (nextPageIndex != 0)
            {
                newPage = m_working_set.get(nextPageIndex, error);
            }
            else
            {
                // TODO
                // newPage = m_working_set.insertPageAfter(m_currentPage, error);
            }
            if (error)
            {
                return;
            }
            size_t spaceNeeded = (bufferSize - availableSpace);
            m_currentPage->moveTo(m_currentPage->dataSize() - spaceNeeded, spaceNeeded, *newPage, error);
            if (error)
            {
                return;
            }
            m_currentPage->insert(buffer, bufferSize, m_currentOffset, error);
            if (!error)
            {
                m_currentOffset += bufferSize;
            }
            // TODO
            //m_updatedPages.insert(&m_currentPage);
            //m_updatedPages.insert(&newPage);
        }
    }
    else
    {
        // Only part of the new data can fit in the current page. We have to
        // move any existing data to the next page.
        /* TODO
        size_t nextPageIndex = m_currentPage.nextPage();
        std::shared_ptr<RecordPage> newPage;
        if (nextPageIndex != 0)
        {
            newPage = m_working_set.get(nextPageIndex, error);
        }
        else
        {
            newPage = m_working_set.insertPageAfter(m_currentPage, error);
        }
        if (error)
        {
            return;
        }
        size_t spaceInCurrentPage = (m_currentPage->maxDataSize() - m_currentOffset);
        if (!error)
        {
            m_currentPage->moveTo(m_currentOffset, (m_currentPage->dataSize() - m_currentOffset), *newPage, error);
            if (!error)
            {
                write(buffer, m_currentPage->availableSpace(), error);
                if (!error)
                {
                    m_currentPage = std::move(newPage);
                    m_currentOffset = 0;
                    m_updatedPages.insert(&m_currentPage);
                    write(buffer + spaceInCurrentPage, bufferSize - spaceInCurrentPage, error);
                }
            }
        }*/
    }
}

void RecordRepositoryWriter::writeLEB128(size_t value, Ishiko::Error& error)
{
    while (true)
    {
        char byte = (value & 0x7F);
        value >>= 7;
        if (value == 0)
        {
            write(&byte, 1, error);
            break;
        }
        else
        {
            byte |= 0x80;
            write(&byte, 1, error);
        }
    }
}

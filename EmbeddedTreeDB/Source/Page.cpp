/*
    Copyright (c) 2018 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "Page.h"
#include "PageFileRepository.h"
#include "EndOfPageRecordData.h"
#include <sstream>

namespace DiplodocusDB
{

Page::Page(PageFileRepository& file,
           size_t index)
    : m_file(file), m_index(index), m_bufferSize(0),
    m_startOfPageRecordData(std::make_shared<StartOfPageRecordData>()),
    m_endOfPageRecord(std::make_shared<EndOfPageRecordData>())
{
}

Page::~Page()
{
}

char* Page::buffer()
{
    return m_buffer;
}

void Page::write(const char* buffer,
                 size_t bufferSize,
                 Ishiko::Error& error)
{
    if ((m_bufferSize + bufferSize + m_endOfPageRecord.size()) <= (sm_bufferCapacity))
    {
        memcpy(m_buffer + m_bufferSize, buffer, bufferSize);
        m_bufferSize += bufferSize;
    }
}

void Page::save(Ishiko::Error& error)
{
    std::fstream& file = m_file.file();

    file.seekp(m_index * sm_bufferCapacity);
    if (!file.good())
    {
        error = -1;
        return;
    }
    
    m_startOfPageRecordData->setSize(m_bufferSize);

    size_t tempBufferSize = m_bufferSize;
    m_bufferSize = 0;
    Record startOfPageRecord(m_startOfPageRecordData);
    startOfPageRecord.write(*this, error);

    m_bufferSize = tempBufferSize;
    m_endOfPageRecord.write(*this, error);
    m_bufferSize = tempBufferSize;

    file.write(m_buffer, sm_bufferCapacity);
    if (!file.good())
    {
        error = -1;
        return;
    }
}

void Page::init()
{
    memset(m_buffer, 0, sm_bufferCapacity);
    m_bufferSize = 10;
}

void Page::load(Ishiko::Error& error)
{
    std::fstream& file = m_file.file();

    file.seekg(m_index * sm_bufferCapacity);
    if (!file.good())
    {
        error = -1;
        return;
    }

    file.read(m_buffer, sm_bufferCapacity);
    if (!file.good())
    {
        error = -1;
        return;
    }

    m_bufferSize = *((uint32_t*)(m_buffer + 6));
}

}

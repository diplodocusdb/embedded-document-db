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

void Page::appendRecord(const Record& record,
                        Ishiko::Error& error)
{
    record.write(m_buffer + m_bufferSize);
    m_bufferSize += record.size();
}

void Page::save(Ishiko::Error& error)
{
    std::fstream& file = m_file.file();

    file.seekp(m_index * 4096);
    if (!file.good())
    {
        error = -1;
        return;
    }
    
    m_startOfPageRecordData->setSize(m_bufferSize);
    Record startOfPageRecord(m_startOfPageRecordData);
    char buf[100];
    startOfPageRecord.write(buf);
    file.write(buf, startOfPageRecord.size());
    if (!file.good())
    {
        error = -1;
        return;
    }

    file.write(m_buffer, m_bufferSize);
    if (!file.good())
    {
        error = -1;
        return;
    }

    m_endOfPageRecord.write(buf);
    file.write(buf, m_endOfPageRecord.size());
    if (!file.good())
    {
        error = -1;
        return;
    }

    memset(m_buffer + m_bufferSize, 0, 4096 - m_bufferSize - startOfPageRecord.size() - m_endOfPageRecord.size());
    file.write(m_buffer + m_bufferSize, 4096 - m_bufferSize - startOfPageRecord.size() - m_endOfPageRecord.size());
    if (!file.good())
    {
        error = -1;
        return;
    }
}

void Page::load(Ishiko::Error& error)
{
    std::fstream& file = m_file.file();

    file.seekg(m_index * 4096);
    if (!file.good())
    {
        error = -1;
        return;
    }

    char buffer[10];
    file.read(buffer, 10);
    if (!file.good())
    {
        error = -1;
        return;
    }

    file.read(m_buffer, 4086);
    if (!file.good())
    {
        error = -1;
        return;
    }

    m_bufferSize = *((uint32_t*)(buffer + 6));
}

}

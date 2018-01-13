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

#include "MasterFile.h"
#include "EmbeddedTreeDBNodeImpl.h"
#include "KeyRecordData.h"

namespace DiplodocusDB
{

MasterFile::MasterFile()
    : m_metadata(std::make_shared<MasterFileMetadata>()),
    m_pageCache(m_file)
{
}

MasterFile::~MasterFile()
{
}

void MasterFile::create(const boost::filesystem::path& path,
                        Ishiko::Error& error)
{
    std::fstream file(path.c_str(), std::fstream::out | std::fstream::binary);
    if (!file.good())
    {
        error = -1;
    }
    else
    {
        Page page(0);
        Record metadataRecord(m_metadata);
        page.appendRecord(metadataRecord, error);
        if (!error)
        {
            page.save(file, error);
        }
    }
    file.close();
}

void MasterFile::open(const boost::filesystem::path& path,
                      Ishiko::Error& error)
{
    m_file.open(path.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);
    if (!m_file.good())
    {
        error = -1;
    }
}

void MasterFile::close()
{
    m_file.close();
}

bool MasterFile::getNode(const TreeDBKey& key,
                         Ishiko::Error& error)
{
    bool result = false;
    size_t offset = 0;
    while (!result)
    {
        TreeDBKey readKey = readString(offset, error);
        if (error)
        {
            break;
        }
        if (readKey == key)
        {
            result = true;
        }
    }
    return result;
}

void MasterFile::commitNode(const EmbeddedTreeDBNodeImpl& node,
                            Ishiko::Error& error)
{
    Page* page = m_pageCache.page(0, error);
    if (!error)
    {
        std::shared_ptr<KeyRecordData> recordData = std::make_shared<KeyRecordData>(node.key());
        Record record(recordData);

        page->appendRecord(record, error);
        if (!error)
        {
            page->save(m_file, error);
        }
    }
}

std::string MasterFile::readString(size_t& offset,
                                   Ishiko::Error& error)
{
    std::string result;

    Page* page = m_pageCache.page(0, error);
    if (!error)
    {
        char* ptr = (page->buffer() + offset);
        uint32_t n = *((uint32_t*)ptr);
        result.assign(ptr + 4, n);

        offset += (4 + n);
    }

    return result;
}

}

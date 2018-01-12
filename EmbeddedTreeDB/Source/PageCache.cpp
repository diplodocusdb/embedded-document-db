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

#include "PageCache.h"

namespace DiplodocusDB
{

PageCache::PageCache(std::fstream& file)
    : m_file(file)
{
}

PageCache::~PageCache()
{
}

Page* PageCache::page(size_t i)
{
    Page* page = nullptr;
    std::map<size_t, std::shared_ptr<Page> >::iterator it = m_pages.find(i);
    if (it != m_pages.end())
    {
        page = it->second.get();
    }
    else
    {
        page = loadPage(i);
    }
    return page;
}

Page* PageCache::loadPage(size_t i)
{
    std::shared_ptr<Page> page = std::make_shared<Page>(i);
    page->load(m_file);
    m_pages.emplace(i, page);
    return page.get();
}

}
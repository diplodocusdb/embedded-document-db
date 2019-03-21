/*
    Copyright (c) 2019 Xavier Leclercq

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

#include "XMLTreeDB.h"
#include "XMLTreeDBImpl.h"

namespace DiplodocusDB
{

XMLTreeDB::XMLTreeDB()
    : m_impl(std::make_shared<XMLTreeDBImpl>())
{
}

XMLTreeDB::~XMLTreeDB()
{
}

void XMLTreeDB::create(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_impl->create(path, error);
}

void XMLTreeDB::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_impl->open(path, error);
}

void XMLTreeDB::close()
{
    m_impl->close();
}

TreeDBNode& XMLTreeDB::root()
{
    return m_impl->root();
}

TreeDBNode XMLTreeDB::insert(TreeDBNode& parent, size_t index, const TreeDBKey& key)
{
    return m_impl->insert(parent, index, key);
}

TreeDBNode XMLTreeDB::insertBefore(TreeDBNode& parent, const TreeDBNode& child, const TreeDBKey& key)
{
    return m_impl->insertBefore(parent, child, key);
}

TreeDBNode XMLTreeDB::insertAfter(TreeDBNode& parent, const TreeDBNode& child, const TreeDBKey& key)
{
    return m_impl->insertAfter(parent, child, key);
}

void XMLTreeDB::commitNode(TreeDBNode& node, Ishiko::Error& error)
{
    m_impl->commitNode(static_cast<XMLTreeDBNodeImpl&>(*node.impl()), error);
}

}

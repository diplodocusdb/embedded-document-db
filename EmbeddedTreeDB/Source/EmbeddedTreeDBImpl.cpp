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

#include "EmbeddedTreeDBImpl.h"
#include "EmbeddedTreeDBNodeImpl.h"

namespace DiplodocusDB
{

EmbeddedTreeDBImpl::EmbeddedTreeDBImpl()
{
}

EmbeddedTreeDBImpl::~EmbeddedTreeDBImpl()
{
}

void EmbeddedTreeDBImpl::create(const boost::filesystem::path& path,
                                Ishiko::Error& error)
{
    m_masterFile.create(path, error);
    if (!error)
    {
        m_root = std::make_shared<EmbeddedTreeDBNodeImpl>(shared_from_this(), "");
    }
}

void EmbeddedTreeDBImpl::open(const boost::filesystem::path& path,
                              Ishiko::Error& error)
{
    m_masterFile.open(path, error);
    if (!error)
    {
        m_root = std::make_shared<EmbeddedTreeDBNodeImpl>(shared_from_this(), "");
    }
}

void EmbeddedTreeDBImpl::close()
{
    m_masterFile.close();
}

TreeDBNode& EmbeddedTreeDBImpl::root()
{
    return *m_root;
}

std::shared_ptr<TreeDBNode> EmbeddedTreeDBImpl::createNode(const TreeDBKey& key)
{
    return std::make_shared<EmbeddedTreeDBNodeImpl>(shared_from_this(), key);
}

std::shared_ptr<TreeDBNode> EmbeddedTreeDBImpl::getNode(const TreeDBKey& key,
                                                        Ishiko::Error& error)
{
    std::shared_ptr<TreeDBNode> result;

    std::shared_ptr<EmbeddedTreeDBNodeImpl> temp = std::make_shared<EmbeddedTreeDBNodeImpl>(shared_from_this(), key);
    bool found = m_masterFile.findNode(key, *temp, error);
    if (!error && found)
    {
        result = temp;
    }
    return result;
}

void EmbeddedTreeDBImpl::commitNode(const EmbeddedTreeDBNodeImpl& node,
                                    Ishiko::Error& error)
{
    m_masterFile.commitNode(node, error);
}

}

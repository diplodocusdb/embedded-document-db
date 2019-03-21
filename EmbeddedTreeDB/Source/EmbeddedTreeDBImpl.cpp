/*
    Copyright (c) 2018-2019 Xavier Leclercq

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

void EmbeddedTreeDBImpl::create(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_masterFile.create(path, error);
    if (!error)
    {
        m_root = TreeDBNode(std::make_shared<EmbeddedTreeDBNodeImpl>("/", m_masterFile.rootNodePosition(), RecordMarker(PageRepositoryPosition(0, 0))));
    }
}

void EmbeddedTreeDBImpl::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_masterFile.open(path, error);
    if (!error)
    {
        m_root = TreeDBNode(std::make_shared<EmbeddedTreeDBNodeImpl>("/", m_masterFile.rootNodePosition(), RecordMarker(PageRepositoryPosition(0, 0))));
    }
}

void EmbeddedTreeDBImpl::close()
{
    m_masterFile.close();
}

TreeDBNode& EmbeddedTreeDBImpl::root()
{
    return m_root;
}

TreeDBNode EmbeddedTreeDBImpl::getNode(const TreeDBKey& key, Ishiko::Error& error)
{
    std::shared_ptr<EmbeddedTreeDBNodeImpl> temp = std::make_shared<EmbeddedTreeDBNodeImpl>(key,
        PageRepositoryPosition(0, 0), PageRepositoryPosition(0, 0));
    bool found = m_masterFile.findNode(key, *temp, error);
    return TreeDBNode(temp);
}

TreeDBNode EmbeddedTreeDBImpl::insertNode(const TreeDBKey& key, const RecordMarker& marker)
{
    return m_uncommittedNodes.createNode(key, marker);
}

TreeDBNode EmbeddedTreeDBImpl::appendNode(const EmbeddedTreeDBNodeImpl& parentNode, const TreeDBKey& key)
{
    return m_uncommittedNodes.createNode(key, m_masterFile.dataEndPosition());
}

bool EmbeddedTreeDBImpl::removeNode(const TreeDBKey& key,
                                    Ishiko::Error& error)
{
    return m_masterFile.removeNode(key, error);
}

void EmbeddedTreeDBImpl::commitNode(const EmbeddedTreeDBNodeImpl& node, Ishiko::Error& error)
{
    m_masterFile.addNode(node, error);
}

}

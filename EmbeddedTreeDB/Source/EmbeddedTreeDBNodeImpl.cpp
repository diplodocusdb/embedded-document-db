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

#include "EmbeddedTreeDBNodeImpl.h"
#include "EmbeddedTreeDBImpl.h"

namespace DiplodocusDB
{

EmbeddedTreeDBNodeImpl::EmbeddedTreeDBNodeImpl(std::shared_ptr<EmbeddedTreeDBImpl> db, const TreeDBKey& key,
    const RecordMarker& nodeMarker, const RecordMarker& childrenMarker)
    : TreeDBNodeImpl(key), m_db(db), m_nodeMarker(nodeMarker), m_childrenMarker(childrenMarker)
{
}

EmbeddedTreeDBNodeImpl::~EmbeddedTreeDBNodeImpl()
{
}

bool EmbeddedTreeDBNodeImpl::isRoot() const
{
    return key().isRoot();
}

TreeDBNode EmbeddedTreeDBNodeImpl::parent(Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

void EmbeddedTreeDBNodeImpl::children(std::vector<TreeDBNode>& children,
                                      Ishiko::Error& error)
{
    for (std::pair<std::string, std::shared_ptr<TreeDBNodeImpl> > item : m_children)
    {

    }
}

TreeDBNode EmbeddedTreeDBNodeImpl::child(const TreeDBKey& key, Ishiko::Error& error)
{
    return m_db->getNode(key, error);
}

TreeDBNode EmbeddedTreeDBNodeImpl::previousSibling(Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

TreeDBNode EmbeddedTreeDBNodeImpl::previousSibling(const TreeDBKey& key, Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

TreeDBNode EmbeddedTreeDBNodeImpl::nextSibling(Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

TreeDBNode EmbeddedTreeDBNodeImpl::nextSibling(const TreeDBKey& key, Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

TreeDBNode EmbeddedTreeDBNodeImpl::insert(const TreeDBKey& key, size_t index)
{
    return m_db->appendNode(*this, key);
}

TreeDBNode EmbeddedTreeDBNodeImpl::insertBefore(const TreeDBKey& key, TreeDBNode& child)
{
    return m_db->insertNode(key, std::static_pointer_cast<EmbeddedTreeDBNodeImpl>(child.impl())->marker());
}

TreeDBNode EmbeddedTreeDBNodeImpl::insertAfter(const TreeDBKey& key,
                                               TreeDBNode& child)
{
    return m_db->insertNode(key, std::static_pointer_cast<EmbeddedTreeDBNodeImpl>(child.impl())->marker());
}

TreeDBNode EmbeddedTreeDBNodeImpl::append(const TreeDBKey& key)
{
    return m_db->appendNode(*this, key);
}

TreeDBNode EmbeddedTreeDBNodeImpl::set(const TreeDBKey& key, Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

bool EmbeddedTreeDBNodeImpl::remove(const TreeDBKey& key,
                                    Ishiko::Error& error)
{
    return m_db->removeNode(key, error);
}

void EmbeddedTreeDBNodeImpl::removeAll(Ishiko::Error& error)
{
}

void EmbeddedTreeDBNodeImpl::commit(Ishiko::Error& error)
{
    m_db->commitNode(*this, error);
}

const RecordMarker& EmbeddedTreeDBNodeImpl::marker() const
{
    return m_nodeMarker;
}

void EmbeddedTreeDBNodeImpl::setMarker(const RecordMarker& marker)
{
    m_nodeMarker = marker;
}

}

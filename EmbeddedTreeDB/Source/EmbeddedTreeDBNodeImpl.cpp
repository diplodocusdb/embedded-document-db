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

#include "EmbeddedTreeDBNodeImpl.h"
#include "EmbeddedTreeDBImpl.h"

namespace DiplodocusDB
{

EmbeddedTreeDBNodeImpl::EmbeddedTreeDBNodeImpl(std::shared_ptr<EmbeddedTreeDBImpl> db,   
                                               const TreeDBKey& key,
                                               const PageRepositoryPosition& position)
    : m_db(db), m_key(key), m_position(position)
{
}

EmbeddedTreeDBNodeImpl::~EmbeddedTreeDBNodeImpl()
{
}

std::shared_ptr<TreeDBNode> EmbeddedTreeDBNodeImpl::child(const TreeDBKey& key,
                                                          Ishiko::Error& error)
{
    return m_db->getNode(key, error);
}

std::shared_ptr<TreeDBNode> EmbeddedTreeDBNodeImpl::insert(const TreeDBKey& key,
                                                           size_t index)
{
    return m_db->appendNode(key);
}

std::shared_ptr<TreeDBNode> EmbeddedTreeDBNodeImpl::insertBefore(const TreeDBKey& key,
                                                                 std::shared_ptr<TreeDBNode> child)
{
    return m_db->insertNode(key, std::static_pointer_cast<EmbeddedTreeDBNodeImpl>(child)->position());
}

std::shared_ptr<TreeDBNode> EmbeddedTreeDBNodeImpl::insertAfter(const TreeDBKey& key,
                                                                std::shared_ptr<TreeDBNode> child)
{
    return m_db->insertNode(key, std::static_pointer_cast<EmbeddedTreeDBNodeImpl>(child)->position());
}

std::shared_ptr<TreeDBNode> EmbeddedTreeDBNodeImpl::append(const TreeDBKey& key)
{
    return m_db->appendNode(key);
}

bool EmbeddedTreeDBNodeImpl::remove(const TreeDBKey& key,
                                    Ishiko::Error& error)
{
    return m_db->removeNode(key, error);
}

void EmbeddedTreeDBNodeImpl::commit(Ishiko::Error& error)
{
    m_db->commitNode(*this, error);
}

const TreeDBKey& EmbeddedTreeDBNodeImpl::key() const
{
    return m_key;
}

const PageRepositoryPosition& EmbeddedTreeDBNodeImpl::position() const
{
    return m_position;
}

void EmbeddedTreeDBNodeImpl::setPosition(const PageRepositoryPosition& pos)
{
    m_position = pos;
}

}

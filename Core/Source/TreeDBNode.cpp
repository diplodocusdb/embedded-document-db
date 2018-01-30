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

#include "TreeDBNode.h"
#include "TreeDBNodeImpl.h"

namespace DiplodocusDB
{

TreeDBNode::TreeDBNode(std::shared_ptr<TreeDBNodeImpl>& impl)
    : m_impl(impl)
{
}

TreeDBNode::~TreeDBNode()
{
}

const TreeDBValue& TreeDBNode::value() const
{
    return m_impl->value();
}

TreeDBValue& TreeDBNode::value()
{
    return m_impl->value();
}

bool TreeDBNode::isRoot() const
{
    return m_impl->isRoot();
}

std::shared_ptr<TreeDBNode> TreeDBNode::parent(Ishiko::Error& error)
{
    return m_impl->parent(error);
}

void TreeDBNode::children(std::vector<std::shared_ptr<TreeDBNode> >& children,
                          Ishiko::Error& error)
{
    m_impl->children(children, error);
}

std::shared_ptr<TreeDBNode> TreeDBNode::child(const TreeDBKey& key,
                                              Ishiko::Error& error)
{
    return m_impl->child(key, error);
}

std::shared_ptr<TreeDBNode> TreeDBNode::insert(const TreeDBKey& key,
                                               size_t index)
{
    return m_impl->insert(key, index);
}

std::shared_ptr<TreeDBNode> TreeDBNode::insertBefore(const TreeDBKey& key,
                                                     std::shared_ptr<TreeDBNode> child)
{
    return m_impl->insertBefore(key, child);
}

std::shared_ptr<TreeDBNode> TreeDBNode::insertAfter(const TreeDBKey& key,
                                                    std::shared_ptr<TreeDBNode> child)
{
    return m_impl->insertAfter(key, child);
}

std::shared_ptr<TreeDBNode> TreeDBNode::append(const TreeDBKey& key)
{
    return m_impl->append(key);
}

bool TreeDBNode::remove(const TreeDBKey& key,
                        Ishiko::Error& error)
{
    return m_impl->remove(key, error);
}

void TreeDBNode::commit(Ishiko::Error& error)
{
    m_impl->commit(error);
}

}

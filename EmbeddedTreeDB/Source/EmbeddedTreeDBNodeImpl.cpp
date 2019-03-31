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

EmbeddedTreeDBNodeImpl::EmbeddedTreeDBNodeImpl(const std::string& name, const RecordMarker& nodeMarker,
    const RecordMarker& childrenMarker)
    : TreeDBNodeImpl(name), m_nodeMarker(nodeMarker), m_childrenMarker(childrenMarker)
{
}

EmbeddedTreeDBNodeImpl::~EmbeddedTreeDBNodeImpl()
{
}

bool EmbeddedTreeDBNodeImpl::isRoot() const
{
    return (name() == "/");
}

void EmbeddedTreeDBNodeImpl::children(std::vector<TreeDBNode>& children, Ishiko::Error& error)
{
    // TODO
}

TreeDBNode EmbeddedTreeDBNodeImpl::child(const std::string& name, Ishiko::Error& error)
{
    /*
    std::shared_ptr<EmbeddedTreeDBImpl> db = m_db.lock();
    if (db)
    {
        return db->getNode(key, error);
    }*/

    // TODO : error
    TreeDBNode result;
    return result;
}

TreeDBNode EmbeddedTreeDBNodeImpl::previousSibling(Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

TreeDBNode EmbeddedTreeDBNodeImpl::previousSibling(const std::string& name, Ishiko::Error& error)
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

TreeDBNode EmbeddedTreeDBNodeImpl::nextSibling(const std::string& name, Ishiko::Error& error)
{
    // TODO
    TreeDBNode result;
    return result;
}

const NodeID& EmbeddedTreeDBNodeImpl::parentNodeID() const
{
    return m_parentNodeID;
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

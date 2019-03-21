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

#ifndef _DIPLODOCUSDB_TREEDB_EMBEDDEDTREEDB_EMBEDDEDTREEDBNODEIMPL_H_
#define _DIPLODOCUSDB_TREEDB_EMBEDDEDTREEDB_EMBEDDEDTREEDBNODEIMPL_H_

#include "RecordMarker.h"
#include "DiplodocusDB/TreeDB/Core/TreeDBNodeImpl.h"

namespace DiplodocusDB
{

class EmbeddedTreeDBImpl;

class EmbeddedTreeDBNodeImpl : public TreeDBNodeImpl
{
public:
    EmbeddedTreeDBNodeImpl(const TreeDBKey& key, const RecordMarker& nodeMarker, const RecordMarker& childrenMarker);
    ~EmbeddedTreeDBNodeImpl() override;

    bool isRoot() const override;
    TreeDBNode parent(Ishiko::Error& error) override;
    void children(std::vector<TreeDBNode>& children, Ishiko::Error& error) override;
    TreeDBNode child(const TreeDBKey& key, Ishiko::Error& error) override;
    TreeDBNode previousSibling(Ishiko::Error& error) override;
    TreeDBNode previousSibling(const TreeDBKey& key, Ishiko::Error& error) override;
    TreeDBNode nextSibling(Ishiko::Error& error) override;
    TreeDBNode nextSibling(const TreeDBKey& key, Ishiko::Error& error) override;
    TreeDBNode insert(const TreeDBKey& key, size_t index) override;
    TreeDBNode insertBefore(const TreeDBKey& key, TreeDBNode& child) override;
    TreeDBNode insertAfter(const TreeDBKey& key, TreeDBNode& child) override;
    TreeDBNode append(const TreeDBKey& key) override;
    TreeDBNode set(const TreeDBKey& key, Ishiko::Error& error) override;
    bool remove(const TreeDBKey& key, Ishiko::Error& error) override;
    void removeAll(Ishiko::Error& error) override;

    const RecordMarker& marker() const;
    void setMarker(const RecordMarker& marker);
    
private:
    RecordMarker m_nodeMarker;
    RecordMarker m_childrenMarker;
};

}

#endif

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

#ifndef _DIPLODOCUSDB_TREEDB_EMBEDDEDTREEDB_EMBEDDEDTREEDBNODEIMPL_H_
#define _DIPLODOCUSDB_TREEDB_EMBEDDEDTREEDB_EMBEDDEDTREEDBNODEIMPL_H_

#include "DiplodocusDB/TreeDB/Core/TreeDBNode.h"
#include "DiplodocusDB/PhysicalStorage/PageRepository/PageRepositoryPosition.h"

namespace DiplodocusDB
{

class EmbeddedTreeDBImpl;

class EmbeddedTreeDBNodeImpl : public TreeDBNode
{
public:
    EmbeddedTreeDBNodeImpl(std::shared_ptr<EmbeddedTreeDBImpl> db, const TreeDBKey& key,
        const PageRepositoryPosition& position);
    ~EmbeddedTreeDBNodeImpl() override;

    std::shared_ptr<TreeDBNode> child(const TreeDBKey& key, Ishiko::Error& error) override;
    std::shared_ptr<TreeDBNode> insert(const TreeDBKey& key, size_t index) override;
    std::shared_ptr<TreeDBNode> insertBefore(const TreeDBKey& key, std::shared_ptr<TreeDBNode> child) override;
    std::shared_ptr<TreeDBNode> insertAfter(const TreeDBKey& key, std::shared_ptr<TreeDBNode> child) override;
    std::shared_ptr<TreeDBNode> append(const TreeDBKey& key) override;
    bool remove(const TreeDBKey& key, Ishiko::Error& error) override;
    void commit(Ishiko::Error& error) override;

    const TreeDBKey& key() const;
    const PageRepositoryPosition& position() const;
    void setPosition(const PageRepositoryPosition& pos);
    
private:
    std::shared_ptr<EmbeddedTreeDBImpl> m_db;
    TreeDBKey m_key;
    PageRepositoryPosition m_position;
};

}

#endif

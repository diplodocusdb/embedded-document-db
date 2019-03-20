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

#ifndef _DIPLODOCUSDB_TREEDB_CORE_TREEDBNODEIMPL_H_
#define _DIPLODOCUSDB_TREEDB_CORE_TREEDBNODEIMPL_H_

#include "TreeDBKey.h"
#include "TreeDBValue.h"
#include "TreeDBNode.h"
#include "Ishiko/Errors/Error.h"
#include <vector>

namespace DiplodocusDB
{

class TreeDBNodeImpl
{
public:
    TreeDBNodeImpl(const TreeDBKey& key);
    virtual ~TreeDBNodeImpl();

    const TreeDBKey& key() const;
    const TreeDBValue& value() const;
    TreeDBValue& value();

    virtual bool isRoot() const = 0;
    virtual TreeDBNode parent(Ishiko::Error& error) = 0;
    virtual void children(std::vector<TreeDBNode>& children, Ishiko::Error& error) = 0;
    virtual TreeDBNode child(const TreeDBKey& key, Ishiko::Error& error) = 0;
    virtual TreeDBNode previousSibling(Ishiko::Error& error) = 0;
    virtual TreeDBNode previousSibling(const TreeDBKey& key, Ishiko::Error& error) = 0;
    virtual TreeDBNode nextSibling(Ishiko::Error& error) = 0;
    virtual TreeDBNode nextSibling(const TreeDBKey& key, Ishiko::Error& error) = 0;
    virtual TreeDBNode insert(const TreeDBKey& key, size_t index) = 0;
    virtual TreeDBNode insertBefore(const TreeDBKey& key, TreeDBNode& child) = 0;
    virtual TreeDBNode insertAfter(const TreeDBKey& key, TreeDBNode& child) = 0;
    virtual TreeDBNode append(const TreeDBKey& key) = 0;
    virtual TreeDBNode set(const TreeDBKey& key, Ishiko::Error& error) = 0;
    virtual bool remove(const TreeDBKey& key, Ishiko::Error& error) = 0;
    virtual void removeAll(Ishiko::Error& error) = 0;

private:
    TreeDBNodeImpl(const TreeDBNodeImpl& other) = delete;
    TreeDBNodeImpl& operator =(const TreeDBNodeImpl& other) = delete;

private:
    TreeDBKey m_key;
    TreeDBValue m_value;
};

}

#endif

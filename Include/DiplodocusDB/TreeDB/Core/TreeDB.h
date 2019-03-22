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

#ifndef _DIPLODOCUSDB_TREEDB_CORE_TREEDB_H_
#define _DIPLODOCUSDB_TREEDB_CORE_TREEDB_H_

#include "TreeDBNode.h"
#include "Ishiko/Errors/Error.h"

namespace DiplodocusDB
{

class TreeDB
{
public:
    virtual ~TreeDB() = default;

    virtual TreeDBNode& root() = 0;

    virtual TreeDBNode insert(TreeDBNode& parent, size_t index, const TreeDBKey& key, Ishiko::Error& error) = 0;
    virtual TreeDBNode insertBefore(TreeDBNode& parent, TreeDBNode& child, const TreeDBKey& key,
        Ishiko::Error& error) = 0;
    virtual TreeDBNode insertAfter(TreeDBNode& parent, TreeDBNode& child, const TreeDBKey& key,
        Ishiko::Error& error) = 0;

    // TODO : this is temporary until I have migrated all the node functions here
    virtual void commitNode(TreeDBNode& node, Ishiko::Error& error) = 0;
};

}

#endif

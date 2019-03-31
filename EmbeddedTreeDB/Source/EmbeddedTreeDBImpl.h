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

#ifndef _DIPLODOCUSDB_TREEDB_EMBEDDEDTREEDB_EMBEDDEDTREEDBIMPL_H_
#define _DIPLODOCUSDB_TREEDB_EMBEDDEDTREEDB_EMBEDDEDTREEDBIMPL_H_

#include "MasterFile.h"
#include "KeyCache.h"
#include "UncommittedNodes.h"
#include "RecordMarker.h"
#include "DiplodocusDB/TreeDB/Core/TreeDBNode.h"
#include "Ishiko/Errors/Error.h"
#include <boost/filesystem/path.hpp>

namespace DiplodocusDB
{

class EmbeddedTreeDBImpl
{
public:
    EmbeddedTreeDBImpl();
    ~EmbeddedTreeDBImpl();

    void create(const boost::filesystem::path& path, Ishiko::Error& error);
    void open(const boost::filesystem::path& path, Ishiko::Error& error);
    void close();

    TreeDBNode& root();

    TreeDBNode parent(TreeDBNode& node, Ishiko::Error& error);

    void setValue(TreeDBNode& node, const TreeDBValue& value, Ishiko::Error& error);

    TreeDBNode insertChildNode(TreeDBNode& parent, size_t index, const std::string& name, Ishiko::Error& error);
    TreeDBNode insertChildNode(TreeDBNode& parent, size_t index, const std::string& name, const TreeDBValue& value,
        Ishiko::Error& error);
    TreeDBNode insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
        Ishiko::Error& error);
    TreeDBNode insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
        const TreeDBValue& value, Ishiko::Error& error);
    TreeDBNode insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
        Ishiko::Error& error);
    TreeDBNode insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
        const TreeDBValue& value, Ishiko::Error& error);
    TreeDBNode appendChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error);
    TreeDBNode appendChildNode(TreeDBNode& parent, const std::string& name, const TreeDBValue& value,
        Ishiko::Error& error);
    TreeDBNode setChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error);
    TreeDBNode setChildNode(TreeDBNode& parent, const std::string& name, const TreeDBValue& value,
        Ishiko::Error& error);
    size_t removeChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error);
    size_t removeAllChildNodes(TreeDBNode& parent, Ishiko::Error& error);

    TreeDBNode getNode(const TreeDBKey& key, Ishiko::Error& error);
    TreeDBNode insertNode(const std::string& name, const RecordMarker& marker);
    TreeDBNode appendNode(const TreeDBKey& key);
    bool removeNode(const TreeDBKey& key, Ishiko::Error& error);
    void commitNode(const EmbeddedTreeDBNodeImpl& node, Ishiko::Error& error);

private:
    MasterFile m_masterFile;
    KeyCache m_keyCache;
    UncommittedNodes m_uncommittedNodes;
    TreeDBNode m_root;
};

}

#endif

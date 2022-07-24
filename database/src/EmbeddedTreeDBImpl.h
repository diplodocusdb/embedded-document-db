/*
    Copyright (c) 2018-2022 Xavier Leclercq

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

#include "CachedRecordFilesSet.h"
#include "TreeDB.hpp"
#include <boost/filesystem/path.hpp>
#include <DiplodocusDB/EmbeddedDocumentDB/StorageEngine.hpp>
#include <Ishiko/Errors.hpp>

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

    Value value(TreeDBNode& node, Ishiko::Error& error);
    Value value(TreeDBNode& node, const DataType& type, Ishiko::Error& error);
    Value childValue(TreeDBNode& parent, const std::string& name, Ishiko::Error& error);
    Value childValue(TreeDBNode& parent, const std::string& name, const DataType& type, Ishiko::Error& error);

    TreeDBNode parent(TreeDBNode& node, Ishiko::Error& error);
    std::vector<TreeDBNode> childNodes(TreeDBNode& parent, Ishiko::Error& error);
    TreeDBNode child(TreeDBNode& parent, const std::string& name, Ishiko::Error& error);
    TreeDBNode previousSibling(TreeDBNode& node, Ishiko::Error& error);
    TreeDBNode previousSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error);
    TreeDBNode nextSibling(TreeDBNode& node, Ishiko::Error& error);
    TreeDBNode nextSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error);

    void traverse(TreeDBNode& node, ETreeTraversalOrder order, void (*callback)(TreeDB& db, TreeDBNode& node),
        void* callbackData);

    TreeDBTransaction createTransaction(Ishiko::Error& error);
    void commitTransaction(TreeDBTransaction& transaction, Ishiko::Error& error);
    void rollbackTransaction(TreeDBTransaction& transaction);

    void setValue(TreeDBNode& node, const Value& value, Ishiko::Error& error);

    TreeDBNode insertChildNode(TreeDBNode& parent, size_t index, const std::string& name, Ishiko::Error& error);
    TreeDBNode insertChildNode(TreeDBNode& parent, size_t index, const std::string& name, const Value& value,
        Ishiko::Error& error);
    TreeDBNode insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
        Ishiko::Error& error);
    TreeDBNode insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
        const Value& value, Ishiko::Error& error);
    TreeDBNode insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
        Ishiko::Error& error);
    TreeDBNode insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
        const Value& value, Ishiko::Error& error);
    TreeDBNode appendChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error);
    TreeDBNode appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent, const std::string& name,
        Ishiko::Error& error);
    TreeDBNode appendChildNode(TreeDBNode& parent, const std::string& name, const Value& value,
        Ishiko::Error& error);
    TreeDBNode appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent, const std::string& name,
        const Value& value, Ishiko::Error& error);
    TreeDBNode setChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error);
    TreeDBNode setChildNode(TreeDBNode& parent, const std::string& name, const Value& value,
        Ishiko::Error& error);
    size_t removeChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error);
    size_t removeAllChildNodes(TreeDBNode& parent, Ishiko::Error& error);

private:
    CachedRecordFilesSet m_cachedRecordFiles;
    TreeDBNode m_root;
};

}

#endif

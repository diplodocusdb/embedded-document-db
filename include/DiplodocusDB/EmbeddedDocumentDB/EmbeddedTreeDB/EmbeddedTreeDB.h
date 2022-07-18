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

#ifndef _DIPLODOCUSDB_TREEDB_EMBEDDEDTREEDB_EMBEDDEDTREEDB_H_
#define _DIPLODOCUSDB_TREEDB_EMBEDDEDTREEDB_EMBEDDEDTREEDB_H_

#include "DiplodocusDB/TreeDB/Core/TreeDB.h"
#include "DiplodocusDB/TreeDB/Core/TreeDBNode.h"
#include "Ishiko/Errors/Error.h"
#include <boost/filesystem/path.hpp>
#include <memory>

namespace DiplodocusDB
{

class EmbeddedTreeDBImpl;

class EmbeddedTreeDB : public TreeDB
{
public:
    EmbeddedTreeDB();

    void create(const boost::filesystem::path& path, Ishiko::Error& error);
    void open(const boost::filesystem::path& path, Ishiko::Error& error);
    void close();

    TreeDBNode& root() override;

    TreeDBValue value(TreeDBNode& node, Ishiko::Error& error) override;
    TreeDBValue value(TreeDBNode& node, const DataType& type, Ishiko::Error& error) override;
    TreeDBValue childValue(TreeDBNode& parent, const std::string& name, Ishiko::Error& error) override;
    TreeDBValue childValue(TreeDBNode& parent, const std::string& name, const DataType& type,
        Ishiko::Error& error) override;

    TreeDBNode parent(TreeDBNode& node, Ishiko::Error& error) override;
    std::vector<TreeDBNode> childNodes(TreeDBNode& parent, Ishiko::Error& error) override;
    TreeDBNode child(TreeDBNode& parent, const std::string& name, Ishiko::Error& error) override;
    TreeDBNode previousSibling(TreeDBNode& node, Ishiko::Error& error) override;
    TreeDBNode previousSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error) override;
    TreeDBNode nextSibling(TreeDBNode& node, Ishiko::Error& error) override;
    TreeDBNode nextSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error) override;

    void traverse(TreeDBNode& node, ETreeTraversalOrder order, void (*callback)(TreeDB& db, TreeDBNode& node),
        void* callbackData) override;

    TreeDBTransaction createTransaction(Ishiko::Error& error) override;
    void commitTransaction(TreeDBTransaction& transaction, Ishiko::Error& error) override;
    void rollbackTransaction(TreeDBTransaction& transaction) override;

    void setValue(TreeDBNode& node, const TreeDBValue& value, Ishiko::Error& error) override;

    TreeDBNode insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
        Ishiko::Error& error) override;
    TreeDBNode insertChildNode(TreeDBNode& parent, size_t index, const std::string& name, const TreeDBValue& value,
        Ishiko::Error& error) override;
    TreeDBNode insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
        Ishiko::Error& error) override;
    TreeDBNode insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
        const TreeDBValue& value, Ishiko::Error& error) override;
    TreeDBNode insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
        Ishiko::Error& error) override;
    TreeDBNode insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
        const TreeDBValue& value, Ishiko::Error& error) override;
    TreeDBNode appendChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error) override;
    TreeDBNode appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent, const std::string& name,
        Ishiko::Error& error) override;
    TreeDBNode appendChildNode(TreeDBNode& parent, const std::string& name, const TreeDBValue& value,
        Ishiko::Error& error) override;
    TreeDBNode appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent, const std::string& name,
        const TreeDBValue& value, Ishiko::Error& error) override;
    TreeDBNode setChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error) override;
    TreeDBNode setChildNode(TreeDBNode& parent, const std::string& name, const TreeDBValue& value,
        Ishiko::Error& error) override;
    size_t removeChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error) override;
    size_t removeAllChildNodes(TreeDBNode& parent, Ishiko::Error& error) override;

private:
    std::shared_ptr<EmbeddedTreeDBImpl> m_impl;
};

}

#include "linkoptions.h"

#endif

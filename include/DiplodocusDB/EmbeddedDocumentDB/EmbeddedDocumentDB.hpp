/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_EMBEDDEDDOCUMENTDB_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_EMBEDDEDDOCUMENTDB_HPP_

#include "TreeDB.hpp"
#include "TreeDBNode.hpp"
#include <boost/filesystem/path.hpp>
#include <Ishiko/Errors.hpp>
#include <memory>

namespace DiplodocusDB
{

class EmbeddedDocumentDBImpl;

class EmbeddedDocumentDB : public TreeDB
{
public:
    EmbeddedDocumentDB();

    void create(const boost::filesystem::path& path, Ishiko::Error& error);
    void open(const boost::filesystem::path& path, Ishiko::Error& error);
    void close();

    TreeDBNode& root() override;

    Value value(TreeDBNode& node, Ishiko::Error& error) override;
    Value value(TreeDBNode& node, const DataType& type, Ishiko::Error& error) override;
    Value childValue(TreeDBNode& parent, const std::string& name, Ishiko::Error& error) override;
    Value childValue(TreeDBNode& parent, const std::string& name, const DataType& type,
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

    void setValue(TreeDBNode& node, const Value& value, Ishiko::Error& error) override;

    TreeDBNode insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
        Ishiko::Error& error) override;
    TreeDBNode insertChildNode(TreeDBNode& parent, size_t index, const std::string& name, const Value& value,
        Ishiko::Error& error) override;
    TreeDBNode insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
        Ishiko::Error& error) override;
    TreeDBNode insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
        const Value& value, Ishiko::Error& error) override;
    TreeDBNode insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
        Ishiko::Error& error) override;
    TreeDBNode insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
        const Value& value, Ishiko::Error& error) override;
    TreeDBNode appendChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error) override;
    TreeDBNode appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent, const std::string& name,
        Ishiko::Error& error) override;
    TreeDBNode appendChildNode(TreeDBNode& parent, const std::string& name, const Value& value,
        Ishiko::Error& error) override;
    TreeDBNode appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent, const std::string& name,
        const Value& value, Ishiko::Error& error) override;
    TreeDBNode setChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error) override;
    TreeDBNode setChildNode(TreeDBNode& parent, const std::string& name, const Value& value,
        Ishiko::Error& error) override;
    size_t removeChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error) override;
    size_t removeAllChildNodes(TreeDBNode& parent, Ishiko::Error& error) override;

private:
    std::shared_ptr<EmbeddedDocumentDBImpl> m_impl;
};

}

#endif

/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TREEDB_XMLTREEDB_XMLTREEDB_HPP_
#define _DIPLODOCUSDB_TREEDB_XMLTREEDB_XMLTREEDB_HPP_

#include "TreeDB.hpp"
#include <boost/filesystem/path.hpp>
#include <Ishiko/Errors.hpp>
#include <memory>

namespace DiplodocusDB
{

class XMLTreeDBImpl;

class XMLTreeDB
{
public:
    XMLTreeDB();
    ~XMLTreeDB();

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
    TreeDBNode appendChildNode(TreeDBNode& parent, const std::string& name, const Value& value, Ishiko::Error& error);
    TreeDBNode setChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error);
    TreeDBNode setChildNode(TreeDBNode& parent, const std::string& name, const Value& value, Ishiko::Error& error);
    size_t removeChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error);
    size_t removeAllChildNodes(TreeDBNode& parent, Ishiko::Error& error);

private:
    std::shared_ptr<XMLTreeDBImpl> m_impl;
};

}

#endif

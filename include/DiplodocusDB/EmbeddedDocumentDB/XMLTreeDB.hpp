/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TREEDB_XMLTREEDB_XMLTREEDB_HPP_
#define _DIPLODOCUSDB_TREEDB_XMLTREEDB_XMLTREEDB_HPP_

#include "XMLTreeDBNode.hpp"
#include <boost/filesystem/path.hpp>
#include <DiplodocusDB/Core.hpp>
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

    XMLTreeDBNode& root();

    Value value(XMLTreeDBNode& node, Ishiko::Error& error);
    Value value(XMLTreeDBNode& node, const DataType& type, Ishiko::Error& error);
    Value childValue(XMLTreeDBNode& parent, const std::string& name, Ishiko::Error& error);
    Value childValue(XMLTreeDBNode& parent, const std::string& name, const DataType& type, Ishiko::Error& error);

    XMLTreeDBNode parent(XMLTreeDBNode& node, Ishiko::Error& error);
    std::vector<XMLTreeDBNode> childNodes(XMLTreeDBNode& parent, Ishiko::Error& error);
    XMLTreeDBNode child(XMLTreeDBNode& parent, const std::string& name, Ishiko::Error& error);
    XMLTreeDBNode previousSibling(XMLTreeDBNode& node, Ishiko::Error& error);
    XMLTreeDBNode previousSibling(XMLTreeDBNode& node, const std::string& name, Ishiko::Error& error);
    XMLTreeDBNode nextSibling(XMLTreeDBNode& node, Ishiko::Error& error);
    XMLTreeDBNode nextSibling(XMLTreeDBNode& node, const std::string& name, Ishiko::Error& error);

    void setValue(XMLTreeDBNode& node, const Value& value, Ishiko::Error& error);

    XMLTreeDBNode insertChildNode(XMLTreeDBNode& parent, size_t index, const std::string& name, Ishiko::Error& error);
    XMLTreeDBNode insertChildNode(XMLTreeDBNode& parent, size_t index, const std::string& name, const Value& value,
        Ishiko::Error& error);
    XMLTreeDBNode appendChildNode(XMLTreeDBNode& parent, const std::string& name, Ishiko::Error& error);
    XMLTreeDBNode appendChildNode(XMLTreeDBNode& parent, const std::string& name, const Value& value,
        Ishiko::Error& error);
    XMLTreeDBNode setChildNode(XMLTreeDBNode& parent, const std::string& name, Ishiko::Error& error);
    XMLTreeDBNode setChildNode(XMLTreeDBNode& parent, const std::string& name, const Value& value,
        Ishiko::Error& error);
    size_t removeChildNode(XMLTreeDBNode& parent, const std::string& name, Ishiko::Error& error);
    size_t removeAllChildNodes(XMLTreeDBNode& parent, Ishiko::Error& error);

private:
    std::shared_ptr<XMLTreeDBImpl> m_impl;
};

}

#endif

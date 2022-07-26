/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TREEDB_XMLTREEDB_XMLTREEDBNODEIMPL_HPP_
#define _DIPLODOCUSDB_TREEDB_XMLTREEDB_XMLTREEDBNODEIMPL_HPP_

#include "XMLTreeDBNode.hpp"
#include <DiplodocusDB/Core.hpp>
#include <Ishiko/Errors.hpp>
#include <pugixml.hpp>
#include <memory>
#include <string>
#include <vector>

namespace DiplodocusDB
{

class XMLTreeDBNodeImpl : public std::enable_shared_from_this<XMLTreeDBNodeImpl>
{
public:
    XMLTreeDBNodeImpl(XMLTreeDBNodeImpl* parent, pugi::xml_node node);
    ~XMLTreeDBNodeImpl();

    const std::string& name() const;
    const Value& value() const;
    Value& value();
    bool isRoot() const;
    XMLTreeDBNode parent(Ishiko::Error& error);
    std::vector<XMLTreeDBNode> childNodes(Ishiko::Error& error);
    XMLTreeDBNode child(const std::string& name, Ishiko::Error& error);
    XMLTreeDBNode previousSibling(Ishiko::Error& error);
    XMLTreeDBNode previousSibling(const std::string& name, Ishiko::Error& error);
    XMLTreeDBNode nextSibling(Ishiko::Error& error);
    XMLTreeDBNode nextSibling(const std::string& name, Ishiko::Error& error);
    XMLTreeDBNode insertChildNode(size_t index, const std::string& name, const Value& value, Ishiko::Error& error);
    XMLTreeDBNode appendChildNode(const std::string& name, const Value& value, Ishiko::Error& error);
    XMLTreeDBNode setChildNode(const std::string& name, const Value& value, Ishiko::Error& error);
    size_t removeChildNode(const std::string& name, Ishiko::Error& error);
    size_t removeAllChildNodes(Ishiko::Error& error);

    void updateValue();

private:
    void loadChildren(Ishiko::Error& error);

private:
    std::string m_name;
    Value m_value;
    XMLTreeDBNodeImpl* m_parent;
    pugi::xml_node m_node;
    std::vector<std::shared_ptr<XMLTreeDBNodeImpl>> m_children;
};

}

#endif

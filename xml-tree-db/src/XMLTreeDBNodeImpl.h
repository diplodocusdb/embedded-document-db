/*
    Copyright (c) 2019 Xavier Leclercq
    Released under the MIT License
    See https://github.com/DiplodocusDB/TreeDB/blob/master/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TREEDB_XMLTREEDB_XMLTREEDBNODEIMPL_H_
#define _DIPLODOCUSDB_TREEDB_XMLTREEDB_XMLTREEDBNODEIMPL_H_

#include "DiplodocusDB/TreeDB/Core/TreeDBNodeImpl.h"
#include <pugixml.hpp>

namespace DiplodocusDB
{

class XMLTreeDBImpl;

class XMLTreeDBNodeImpl : public TreeDBNodeImpl, public std::enable_shared_from_this<XMLTreeDBNodeImpl>
{
public:
    XMLTreeDBNodeImpl(XMLTreeDBNodeImpl* parent, pugi::xml_node node);
    ~XMLTreeDBNodeImpl() override;

    bool isRoot() const override;
    TreeDBNode parent(Ishiko::Error& error);
    std::vector<TreeDBNode> childNodes(Ishiko::Error& error);
    TreeDBNode child(const std::string& name, Ishiko::Error& error);
    TreeDBNode previousSibling(Ishiko::Error& error);
    TreeDBNode previousSibling(const std::string& name, Ishiko::Error& error);
    TreeDBNode nextSibling(Ishiko::Error& error);
    TreeDBNode nextSibling(const std::string& name, Ishiko::Error& error);
    TreeDBNode insertChildNode(size_t index, const std::string& name, const TreeDBValue& value, Ishiko::Error& error);
    TreeDBNode insertChildNodeBefore(const TreeDBNode& nextChild, const std::string& name, const TreeDBValue& value,
        Ishiko::Error& error);
    TreeDBNode insertChildNodeAfter(const TreeDBNode& previousChild, const std::string& name, const TreeDBValue& value,
        Ishiko::Error& error);
    TreeDBNode appendChildNode(const std::string& name, const TreeDBValue& value, Ishiko::Error& error);
    TreeDBNode setChildNode(const std::string& name, const TreeDBValue& value, Ishiko::Error& error);
    size_t removeChildNode(const std::string& name, Ishiko::Error& error);
    size_t removeAllChildNodes(Ishiko::Error& error);

    void updateValue();

private:
    void loadChildren(Ishiko::Error& error);

private:
    XMLTreeDBNodeImpl* m_parent;
    pugi::xml_node m_node;
    std::vector<std::shared_ptr<XMLTreeDBNodeImpl>> m_children;
};

}

#endif

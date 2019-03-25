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
    TreeDBNode parent(Ishiko::Error& error) override;
    void children(std::vector<TreeDBNode>& children, Ishiko::Error& error) override;
    TreeDBNode child(const TreeDBKey& key, Ishiko::Error& error) override;
    TreeDBNode previousSibling(Ishiko::Error& error) override;
    TreeDBNode previousSibling(const TreeDBKey& key, Ishiko::Error& error) override;
    TreeDBNode nextSibling(Ishiko::Error& error) override;
    TreeDBNode nextSibling(const TreeDBKey& key, Ishiko::Error& error) override;
    TreeDBNode insertChildNode(size_t index, const std::string& name, const TreeDBValue& value, Ishiko::Error& error);
    TreeDBNode insertChildNodeBefore(const TreeDBNode& nextChild, const std::string& name, const TreeDBValue& value,
        Ishiko::Error& error);
    TreeDBNode insertChildNodeAfter(const TreeDBNode& previousChild, const std::string& name, Ishiko::Error& error);
    TreeDBNode appendChildNode(const std::string& name, Ishiko::Error& error);
    TreeDBNode setChildNode(const std::string& name, Ishiko::Error& error);
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

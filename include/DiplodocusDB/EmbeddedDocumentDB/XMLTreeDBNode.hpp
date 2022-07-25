/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TREEDB_CORE_XMLTREEDBNODE_HPP_
#define _DIPLODOCUSDB_TREEDB_CORE_XMLTREEDBNODE_HPP_

#include <Ishiko/Errors.hpp>
#include <string>
#include <vector>
#include <memory>

namespace DiplodocusDB
{

class XMLTreeDBNodeImpl;

class XMLTreeDBNode
{
public:
    XMLTreeDBNode() = default;
    XMLTreeDBNode(std::shared_ptr<XMLTreeDBNodeImpl> impl);

    explicit operator bool() const;
    bool operator !() const;
    bool operator ==(const XMLTreeDBNode& other) const;
    bool operator !=(const XMLTreeDBNode& other) const;

    const std::string& name() const;

    bool isRoot() const;

    std::shared_ptr<XMLTreeDBNodeImpl>& impl();

private:
    std::shared_ptr<XMLTreeDBNodeImpl> m_impl;
};

}

#endif

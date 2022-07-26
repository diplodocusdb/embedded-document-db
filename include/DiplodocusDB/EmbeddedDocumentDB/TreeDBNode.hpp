/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TREEDB_CORE_TREEDBNODE_HPP_
#define _DIPLODOCUSDB_TREEDB_CORE_TREEDBNODE_HPP_

#include <Ishiko/Errors.hpp>
#include <string>
#include <vector>
#include <memory>

namespace DiplodocusDB
{

class EmbeddedDocumentDBNodeImpl;

class TreeDBNode
{
public:
    TreeDBNode() = default;
    TreeDBNode(std::shared_ptr<EmbeddedDocumentDBNodeImpl> impl);

    explicit operator bool() const;
    bool operator !() const;
    bool operator ==(const TreeDBNode& other) const;
    bool operator !=(const TreeDBNode& other) const;

    const std::string& name() const;

    bool isRoot() const;

    std::shared_ptr<EmbeddedDocumentDBNodeImpl>& impl();

private:
    std::shared_ptr<EmbeddedDocumentDBNodeImpl> m_impl;
};

}

#endif

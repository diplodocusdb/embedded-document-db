/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TREEDB_CORE_TREEDBNODEIMPL_HPP_
#define _DIPLODOCUSDB_TREEDB_CORE_TREEDBNODEIMPL_HPP_

#include "TreeDBValue.hpp"
#include "TreeDBNode.hpp"
#include <Ishiko/Errors.hpp>
#include <vector>

namespace DiplodocusDB
{

class TreeDBNodeImpl
{
public:
    TreeDBNodeImpl(const std::string& name);
    virtual ~TreeDBNodeImpl() noexcept = default;

    const std::string& name() const;
    const TreeDBValue& value() const;
    TreeDBValue& value();

    virtual bool isRoot() const = 0;

private:
    std::string m_name;
    TreeDBValue m_value;
};

}

#endif

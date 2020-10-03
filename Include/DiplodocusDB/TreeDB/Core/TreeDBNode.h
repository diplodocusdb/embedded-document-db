/*
    Copyright (c) 2018-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/DiplodocusDB/TreeDB/blob/master/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TREEDB_CORE_TREEDBNODE_H_
#define _DIPLODOCUSDB_TREEDB_CORE_TREEDBNODE_H_

#include "TreeDBValue.h"
#include "Ishiko/Errors/Error.h"
#include <string>
#include <vector>
#include <memory>

namespace DiplodocusDB
{

class TreeDBNodeImpl;

class TreeDBNode
{
public:
    TreeDBNode() = default;
    TreeDBNode(std::shared_ptr<TreeDBNodeImpl> impl);

    explicit operator bool() const;
    bool operator !() const;
    bool operator ==(const TreeDBNode& other) const;
    bool operator !=(const TreeDBNode& other) const;

    const std::string& name() const;

    bool isRoot() const;

    std::shared_ptr<TreeDBNodeImpl>& impl();

private:
    std::shared_ptr<TreeDBNodeImpl> m_impl;
};

}

#include "linkoptions.h"

#endif

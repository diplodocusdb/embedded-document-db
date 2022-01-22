/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TREEDB_CORE_TREEDBTRANSACTION_HPP_
#define _DIPLODOCUSDB_TREEDB_CORE_TREEDBTRANSACTION_HPP_

#include <memory>

namespace DiplodocusDB
{

class TreeDBTransactionImpl;

class TreeDBTransaction
{
public:
    TreeDBTransaction(std::shared_ptr<TreeDBTransactionImpl> impl);

    std::shared_ptr<TreeDBTransactionImpl>& impl();

private:
    std::shared_ptr<TreeDBTransactionImpl> m_impl;
};

}

#endif

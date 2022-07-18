/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "TreeDBTransaction.hpp"

namespace DiplodocusDB
{

TreeDBTransaction::TreeDBTransaction(std::shared_ptr<TreeDBTransactionImpl> impl)
    : m_impl(impl)
{
}

std::shared_ptr<TreeDBTransactionImpl>& TreeDBTransaction::impl()
{
    return m_impl;
}

}

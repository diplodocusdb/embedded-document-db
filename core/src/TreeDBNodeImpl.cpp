/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "TreeDBNodeImpl.hpp"

namespace DiplodocusDB
{

TreeDBNodeImpl::TreeDBNodeImpl(const std::string& name)
    : m_name(name)
{
}

const std::string& TreeDBNodeImpl::name() const
{
    return m_name;
}

const TreeDBValue& TreeDBNodeImpl::value() const
{
    return m_value;
}

TreeDBValue& TreeDBNodeImpl::value()
{
    return m_value;
}

}

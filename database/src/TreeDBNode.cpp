/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "TreeDBNode.hpp"
#include "TreeDBNodeImpl.hpp"

namespace DiplodocusDB
{

TreeDBNode::TreeDBNode(std::shared_ptr<TreeDBNodeImpl> impl)
    : m_impl(impl)
{
}

TreeDBNode::operator bool() const
{
    return static_cast<bool>(m_impl);
}

bool TreeDBNode::operator !() const
{
    return !m_impl;
}

bool TreeDBNode::operator ==(const TreeDBNode& other) const
{
    return (m_impl == other.m_impl);
}

bool TreeDBNode::operator !=(const TreeDBNode& other) const
{
    return (m_impl != other.m_impl);
}

const std::string& TreeDBNode::name() const
{
    return m_impl->name();
}

bool TreeDBNode::isRoot() const
{
    return m_impl->isRoot();
}

std::shared_ptr<TreeDBNodeImpl>& TreeDBNode::impl()
{
    return m_impl;
}

}

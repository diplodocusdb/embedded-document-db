/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "XMLTreeDBNode.hpp"
#include "TreeDBNodeImpl.hpp"

using namespace DiplodocusDB;

XMLTreeDBNode::XMLTreeDBNode(std::shared_ptr<TreeDBNodeImpl> impl)
    : m_impl(impl)
{
}

XMLTreeDBNode::operator bool() const
{
    return static_cast<bool>(m_impl);
}

bool XMLTreeDBNode::operator !() const
{
    return !m_impl;
}

bool XMLTreeDBNode::operator ==(const XMLTreeDBNode& other) const
{
    return (m_impl == other.m_impl);
}

bool XMLTreeDBNode::operator !=(const XMLTreeDBNode& other) const
{
    return (m_impl != other.m_impl);
}

const std::string& XMLTreeDBNode::name() const
{
    return m_impl->name();
}

bool XMLTreeDBNode::isRoot() const
{
    return m_impl->isRoot();
}

std::shared_ptr<TreeDBNodeImpl>& XMLTreeDBNode::impl()
{
    return m_impl;
}

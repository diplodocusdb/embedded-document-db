/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "TreeDBKey.hpp"

namespace DiplodocusDB
{

TreeDBKey::TreeDBKey(const char* key)
    : m_value(key)
{
}

TreeDBKey::TreeDBKey(const std::string& key)
    : m_value(key)
{
}

TreeDBKey::~TreeDBKey()
{
}

const std::string& TreeDBKey::value() const
{
    return m_value;
}

bool TreeDBKey::isRoot() const
{
    return (m_value == "/");
}

bool TreeDBKey::isNull() const
{
    return (m_value == "");
}

TreeDBKey TreeDBKey::parentKey() const
{
    TreeDBKey result("");
    size_t pos = m_value.rfind('/');
    if ((pos == 0) && (m_value.size() > 1))
    {
        result = TreeDBKey("/");
    }
    else if (pos != std::string::npos)
    {
        result = TreeDBKey(m_value.substr(0, pos));
    }
    return result;
}

std::string TreeDBKey::base() const
{
    std::string result;
    size_t pos = m_value.rfind('/');
    if (pos != std::string::npos)
    {
        result = m_value.substr(pos + 1);
    }
    else
    {
        result = m_value;
    }
    return result;
}

bool TreeDBKey::operator ==(const TreeDBKey& other) const
{
    return (m_value == other.m_value);
}

bool TreeDBKey::operator !=(const TreeDBKey& other) const
{
    return (m_value != other.m_value);
}

bool TreeDBKey::operator <(const TreeDBKey& other) const
{
    return (m_value < other.m_value);
}

bool TreeDBKey::operator >(const TreeDBKey& other) const
{
    return (m_value > other.m_value);
}

}

/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TREEDB_CORE_TREEDBKEY_HPP_
#define _DIPLODOCUSDB_TREEDB_CORE_TREEDBKEY_HPP_

#include <string>

namespace DiplodocusDB
{

class TreeDBKey
{
public:
    TreeDBKey(const char* key);
    TreeDBKey(const std::string& key);
    ~TreeDBKey();

    const std::string& value() const;

    bool isRoot() const;
    bool isNull() const;
    TreeDBKey parentKey() const;
    std::string base() const;
    bool operator ==(const TreeDBKey& other) const;
    bool operator !=(const TreeDBKey& other) const;
    bool operator <(const TreeDBKey& other) const;
    bool operator >(const TreeDBKey& other) const;

private:
    std::string m_value;
};

}

#endif

/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "TreeDBErrorCategory.hpp"

namespace DiplodocusDB
{

const TreeDBErrorCategory& TreeDBErrorCategory::Get() noexcept
{
    static TreeDBErrorCategory theCategory;
    return theCategory;
}

const char* TreeDBErrorCategory::name() const noexcept
{
    return "DiplodocusDB::TreeDBErrorCategory";
}

void Fail(Ishiko::Error& error, TreeDBErrorCategory::EErrorValues value) noexcept
{
    error.fail(value, TreeDBErrorCategory::Get());
}

void Fail(Ishiko::Error& error, TreeDBErrorCategory::EErrorValues value, const std::string& message, const char* file,
    int line) noexcept
{
    error.fail(value, TreeDBErrorCategory::Get(), message, file, line);
}

}

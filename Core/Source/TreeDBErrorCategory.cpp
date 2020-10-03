/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/DiplodocusDB/TreeDB/blob/master/LICENSE.txt
*/

#include "TreeDBErrorCategory.h"

namespace DiplodocusDB
{

const TreeDBErrorCategory& TreeDBErrorCategory::Get() noexcept
{
    static TreeDBErrorCategory theCategory;
    return theCategory;
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

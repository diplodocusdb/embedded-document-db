/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TREEDB_CORE_TREEDBERRORCATEGORY_H_
#define _DIPLODOCUSDB_TREEDB_CORE_TREEDBERRORCATEGORY_H_

#include <Ishiko/Errors.hpp>

namespace DiplodocusDB
{

class TreeDBErrorCategory : public Ishiko::ErrorCategory
{
public:
    enum EErrorValues
    {
        eGeneric = -1
    };

    static const TreeDBErrorCategory& Get() noexcept;

    const char* name() const noexcept override;

private:
    TreeDBErrorCategory() noexcept = default;
};

void Fail(Ishiko::Error& error, TreeDBErrorCategory::EErrorValues value) noexcept;
void Fail(Ishiko::Error& error, TreeDBErrorCategory::EErrorValues value, const std::string& message, const char* file,
    int line) noexcept;

}

#endif

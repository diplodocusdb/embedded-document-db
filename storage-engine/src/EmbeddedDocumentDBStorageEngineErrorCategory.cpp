/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "StorageEngineErrorCategory.hpp"

using namespace DiplodocusDB;

const StorageEngineErrorCategory& StorageEngineErrorCategory::Get() noexcept
{
    static StorageEngineErrorCategory theCategory;
    return theCategory;
}

const char* StorageEngineErrorCategory::name() const noexcept
{
    return "DiplodocusDB::StorageEngineErrorCategory";
}

void Fail(Ishiko::Error& error, StorageEngineErrorCategory::EErrorValues value) noexcept
{
    error.fail(value, StorageEngineErrorCategory::Get());
}

void Fail(Ishiko::Error& error, StorageEngineErrorCategory::EErrorValues value, const std::string& message,
    const char* file, int line) noexcept
{
    error.fail(value, StorageEngineErrorCategory::Get(), message, file, line);
}

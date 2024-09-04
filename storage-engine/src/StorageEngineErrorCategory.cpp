/*
    Copyright (c) 2022-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "StorageEngineErrorCategory.hpp"

using namespace DiplodocusDB::EDDBImpl;

const StorageEngineErrorCategory& StorageEngineErrorCategory::Get() noexcept
{
    static StorageEngineErrorCategory theCategory;
    return theCategory;
}

const char* StorageEngineErrorCategory::name() const noexcept
{
    return "DiplodocusDB::EDDBImpl::StorageEngineErrorCategory";
}

const char* StorageEngineErrorCategory::message(int ev, char* buffer, size_t len) const noexcept
{
    switch (static_cast<Value>(ev))
    {
    case Value::generic_error:
        return "generic error";

    default:
        return "unknown value";
    }
}

void DiplodocusDB::EDDBImpl::Fail(Ishiko::Error& error, StorageEngineErrorCategory::Value value) noexcept
{
    error.fail(StorageEngineErrorCategory::Get(), value);
}

void DiplodocusDB::EDDBImpl::Fail(Ishiko::Error& error, StorageEngineErrorCategory::Value value,
    const std::string& message, const char* file, int line) noexcept
{
    error.fail(StorageEngineErrorCategory::Get(), value, message, file, line);
}

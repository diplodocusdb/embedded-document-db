/*
    Copyright (c) 2022 Xavier Leclercq
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

std::ostream& StorageEngineErrorCategory::streamOut(int value, std::ostream& os) const
{
    switch (static_cast<Value>(value))
    {
    case Value::generic_error:
        os << "generic error";
        break;

    default:
        os << "unknown value";
        break;
    }
    return os;
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

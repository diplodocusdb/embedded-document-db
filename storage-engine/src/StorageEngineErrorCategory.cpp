/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "EmbeddedDocumentDBStorageEngineErrorCategory.hpp"

using namespace DiplodocusDB;

const EmbeddedDocumentDBStorageEngineErrorCategory& EmbeddedDocumentDBStorageEngineErrorCategory::Get() noexcept
{
    static EmbeddedDocumentDBStorageEngineErrorCategory theCategory;
    return theCategory;
}

const char* EmbeddedDocumentDBStorageEngineErrorCategory::name() const noexcept
{
    return "DiplodocusDB::EmbeddedDocumentDBStorageEngineErrorCategory";
}

std::ostream& EmbeddedDocumentDBStorageEngineErrorCategory::streamOut(int value, std::ostream& os) const
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

void Fail(Ishiko::Error& error, EmbeddedDocumentDBStorageEngineErrorCategory::Value value) noexcept
{
    error.fail(EmbeddedDocumentDBStorageEngineErrorCategory::Get(), value);
}

void Fail(Ishiko::Error& error, EmbeddedDocumentDBStorageEngineErrorCategory::Value value, const std::string& message,
    const char* file, int line) noexcept
{
    error.fail(EmbeddedDocumentDBStorageEngineErrorCategory::Get(), value, message, file, line);
}

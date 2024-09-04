/*
    Copyright (c) 2020-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "EmbeddedDocumentDBErrorCategory.hpp"

using namespace DiplodocusDB;

const EmbeddedDocumentDBErrorCategory& EmbeddedDocumentDBErrorCategory::Get() noexcept
{
    static EmbeddedDocumentDBErrorCategory theCategory;
    return theCategory;
}

const char* EmbeddedDocumentDBErrorCategory::name() const noexcept
{
    return "DiplodocusDB::EmbeddedDocumentDBErrorCategory";
}

const char* EmbeddedDocumentDBErrorCategory::message(int ev, char* buffer, size_t len) const noexcept
{
    switch (static_cast<Value>(ev))
    {
    case Value::generic_error:
        return "generic error";

    default:
        return "unknown value";
    }
}

void DiplodocusDB::Fail(Ishiko::Error& error, EmbeddedDocumentDBErrorCategory::Value value) noexcept
{
    error.fail(EmbeddedDocumentDBErrorCategory::Get(), value);
}

void DiplodocusDB::Fail(Ishiko::Error& error, EmbeddedDocumentDBErrorCategory::Value value,
    const std::string& message, const char* file, int line) noexcept
{
    error.fail(EmbeddedDocumentDBErrorCategory::Get(), value, message, file, line);
}

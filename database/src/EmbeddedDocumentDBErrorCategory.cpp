/*
    Copyright (c) 2020-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "EmbeddedDocumentDBErrorCategory.hpp"

using namespace DiplodocusDB;

EmbeddedDocumentDBErrorCategory::EmbeddedDocumentDBErrorCategory() noexcept
    : Ishiko::ErrorCategory(ID(0x552e077f48b843f0ULL, 0xa2da2d4e6e404d1cULL)) // 552e077f-48b8-43f0-a2da-2d4e6e404d1c
{
}

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

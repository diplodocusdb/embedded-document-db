/*
    Copyright (c) 2020-2022 Xavier Leclercq
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

std::ostream& EmbeddedDocumentDBErrorCategory::streamOut(int value, std::ostream& os) const
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

void DiplodocusDB::Fail(Ishiko::Error& error, EmbeddedDocumentDBErrorCategory::Value value) noexcept
{
    error.fail(EmbeddedDocumentDBErrorCategory::Get(), value);
}

void DiplodocusDB::Fail(Ishiko::Error& error, EmbeddedDocumentDBErrorCategory::Value value,
    const std::string& message, const char* file, int line) noexcept
{
    error.fail(EmbeddedDocumentDBErrorCategory::Get(), value, message, file, line);
}

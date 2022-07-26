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
    return "DiplodocusDB::TreeDBErrorCategory";
}

void DiplodocusDB::Fail(Ishiko::Error& error, EmbeddedDocumentDBErrorCategory::EErrorValues value) noexcept
{
    error.fail(value, EmbeddedDocumentDBErrorCategory::Get());
}

void DiplodocusDB::Fail(Ishiko::Error& error, EmbeddedDocumentDBErrorCategory::EErrorValues value,
    const std::string& message, const char* file, int line) noexcept
{
    error.fail(value, EmbeddedDocumentDBErrorCategory::Get(), message, file, line);
}

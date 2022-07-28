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

void Fail(Ishiko::Error& error, EmbeddedDocumentDBStorageEngineErrorCategory::EErrorValues value) noexcept
{
    error.fail(value, EmbeddedDocumentDBStorageEngineErrorCategory::Get());
}

void Fail(Ishiko::Error& error, EmbeddedDocumentDBStorageEngineErrorCategory::EErrorValues value, const std::string& message,
    const char* file, int line) noexcept
{
    error.fail(value, EmbeddedDocumentDBStorageEngineErrorCategory::Get(), message, file, line);
}

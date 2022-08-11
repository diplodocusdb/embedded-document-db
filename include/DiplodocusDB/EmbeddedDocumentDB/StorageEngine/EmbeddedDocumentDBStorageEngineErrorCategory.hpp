/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_EMBEDDEDDOCUMENTDBSTORAGEENGINEERRORCATEGORY_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_EMBEDDEDDOCUMENTDBSTORAGEENGINEERRORCATEGORY_HPP

#include <Ishiko/Errors.hpp>

namespace DiplodocusDB
{

class EmbeddedDocumentDBStorageEngineErrorCategory : public Ishiko::ErrorCategory
{
public:
    enum Value
    {
        generic_error = -1
    };

    static const EmbeddedDocumentDBStorageEngineErrorCategory& Get() noexcept;

    const char* name() const noexcept override;
    std::ostream& streamOut(int value, std::ostream& os) const override;

private:
    EmbeddedDocumentDBStorageEngineErrorCategory() noexcept = default;
};

void Fail(Ishiko::Error& error, EmbeddedDocumentDBStorageEngineErrorCategory::Value value) noexcept;
void Fail(Ishiko::Error& error, EmbeddedDocumentDBStorageEngineErrorCategory::Value value, const std::string& message,
    const char* file, int line) noexcept;

}

#endif

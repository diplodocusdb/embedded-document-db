/*
    Copyright (c) 2022-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_STORAGEENGINEERRORCATEGORY_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_STORAGEENGINEERRORCATEGORY_HPP

#include <Ishiko/Errors.hpp>

namespace DiplodocusDB
{
namespace EDDBImpl
{

class StorageEngineErrorCategory : public Ishiko::ErrorCategory
{
public:
    enum Value
    {
        generic_error = -1
    };

    static const StorageEngineErrorCategory& Get() noexcept;

    const char* name() const noexcept override;
    const char* message(int ev, char* buffer, size_t len) const noexcept override;

private:
    StorageEngineErrorCategory() noexcept = default;
};

void Fail(Ishiko::Error& error, StorageEngineErrorCategory::Value value) noexcept;
void Fail(Ishiko::Error& error, StorageEngineErrorCategory::Value value, const std::string& message, const char* file,
    int line) noexcept;

}
}

#endif

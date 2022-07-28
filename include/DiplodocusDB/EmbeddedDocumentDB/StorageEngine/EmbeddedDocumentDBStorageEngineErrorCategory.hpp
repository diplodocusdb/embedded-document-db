/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_STORAGEENGINEERRORCATEGORY_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_STORAGEENGINEERRORCATEGORY_HPP_

#include <Ishiko/Errors.hpp>

namespace DiplodocusDB
{

class StorageEngineErrorCategory : public Ishiko::ErrorCategory
{
public:
    enum EErrorValues
    {
        eGeneric = -1
    };

    static const StorageEngineErrorCategory& Get() noexcept;

    const char* name() const noexcept override;

private:
    StorageEngineErrorCategory() noexcept = default;
};

void Fail(Ishiko::Error& error, StorageEngineErrorCategory::EErrorValues value) noexcept;
void Fail(Ishiko::Error& error, StorageEngineErrorCategory::EErrorValues value, const std::string& message,
    const char* file, int line) noexcept;

}

#endif

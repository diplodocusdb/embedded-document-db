/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TREEDB_CORE_EMBEDDEDDOCUMENTDBERRORCATEGORY_HPP_
#define _DIPLODOCUSDB_TREEDB_CORE_EMBEDDEDDOCUMENTDBERRORCATEGORY_HPP_

#include <Ishiko/Errors.hpp>

namespace DiplodocusDB
{

class EmbeddedDocumentDBErrorCategory : public Ishiko::ErrorCategory
{
public:
    enum EErrorValues
    {
        eGeneric = -1
    };

    static const EmbeddedDocumentDBErrorCategory& Get() noexcept;

    const char* name() const noexcept override;

private:
    EmbeddedDocumentDBErrorCategory() noexcept = default;
};

void Fail(Ishiko::Error& error, EmbeddedDocumentDBErrorCategory::EErrorValues value) noexcept;
void Fail(Ishiko::Error& error, EmbeddedDocumentDBErrorCategory::EErrorValues value, const std::string& message,
    const char* file, int line) noexcept;

}

#endif

/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDPAGEWORKINGSET_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDPAGEWORKINGSET_HPP

#include "RecordPage.hpp"
#include <map>
#include <memory>

namespace DiplodocusDB
{
namespace EDDBImpl
{

class RecordPageWorkingSet
{
public:
    /// Constructor.
    RecordPageWorkingSet() = default;

    bool get(size_t index, std::shared_ptr<RecordPage>& page);
    void set(std::shared_ptr<RecordPage>& page);

private:
    std::map<size_t, std::shared_ptr<RecordPage>> m_pages;
};

}
}

#endif

/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDREPOSITORY_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDREPOSITORY_HPP

#include "RecordPage.hpp"
#include <DiplodocusDB/PhysicalStorage.hpp>
#include <Ishiko/Errors.hpp>

namespace DiplodocusDB
{
namespace EDDBImpl
{

class RecordRepository
{
public:
    virtual ~RecordRepository() noexcept = default;

    virtual RecordPage page(size_t index, Ishiko::Error& error) = 0;
    virtual RecordPage insertPageAfter(RecordPage& page, Ishiko::Error& error) = 0;
    virtual void store(RecordPage& page, Ishiko::Error& error) = 0;
};

}
}

#endif

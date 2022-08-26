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
#include <memory>

namespace DiplodocusDB
{
namespace EDDBImpl
{

class RecordRepository
{
public:
    virtual ~RecordRepository() noexcept = default;

    virtual std::shared_ptr<RecordPage> page(size_t index, Ishiko::Error& error) = 0;
    virtual std::shared_ptr<RecordPage> insertPageAfter(RecordPage& page, Ishiko::Error& error) = 0;
    virtual void store(const RecordPage& page, Ishiko::Error& error) = 0;
};

}
}

#endif

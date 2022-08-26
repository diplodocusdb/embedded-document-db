/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDFILE_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDFILE_HPP

#include "RecordRepository.hpp"
#include "RecordRepositoryReader.hpp"
#include "RecordRepositoryWriter.hpp"
#include <DiplodocusDB/PhysicalStorage.hpp>
#include <boost/filesystem.hpp>
#include <Ishiko/Errors.hpp>

namespace DiplodocusDB
{
namespace EDDBImpl
{

class RecordFile : public RecordRepository
{
public:
    void create(const boost::filesystem::path& path, Ishiko::Error& error);
    void open(const boost::filesystem::path& path, Ishiko::Error& error);
    void close();

    size_t pageCount();
    RecordPage page(size_t index, Ishiko::Error& error) override;
    RecordPage allocatePage(Ishiko::Error& error);
    RecordPage insertPageAfter(RecordPage& page, Ishiko::Error& error) override;
    void store(RecordPage& page, Ishiko::Error& error) override;

    RecordRepositoryReader read(const PhysicalStorage::PageRepositoryPosition& pos, Ishiko::Error& error);
    RecordRepositoryReader read(size_t startPage, size_t offset, Ishiko::Error& error);
    RecordRepositoryReader read(const RecordPage& startPage, size_t offset, Ishiko::Error& error);

    RecordRepositoryWriter insert(const PhysicalStorage::PageRepositoryPosition& pos, Ishiko::Error& error);
    RecordRepositoryWriter insert(size_t startPage, size_t offset, Ishiko::Error& error);
    RecordRepositoryWriter insert(RecordPage& startPage, size_t offset, Ishiko::Error& error);

private:
    PhysicalStorage::PageFile m_page_file;
};

}
}

#endif

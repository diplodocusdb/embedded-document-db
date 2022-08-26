/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDPAGE_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDPAGE_HPP

#include <DiplodocusDB/PhysicalStorage.hpp>
#include <Ishiko/Errors.hpp>

namespace DiplodocusDB
{
namespace EDDBImpl
{

/// A page containing a list of records.
/**
    Each page has a number which is its position in the repository.
*/
class RecordPage
{
public:
    // TODO: try to get rid of this constructor that doesn#t construct valid objects
    RecordPage();
    RecordPage(const RecordPage& other) = default;
    RecordPage(RecordPage&& other) noexcept = default;

    RecordPage& operator=(const RecordPage& other) = delete;
    RecordPage& operator=(RecordPage&& other) noexcept = default;

    static RecordPage Create(PhysicalStorage::Page&& page);
    static RecordPage Load(PhysicalStorage::Page&& page);

    /// Stores the contents of the page to the repository.
    /**
        @param error The result of the operation.
    */
    void store(PhysicalStorage::PageRepository& repository, Ishiko::Error& error);

    size_t number() const;
    /// Returns the amount of data stored in the page.
    /**
        @returns The amount of data stored in the page.
    */
    size_t dataSize() const;
    /// Returns the maximum amount of data that can be stored in the page.
    /** 
        This is less than the page size because a page has a page start marker at the beginning and a page end marker
        at the end of the data that occupy some space.

        @returns The maximum amount of data that can be store in a page.
    */
    size_t maxDataSize() const;
    /// Returns the available space in the page.
    /**
        This is equivalent to maxDataSize() - dataSize().

        @returns Yhe available space in the page.
    */
    size_t availableSpace() const;
    size_t nextPage() const;
    void setNextPage(size_t index);

    void get(char* buffer, size_t pos, size_t n, Ishiko::Error& error) const;
    void insert(const char* buffer, size_t bufferSize, size_t pos, Ishiko::Error& error);
    void erase(size_t pos, size_t n, Ishiko::Error& error);
    void moveTo(size_t pos, size_t n, RecordPage& targetPage, Ishiko::Error& error);

    static const size_t sm_startMarkerSize = 8;
    static const size_t sm_endMarkerSize = 8;

private:
    /// Constructor.
    /**
        Note that the page contents are not initialized by this constructor. Use the init() function to initialize the
        page to all zeroes.

        @param index The index of the page.
    */
    RecordPage(PhysicalStorage::Page&& page, size_t data_size, size_t available_space, size_t next_page);

    PhysicalStorage::Page m_page;
    size_t m_dataSize;
    size_t m_availableSpace;
    size_t m_nextPage;
};

}
}

#endif

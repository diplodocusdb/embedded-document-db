/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "RecordPageTests.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/RecordPage.hpp"

using namespace DiplodocusDB;
using namespace DiplodocusDB::EDDBImpl;
using namespace Ishiko;

RecordPageTests::RecordPageTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "RecordPage tests", context)
{
    append<HeapAllocationErrorsTest>("ConstructorTest1 test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Create test 1", CreateTest1);
    append<HeapAllocationErrorsTest>("Load test 1", LoadTest1);
    append<HeapAllocationErrorsTest>("Load test 2", LoadTest2);
    append<HeapAllocationErrorsTest>("Load test 3", LoadTest3);
    append<HeapAllocationErrorsTest>("Load test 4", LoadTest4);
    append<HeapAllocationErrorsTest>("get test 1", GetTest1);
    append<HeapAllocationErrorsTest>("insert test 1", InsertTest1);
    append<HeapAllocationErrorsTest>("insert test 2", InsertTest2);
    append<HeapAllocationErrorsTest>("insert test 3", InsertTest3);
    append<HeapAllocationErrorsTest>("erase test 1", EraseTest1);
    append<HeapAllocationErrorsTest>("erase test 2", EraseTest2);
    append<HeapAllocationErrorsTest>("erase test 3", EraseTest3);
    append<HeapAllocationErrorsTest>("moveTo test 1", MoveToTest1);
    append<HeapAllocationErrorsTest>("moveTo test 2", MoveToTest2);
}

void RecordPageTests::ConstructorTest1(Test& test)
{
    RecordPage page;

    ISHIKO_TEST_PASS();
}

void RecordPageTests::CreateTest1(Test& test)
{
    const char* basename = "PageTests_WriteTest1.dpdb";

    Error error;

    PhysicalStorage::PageFile repository;
    repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    PhysicalStorage::Page page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage record_page = RecordPage::Create(std::move(page));

    repository.close();

    ISHIKO_TEST_FAIL_IF_NEQ(record_page.dataSize(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(record_page.availableSpace(), 4080);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

/// Tests reading an empty page.
void RecordPageTests::LoadTest1(Test& test)
{
    Error error;

    PhysicalStorage::PageFile repository;
    repository.open(test.context().getDataPath("PageTests_ReadTest1.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    PhysicalStorage::Page page = repository.load(0, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage record_page = RecordPage::Load(std::move(page));

    ISHIKO_TEST_FAIL_IF_NEQ(record_page.dataSize(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(record_page.availableSpace(), 4080);
    ISHIKO_TEST_FAIL_IF_NEQ(record_page.nextPage(), 0);
    ISHIKO_TEST_PASS();
}

/// Tests reading a page containing 6 bytes of data.
void RecordPageTests::LoadTest2(Test& test)
{
    Error error;

    PhysicalStorage::PageFile repository;
    repository.open(test.context().getDataPath("PageTests_ReadTest2.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    PhysicalStorage::Page page = repository.load(0, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage record_page = RecordPage::Load(std::move(page));

    ISHIKO_TEST_FAIL_IF_NEQ(record_page.dataSize(), 6);
    ISHIKO_TEST_FAIL_IF_NEQ(record_page.availableSpace(), 4074);
    ISHIKO_TEST_FAIL_IF_NEQ(record_page.nextPage(), 0);
    ISHIKO_TEST_PASS();
}

/// Tests reading the second page.
void RecordPageTests::LoadTest3(Test& test)
{
    Error error;

    PhysicalStorage::PageFile repository;
    repository.open(test.context().getDataPath("PageTests_ReadTest3.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    PhysicalStorage::Page page = repository.load(1, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage record_page = RecordPage::Load(std::move(page));

    ISHIKO_TEST_FAIL_IF_NEQ(record_page.dataSize(), 10);
    ISHIKO_TEST_FAIL_IF_NEQ(record_page.availableSpace(), 4070);
    ISHIKO_TEST_FAIL_IF_NEQ(record_page.nextPage(), 0);
    ISHIKO_TEST_PASS();
}

/// Tests reading a page that is incomplete, this should be impossible unless the file has been truncated.
void RecordPageTests::LoadTest4(Test& test)
{
    Error error;

    PhysicalStorage::PageFile repository;
    repository.open(test.context().getDataPath("PageTests_ReadTest5.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    PhysicalStorage::Page page = repository.load(0, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage record_page = RecordPage::Load(std::move(page));

    ISHIKO_TEST_FAIL_IF_NEQ(record_page.dataSize(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(record_page.availableSpace(), 4080);
    ISHIKO_TEST_PASS();
}

void RecordPageTests::GetTest1(Test& test)
{
    Error error;

    PhysicalStorage::PageFile repository;
    repository.open(test.context().getDataPath("PageTests_GetTest1.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    PhysicalStorage::Page page = repository.load(0, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage record_page = RecordPage::Load(std::move(page));

    ISHIKO_TEST_FAIL_IF_NEQ(record_page.dataSize(), 6);
    ISHIKO_TEST_FAIL_IF_NEQ(record_page.availableSpace(), 4074);

    char buffer[6];
    record_page.get(buffer, 0, 6, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(strncmp(buffer, "value1", 6) == 0);
    ISHIKO_TEST_PASS();
}

void RecordPageTests::InsertTest1(Test& test)
{
    const char* basename = "PageTests_InsertTest1.dpdb";

    Error error;

    PhysicalStorage::PageFile repository;
    repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    PhysicalStorage::Page page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage record_page = RecordPage::Create(std::move(page));
    record_page.insert("value1", 6, 0, error);

    ISHIKO_TEST_FAIL_IF(error);

    record_page.write(repository, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordPageTests::InsertTest2(Test& test)
{
    // TODO: need to copy to output dir
    const char* basename = "PageTests_InsertTest2.dpdb";

    Error error;

    PhysicalStorage::PageFile repository;
    repository.open(test.context().getDataPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    PhysicalStorage::Page page = repository.load(0, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage record_page = RecordPage::Load(std::move(page));

    record_page.insert("value0", 6, 0, error);

    ISHIKO_TEST_FAIL_IF(error);

    PhysicalStorage::PageFile output_repository;
    output_repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    record_page.write(output_repository, error);

    ISHIKO_TEST_FAIL_IF(error);

    output_repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

/// Tests an insertion that doesn't fit in the current page.
void RecordPageTests::InsertTest3(Test& test)
{
    Error error;

    PhysicalStorage::PageFile repository;
    repository.open(test.context().getDataPath("PageTests_InsertTest3.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    PhysicalStorage::Page page = repository.load(0, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage record_page = RecordPage::Load(std::move(page));

    record_page.insert("", 4075, 0, error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_PASS();
}

void RecordPageTests::EraseTest1(Test& test)
{
    const char* basename = "PageTests_EraseTest1.dpdb";

    Error error;

    PhysicalStorage::PageFile repository;
    repository.open(test.context().getDataPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    PhysicalStorage::Page page = repository.load(0, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage record_page = RecordPage::Load(std::move(page));

    ISHIKO_TEST_ABORT_IF(error);

    record_page.erase(0, 6, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(record_page.dataSize(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(record_page.availableSpace(), 4080);

    PhysicalStorage::PageFile output_repository;
    output_repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    record_page.write(output_repository, error);

    ISHIKO_TEST_FAIL_IF(error);

    output_repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordPageTests::EraseTest2(Test& test)
{
    const char* basename = "PageTests_EraseTest2.dpdb";

    Error error;

    PhysicalStorage::PageFile repository;
    repository.open(test.context().getDataPath(basename), error);

    RecordPage page{0};
    page.read(repository, error);

    ISHIKO_TEST_ABORT_IF(error);

    page.erase(5, 1, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(page.dataSize(), 5);
    ISHIKO_TEST_FAIL_IF_NEQ(page.availableSpace(), 4075);

    PhysicalStorage::PageFile output_repository;
    output_repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    page.write(output_repository, error);

    ISHIKO_TEST_FAIL_IF(error);

    output_repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordPageTests::EraseTest3(Test& test)
{
    const char* basename = "PageTests_EraseTest3.dpdb";

    Error error;

    PhysicalStorage::PageFile repository;
    repository.open(test.context().getDataPath(basename), error);

    RecordPage page{0};
    page.read(repository, error);

    ISHIKO_TEST_ABORT_IF(error);

    page.erase(2, 10, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(page.dataSize(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(page.availableSpace(), 4078);

    PhysicalStorage::PageFile output_repository;
    output_repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    page.write(output_repository, error);

    ISHIKO_TEST_FAIL_IF(error);

    output_repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordPageTests::MoveToTest1(Test& test)
{
    const char* basename = "PageTests_MoveToTest1.dpdb";

    Error error;

    PhysicalStorage::PageFile repository;
    repository.open(test.context().getDataPath(basename), error);

    RecordPage page1{0};
    page1.read(repository, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page2{1};
    page2.read(repository, error);

    page1.moveTo(0, 6, page2, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(page1.dataSize(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(page2.dataSize(), 6);

    PhysicalStorage::PageFile output_repository;
    output_repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    page1.write(output_repository, error);

    ISHIKO_TEST_FAIL_IF(error);

    page2.write(output_repository, error);

    ISHIKO_TEST_FAIL_IF(error);

    output_repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordPageTests::MoveToTest2(Test& test)
{
    const char* basename = "PageTests_MoveToTest2.dpdb";

    Error error;

    PhysicalStorage::PageFile repository;
    repository.open(test.context().getDataPath(basename), error);

    RecordPage page1{0};
    page1.read(repository, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page2{1};
    page2.read(repository, error);

    page1.moveTo(0, 6, page2, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(page1.dataSize(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(page2.dataSize(), 12);

    PhysicalStorage::PageFile output_repository;
    output_repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    page1.write(output_repository, error);

    ISHIKO_TEST_FAIL_IF(error);

    page2.write(output_repository, error);

    ISHIKO_TEST_FAIL_IF(error);

    output_repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

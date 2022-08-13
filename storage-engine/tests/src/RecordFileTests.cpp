/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "RecordFileTests.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/RecordFile.hpp"
#include <boost/filesystem.hpp>
#include <Ishiko/Errors.hpp>
#include <memory>

using namespace DiplodocusDB::EDDBImpl;
using namespace Ishiko;

RecordFileTests::RecordFileTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "RecordFile tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("create test 1", CreateTest1);
    append<HeapAllocationErrorsTest>("open test 1", OpenTest1);
    append<HeapAllocationErrorsTest>("open test 2", OpenTest2);
    append<HeapAllocationErrorsTest>("allocatePage test 1", AllocatePageTest1);
    append<HeapAllocationErrorsTest>("allocatePage test 2", AllocatePageTest2);
    append<HeapAllocationErrorsTest>("insertPageAfter test 1", InsertPageAfterTest1);
}

void RecordFileTests::CreationTest1(Test& test)
{
    RecordFile repository;

    ISHIKO_TEST_PASS();
}

void RecordFileTests::CreateTest1(Test& test)
{
    const char* outputName = "PageFileRepositoryCreateTest1.dpdb";

    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void RecordFileTests::OpenTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("PageFileRepositoryOpenTest1.dpdb");

    Error error;

    RecordFile repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(repository.pageCount(), 0);
    ISHIKO_TEST_PASS();
}

void RecordFileTests::OpenTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("PageFileRepositoryOpenTest2.dpdb");

    Error error;

    RecordFile repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(repository.pageCount(), 1);
    ISHIKO_TEST_PASS();
}

void RecordFileTests::AllocatePageTest1(Test& test)
{
    const char* outputName = "PageFileRepositoryTests_AllocatePageTest1.dpdb";

    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::PhysicalStorage::Page2> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(page);

    repository.store(*page, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void RecordFileTests::AllocatePageTest2(Test& test)
{
    const char* outputName = "PageFileRepositoryTests_AllocatePageTest2.dpdb";

    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::PhysicalStorage::Page2> page1 = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(page1);

    repository.store(*page1, error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::PhysicalStorage::Page2> page2 = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(page2);

    repository.store(*page2, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void RecordFileTests::InsertPageAfterTest1(Test& test)
{
    const char* outputName = "PageFileRepositoryTests_InsertPageAfterTest1.dpdb";
    boost::filesystem::path outputPath = test.context().getOutputPath(outputName);

    boost::filesystem::copy_file(test.context().getDataPath("PageFileRepositoryTests_InsertPageAfterTest1.dpdb"), outputPath,
        boost::filesystem::copy_option::overwrite_if_exists);

    Error error;

    RecordFile repository;
    repository.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::PhysicalStorage::Page2> page1 = repository.page(0, error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(page1);

    std::shared_ptr<DiplodocusDB::PhysicalStorage::Page2> page2 = repository.insertPageAfter(*page1, error);

    ISHIKO_TEST_ABORT_IF(error);

    repository.store(*page1, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.store(*page2, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}
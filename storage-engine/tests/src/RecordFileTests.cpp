/*
    Copyright (c) 2022-2024 Xavier Leclercq
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
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("create test 1", CreateTest1);
    append<HeapAllocationErrorsTest>("open test 1", OpenTest1);
    append<HeapAllocationErrorsTest>("open test 2", OpenTest2);
    append<HeapAllocationErrorsTest>("allocatePage test 1", AllocatePageTest1);
    append<HeapAllocationErrorsTest>("allocatePage test 2", AllocatePageTest2);
    append<HeapAllocationErrorsTest>("store test 1", StoreTest1);
    append<HeapAllocationErrorsTest>("store test 2", StoreTest2);
    append<HeapAllocationErrorsTest>("insertPageAfter test 1", InsertPageAfterTest1);
}

void RecordFileTests::ConstructorTest1(Test& test)
{
    RecordFile repository;

    ISHIKO_TEST_PASS();
}

void RecordFileTests::CreateTest1(Test& test)
{
    const char* basename = "RecordFileTests_CreateTest1.dpdb";

    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordFileTests::OpenTest1(Test& test)
{
    Error error;

    RecordFile repository;
    repository.open(test.context().getDataPath("RecordFileTests_OpenTest1.dpdb"), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(repository.pageCount(), 0);
    ISHIKO_TEST_PASS();
}

void RecordFileTests::OpenTest2(Test& test)
{
    Error error;

    RecordFile repository;
    repository.open(test.context().getDataPath("RecordFileTests_OpenTest2.dpdb"), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(repository.pageCount(), 1);
    ISHIKO_TEST_PASS();
}

void RecordFileTests::AllocatePageTest1(Test& test)
{
    const char* basename = "RecordFileTests_AllocatePageTest1.dpdb";

    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordFileTests::AllocatePageTest2(Test& test)
{
    const char* basename = "RecordFileTests_AllocatePageTest2.dpdb";

    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page1 = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page2 = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordFileTests::StoreTest1(Test& test)
{
    const char* basename = "RecordFileTests_StoreTest1.dpdb";

    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    repository.store(page, error);

    ISHIKO_TEST_ABORT_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordFileTests::StoreTest2(Test& test)
{
    const char* basename = "RecordFileTests_StoreTest2.dpdb";

    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page1 = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page2 = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    repository.store(page1, error);

    ISHIKO_TEST_ABORT_IF(error);

    repository.store(page2, error);

    ISHIKO_TEST_ABORT_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordFileTests::InsertPageAfterTest1(Test& test)
{
    const char* basename = "RecordFileTests_InsertPageAfterTest1.dpdb";
    boost::filesystem::path outputPath = test.context().getOutputPath(basename);

    boost::filesystem::copy_file(test.context().getDataPath(basename), outputPath,
        boost::filesystem::copy_options::overwrite_if_exists);

    Error error;

    RecordFile repository;
    repository.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page1 = repository.page(0, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page2 = repository.insertPageAfter(page1, error);

    ISHIKO_TEST_ABORT_IF(error);

    repository.store(page1, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.store(page2, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

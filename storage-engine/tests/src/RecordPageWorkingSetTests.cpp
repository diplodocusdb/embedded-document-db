/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "RecordPageWorkingSetTests.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/RecordFile.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/RecordPageWorkingSet.hpp"
#include <Ishiko/Errors.hpp>
#include <memory>

using namespace DiplodocusDB::EDDBImpl;
using namespace Ishiko;

RecordPageWorkingSetTests::RecordPageWorkingSetTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "RecordPageWorkingSet tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("get test 1", GetTest1);
}

void RecordPageWorkingSetTests::ConstructorTest1(Test& test)
{
    RecordFile repository;
    RecordPageWorkingSet working_set{repository};

    ISHIKO_TEST_PASS();
}

void RecordPageWorkingSetTests::GetTest1(Test& test)
{
    Error error;

    RecordFile repository;
    repository.open(test.context().getDataPath("RecordFileTests_OpenTest2.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPageWorkingSet working_set{repository};

    std::shared_ptr<RecordPage> page = working_set.get(0, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(page->dataSize(), 0);

    std::shared_ptr<RecordPage> same_page = working_set.get(0, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(same_page.get(), page.get());
    ISHIKO_TEST_PASS();
}

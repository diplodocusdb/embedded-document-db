/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "SiblingNodesRecordGroupTests.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/RecordFile.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/SiblingNodesRecordGroup.hpp"
#include <DiplodocusDB/PhysicalStorage.hpp>

using namespace DiplodocusDB;
using namespace DiplodocusDB::EDDBImpl;
using namespace Ishiko;

SiblingNodesRecordGroupTests::SiblingNodesRecordGroupTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "SiblingNodesRecordGroup tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructionTest1);
    append<HeapAllocationErrorsTest>("write test 1", WriteTest1);
    append<HeapAllocationErrorsTest>("write test 2", WriteTest2);
    append<HeapAllocationErrorsTest>("write test 3", WriteTest3);
    append<HeapAllocationErrorsTest>("write test 4", WriteTest4);
}

void SiblingNodesRecordGroupTests::ConstructionTest1(Test& test)
{
    SiblingNodesRecordGroup siblingNodesRecordGroup;

    ISHIKO_TEST_PASS();
}

void SiblingNodesRecordGroupTests::WriteTest1(Test& test)
{
    const char* testName = "SiblingNodesRecordGroupTests_WriteTest1.dpdb";
    
    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordRepositoryWriter writer{repository, page, 0};

    ISHIKO_TEST_ABORT_IF(error);

    SiblingNodesRecordGroup siblingNodesRecordGroup;
    siblingNodesRecordGroup.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.store(page, error);
    repository.close();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void SiblingNodesRecordGroupTests::WriteTest2(Test& test)
{
    const char* testName = "SiblingNodesRecordGroupTests_WriteTest2.dpdb";

    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordRepositoryWriter writer{repository, page, 0};

    ISHIKO_TEST_ABORT_IF(error);

    // Create a root node
    SiblingNodeRecordGroup sibling("/", NodeID(1));
    SiblingNodesRecordGroup siblingNodesRecordGroup(NodeID(0), sibling);
    siblingNodesRecordGroup.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.store(page, error);
    repository.close();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void SiblingNodesRecordGroupTests::WriteTest3(Test& test)
{
    const char* testName = "SiblingNodesRecordGroupTests_WriteTest3.dpdb";
   
    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordRepositoryWriter writer{repository, page, 0};

    ISHIKO_TEST_ABORT_IF(error);

    // TODO: is this test correct? Why is the root node id 1 and the child 0?
    SiblingNodeRecordGroup sibling("name1", NodeID(0));
    SiblingNodesRecordGroup siblingNodesRecordGroup(NodeID(1), sibling);
    siblingNodesRecordGroup.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.store(page, error);
    repository.close();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void SiblingNodesRecordGroupTests::WriteTest4(Test& test)
{
    const char* testName = "SiblingNodesRecordGroupTests_WriteTest4.dpdb";

    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordRepositoryWriter writer{repository, page, 0};

    ISHIKO_TEST_ABORT_IF(error);

    // TODO: is this test correct? Why is the root node id 1 and both children 0?
    SiblingNodeRecordGroup sibling1("name1", NodeID(0));
    SiblingNodesRecordGroup siblingNodesRecordGroup(NodeID(1), sibling1);
    SiblingNodeRecordGroup sibling2("name2", NodeID(0));
    siblingNodesRecordGroup.push_back(sibling2);
    siblingNodesRecordGroup.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.store(page, error);
    repository.close();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

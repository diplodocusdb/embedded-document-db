/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "RecordFilesSetTests.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/RecordFilesSet.hpp"

using namespace DiplodocusDB::EDDBImpl;
using namespace Ishiko;

RecordFilesSetTests::RecordFilesSetTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "RecordFilesSet tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructionTest1);
    append<HeapAllocationErrorsTest>("createMasterFile test 1", CreateMasterFileTest1);
    append<HeapAllocationErrorsTest>("openMasterFile test 1", OpenMasterFileTest1);
    append<HeapAllocationErrorsTest>("openMasterFile test 2", OpenMasterFileTest2);
    append<HeapAllocationErrorsTest>("findSiblingNodesRecordGroup test 1", FindSiblingNodesRecordGroupTest1);
    append<HeapAllocationErrorsTest>("findSiblingNodesRecordGroup test 2", FindSiblingNodesRecordGroupTest2);
    append<HeapAllocationErrorsTest>("findSiblingNodesRecordGroup test 3", FindSiblingNodesRecordGroupTest3);
}

void RecordFilesSetTests::ConstructionTest1(Test& test)
{
    RecordFilesSet set;

    ISHIKO_TEST_PASS();
}

void RecordFilesSetTests::CreateMasterFileTest1(Test& test)
{
    const char* basename = "MasterFileTests_CreateTest1.dpdb";

    Error error;

    RecordFilesSet set;
    set.createMasterFile(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_FAIL_IF(error);

    set.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordFilesSetTests::OpenMasterFileTest1(Test& test)
{
    Error error;

    RecordFilesSet set;
    set.openMasterFile(test.context().getDataPath("MasterFileTests_OpenTest1.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    // Get the root node record group. This only ever contains one node, the root, and has no parent node ID.
    // The record group can be found by passing 0 as the parent Node ID.
    SiblingNodesRecordGroup siblingsNodesRecordGroup;
    bool found = set.findSiblingNodesRecordGroup(NodeID(0), siblingsNodesRecordGroup, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(siblingsNodesRecordGroup.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(siblingsNodesRecordGroup[0].name(), "/");
    ISHIKO_TEST_PASS();
}

void RecordFilesSetTests::OpenMasterFileTest2(Test& test)
{
    Error error;

    RecordFilesSet set;
    set.openMasterFile(test.context().getDataPath("MasterFileTests_OpenTest2.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    SiblingNodesRecordGroup siblingsNodesRecordGroup;
    bool found = set.findSiblingNodesRecordGroup(NodeID(1), siblingsNodesRecordGroup, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(siblingsNodesRecordGroup.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(siblingsNodesRecordGroup[0].name(), "key1");
    ISHIKO_TEST_PASS();
}

void RecordFilesSetTests::FindSiblingNodesRecordGroupTest1(Test& test)
{
    Error error;

    RecordFilesSet set;
    set.openMasterFile(test.context().getDataPath("MasterFileTests_OpenTest1.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    // Get the root node record group. This only ever contains one node, the root, and has no parent node ID.
    // The record group can be found by passing 0 as the parent Node ID.
    SiblingNodesRecordGroup siblingsNodesRecordGroup;
    bool found = set.findSiblingNodesRecordGroup(NodeID(0), siblingsNodesRecordGroup, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(siblingsNodesRecordGroup.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(siblingsNodesRecordGroup[0].name(), "/");
    ISHIKO_TEST_PASS();
}

void RecordFilesSetTests::FindSiblingNodesRecordGroupTest2(Test& test)
{
    Error error;

    RecordFilesSet set;
    set.openMasterFile(test.context().getDataPath("MasterFileTests_OpenTest2.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    SiblingNodesRecordGroup siblingsNodesRecordGroup;
    bool found = set.findSiblingNodesRecordGroup(NodeID(1), siblingsNodesRecordGroup, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(siblingsNodesRecordGroup.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(siblingsNodesRecordGroup[0].name(), "key1");
    ISHIKO_TEST_PASS();
}

void RecordFilesSetTests::FindSiblingNodesRecordGroupTest3(Test& test)
{
    Error error;

    RecordFilesSet set;
    set.openMasterFile(test.context().getDataPath("MasterFileTests_OpenTest2.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    SiblingNodesRecordGroup siblingsNodesRecordGroup;
    bool found = set.findSiblingNodesRecordGroup(NodeID(3), siblingsNodesRecordGroup, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(!found);
    ISHIKO_TEST_PASS();
}

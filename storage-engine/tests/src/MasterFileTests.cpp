/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "MasterFileTests.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/MasterFile.hpp"
#include <sstream>

using namespace DiplodocusDB;
using namespace DiplodocusDB::EDDBImpl;
using namespace Ishiko;

MasterFileTests::MasterFileTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "MasterFile tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructionTest1);
    append<HeapAllocationErrorsTest>("create test 1", CreateTest1);
    append<HeapAllocationErrorsTest>("open test 1", OpenTest1);
    append<HeapAllocationErrorsTest>("open test 2", OpenTest2);
    append<HeapAllocationErrorsTest>("addSiblingNodesRecordGroup test 1", AddSiblingNodesRecordGroupTest1);
    append<HeapAllocationErrorsTest>("addSiblingNodesRecordGroup test 2", AddSiblingNodesRecordGroupTest2);
    append<HeapAllocationErrorsTest>("addSiblingNodesRecordGroup test 3", AddSiblingNodesRecordGroupTest3);
    append<HeapAllocationErrorsTest>("addSiblingNodesRecordGroup test 4", AddSiblingNodesRecordGroupTest4);
    append<HeapAllocationErrorsTest>("addSiblingNodesRecordGroup test 5", AddSiblingNodesRecordGroupTest5);
    append<HeapAllocationErrorsTest>("addSiblingNodesRecordGroup test 6", AddSiblingNodesRecordGroupTest6);
    append<HeapAllocationErrorsTest>("addSiblingNodesRecordGroup test 7", AddSiblingNodesRecordGroupTest7);
    append<HeapAllocationErrorsTest>("addSiblingNodesRecordGroup test 8", AddSiblingNodesRecordGroupTest8);
    append<HeapAllocationErrorsTest>("addSiblingNodesRecordGroup test 9", AddSiblingNodesRecordGroupTest9);
    append<HeapAllocationErrorsTest>("addSiblingNodesRecordGroup test 10", AddSiblingNodesRecordGroupTest10);
    // TODO
    //append<HeapAllocationErrorsTest>("removeSiblingNodesRecordGroup test 1", RemoveSiblingNodesRecordGroupTest1);
}

void MasterFileTests::ConstructionTest1(Test& test)
{
    MasterFile masterFile;

    ISHIKO_TEST_PASS();
}

void MasterFileTests::CreateTest1(Test& test)
{
    const char* basename = "MasterFileTests_CreateTest1.dpdb";

    Error error;

    MasterFile masterFile;
    masterFile.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_FAIL_IF(error);

    masterFile.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void MasterFileTests::OpenTest1(Test& test)
{
    Error error;

    MasterFile masterFile;
    masterFile.open(test.context().getDataPath("MasterFileTests_OpenTest1.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordMarker rootMarker = masterFile.rootNodePosition();

    ISHIKO_TEST_FAIL_IF_NEQ(rootMarker.position().page(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(rootMarker.position().offset(), 15);

    RecordMarker dataEndMarker = masterFile.dataEndPosition();

    ISHIKO_TEST_FAIL_IF_NEQ(dataEndMarker.position().page(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(dataEndMarker.position().offset(), 20);

    ISHIKO_TEST_PASS();
}

void MasterFileTests::OpenTest2(Test& test)
{
    Error error;

    MasterFile masterFile;
    masterFile.open(test.context().getDataPath("MasterFileTests_OpenTest2.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordMarker rootMarker = masterFile.rootNodePosition();

    ISHIKO_TEST_FAIL_IF_NEQ(rootMarker.position().page(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(rootMarker.position().offset(), 15);

    RecordMarker dataEndMarker = masterFile.dataEndPosition();

    ISHIKO_TEST_FAIL_IF_NEQ(dataEndMarker.position().page(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(dataEndMarker.position().offset(), 30);

    ISHIKO_TEST_PASS();
}

void MasterFileTests::AddSiblingNodesRecordGroupTest1(Test& test)
{
    const char* basename = "MasterFileTests_AddSiblingNodesRecordGroupTest1.dpdb";

    Error error;

    MasterFile masterFile;
    masterFile.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    // Create a node whose parent is the root (ID 1)
    SiblingNodeRecordGroup sibling("key1", NodeID(0));
    masterFile.addSiblingNodesRecordGroup(SiblingNodesRecordGroup(NodeID(1), sibling), error);

    ISHIKO_TEST_FAIL_IF(error);

    masterFile.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void MasterFileTests::AddSiblingNodesRecordGroupTest2(Test& test)
{
    const char* basename = "MasterFileTests_AddSiblingNodesRecordGroupTest2.dpdb";

    Error error;

    MasterFile masterFile;
    masterFile.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    // Create a node whose parent is the root (ID 1) and has a node ID as it will be the parent of another node
    SiblingNodeRecordGroup newNode1("key1", NodeID(2));
    masterFile.addSiblingNodesRecordGroup(SiblingNodesRecordGroup(NodeID(1), newNode1), error);

    ISHIKO_TEST_FAIL_IF(error);

    SiblingNodeRecordGroup newNode2("key1_1", NodeID(0));
    masterFile.addSiblingNodesRecordGroup(SiblingNodesRecordGroup(NodeID(2), newNode2), error);

    ISHIKO_TEST_FAIL_IF(error);

    masterFile.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void MasterFileTests::AddSiblingNodesRecordGroupTest3(Test& test)
{
    const char* basename = "MasterFileTests_AddSiblingNodesRecordGroupTest3.dpdb";

    Error error;

    MasterFile masterFile;
    masterFile.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    // Create a node whose parent is the root (ID 1)
    SiblingNodeRecordGroup newNode1("key1", NodeID(0));
    // Create a second node whose parent is the root (ID 1)
    SiblingNodeRecordGroup newNode2("key2", NodeID(0));
    SiblingNodesRecordGroup siblingsNodesRecordGroup(NodeID(1));
    siblingsNodesRecordGroup.push_back(newNode1);
    siblingsNodesRecordGroup.push_back(newNode2);
    masterFile.addSiblingNodesRecordGroup(siblingsNodesRecordGroup, error);

    ISHIKO_TEST_FAIL_IF(error);

    masterFile.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

/// This test fills a page up to the last byte
void MasterFileTests::AddSiblingNodesRecordGroupTest4(Test& test)
{
    const char* basename = "MasterFileTests_AddSiblingNodesRecordGroupTest4.dpdb";

    Error error;

    MasterFile masterFile;
    masterFile.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    SiblingNodesRecordGroup siblingsNodesRecordGroup(NodeID(1));
    for (size_t i = 0; i < 520; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        SiblingNodeRecordGroup newNode(key.str(), NodeID(0));
        siblingsNodesRecordGroup.push_back(newNode);
    }

    ISHIKO_TEST_FAIL_IF(error);

    // The name length is exactly the number of characters needed to fill the page
    SiblingNodeRecordGroup newNode("k12", NodeID(0));
    siblingsNodesRecordGroup.push_back(newNode);

    masterFile.addSiblingNodesRecordGroup(siblingsNodesRecordGroup, error);

    ISHIKO_TEST_FAIL_IF(error);

    masterFile.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

/// This test uses just one byte more than can be stored in a page
void MasterFileTests::AddSiblingNodesRecordGroupTest5(Test& test)
{
    const char* basename = "MasterFileTests_AddSiblingNodesRecordGroupTest5.dpdb";

    Error error;

    MasterFile masterFile;
    masterFile.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    SiblingNodesRecordGroup siblingsNodesRecordGroup(NodeID(1));
    for (size_t i = 0; i < 520; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        SiblingNodeRecordGroup newNode(key.str(), NodeID(0));
        siblingsNodesRecordGroup.push_back(newNode);
    }

    ISHIKO_TEST_FAIL_IF(error);

    // The name length is exactly the number of characters needed to fill the page plus one byte
    SiblingNodeRecordGroup newNode("k123", NodeID(0));
    siblingsNodesRecordGroup.push_back(newNode);

    masterFile.addSiblingNodesRecordGroup(siblingsNodesRecordGroup, error);

    masterFile.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void MasterFileTests::AddSiblingNodesRecordGroupTest6(Test& test)
{
    const char* basename = "MasterFileTests_AddSiblingNodesRecordGroupTest6.dpdb";

    Error error;

    MasterFile masterFile;
    masterFile.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    SiblingNodesRecordGroup siblingsNodesRecordGroup(NodeID(1));
    for (size_t i = 0; i < 10000; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        SiblingNodeRecordGroup newNode(key.str(), NodeID(0));
        siblingsNodesRecordGroup.push_back(newNode);
    }

    masterFile.addSiblingNodesRecordGroup(siblingsNodesRecordGroup, error);

    ISHIKO_TEST_FAIL_IF(error);

    masterFile.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void MasterFileTests::AddSiblingNodesRecordGroupTest7(Test& test)
{
    const char* basename = "MasterFileTests_AddSiblingNodesRecordGroupTest7.dpdb";

    Error error;

    MasterFile masterFile;
    masterFile.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    SiblingNodesRecordGroup siblingsNodesRecordGroup(NodeID(1));
    for (size_t i = 0; i < 100000; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        SiblingNodeRecordGroup newNode(key.str(), NodeID(0));
        siblingsNodesRecordGroup.push_back(newNode);
    }

    masterFile.addSiblingNodesRecordGroup(siblingsNodesRecordGroup, error);

    ISHIKO_TEST_FAIL_IF(error);

    masterFile.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void MasterFileTests::AddSiblingNodesRecordGroupTest8(Test& test)
{
    const char* basename = "MasterFileTests_AddSiblingNodesRecordGroupTest8.dpdb";

    Error error;

    MasterFile masterFile;
    masterFile.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    SiblingNodesRecordGroup siblingsNodesRecordGroup(NodeID(1));
    for (size_t i = 0; i < 1000000; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        SiblingNodeRecordGroup newNode(key.str(), NodeID(0));
        siblingsNodesRecordGroup.push_back(newNode);
    }

    masterFile.addSiblingNodesRecordGroup(siblingsNodesRecordGroup, error);

    ISHIKO_TEST_FAIL_IF(error);

    masterFile.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void MasterFileTests::AddSiblingNodesRecordGroupTest9(Test& test)
{
    const char* basename = "MasterFileTests_AddSiblingNodesRecordGroupTest9.dpdb";

    Error error;

    MasterFile masterFile;
    masterFile.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    // Create a node whose parent is the root (ID 1)
    SiblingNodeRecordGroup newNode("key1", NodeID(0));
    newNode.value() = Value::UTF8String("value1");
    masterFile.addSiblingNodesRecordGroup(SiblingNodesRecordGroup(NodeID(1), newNode), error);

    ISHIKO_TEST_FAIL_IF(error);

    masterFile.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void MasterFileTests::AddSiblingNodesRecordGroupTest10(Test& test)
{
    const char* basename = "MasterFileTests_AddSiblingNodesRecordGroupTest10.dpdb";
    
    Error error;

    MasterFile masterFile;
    masterFile.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    // Create a node whose parent is the root (ID 1)
    SiblingNodeRecordGroup sibling1("key1", NodeID(0));
    sibling1.value() = Value::UTF8String("value1");
    // Create a second node whose parent is the root (ID 1)
    SiblingNodeRecordGroup sibling2("key2", NodeID(0));
    sibling2.value() = Value::UTF8String("value2");
    SiblingNodesRecordGroup siblingNodesRecordGroup(NodeID(1), sibling1);
    siblingNodesRecordGroup.push_back(sibling2);
    masterFile.addSiblingNodesRecordGroup(siblingNodesRecordGroup, error);

    ISHIKO_TEST_FAIL_IF(error);

    masterFile.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

/* TODO
void MasterFileTests::RemoveSiblingNodesRecordGroupTest1(Test& test)
{
}
*/

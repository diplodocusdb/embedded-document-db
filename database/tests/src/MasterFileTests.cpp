/*
    Copyright (c) 2018-2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "MasterFileTests.h"
#include "MasterFile.h"
#include <sstream>

using namespace Ishiko::Tests;

MasterFileTests::MasterFileTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "MasterFile tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructionTest1);
    append<FileComparisonTest>("create test 1", CreateTest1);
    append<HeapAllocationErrorsTest>("open test 1", OpenTest1);
    append<HeapAllocationErrorsTest>("open test 2", OpenTest2);
    append<HeapAllocationErrorsTest>("open test 3", OpenTest3);
    append<HeapAllocationErrorsTest>("open test 4", OpenTest4);
    append<FileComparisonTest>("addSiblingNodesRecordGroup test 1", AddSiblingNodesRecordGroupTest1);
    append<FileComparisonTest>("addSiblingNodesRecordGroup test 2", AddSiblingNodesRecordGroupTest2);
    append<FileComparisonTest>("addSiblingNodesRecordGroup test 3", AddSiblingNodesRecordGroupTest3);
    append<FileComparisonTest>("addSiblingNodesRecordGroup test 4", AddSiblingNodesRecordGroupTest4);
    append<FileComparisonTest>("addSiblingNodesRecordGroup test 5", AddSiblingNodesRecordGroupTest5);
    append<FileComparisonTest>("addSiblingNodesRecordGroup test 6", AddSiblingNodesRecordGroupTest6);
    append<FileComparisonTest>("addSiblingNodesRecordGroup test 7", AddSiblingNodesRecordGroupTest7);
    append<FileComparisonTest>("addSiblingNodesRecordGroup test 8", AddSiblingNodesRecordGroupTest8);
    append<FileComparisonTest>("addSiblingNodesRecordGroup test 9", AddSiblingNodesRecordGroupTest9);
    append<FileComparisonTest>("addSiblingNodesRecordGroup test 10", AddSiblingNodesRecordGroupTest10);
    append<HeapAllocationErrorsTest>("findSiblingNodesRecordGroup test 1", FindSiblingNodesRecordGroupTest1);
    append<HeapAllocationErrorsTest>("findSiblingNodesRecordGroup test 2", FindSiblingNodesRecordGroupTest2);
    append<HeapAllocationErrorsTest>("findSiblingNodesRecordGroup test 3", FindSiblingNodesRecordGroupTest3);
    append<FileComparisonTest>("removeSiblingNodesRecordGroup test 1", RemoveSiblingNodesRecordGroupTest1);
}

void MasterFileTests::ConstructionTest1(Test& test)
{
    DiplodocusDB::MasterFile masterFile;

    ISHTF_PASS();
}

void MasterFileTests::CreateTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "MasterFileTests_CreateTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.create(outputPath, error);

    ISHTF_FAIL_IF((bool)error);

    masterFile.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "MasterFileTests_CreateTest1.dpdb");

    ISHTF_PASS();
}

void MasterFileTests::OpenTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "MasterFileTests_OpenTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::RecordMarker rootMarker = masterFile.rootNodePosition();

    ISHTF_FAIL_UNLESS(rootMarker.position().page() == 0);
    ISHTF_FAIL_UNLESS(rootMarker.position().offset() == 15);

    DiplodocusDB::RecordMarker dataEndMarker = masterFile.dataEndPosition();

    ISHTF_FAIL_UNLESS(dataEndMarker.position().page() == 0);
    ISHTF_FAIL_UNLESS(dataEndMarker.position().offset() == 20);

    ISHTF_PASS();
}

void MasterFileTests::OpenTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "MasterFileTests_OpenTest2.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::RecordMarker rootMarker = masterFile.rootNodePosition();

    ISHTF_FAIL_UNLESS(rootMarker.position().page() == 0);
    ISHTF_FAIL_UNLESS(rootMarker.position().offset() == 15);

    DiplodocusDB::RecordMarker dataEndMarker = masterFile.dataEndPosition();

    ISHTF_FAIL_UNLESS(dataEndMarker.position().page() == 0);
    ISHTF_FAIL_UNLESS(dataEndMarker.position().offset() == 30);

    ISHTF_PASS();
}

void MasterFileTests::OpenTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "MasterFileTests_OpenTest3.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    // Get the root node record group. This only ever contains one node, the root, and has no parent node ID.
    // The record group can be found by passing 0 as the parent Node ID.
    DiplodocusDB::SiblingNodesRecordGroup siblingsNodesRecordGroup1;
    bool found1 = masterFile.findSiblingNodesRecordGroup(DiplodocusDB::NodeID(0), siblingsNodesRecordGroup1, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(found1);
    ISHTF_ABORT_UNLESS(siblingsNodesRecordGroup1.size() == 1);
    ISHTF_FAIL_UNLESS(siblingsNodesRecordGroup1[0].name() == "/");

    DiplodocusDB::SiblingNodesRecordGroup siblingsNodesRecordGroup2;
    bool found2 = masterFile.findSiblingNodesRecordGroup(DiplodocusDB::NodeID(1), siblingsNodesRecordGroup2, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(found2);
    ISHTF_ABORT_UNLESS(siblingsNodesRecordGroup2.size() == 521);
    ISHTF_FAIL_UNLESS(siblingsNodesRecordGroup2[0].name() == "key0");
    ISHTF_FAIL_UNLESS(siblingsNodesRecordGroup2[520].name() == "k123");

    ISHTF_PASS();
}

void MasterFileTests::OpenTest4(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "MasterFileTests_OpenTest4.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    // Get the root node record group. This only ever contains one node, the root, and has no parent node ID.
    // The record group can be found by passing 0 as the parent Node ID.
    DiplodocusDB::SiblingNodesRecordGroup siblingsNodesRecordGroup1;
    bool found1 = masterFile.findSiblingNodesRecordGroup(DiplodocusDB::NodeID(0), siblingsNodesRecordGroup1, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(found1);
    ISHTF_ABORT_UNLESS(siblingsNodesRecordGroup1.size() == 1);
    ISHTF_FAIL_UNLESS(siblingsNodesRecordGroup1[0].name() == "/");

    DiplodocusDB::SiblingNodesRecordGroup siblingsNodesRecordGroup2;
    bool found2 = masterFile.findSiblingNodesRecordGroup(DiplodocusDB::NodeID(1), siblingsNodesRecordGroup2, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(found2);
    ISHTF_ABORT_UNLESS(siblingsNodesRecordGroup2.size() == 1000000);
    ISHTF_FAIL_UNLESS(siblingsNodesRecordGroup2[0].name() == "key0");
    ISHTF_FAIL_UNLESS(siblingsNodesRecordGroup2[999999].name() == "key999999");

    ISHTF_PASS();
}

void MasterFileTests::AddSiblingNodesRecordGroupTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    // Create a node whose parent is the root (ID 1)
    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), "key1");
    masterFile.addSiblingNodesRecordGroup(DiplodocusDB::SiblingNodesRecordGroup(newNode), error);

    ISHTF_FAIL_IF((bool)error);

    masterFile.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest1.dpdb");

    ISHTF_PASS();
}

void MasterFileTests::AddSiblingNodesRecordGroupTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest2.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    // Create a node whose parent is the root (ID 1) and has a node ID as it will be the parent of another node
    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode1(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(2), "key1");
    masterFile.addSiblingNodesRecordGroup(DiplodocusDB::SiblingNodesRecordGroup(newNode1), error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode2(DiplodocusDB::NodeID(2), DiplodocusDB::NodeID(0), "key1_1");
    masterFile.addSiblingNodesRecordGroup(DiplodocusDB::SiblingNodesRecordGroup(newNode2), error);

    ISHTF_FAIL_IF((bool)error);

    masterFile.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest2.dpdb");

    ISHTF_PASS();
}

void MasterFileTests::AddSiblingNodesRecordGroupTest3(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest3.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    // Create a node whose parent is the root (ID 1)
    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode1(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), "key1");
    // Create a second node whose parent is the root (ID 1)
    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode2(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), "key2");
    DiplodocusDB::SiblingNodesRecordGroup siblingsNodesRecordGroup;
    siblingsNodesRecordGroup.push_back(newNode1);
    siblingsNodesRecordGroup.push_back(newNode2);
    masterFile.addSiblingNodesRecordGroup(siblingsNodesRecordGroup, error);

    ISHTF_FAIL_IF((bool)error);

    masterFile.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest3.dpdb");

    ISHTF_PASS();
}

/// This test fills a page up to the last byte
void MasterFileTests::AddSiblingNodesRecordGroupTest4(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest4.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::SiblingNodesRecordGroup siblingsNodesRecordGroup;
    for (size_t i = 0; i < 520; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        DiplodocusDB::EmbeddedTreeDBNodeImpl newNode(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), key.str());
        siblingsNodesRecordGroup.push_back(newNode);
    }

    ISHTF_FAIL_IF((bool)error);

    // The name length is exactly the number of characters needed to fill the page
    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), "k12");
    siblingsNodesRecordGroup.push_back(newNode);

    masterFile.addSiblingNodesRecordGroup(siblingsNodesRecordGroup, error);

    ISHTF_FAIL_IF((bool)error);

    masterFile.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest4.dpdb");

    ISHTF_PASS();
}

/// This test uses just one byte more than can be stored in a page
void MasterFileTests::AddSiblingNodesRecordGroupTest5(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest5.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::SiblingNodesRecordGroup siblingsNodesRecordGroup;
    for (size_t i = 0; i < 520; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        DiplodocusDB::EmbeddedTreeDBNodeImpl newNode(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), key.str());
        siblingsNodesRecordGroup.push_back(newNode);
    }

    ISHTF_FAIL_IF((bool)error);

    // The name length is exactly the number of characters needed to fill the page plus one byte
    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), "k123");
    siblingsNodesRecordGroup.push_back(newNode);

    masterFile.addSiblingNodesRecordGroup(siblingsNodesRecordGroup, error);

    masterFile.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest5.dpdb");

    ISHTF_PASS();
}

void MasterFileTests::AddSiblingNodesRecordGroupTest6(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest6.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::SiblingNodesRecordGroup siblingsNodesRecordGroup;
    for (size_t i = 0; i < 10000; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        DiplodocusDB::EmbeddedTreeDBNodeImpl newNode(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), key.str());
        siblingsNodesRecordGroup.push_back(newNode);
    }

    masterFile.addSiblingNodesRecordGroup(siblingsNodesRecordGroup, error);

    ISHTF_FAIL_IF((bool)error);

    masterFile.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest6.dpdb");

    ISHTF_PASS();
}

void MasterFileTests::AddSiblingNodesRecordGroupTest7(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest7.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::SiblingNodesRecordGroup siblingsNodesRecordGroup;
    for (size_t i = 0; i < 100000; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        DiplodocusDB::EmbeddedTreeDBNodeImpl newNode(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), key.str());
        siblingsNodesRecordGroup.push_back(newNode);
    }

    masterFile.addSiblingNodesRecordGroup(siblingsNodesRecordGroup, error);

    ISHTF_FAIL_IF((bool)error);

    masterFile.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest7.dpdb");

    ISHTF_PASS();
}

void MasterFileTests::AddSiblingNodesRecordGroupTest8(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest8.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::SiblingNodesRecordGroup siblingsNodesRecordGroup;
    for (size_t i = 0; i < 1000000; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        DiplodocusDB::EmbeddedTreeDBNodeImpl newNode(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), key.str());
        siblingsNodesRecordGroup.push_back(newNode);
    }

    masterFile.addSiblingNodesRecordGroup(siblingsNodesRecordGroup, error);

    ISHTF_FAIL_IF((bool)error);

    masterFile.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest8.dpdb");

    ISHTF_PASS();
}

void MasterFileTests::AddSiblingNodesRecordGroupTest9(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest9.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    // Create a node whose parent is the root (ID 1)
    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), "key1");
    newNode.value() = DiplodocusDB::TreeDBValue::UTF8String("value1");
    masterFile.addSiblingNodesRecordGroup(DiplodocusDB::SiblingNodesRecordGroup(newNode), error);

    ISHTF_FAIL_IF((bool)error);

    masterFile.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest9.dpdb");

    ISHTF_PASS();
}

void MasterFileTests::AddSiblingNodesRecordGroupTest10(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest10.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    // Create a node whose parent is the root (ID 1)
    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode1(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), "key1");
    newNode1.value() = DiplodocusDB::TreeDBValue::UTF8String("value1");
    // Create a second node whose parent is the root (ID 1)
    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode2(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), "key2");
    newNode2.value() = DiplodocusDB::TreeDBValue::UTF8String("value2");
    DiplodocusDB::SiblingNodesRecordGroup siblingNodesRecordGroup(newNode1);
    siblingNodesRecordGroup.push_back(newNode2);
    masterFile.addSiblingNodesRecordGroup(siblingNodesRecordGroup, error);

    ISHTF_FAIL_IF((bool)error);

    masterFile.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "MasterFileTests_AddSiblingNodesRecordGroupTest10.dpdb");

    ISHTF_PASS();
}

void MasterFileTests::FindSiblingNodesRecordGroupTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "MasterFileTests_OpenTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    // Get the root node record group. This only ever contains one node, the root, and has no parent node ID.
    // The record group can be found by passing 0 as the parent Node ID.
    DiplodocusDB::SiblingNodesRecordGroup siblingsNodesRecordGroup;
    bool found = masterFile.findSiblingNodesRecordGroup(DiplodocusDB::NodeID(0), siblingsNodesRecordGroup, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(found);
    ISHTF_FAIL_UNLESS(siblingsNodesRecordGroup.size() == 1);
    ISHTF_FAIL_UNLESS(siblingsNodesRecordGroup[0].name() == "/");
    ISHTF_PASS();
}

void MasterFileTests::FindSiblingNodesRecordGroupTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "MasterFileTests_OpenTest2.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::SiblingNodesRecordGroup siblingsNodesRecordGroup;
    bool found = masterFile.findSiblingNodesRecordGroup(DiplodocusDB::NodeID(1), siblingsNodesRecordGroup, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(found);
    ISHTF_FAIL_UNLESS(siblingsNodesRecordGroup.size() == 1);
    ISHTF_FAIL_UNLESS(siblingsNodesRecordGroup[0].name() == "key1");
    ISHTF_PASS();
}

void MasterFileTests::FindSiblingNodesRecordGroupTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "MasterFileTests_OpenTest2.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::SiblingNodesRecordGroup siblingsNodesRecordGroup;
    bool found = masterFile.findSiblingNodesRecordGroup(DiplodocusDB::NodeID(3), siblingsNodesRecordGroup, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(!found);
    ISHTF_PASS();
}

void MasterFileTests::RemoveSiblingNodesRecordGroupTest1(Ishiko::Tests::FileComparisonTest& test)
{
}

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
    append<FileComparisonTest>("addNode test 1", AddNodeTest1);
    append<FileComparisonTest>("addNode test 2", AddNodeTest2);
    append<FileComparisonTest>("addNode test 3", AddNodeTest3);
    append<FileComparisonTest>("addNode test 4", AddNodeTest4);
    append<FileComparisonTest>("addNode test 5", AddNodeTest5);
}

void MasterFileTests::ConstructionTest1(Test& test)
{
    DiplodocusDB::MasterFile masterFile;

    ISHTF_PASS();
}

void MasterFileTests::CreateTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "MasterFileTests_CreateTest1.dpdb");

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

void MasterFileTests::AddNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "MasterFileTests_AddNodeTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    // Create a node whose parent is the root (ID 1)
    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), "key1",
        masterFile.dataEndPosition(), DiplodocusDB::RecordMarker(DiplodocusDB::PageRepositoryPosition(0, 0)));
    masterFile.addNode(newNode, error);

    ISHTF_FAIL_IF((bool)error);

    masterFile.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "MasterFileTests_AddNodeTest1.dpdb");

    ISHTF_PASS();
}

void MasterFileTests::AddNodeTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "MasterFileTests_AddNodeTest2.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    // Create a node whose parent is the root (ID 1) and has a node ID as it will be the parent of another node
    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode1(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(2), "key1",
        masterFile.dataEndPosition(), DiplodocusDB::RecordMarker(DiplodocusDB::PageRepositoryPosition(0, 0)));
    masterFile.addNode(newNode1, error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode2(DiplodocusDB::NodeID(2), DiplodocusDB::NodeID(0), "key1_1",
        masterFile.dataEndPosition(), DiplodocusDB::RecordMarker(DiplodocusDB::PageRepositoryPosition(0, 0)));
    masterFile.addNode(newNode2, error);

    ISHTF_FAIL_IF((bool)error);

    masterFile.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "MasterFileTests_AddNodeTest2.dpdb");

    ISHTF_PASS();
}

void MasterFileTests::AddNodeTest3(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "MasterFileTests_AddNodeTest3.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    // Create a node whose parent is the root (ID 1)
    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode1(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), "key1",
        masterFile.dataEndPosition(), DiplodocusDB::RecordMarker(DiplodocusDB::PageRepositoryPosition(0, 0)));
    masterFile.addNode(newNode1, error);

    ISHTF_FAIL_IF((bool)error);

    // Create a second node whose parent is the root (ID 1)
    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode2(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), "key2",
        masterFile.dataEndPosition(), DiplodocusDB::RecordMarker(DiplodocusDB::PageRepositoryPosition(0, 0)));
    masterFile.addNode(newNode2, error);

    ISHTF_FAIL_IF((bool)error);

    masterFile.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "MasterFileTests_AddNodeTest3.dpdb");

    ISHTF_PASS();
}

/// This test fills a page up to the last byte
void MasterFileTests::AddNodeTest4(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "MasterFileTests_AddNodeTest4.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    for (size_t i = 0; i < 346; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        DiplodocusDB::EmbeddedTreeDBNodeImpl newNode(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), key.str(),
            masterFile.dataEndPosition(), DiplodocusDB::RecordMarker(DiplodocusDB::PageRepositoryPosition(0, 0)));
        masterFile.addNode(newNode, error);
        if (error)
        {
            break;
        }
    }

    ISHTF_FAIL_IF((bool)error);

    // The name length is exactly the number of characters needed to fill the page
    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), "key34612345",
        masterFile.dataEndPosition(), DiplodocusDB::RecordMarker(DiplodocusDB::PageRepositoryPosition(0, 0)));
    masterFile.addNode(newNode, error);

    ISHTF_FAIL_IF((bool)error);

    masterFile.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "MasterFileTests_AddNodeTest4.dpdb");

    ISHTF_PASS();
}

/// This test uses just one byte more than can be stored in a page
void MasterFileTests::AddNodeTest5(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "MasterFileTests_AddNodeTest5.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::MasterFile masterFile;
    masterFile.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    for (size_t i = 0; i < 346; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        DiplodocusDB::EmbeddedTreeDBNodeImpl newNode(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), key.str(),
            masterFile.dataEndPosition(), DiplodocusDB::RecordMarker(DiplodocusDB::PageRepositoryPosition(0, 0)));
        masterFile.addNode(newNode, error);
        if (error)
        {
            break;
        }
    }

    ISHTF_FAIL_IF((bool)error);

    // The name length is exactly the number of characters needed to fill the page plus one byte
    DiplodocusDB::EmbeddedTreeDBNodeImpl newNode(DiplodocusDB::NodeID(1), DiplodocusDB::NodeID(0), "key346123456",
        masterFile.dataEndPosition(), DiplodocusDB::RecordMarker(DiplodocusDB::PageRepositoryPosition(0, 0)));
    masterFile.addNode(newNode, error);

    ISHTF_FAIL_IF((bool)error);

    masterFile.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "MasterFileTests_AddNodeTest5.dpdb");

    ISHTF_PASS();
}

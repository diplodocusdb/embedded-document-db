/*
    Copyright (c) 2019 Xavier Leclercq

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

#include "CachedRecordFilesSetTests.h"
#include "CachedRecordFilesSet.h"

using namespace Ishiko::Tests;

CachedRecordFilesSetTests::CachedRecordFilesSetTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "CachedRecordFilesSet tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructionTest1);
    append<FileComparisonTest>("createMasterFile test 1", CreateMasterFileTest1);
    append<HeapAllocationErrorsTest>("openMasterFile test 1", OpenMasterFileTest1);
    append<HeapAllocationErrorsTest>("openMasterFile test 2", OpenMasterFileTest2);
    append<HeapAllocationErrorsTest>("findSiblingNodesRecordGroup test 1", FindSiblingNodesRecordGroupTest1);
    append<HeapAllocationErrorsTest>("findSiblingNodesRecordGroup test 2", FindSiblingNodesRecordGroupTest2);
    append<HeapAllocationErrorsTest>("findSiblingNodesRecordGroup test 3", FindSiblingNodesRecordGroupTest3);
}

void CachedRecordFilesSetTests::ConstructionTest1(Test& test)
{
    DiplodocusDB::CachedRecordFilesSet cachedSet;

    ISHTF_PASS();
}

void CachedRecordFilesSetTests::CreateMasterFileTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "MasterFileTests_CreateTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::CachedRecordFilesSet cachedSet;
    cachedSet.createMasterFile(outputPath, error);

    ISHTF_FAIL_IF((bool)error);

    cachedSet.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "MasterFileTests_CreateTest1.dpdb");

    ISHTF_PASS();
}

void CachedRecordFilesSetTests::OpenMasterFileTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "MasterFileTests_OpenTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::CachedRecordFilesSet cachedSet;
    cachedSet.openMasterFile(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    // Get the root node record group. This only ever contains one node, the root, and has no parent node ID.
    // The record group can be found by passing 0 as the parent Node ID.
    std::shared_ptr<DiplodocusDB::SiblingNodesRecordGroup> siblingsNodesRecordGroup;
    bool found = cachedSet.findSiblingNodesRecordGroup(DiplodocusDB::NodeID(0), siblingsNodesRecordGroup, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(found);
    ISHTF_FAIL_UNLESS(siblingsNodesRecordGroup->size() == 1);
    ISHTF_FAIL_UNLESS((*siblingsNodesRecordGroup)[0].name() == "/");
    ISHTF_PASS();
}

void CachedRecordFilesSetTests::OpenMasterFileTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "MasterFileTests_OpenTest2.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::CachedRecordFilesSet cachedSet;
    cachedSet.openMasterFile(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::SiblingNodesRecordGroup> siblingsNodesRecordGroup;
    bool found = cachedSet.findSiblingNodesRecordGroup(DiplodocusDB::NodeID(1), siblingsNodesRecordGroup, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(found);
    ISHTF_FAIL_UNLESS(siblingsNodesRecordGroup->size() == 1);
    ISHTF_FAIL_UNLESS((*siblingsNodesRecordGroup)[0].name() == "key1");
    ISHTF_PASS();
}

void CachedRecordFilesSetTests::FindSiblingNodesRecordGroupTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "MasterFileTests_OpenTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::CachedRecordFilesSet cachedSet;
    cachedSet.openMasterFile(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    // Get the root node record group. This only ever contains one node, the root, and has no parent node ID.
    // The record group can be found by passing 0 as the parent Node ID.
    std::shared_ptr<DiplodocusDB::SiblingNodesRecordGroup> siblingsNodesRecordGroup1;
    bool found1 = cachedSet.findSiblingNodesRecordGroup(DiplodocusDB::NodeID(0), siblingsNodesRecordGroup1, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(found1);
    ISHTF_FAIL_UNLESS(siblingsNodesRecordGroup1->size() == 1);
    ISHTF_FAIL_UNLESS((*siblingsNodesRecordGroup1)[0].name() == "/");

    // Verify the cache is working as expected
    std::shared_ptr<DiplodocusDB::SiblingNodesRecordGroup> siblingsNodesRecordGroup2;
    bool found2 = cachedSet.findSiblingNodesRecordGroup(DiplodocusDB::NodeID(0), siblingsNodesRecordGroup2, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(found2);
    ISHTF_FAIL_UNLESS(siblingsNodesRecordGroup1.get() == siblingsNodesRecordGroup2.get());

    ISHTF_PASS();
}

void CachedRecordFilesSetTests::FindSiblingNodesRecordGroupTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "MasterFileTests_OpenTest2.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::CachedRecordFilesSet cachedSet;
    cachedSet.openMasterFile(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::SiblingNodesRecordGroup> siblingsNodesRecordGroup1;
    bool found1 = cachedSet.findSiblingNodesRecordGroup(DiplodocusDB::NodeID(1), siblingsNodesRecordGroup1, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(found1);
    ISHTF_FAIL_UNLESS(siblingsNodesRecordGroup1->size() == 1);
    ISHTF_FAIL_UNLESS((*siblingsNodesRecordGroup1)[0].name() == "key1");

    // Verify the cache is working as expected
    std::shared_ptr<DiplodocusDB::SiblingNodesRecordGroup> siblingsNodesRecordGroup2;
    bool found2 = cachedSet.findSiblingNodesRecordGroup(DiplodocusDB::NodeID(1), siblingsNodesRecordGroup2, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(found2);
    ISHTF_FAIL_UNLESS(siblingsNodesRecordGroup1.get() == siblingsNodesRecordGroup2.get());

    ISHTF_PASS();
}

void CachedRecordFilesSetTests::FindSiblingNodesRecordGroupTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "MasterFileTests_OpenTest2.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::CachedRecordFilesSet cachedSet;
    cachedSet.openMasterFile(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::SiblingNodesRecordGroup> siblingsNodesRecordGroup1;
    bool found1 = cachedSet.findSiblingNodesRecordGroup(DiplodocusDB::NodeID(3), siblingsNodesRecordGroup1, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(!found1);

    // Verify the cache is working as expected
    std::shared_ptr<DiplodocusDB::SiblingNodesRecordGroup> siblingsNodesRecordGroup2;
    bool found2 = cachedSet.findSiblingNodesRecordGroup(DiplodocusDB::NodeID(3), siblingsNodesRecordGroup2, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(!found2);

    ISHTF_PASS();
}

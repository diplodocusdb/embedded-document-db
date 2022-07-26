/*
    Copyright (c) 2019-2022 Xavier Leclercq

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

#include "SiblingNodesRecordGroupTests.h"
#include "DiplodocusDB/EmbeddedDocumentDB/SiblingNodesRecordGroup.h"
#include "DiplodocusDB/PhysicalStorage/PageRepository/PageFileRepository.h"

using namespace DiplodocusDB;
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
    DiplodocusDB::SiblingNodesRecordGroup siblingNodesRecordGroup;

    ISHIKO_TEST_PASS();
}

void SiblingNodesRecordGroupTests::WriteTest1(Test& test)
{
    const char* testName = "SiblingNodesRecordGroupTests_WriteTest1.dpdb";
    
    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::SiblingNodesRecordGroup siblingNodesRecordGroup;
    siblingNodesRecordGroup.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void SiblingNodesRecordGroupTests::WriteTest2(Test& test)
{
    const char* testName = "SiblingNodesRecordGroupTests_WriteTest2.dpdb";

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    // Create a root node
    SiblingNodeRecordGroup sibling("/", NodeID(1));
    SiblingNodesRecordGroup siblingNodesRecordGroup(NodeID(0), sibling);
    siblingNodesRecordGroup.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void SiblingNodesRecordGroupTests::WriteTest3(Test& test)
{
    const char* testName = "SiblingNodesRecordGroupTests_WriteTest3.dpdb";
   
    Error error;

    PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    // TODO: is this test correct? Why is the root node id 1 and the child 0?
    SiblingNodeRecordGroup sibling("name1", NodeID(0));
    SiblingNodesRecordGroup siblingNodesRecordGroup(NodeID(1), sibling);
    siblingNodesRecordGroup.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void SiblingNodesRecordGroupTests::WriteTest4(Test& test)
{
    const char* testName = "SiblingNodesRecordGroupTests_WriteTest4.dpdb";

    Error error;

    PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    // TODO: is this test correct? Why is the root node id 1 and both children 0?
    SiblingNodeRecordGroup sibling1("name1", NodeID(0));
    SiblingNodesRecordGroup siblingNodesRecordGroup(NodeID(1), sibling1);
    SiblingNodeRecordGroup sibling2("name2", NodeID(0));
    siblingNodesRecordGroup.push_back(sibling2);
    siblingNodesRecordGroup.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

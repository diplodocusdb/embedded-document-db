/*
    Copyright (c) 2018-2022 Xavier Leclercq

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

#include "EmbeddedTreeDBTests.h"
#include "DiplodocusDB/EmbeddedDocumentDB/EmbeddedTreeDB.h"
#include <boost/filesystem/operations.hpp>
#include <sstream>

using namespace Ishiko;

EmbeddedTreeDBTests::EmbeddedTreeDBTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "EmbeddedTreeDB tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("create test 1", CreateTest1);
    append<HeapAllocationErrorsTest>("open test 1", OpenTest1);
    append<HeapAllocationErrorsTest>("open test 2", OpenTest2);
    append<HeapAllocationErrorsTest>("open test 3", OpenTest3);
    append<HeapAllocationErrorsTest>("open test 4", OpenTest4);
    append<HeapAllocationErrorsTest>("open test 5", OpenTest5);
    append<HeapAllocationErrorsTest>("childNodes test 1", ChildNodesTest1);
    append<HeapAllocationErrorsTest>("childNodes test 2", ChildNodesTest2);
    append<HeapAllocationErrorsTest>("insertChildNode test 1", InsertChildNodeTest1);
    append<HeapAllocationErrorsTest>("insertChildNodeBefore test 1", InsertChildNodeBeforeTest1);
    append<HeapAllocationErrorsTest>("insertChildNodeBefore test 2", InsertChildNodeBeforeTest2);
    append<HeapAllocationErrorsTest>("insertChildNodeBefore test 3", InsertChildNodeBeforeTest3);
    append<HeapAllocationErrorsTest>("insertChildNodeAfter test 1", InsertChildNodeAfterTest1);
    append<HeapAllocationErrorsTest>("insertChildNodeAfter test 2", InsertChildNodeAfterTest2);
    append<HeapAllocationErrorsTest>("appendChildNode test 1", AppendChildNodeTest1);
    append<HeapAllocationErrorsTest>("appendChildNode test 2", AppendChildNodeTest2);
    append<HeapAllocationErrorsTest>("appendChildNode test 3", AppendChildNodeTest3);
    append<HeapAllocationErrorsTest>("appendChildNode test 4", AppendChildNodeTest4);
    append<HeapAllocationErrorsTest>("appendChildNode test 5", AppendChildNodeTest5);
    append<HeapAllocationErrorsTest>("appendChildNode test 6", AppendChildNodeTest6);
    append<HeapAllocationErrorsTest>("removeChildNode test 1", RemoveChildNodeTest1);
    append<HeapAllocationErrorsTest>("removeAllChildNodes test 1", RemoveAllChildNodesTest1);
}

void EmbeddedTreeDBTests::CreationTest1(Test& test)
{
    DiplodocusDB::EmbeddedTreeDB db;

    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::CreateTest1(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_CreateTest1.dpdb";

    Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_FAIL_IF(error);
    
    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::OpenTest1(Test& test)
{
    Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(test.context().getDataPath("EmptyEmbeddedTreeDB.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode& node = db.root();

    ISHIKO_TEST_FAIL_IF_NOT(node.isRoot());
   
    std::vector<DiplodocusDB::TreeDBNode> children = db.childNodes(node, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(children.size(), 0);
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::OpenTest2(Test& test)
{
    Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(test.context().getDataPath("EmbeddedTreeDBTests_OpenTest2.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);

    DiplodocusDB::TreeDBValue value = db.value(node, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value.type(), DiplodocusDB::PrimitiveDataType::null);
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::OpenTest3(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory() / "EmbeddedTreeDBTests_OpenTest3.dpdb");

    DiplodocusDB::EmbeddedTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.child(db.root(), "key1", error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::TreeDBValue value1 = db.value(node1, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(value1.type() == DiplodocusDB::PrimitiveDataType::null);

    DiplodocusDB::TreeDBNode node2 = db.child(db.root(), "key2", error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::TreeDBValue value2 = db.value(node2, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(value2.type() == DiplodocusDB::PrimitiveDataType::null);

    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::OpenTest4(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory() / "EmbeddedTreeDBTests_OpenTest4.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::TreeDBValue value = db.value(node, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(value.asUTF8String() == "value1");
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::OpenTest5(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory() / "EmbeddedTreeDBTests_OpenTest5.dpdb");

    DiplodocusDB::EmbeddedTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node1 = db.child(db.root(), "key1", error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::TreeDBValue value1 = db.value(node1, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(value1.asUTF8String() == "value1");
    
    DiplodocusDB::TreeDBNode node2 = db.child(db.root(), "key2", error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::TreeDBValue value2 = db.value(node2, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(value2.asUTF8String() == "value2");
        
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::ChildNodesTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory() / "EmptyEmbeddedTreeDB.dpdb");

    DiplodocusDB::EmbeddedTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    std::vector<DiplodocusDB::TreeDBNode> children = db.childNodes(db.root(), error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(children.size() == 0);
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::ChildNodesTest2(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory() / "EmbeddedTreeDBTests_ChildNodesTest2.dpdb");

    DiplodocusDB::EmbeddedTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    std::vector<DiplodocusDB::TreeDBNode> children = db.childNodes(db.root(), error);
 
    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(children.size() == 1);
    ISHTF_FAIL_UNLESS(children[0].name() == "key1");
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::InsertChildNodeTest1(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_InsertChildNodeTest1.dpdb";
    
    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node = db.insertChildNode(db.root(), 0, "key1", error);
        
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::InsertChildNodeBeforeTest1(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_InsertChildNodeBeforeTest1.dpdb";
    boost::filesystem::path inputPath = test.context().getDataPath(testName);
    boost::filesystem::path outputPath = test.context().getOutputPath(testName);

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);

    ISHIKO_TEST_ABORT_IF(error);
        
    DiplodocusDB::TreeDBNode newNode = db.insertChildNodeBefore(db.root(), node, "key0", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::InsertChildNodeBeforeTest2(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_InsertChildNodeBeforeTest2.dpdb";
    boost::filesystem::path inputPath = test.context().getDataPath(testName);
    boost::filesystem::path outputPath = test.context().getOutputPath(testName);

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key2", error);

    ISHIKO_TEST_ABORT_IF(error);
        
    DiplodocusDB::TreeDBNode newNode1 = db.insertChildNodeBefore(db.root(), node, "key1", error);
    
    ISHIKO_TEST_ABORT_IF(error);
            
    DiplodocusDB::TreeDBNode newNode2 = db.insertChildNodeBefore(db.root(), newNode1, "key0", error);

    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::InsertChildNodeBeforeTest3(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_InsertChildNodeBeforeTest3.dpdb";
    boost::filesystem::path inputPath = test.context().getDataPath(testName);
    boost::filesystem::path outputPath = test.context().getOutputPath(testName);

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key2", error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode newNode1 = db.insertChildNodeBefore(db.root(), node, "key1", error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode newNode2 = db.insertChildNodeBefore(db.root(), newNode1, "key0", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::InsertChildNodeAfterTest1(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_InsertChildNodeAfterTest1.dpdb";
    boost::filesystem::path inputPath = test.context().getDataPath(testName);
    boost::filesystem::path outputPath = test.context().getOutputPath(testName);

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);
    
    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode newNode = db.insertChildNodeAfter(db.root(), node, "key2", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::InsertChildNodeAfterTest2(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_InsertChildNodeAfterTest2.dpdb";
    boost::filesystem::path inputPath = test.context().getDataPath(testName);
    boost::filesystem::path outputPath = test.context().getOutputPath(testName);

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);
    
    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode newNode = db.insertChildNodeAfter(db.root(), node, "key2", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::AppendChildNodeTest1(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_AppendChildNodeTest1.dpdb";

    Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(test.context().getOutputPath("EmbeddedTreeDBTests_AppendChildNodeTest1.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode node = db.appendChildNode(db.root(), "key1", error);
    
    ISHIKO_TEST_FAIL_IF(error);
    
    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::AppendChildNodeTest2(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_AppendChildNodeTest2.dpdb";
    
    Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node1 = db.appendChildNode(db.root(), "key1", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    DiplodocusDB::TreeDBNode node2 = db.appendChildNode(db.root(), "key2", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::AppendChildNodeTest3(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_AppendChildNodeTest3.dpdb";

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode node = db.appendChildNode(db.root(), "key1",
        DiplodocusDB::TreeDBValue::UTF8String("value1"), error);

    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::AppendChildNodeTest4(Test& test)
{
    boost::filesystem::path outputPath(test.context().getTestOutputDirectory() / "EmbeddedTreeDBTests_AppendChildNodeTest4.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node1 = db.appendChildNode(db.root(), "key1", 
        DiplodocusDB::TreeDBValue::UTF8String("value1"), error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::TreeDBNode node2 = db.appendChildNode(db.root(), "key2", 
        DiplodocusDB::TreeDBValue::UTF8String("value2"), error);

    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.context().getReferenceDataDirectory() / "EmbeddedTreeDBTests_AppendChildNodeTest4.dpdb");

    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::AppendChildNodeTest5(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_AppendChildNodeTest5.dpdb";

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    for (size_t i = 0; i < 523; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        DiplodocusDB::TreeDBNode node = db.appendChildNode(db.root(), key.str(), error);
        if (error)
        {
            break;
        }
    }
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::AppendChildNodeTest6(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory() / "EmptyEmbeddedTreeDB.dpdb");
    boost::filesystem::path outputPath(test.context().getTestOutputDirectory() / "EmbeddedTreeDBTests_AppendChildNodeTest6.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode node1 = db.appendChildNode(db.root(), "key1", error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::TreeDBNode node2 = db.appendChildNode(node1, "key2", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.context().getReferenceDataDirectory() / "EmbeddedTreeDBTests_AppendChildNodeTest6.dpdb");

    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::RemoveChildNodeTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory() / "EmbeddedTreeDBTests_RemoveChildNodeTest1.dpdb");
    boost::filesystem::path outputPath(test.context().getTestOutputDirectory() / "EmbeddedTreeDBTests_RemoveChildNodeTest1.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    db.removeChildNode(db.root(), "key1", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.context().getReferenceDataDirectory() / "EmbeddedTreeDBTests_RemoveChildNodeTest1.dpdb");

    ISHIKO_TEST_PASS();
}

void EmbeddedTreeDBTests::RemoveAllChildNodesTest1(Test& test)
{
}

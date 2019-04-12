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

#include "EmbeddedTreeDBTests.h"
#include "DiplodocusDB/TreeDB/EmbeddedTreeDB/EmbeddedTreeDB.h"
#include <boost/filesystem/operations.hpp>
#include <sstream>

using namespace Ishiko::Tests;

EmbeddedTreeDBTests::EmbeddedTreeDBTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "EmbeddedTreeDB tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<FileComparisonTest>("create test 1", CreateTest1);
    append<HeapAllocationErrorsTest>("open test 1", OpenTest1);
    append<HeapAllocationErrorsTest>("open test 2", OpenTest2);
    append<HeapAllocationErrorsTest>("open test 3", OpenTest3);
    append<HeapAllocationErrorsTest>("open test 4", OpenTest4);
    append<HeapAllocationErrorsTest>("open test 5", OpenTest5);
    append<HeapAllocationErrorsTest>("childNodes test 1", ChildNodesTest1);
    append<HeapAllocationErrorsTest>("childNodes test 2", ChildNodesTest2);
    append<FileComparisonTest>("insertChildNode test 1", InsertChildNodeTest1);
    append<FileComparisonTest>("insertChildNodeBefore test 1", InsertChildNodeBeforeTest1);
    append<FileComparisonTest>("insertChildNodeBefore test 2", InsertChildNodeBeforeTest2);
    append<FileComparisonTest>("insertChildNodeBefore test 3", InsertChildNodeBeforeTest3);
    append<FileComparisonTest>("insertChildNodeAfter test 1", InsertChildNodeAfterTest1);
    append<FileComparisonTest>("insertChildNodeAfter test 2", InsertChildNodeAfterTest2);
    append<FileComparisonTest>("appendChildNode test 1", AppendChildNodeTest1);
    append<FileComparisonTest>("appendChildNode test 2", AppendChildNodeTest2);
    append<FileComparisonTest>("appendChildNode test 3", AppendChildNodeTest3);
    append<FileComparisonTest>("appendChildNode test 4", AppendChildNodeTest4);
    append<FileComparisonTest>("appendChildNode test 5", AppendChildNodeTest5);
    append<FileComparisonTest>("appendChildNode test 6", AppendChildNodeTest6);
    append<FileComparisonTest>("removeChildNode test 1", RemoveChildNodeTest1);
}

void EmbeddedTreeDBTests::CreationTest1(Test& test)
{
    DiplodocusDB::EmbeddedTreeDB db;

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::CreateTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBTests_CreateTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_FAIL_IF((bool)error);
    
    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBTests_CreateTest1.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::OpenTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyEmbeddedTreeDB.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode& node = db.root();

    ISHTF_FAIL_UNLESS(node.isRoot());
   
    std::vector<DiplodocusDB::TreeDBNode> children = db.childNodes(node, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(children.size() == 0);
    ISHTF_PASS();
}

void EmbeddedTreeDBTests::OpenTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBTests_OpenTest2.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node.value().type() == DiplodocusDB::EPrimitiveDataType::eNULL);
    ISHTF_PASS();
}

void EmbeddedTreeDBTests::OpenTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBTests_OpenTest3.dpdb");

    DiplodocusDB::EmbeddedTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.child(db.root(), "key1", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node1.value().type() == DiplodocusDB::EPrimitiveDataType::eNULL);

    DiplodocusDB::TreeDBNode node2 = db.child(db.root(), "key2", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node2.value().type() == DiplodocusDB::EPrimitiveDataType::eNULL);

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::OpenTest4(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBOpenTest4.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node.value().asUTF8String() == "value1");
    ISHTF_PASS();
}

void EmbeddedTreeDBTests::OpenTest5(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBOpenTest5.dpdb");

    DiplodocusDB::EmbeddedTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node1 = db.child(db.root(), "key1", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node1.value().asUTF8String() == "value1");
    
    DiplodocusDB::TreeDBNode node2 = db.child(db.root(), "key2", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node2.value().asUTF8String() == "value2");
        
    ISHTF_PASS();
}

void EmbeddedTreeDBTests::ChildNodesTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyEmbeddedTreeDB.dpdb");

    DiplodocusDB::EmbeddedTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    std::vector<DiplodocusDB::TreeDBNode> children = db.childNodes(db.root(), error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(children.size() == 0);
    ISHTF_PASS();
}

void EmbeddedTreeDBTests::ChildNodesTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBOneNullKey.dpdb");

    DiplodocusDB::EmbeddedTreeDB db;

    Ishiko::Error error;
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    std::vector<DiplodocusDB::TreeDBNode> children = db.childNodes(db.root(), error);
 
    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(children.size() == 1);
    ISHTF_PASS();
}

void EmbeddedTreeDBTests::InsertChildNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBTests_InsertChildNodeTest1.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.insertChildNode(db.root(), 0, "key1", error);
        
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBTests_InsertChildNodeTest1.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::InsertChildNodeBeforeTest1(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBTests_InsertChildNodeBeforeTest1.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBTests_InsertChildNodeBeforeTest1.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);

    ISHTF_ABORT_IF((bool)error);
        
    DiplodocusDB::TreeDBNode newNode = db.insertChildNodeBefore(db.root(), node, "key0", error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBTests_InsertChildNodeBeforeTest1.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::InsertChildNodeBeforeTest2(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBTests_InsertChildNodeBeforeTest2.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBTests_InsertChildNodeBeforeTest2.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key2", error);

    ISHTF_ABORT_IF((bool)error);
        
    DiplodocusDB::TreeDBNode newNode1 = db.insertChildNodeBefore(db.root(), node, "key1", error);
    
    ISHTF_ABORT_IF((bool)error);
            
    DiplodocusDB::TreeDBNode newNode2 = db.insertChildNodeBefore(db.root(), newNode1, "key0", error);

    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBTests_InsertChildNodeBeforeTest2.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::InsertChildNodeBeforeTest3(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBTests_InsertChildNodeBeforeTest3.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBTests_InsertChildNodeBeforeTest3.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key2", error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode newNode1 = db.insertChildNodeBefore(db.root(), node, "key1", error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode newNode2 = db.insertChildNodeBefore(db.root(), newNode1, "key0", error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBTests_InsertChildNodeBeforeTest3.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::InsertChildNodeAfterTest1(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBTests_InsertChildNodeAfterTest1.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBTests_InsertChildNodeAfterTest1.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);
    
    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode newNode = db.insertChildNodeAfter(db.root(), node, "key2", error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBTests_InsertChildNodeAfterTest1.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::InsertChildNodeAfterTest2(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBTests_InsertChildNodeAfterTest2.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBTests_InsertChildNodeAfterTest2.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);
    
    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode newNode = db.insertChildNodeAfter(db.root(), node, "key2", error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBTests_InsertChildNodeAfterTest2.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::AppendChildNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBTests_AppendChildNodeTest1.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node = db.appendChildNode(db.root(), "key1", error);
    
    ISHTF_FAIL_IF((bool)error);
    
    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBTests_AppendChildNodeTest1.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::AppendChildNodeTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBTests_AppendChildNodeTest2.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.appendChildNode(db.root(), "key1", error);
    
    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::TreeDBNode node2 = db.appendChildNode(db.root(), "key2", error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBTests_AppendChildNodeTest2.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::AppendChildNodeTest3(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBTests_AppendChildNodeTest3.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node = db.appendChildNode(db.root(), "key1",
        DiplodocusDB::TreeDBValue::UTF8String("value1"), error);

    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBTests_AppendChildNodeTest3.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::AppendChildNodeTest4(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBTests_AppendChildNodeTest4.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.appendChildNode(db.root(), "key1", 
        DiplodocusDB::TreeDBValue::UTF8String("value1"), error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::TreeDBNode node2 = db.appendChildNode(db.root(), "key2", 
        DiplodocusDB::TreeDBValue::UTF8String("value2"), error);

    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBTests_AppendChildNodeTest4.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::AppendChildNodeTest5(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBTests_AppendChildNodeTest5.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
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
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBTests_AppendChildNodeTest5.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::AppendChildNodeTest6(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyEmbeddedTreeDB.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBTests_AppendChildNodeTest6.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node1 = db.appendChildNode(db.root(), "key1", error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node2 = db.appendChildNode(node1, "key2", error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBTests_AppendChildNodeTest6.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::RemoveChildNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBTests_RemoveChildNodeTest1.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBTests_RemoveChildNodeTest1.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    db.removeChildNode(db.root(), "key1", error);
    
    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBTests_RemoveChildNodeTest1.dpdb");

    ISHTF_PASS();
}

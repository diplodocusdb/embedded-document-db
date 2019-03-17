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
    append<HeapAllocationErrorsTest>("children test 1", ChildrenTest1);
    append<HeapAllocationErrorsTest>("children test 2", ChildrenTest2);
    append<FileComparisonTest>("insert test 1", InsertTest1);
    append<FileComparisonTest>("insertBefore test 1", InsertBeforeTest1);
    append<FileComparisonTest>("insertBefore test 2", InsertBeforeTest2);
    append<FileComparisonTest>("insertBefore test 3", InsertBeforeTest3);
    append<FileComparisonTest>("insertAfter test 1", InsertAfterTest1);
    append<FileComparisonTest>("insertAfter test 2", InsertAfterTest2);
    append<FileComparisonTest>("append test 1", AppendTest1);
    append<FileComparisonTest>("append test 2", AppendTest2);
    append<FileComparisonTest>("append test 3", AppendTest3);
    append<FileComparisonTest>("append test 4", AppendTest4);
    append<FileComparisonTest>("append test 5", AppendTest5);
    append<FileComparisonTest>("append test 6", AppendTest6);
    append<FileComparisonTest>("remove test 1", RemoveTest1);
}

void EmbeddedTreeDBTests::CreationTest1(Test& test)
{
    DiplodocusDB::EmbeddedTreeDB db;

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::CreateTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBCreateTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_FAIL_IF((bool)error);
    
    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBCreateTest1.dpdb");

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
   
    std::vector<DiplodocusDB::TreeDBNode> children;
    node.children(children, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(children.size() == 0);
    ISHTF_PASS();
}

void EmbeddedTreeDBTests::OpenTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBOpenTest2.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node = db.root().child("key1", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node.value().type() == DiplodocusDB::EPrimitiveDataType::eNULL);
    ISHTF_PASS();
}

void EmbeddedTreeDBTests::OpenTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBOpenTest3.dpdb");

    DiplodocusDB::EmbeddedTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.root().child("key1", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node1.value().type() == DiplodocusDB::EPrimitiveDataType::eNULL);

    DiplodocusDB::TreeDBNode node2 = db.root().child("key2", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node2.value().type() == DiplodocusDB::EPrimitiveDataType::eNULL);

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::OpenTest4(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBOpenTest4.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node = db.root().child("key1", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node.value().asString() == "value1");
    ISHTF_PASS();
}

void EmbeddedTreeDBTests::OpenTest5(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBOpenTest5.dpdb");

    DiplodocusDB::EmbeddedTreeDB db;

    Ishiko::Error error;
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node1 = db.root().child("key1", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node1.value().asString() == "value1");
    
    DiplodocusDB::TreeDBNode node2 = db.root().child("key2", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node2.value().asString() == "value2");
        
    ISHTF_PASS();
}

void EmbeddedTreeDBTests::ChildrenTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyEmbeddedTreeDB.dpdb");

    DiplodocusDB::EmbeddedTreeDB db;

    Ishiko::Error error;
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    std::vector<DiplodocusDB::TreeDBNode> children;
    db.root().children(children, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(children.size() == 0);
    ISHTF_PASS();
}

void EmbeddedTreeDBTests::ChildrenTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBOneNullKey.dpdb");

    DiplodocusDB::EmbeddedTreeDB db;

    Ishiko::Error error;
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    std::vector<DiplodocusDB::TreeDBNode> children;
    db.root().children(children, error);
 
    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(children.size() == 1);
    ISHTF_PASS();
}

void EmbeddedTreeDBTests::InsertTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeInsertTest1.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.root().insert("key1", 0);
    node.commit(error);
        
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeInsertTest1.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::InsertBeforeTest1(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBNodeInsertBeforeTest1.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeInsertBeforeTest1.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.root().child("key1", error);

    ISHTF_ABORT_IF((bool)error);
        
    DiplodocusDB::TreeDBNode newNode = node.insertBefore("key0", node);
    newNode.commit(error);

    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeInsertBeforeTest1.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::InsertBeforeTest2(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBNodeInsertBeforeTest2.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeInsertBeforeTest2.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.root().child("key2", error);

    ISHTF_ABORT_IF((bool)error);
        
    DiplodocusDB::TreeDBNode newNode1 = node.insertBefore("key1", node);
    DiplodocusDB::TreeDBNode newNode2 = node.insertBefore("key0", newNode1);
    newNode1.commit(error);

    ISHTF_FAIL_IF((bool)error);
            
    newNode2.commit(error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeInsertBeforeTest2.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::InsertBeforeTest3(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBNodeInsertBeforeTest3.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeInsertBeforeTest3.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.root().child("key2", error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode newNode1 = node.insertBefore("key1", node);
    DiplodocusDB::TreeDBNode newNode2 = node.insertBefore("key0", newNode1);
    newNode2.commit(error);

    ISHTF_FAIL_IF((bool)error);
    
    newNode1.commit(error);
 
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeInsertBeforeTest2.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::InsertAfterTest1(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBNodeInsertAfterTest1.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeInsertAfterTest1.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node = db.root().child("key1", error);
    
    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode newNode = node.insertAfter("key2", node);
    newNode.commit(error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeInsertAfterTest1.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::InsertAfterTest2(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBNodeInsertAfterTest2.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeInsertAfterTest2.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node = db.root().child("key1", error);
    
    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode newNode = node.insertAfter("key2", node);
    newNode.commit(error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeInsertAfterTest2.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::AppendTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeAppendTest1.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node = db.root().append("key1");
    node.commit(error);

    ISHTF_FAIL_IF((bool)error);
    
    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeAppendTest1.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::AppendTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeAppendTest2.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.root().append("key1");
    node1.commit(error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::TreeDBNode node2 = db.root().append("key2");
    node2.commit(error);

    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeAppendTest2.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::AppendTest3(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeAppendTest3.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node = db.root().append("key1");
    node.value().setString("value1");
    node.commit(error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeAppendTest3.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::AppendTest4(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeAppendTest4.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.root().append("key1");
    node1.value().setString("value1");
    node1.commit(error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::TreeDBNode node2 = db.root().append("key2");
    node2.value().setString("value2");
    node2.commit(error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeAppendTest4.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::AppendTest5(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeAppendTest5.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    for (size_t i = 0; i < 523; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        DiplodocusDB::TreeDBNode node = db.root().append(key.str());
        node.commit(error);
        if (error)
        {
            break;
        }
    }
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeAppendTest5.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::AppendTest6(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyEmbeddedTreeDB.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeAppendTest6.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node1 = db.root().append("key1");
    DiplodocusDB::TreeDBNode node2 = node1.append("key2");
    node1.commit(error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeAppendTest5.dpdb");

    ISHTF_PASS();
}

void EmbeddedTreeDBTests::RemoveTest1(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBNodeRemoveTest1.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeRemoveTest1.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    db.root().remove("key1", error);
    
    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeRemoveTest1.dpdb");

    ISHTF_PASS();
}

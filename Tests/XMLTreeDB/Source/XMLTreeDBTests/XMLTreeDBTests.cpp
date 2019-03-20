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

#include "XMLTreeDBTests.h"
#include "DiplodocusDB/TreeDB/XMLTreeDB/XMLTreeDB.h"
#include <boost/filesystem/operations.hpp>
#include <sstream>

using namespace Ishiko::Tests;

XMLTreeDBTests::XMLTreeDBTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "XMLTreeDB tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<FileComparisonTest>("create test 1", CreateTest1);
    append<HeapAllocationErrorsTest>("open test 1", OpenTest1);
    append<HeapAllocationErrorsTest>("open test 2", OpenTest2);
    append<HeapAllocationErrorsTest>("open test 3", OpenTest3);
    append<HeapAllocationErrorsTest>("open test 4", OpenTest4);
    append<HeapAllocationErrorsTest>("open test 5", OpenTest5);
    append<HeapAllocationErrorsTest>("open test 6", OpenTest6);
    append<HeapAllocationErrorsTest>("parent test 1", ParentTest1);
    append<HeapAllocationErrorsTest>("parent test 2", ParentTest2);
    append<HeapAllocationErrorsTest>("children test 1", ChildrenTest1);
    append<HeapAllocationErrorsTest>("children test 2", ChildrenTest2);
    append<HeapAllocationErrorsTest>("nextSibling test 1", NextSiblingTest1);
    append<HeapAllocationErrorsTest>("nextSibling test 2", NextSiblingTest2);
    append<HeapAllocationErrorsTest>("nextSibling test 3", NextSiblingTest3);
    append<FileComparisonTest>("insert test 1", InsertTest1);
    append<FileComparisonTest>("append test 1", AppendTest1);
    append<FileComparisonTest>("append test 2", AppendTest2);
    append<FileComparisonTest>("append test 3", AppendTest3);
    append<FileComparisonTest>("append test 4", AppendTest4);
    append<FileComparisonTest>("append test 5", AppendTest5);
    append<FileComparisonTest>("append test 6", AppendTest6);
    append<FileComparisonTest>("append test 7", AppendTest7);
    append<FileComparisonTest>("set test 1", SetTest1);
    append<FileComparisonTest>("set test 2", SetTest2);
    append<FileComparisonTest>("removeAll test 1", RemoveAllTest1);
}

void XMLTreeDBTests::CreationTest1(Test& test)
{
    DiplodocusDB::XMLTreeDB db;

    ISHTF_PASS();
}

void XMLTreeDBTests::CreateTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_CreateTest1.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_FAIL_IF((bool)error);
    
    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_CreateTest1.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::OpenTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyXMLTreeDB.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
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

void XMLTreeDBTests::OpenTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_OpenTest2.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.root().child("key1", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node.value().type() == DiplodocusDB::EPrimitiveDataType::eNULL);
    ISHTF_PASS();
}

void XMLTreeDBTests::OpenTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_OpenTest3.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node = db.root().child("key1", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node.value().type() == DiplodocusDB::EPrimitiveDataType::eNULL);
    ISHTF_PASS();
}

void XMLTreeDBTests::OpenTest4(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_OpenTest4.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.root().child("key1", error);

    ISHTF_FAIL_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node2 = db.root().child("key2", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node1.value().type() == DiplodocusDB::EPrimitiveDataType::eNULL);
    ISHTF_FAIL_UNLESS(node2.value().type() == DiplodocusDB::EPrimitiveDataType::eNULL);
    ISHTF_PASS();
}

void XMLTreeDBTests::OpenTest5(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_OpenTest5.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.root().child("key1", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node.value().asString() == "value1");
    ISHTF_PASS();
}

void XMLTreeDBTests::OpenTest6(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_OpenTest6.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.root().child("key1", error);

    ISHTF_FAIL_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node2 = db.root().child("key2", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node1.value().asString() == "value1");
    ISHTF_FAIL_UNLESS(node2.value().asString() == "value2");
    ISHTF_PASS();
}

void XMLTreeDBTests::ParentTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyXMLTreeDB.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode parent = db.root().parent(error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_IF((bool)parent);
    ISHTF_PASS();
}

void XMLTreeDBTests::ParentTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_ParentTest2.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode childNode = db.root().child("key1", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(childNode);
    
    DiplodocusDB::TreeDBNode parentNode = childNode.parent(error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(parentNode == db.root());
    ISHTF_PASS();
}

void XMLTreeDBTests::ChildrenTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyXMLTreeDB.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    std::vector<DiplodocusDB::TreeDBNode> children;
    db.root().children(children, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(children.empty());
    ISHTF_PASS();
}

void XMLTreeDBTests::ChildrenTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_ChildrenTest2.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    std::vector<DiplodocusDB::TreeDBNode> children;
    db.root().children(children, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(children.size() == 1);
    ISHTF_PASS();
}

void XMLTreeDBTests::NextSiblingTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyXMLTreeDB.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode nextSibling = db.root().nextSibling(error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_IF((bool)nextSibling);
    ISHTF_PASS();
}

void XMLTreeDBTests::NextSiblingTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_NextSiblingTest2.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode key1Node = db.root().child("key1", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS((bool)key1Node);

    DiplodocusDB::TreeDBNode nextSibling = key1Node.nextSibling(error);
    
    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_IF((bool)nextSibling);
    ISHTF_PASS();
}

void XMLTreeDBTests::NextSiblingTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_NextSiblingTest3.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode key1Node = db.root().child("key1", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(key1Node);

    DiplodocusDB::TreeDBNode nextSibling = key1Node.nextSibling(error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(nextSibling);
    ISHTF_FAIL_UNLESS(nextSibling.value().type() == DiplodocusDB::EPrimitiveDataType::eNULL);
    
    nextSibling = nextSibling.nextSibling(error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_IF((bool)nextSibling);
    ISHTF_PASS();
}

void XMLTreeDBTests::InsertTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_InsertTest1.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node = db.root().insert("key1", 0);
    db.commitNode(node, error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_InsertTest1.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::AppendTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendTest1.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.root().append("key1");
    db.commitNode(node, error);
        
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendTest1.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::AppendTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendTest2.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.root().append("key1");
    db.commitNode(node1, error);

    ISHTF_FAIL_IF((bool)error);
        
    DiplodocusDB::TreeDBNode node2 = db.root().append("key2");
    db.commitNode(node2, error);

    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendTest2.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::AppendTest3(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendTest3.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.root().append("key1");
    node.value().setString("value1");
    db.commitNode(node, error);

    ISHTF_FAIL_IF((bool)error);
   
    db.close();


    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendTest3.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::AppendTest4(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendTest4.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.root().append("key1");
    node1.value().setString("value1");
    db.commitNode(node1, error);

    ISHTF_FAIL_IF((bool)error);
        
    DiplodocusDB::TreeDBNode node2 = db.root().append("key2");
    node2.value().setString("value2");
    db.commitNode(node2, error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendTest4.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::AppendTest5(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendTest5.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    for (size_t i = 0; i < 523; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        DiplodocusDB::TreeDBNode node = db.root().append(key.str());
        db.commitNode(node, error);
        if (error)
        {
            break;
        }
    }
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendTest5.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::AppendTest6(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyXMLTreeDB.xml");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendTest6.xml");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.root().append("key1");
    DiplodocusDB::TreeDBNode node2 = node1.append("key2");
    db.commitNode(node1, error);

    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendTest6.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::AppendTest7(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendTest7.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.root().append("key1");
    node1.value().setString("value1");
    DiplodocusDB::TreeDBNode node2 = node1.append("key2");
    db.commitNode(db.root(), error);

    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendTest7.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::SetTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_SetTest1.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.root().set("key1", error);
    db.commitNode(node, error);
        
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_SetTest1.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::SetTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_SetTest2.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.root().set("key1", error);
    db.commitNode(node1, error);

    ISHTF_FAIL_IF((bool)error);
        
    DiplodocusDB::TreeDBNode node2 = db.root().set("key1", error);
    db.commitNode(node2, error);

    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_SetTest2.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::RemoveAllTest1(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_RemoveAllTest1.xml");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_RemoveAllTest1.xml");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.root();
    node.removeAll(error);

    ISHTF_FAIL_IF((bool)error);

    db.commitNode(node, error);
        
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_RemoveAllTest1.xml");

    ISHTF_PASS();
}

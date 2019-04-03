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
    append<HeapAllocationErrorsTest>("childNodes test 1", ChildNodesTest1);
    append<HeapAllocationErrorsTest>("childNodes test 2", ChildNodesTest2);
    append<HeapAllocationErrorsTest>("nextSibling test 1", NextSiblingTest1);
    append<HeapAllocationErrorsTest>("nextSibling test 2", NextSiblingTest2);
    append<HeapAllocationErrorsTest>("nextSibling test 3", NextSiblingTest3);
    append<FileComparisonTest>("insertChildNode test 1", InsertChildNodeTest1);
    append<FileComparisonTest>("appendChildNode test 1", AppendChildNodeTest1);
    append<FileComparisonTest>("appendChildNode test 2", AppendChildNodeTest2);
    append<FileComparisonTest>("appendChildNode test 3", AppendChildNodeTest3);
    append<FileComparisonTest>("appendChildNode test 4", AppendChildNodeTest4);
    append<FileComparisonTest>("appendChildNode test 5", AppendChildNodeTest5);
    append<FileComparisonTest>("appendChildNode test 6", AppendChildNodeTest6);
    append<FileComparisonTest>("appendChildNode test 7", AppendChildNodeTest7);
    append<FileComparisonTest>("setChildNode test 1", SetChildNodeTest1);
    append<FileComparisonTest>("setChildNode test 2", SetChildNodeTest2);
    append<FileComparisonTest>("removeAllChildNodes test 1", RemoveAllChildNodesTest1);
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

    std::vector<DiplodocusDB::TreeDBNode> children = db.childNodes(node, error);

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
    
    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);

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

    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);

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
    
    DiplodocusDB::TreeDBNode node1 = db.child(db.root(), "key1", error);

    ISHTF_FAIL_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node2 = db.child(db.root(), "key2", error);

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
    
    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node.value().asUTF8String() == "value1");
    ISHTF_PASS();
}

void XMLTreeDBTests::OpenTest6(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_OpenTest6.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.child(db.root(), "key1", error);

    ISHTF_FAIL_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node2 = db.child(db.root(), "key2", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(node1.value().asUTF8String() == "value1");
    ISHTF_FAIL_UNLESS(node2.value().asUTF8String() == "value2");
    ISHTF_PASS();
}

void XMLTreeDBTests::ParentTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyXMLTreeDB.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode parent = db.parent(db.root(), error);

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
    
    DiplodocusDB::TreeDBNode childNode = db.child(db.root(), "key1", error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(childNode);
    
    DiplodocusDB::TreeDBNode parentNode = db.parent(childNode, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(parentNode == db.root());
    ISHTF_PASS();
}

void XMLTreeDBTests::ChildNodesTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyXMLTreeDB.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    std::vector<DiplodocusDB::TreeDBNode> children = db.childNodes(db.root(), error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(children.empty());
    ISHTF_PASS();
}

void XMLTreeDBTests::ChildNodesTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_ChildNodesTest2.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    std::vector<DiplodocusDB::TreeDBNode> children = db.childNodes(db.root(), error);

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
    
    DiplodocusDB::TreeDBNode key1Node = db.child(db.root(), "key1", error);

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
    
    DiplodocusDB::TreeDBNode key1Node = db.child(db.root(), "key1", error);

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

void XMLTreeDBTests::InsertChildNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_InsertChildNodeTest1.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node = db.insertChildNode(db.root(), 0, "key1", error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_InsertChildNodeTest1.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendChildNodeTest1.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.appendChildNode(db.root(), "key1", error);
        
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendChildNodeTest1.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendChildNodeTest2.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.appendChildNode(db.root(), "key1", error);
    
    ISHTF_FAIL_IF((bool)error);
        
    DiplodocusDB::TreeDBNode node2 = db.appendChildNode(db.root(), "key2", error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendChildNodeTest2.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest3(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendChildNodeTest3.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.appendChildNode(db.root(), "key1",
        DiplodocusDB::TreeDBValue::UTF8String("value1"), error);

    ISHTF_FAIL_IF((bool)error);
   
    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendChildNodeTest3.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest4(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendChildNodeTest4.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
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
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendChildNodeTest4.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest5(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendChildNodeTest5.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
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
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendChildNodeTest5.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest6(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyXMLTreeDB.xml");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendChildNodeTest6.xml");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.appendChildNode(db.root(), "key1", error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::TreeDBNode node2 = db.appendChildNode(node1, "key2", error);

    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendChildNodeTest6.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest7(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendChildNodeTest7.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.appendChildNode(db.root(), "key1",
        DiplodocusDB::TreeDBValue::UTF8String("value1"), error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::TreeDBNode node2 = db.appendChildNode(node1, "key2", error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendChildNodeTest7.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::SetChildNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_SetChildNodeTest1.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node = db.setChildNode(db.root(), "key1", error);
        
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_SetChildNodeTest1.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::SetChildNodeTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_SetChildNodeTest2.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    DiplodocusDB::TreeDBNode node1 = db.setChildNode(db.root(), "key1", error);
   
    ISHTF_FAIL_IF((bool)error);
        
    DiplodocusDB::TreeDBNode node2 = db.setChildNode(db.root(), "key1", error);
    
    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_SetChildNodeTest2.xml");

    ISHTF_PASS();
}

void XMLTreeDBTests::RemoveAllChildNodesTest1(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_RemoveAllChildNodesTest1.xml");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_RemoveAllChildNodesTest1.xml");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.open(outputPath, error);

    ISHTF_ABORT_IF((bool)error);
    
    db.removeAllChildNodes(db.root(), error);

    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_RemoveAllChildNodesTest1.xml");

    ISHTF_PASS();
}

/*
    Copyright (c) 2019-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
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
    append<FileComparisonTest>("appendChildNode test 8", AppendChildNodeTest8);
    append<FileComparisonTest>("setChildNode test 1", SetChildNodeTest1);
    append<FileComparisonTest>("setChildNode test 2", SetChildNodeTest2);
    append<FileComparisonTest>("removeAllChildNodes test 1", RemoveAllChildNodesTest1);
}

void XMLTreeDBTests::CreationTest1(Test& test)
{
    DiplodocusDB::XMLTreeDB db;

    ISHIKO_PASS();
}

void XMLTreeDBTests::CreateTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_CreateTest1.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHIKO_FAIL_IF(error);
    
    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_CreateTest1.xml");

    ISHIKO_PASS();
}

void XMLTreeDBTests::OpenTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyXMLTreeDB.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.open(inputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode& node = db.root();

    ISHIKO_FAIL_IF_NOT(node.isRoot());

    std::vector<DiplodocusDB::TreeDBNode> children = db.childNodes(node, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(children.size(), 0);
    ISHIKO_PASS();
}

void XMLTreeDBTests::OpenTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_OpenTest2.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.open(inputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);

    ISHIKO_FAIL_IF(error);

    DiplodocusDB::TreeDBValue value = db.value(node, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(value.type(), DiplodocusDB::PrimitiveDataType::null);
    ISHIKO_PASS();
}

void XMLTreeDBTests::OpenTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_OpenTest3.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.open(inputPath, error);

    ISHIKO_ABORT_IF(error);

    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);

    ISHIKO_FAIL_IF(error);

    DiplodocusDB::TreeDBValue value = db.value(node, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(value.type(), DiplodocusDB::PrimitiveDataType::null);
    ISHIKO_PASS();
}

void XMLTreeDBTests::OpenTest4(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_OpenTest4.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node1 = db.child(db.root(), "key1", error);

    ISHIKO_FAIL_IF(error);
    
    DiplodocusDB::TreeDBNode node2 = db.child(db.root(), "key2", error);

    ISHIKO_FAIL_IF(error);

    DiplodocusDB::TreeDBValue value1 = db.value(node1, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(value1.type(), DiplodocusDB::PrimitiveDataType::null);

    DiplodocusDB::TreeDBValue value2 = db.value(node2, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(value2.type(), DiplodocusDB::PrimitiveDataType::null);

    ISHIKO_PASS();
}

void XMLTreeDBTests::OpenTest5(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_OpenTest5.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.open(inputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);

    ISHIKO_FAIL_IF(error);

    DiplodocusDB::TreeDBValue value = db.value(node, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(value.asUTF8String(), "value1");
    ISHIKO_PASS();
}

void XMLTreeDBTests::OpenTest6(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_OpenTest6.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node1 = db.child(db.root(), "key1", error);

    ISHIKO_FAIL_IF(error);
    
    DiplodocusDB::TreeDBNode node2 = db.child(db.root(), "key2", error);

    ISHIKO_FAIL_IF(error);

    DiplodocusDB::TreeDBValue value1 = db.value(node1, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(value1.asUTF8String(), "value1");

    DiplodocusDB::TreeDBValue value2 = db.value(node2, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(value2.asUTF8String(), "value2");
    ISHIKO_PASS();
}

void XMLTreeDBTests::ParentTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyXMLTreeDB.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode parent = db.parent(db.root(), error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF(parent);
    ISHIKO_PASS();
}

void XMLTreeDBTests::ParentTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_ParentTest2.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode childNode = db.child(db.root(), "key1", error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NOT(childNode);
    
    DiplodocusDB::TreeDBNode parentNode = db.parent(childNode, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(parentNode, db.root());
    ISHIKO_PASS();
}

void XMLTreeDBTests::ChildNodesTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyXMLTreeDB.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHIKO_ABORT_IF(error);
    
    std::vector<DiplodocusDB::TreeDBNode> children = db.childNodes(db.root(), error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NOT(children.empty());
    ISHIKO_PASS();
}

void XMLTreeDBTests::ChildNodesTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_ChildNodesTest2.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHIKO_ABORT_IF((bool)error);
    
    std::vector<DiplodocusDB::TreeDBNode> children = db.childNodes(db.root(), error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(children.size(), 1);
    ISHIKO_PASS();
}

void XMLTreeDBTests::NextSiblingTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyXMLTreeDB.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode nextSibling = db.nextSibling(db.root(), error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF(nextSibling);
    ISHIKO_PASS();
}

void XMLTreeDBTests::NextSiblingTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_NextSiblingTest2.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode key1Node = db.child(db.root(), "key1", error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NOT(key1Node);

    DiplodocusDB::TreeDBNode nextSibling = db.nextSibling(key1Node, error);
    
    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF(nextSibling);
    ISHIKO_PASS();
}

void XMLTreeDBTests::NextSiblingTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_NextSiblingTest3.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error(0);
    db.open(inputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode key1Node = db.child(db.root(), "key1", error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NOT(key1Node);

    DiplodocusDB::TreeDBNode nextSibling = db.nextSibling(key1Node, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NOT(nextSibling);

    DiplodocusDB::TreeDBValue value = db.value(nextSibling, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(value.type(), DiplodocusDB::PrimitiveDataType::null);
    
    nextSibling = db.nextSibling(nextSibling, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF(nextSibling);
    ISHIKO_PASS();
}

void XMLTreeDBTests::InsertChildNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_InsertChildNodeTest1.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHIKO_ABORT_IF(error);

    DiplodocusDB::TreeDBNode node = db.insertChildNode(db.root(), 0, "key1", error);
    
    ISHIKO_FAIL_IF(error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_InsertChildNodeTest1.xml");

    ISHIKO_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendChildNodeTest1.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node = db.appendChildNode(db.root(), "key1", error);
        
    ISHIKO_FAIL_IF(error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendChildNodeTest1.xml");

    ISHIKO_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendChildNodeTest2.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node1 = db.appendChildNode(db.root(), "key1", error);
    
    ISHIKO_FAIL_IF(error);
        
    DiplodocusDB::TreeDBNode node2 = db.appendChildNode(db.root(), "key2", error);
    
    ISHIKO_FAIL_IF(error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendChildNodeTest2.xml");

    ISHIKO_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest3(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendChildNodeTest3.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node = db.appendChildNode(db.root(), "key1",
        DiplodocusDB::TreeDBValue::UTF8String("value1"), error);

    ISHIKO_FAIL_IF(error);
   
    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendChildNodeTest3.xml");

    ISHIKO_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest4(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendChildNodeTest4.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node1 = db.appendChildNode(db.root(), "key1",
        DiplodocusDB::TreeDBValue::UTF8String("value1"), error);

    ISHIKO_FAIL_IF(error);
        
    DiplodocusDB::TreeDBNode node2 = db.appendChildNode(db.root(), "key2",
        DiplodocusDB::TreeDBValue::UTF8String("value2"), error);
    
    ISHIKO_FAIL_IF(error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendChildNodeTest4.xml");

    ISHIKO_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest5(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendChildNodeTest5.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHIKO_ABORT_IF(error);
    
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
    
    ISHIKO_FAIL_IF(error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendChildNodeTest5.xml");

    ISHIKO_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest6(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyXMLTreeDB.xml");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendChildNodeTest6.xml");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.open(outputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node1 = db.appendChildNode(db.root(), "key1", error);

    ISHIKO_ABORT_IF(error);

    DiplodocusDB::TreeDBNode node2 = db.appendChildNode(node1, "key2", error);

    ISHIKO_FAIL_IF(error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendChildNodeTest6.xml");

    ISHIKO_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest7(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendChildNodeTest7.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node1 = db.appendChildNode(db.root(), "key1",
        DiplodocusDB::TreeDBValue::UTF8String("value1"), error);

    ISHIKO_FAIL_IF(error);

    DiplodocusDB::TreeDBNode node2 = db.appendChildNode(node1, "key2", error);
    
    ISHIKO_FAIL_IF(error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendChildNodeTest7.xml");

    ISHIKO_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest8(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendChildNodeTest8.xml");

    Ishiko::Error error;

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHIKO_ABORT_IF(error);

    DiplodocusDB::TreeDBNode node = db.appendChildNode(db.root(), "key1", DiplodocusDB::TreeDBValue::Double(123.45),
        error);

    ISHIKO_FAIL_IF(error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendChildNodeTest8.xml");

    ISHIKO_PASS();
}

void XMLTreeDBTests::SetChildNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_SetChildNodeTest1.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node = db.setChildNode(db.root(), "key1", error);
        
    ISHIKO_FAIL_IF(error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_SetChildNodeTest1.xml");

    ISHIKO_PASS();
}

void XMLTreeDBTests::SetChildNodeTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_SetChildNodeTest2.xml");

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);

    ISHIKO_ABORT_IF(error);
    
    DiplodocusDB::TreeDBNode node1 = db.setChildNode(db.root(), "key1", error);
   
    ISHIKO_FAIL_IF(error);
        
    DiplodocusDB::TreeDBNode node2 = db.setChildNode(db.root(), "key1", error);
    
    ISHIKO_FAIL_IF(error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_SetChildNodeTest2.xml");

    ISHIKO_PASS();
}

void XMLTreeDBTests::RemoveAllChildNodesTest1(FileComparisonTest& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_RemoveAllChildNodesTest1.xml");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_RemoveAllChildNodesTest1.xml");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error(0);

    DiplodocusDB::XMLTreeDB db;
    db.open(outputPath, error);

    ISHIKO_ABORT_IF(error);
    
    db.removeAllChildNodes(db.root(), error);

    ISHIKO_FAIL_IF(error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_RemoveAllChildNodesTest1.xml");

    ISHIKO_PASS();
}

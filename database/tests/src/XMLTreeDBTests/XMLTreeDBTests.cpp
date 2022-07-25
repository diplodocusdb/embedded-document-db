/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "XMLTreeDBTests.h"
#include "DiplodocusDB/EmbeddedDocumentDB/XMLTreeDB.hpp"
#include <boost/filesystem/operations.hpp>
#include <sstream>

using namespace DiplodocusDB;
using namespace Ishiko;

XMLTreeDBTests::XMLTreeDBTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "XMLTreeDB tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("create test 1", CreateTest1);
    append<HeapAllocationErrorsTest>("open test 1", OpenTest1);
    append<HeapAllocationErrorsTest>("open test 2", OpenTest2);
    append<HeapAllocationErrorsTest>("open test 3", OpenTest3);
    append<HeapAllocationErrorsTest>("open test 4", OpenTest4);
    append<HeapAllocationErrorsTest>("open test 5", OpenTest5);
    append<HeapAllocationErrorsTest>("open test 6", OpenTest6);
    append<HeapAllocationErrorsTest>("open test 7", OpenTest7);
    append<HeapAllocationErrorsTest>("open test 8", OpenTest8);
    append<HeapAllocationErrorsTest>("open test 9", OpenTest9);
    append<HeapAllocationErrorsTest>("open test 10", OpenTest10);
    append<HeapAllocationErrorsTest>("parent test 1", ParentTest1);
    append<HeapAllocationErrorsTest>("parent test 2", ParentTest2);
    append<HeapAllocationErrorsTest>("childNodes test 1", ChildNodesTest1);
    append<HeapAllocationErrorsTest>("childNodes test 2", ChildNodesTest2);
    append<HeapAllocationErrorsTest>("nextSibling test 1", NextSiblingTest1);
    append<HeapAllocationErrorsTest>("nextSibling test 2", NextSiblingTest2);
    append<HeapAllocationErrorsTest>("nextSibling test 3", NextSiblingTest3);
    append<HeapAllocationErrorsTest>("insertChildNode test 1", InsertChildNodeTest1);
    append<HeapAllocationErrorsTest>("appendChildNode test 1", AppendChildNodeTest1);
    append<HeapAllocationErrorsTest>("appendChildNode test 2", AppendChildNodeTest2);
    append<HeapAllocationErrorsTest>("appendChildNode test 3", AppendChildNodeTest3);
    append<HeapAllocationErrorsTest>("appendChildNode test 4", AppendChildNodeTest4);
    append<HeapAllocationErrorsTest>("appendChildNode test 5", AppendChildNodeTest5);
    append<HeapAllocationErrorsTest>("appendChildNode test 6", AppendChildNodeTest6);
    append<HeapAllocationErrorsTest>("appendChildNode test 7", AppendChildNodeTest7);
    append<HeapAllocationErrorsTest>("appendChildNode test 8", AppendChildNodeTest8);
    append<HeapAllocationErrorsTest>("appendChildNode test 9", AppendChildNodeTest9);
    append<HeapAllocationErrorsTest>("appendChildNode test 10", AppendChildNodeTest10);
    append<HeapAllocationErrorsTest>("setChildNode test 1", SetChildNodeTest1);
    append<HeapAllocationErrorsTest>("setChildNode test 2", SetChildNodeTest2);
    append<HeapAllocationErrorsTest>("removeAllChildNodes test 1", RemoveAllChildNodesTest1);
}

void XMLTreeDBTests::CreationTest1(Test& test)
{
    DiplodocusDB::XMLTreeDB db;

    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::CreateTest1(Test& test)
{
    const char* outputName = "XMLTreeDBTests_CreateTest1.xml";

    Error error;

    DiplodocusDB::XMLTreeDB db;
    db.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_FAIL_IF(error);
    
    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::OpenTest1(Test& test)
{
    boost::filesystem::path inputPath("doesnotexist");

    Error error;

    DiplodocusDB::XMLTreeDB db;
    db.open(inputPath, error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::OpenTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("EmptyXMLTreeDB.xml");

    Error error;

    DiplodocusDB::XMLTreeDB db;
    db.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::XMLTreeDBNode& node = db.root();

    ISHIKO_TEST_FAIL_IF_NOT(node.isRoot());

    std::vector<DiplodocusDB::XMLTreeDBNode> children = db.childNodes(node, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(children.size(), 0);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::OpenTest3(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("XMLTreeDBTests_OpenTest3.xml");

    Error error;

    XMLTreeDB db;
    db.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    XMLTreeDBNode node = db.child(db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);

    Value value = db.value(node, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value.type(), DiplodocusDB::PrimitiveDataType::null);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::OpenTest4(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("XMLTreeDBTests_OpenTest4.xml");

    Error error;

    DiplodocusDB::XMLTreeDB db;
    db.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    XMLTreeDBNode node = db.child(db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);

    Value value = db.value(node, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value.type(), DiplodocusDB::PrimitiveDataType::null);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::OpenTest5(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("XMLTreeDBTests_OpenTest5.xml");

    DiplodocusDB::XMLTreeDB db;

    Error error;
    db.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    XMLTreeDBNode node1 = db.child(db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);
    
    XMLTreeDBNode node2 = db.child(db.root(), "key2", error);

    ISHIKO_TEST_FAIL_IF(error);

    Value value1 = db.value(node1, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value1.type(), DiplodocusDB::PrimitiveDataType::null);

    Value value2 = db.value(node2, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value2.type(), DiplodocusDB::PrimitiveDataType::null);

    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::OpenTest6(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("XMLTreeDBTests_OpenTest6.xml");

    Error error;

    XMLTreeDB db;
    db.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    XMLTreeDBNode node = db.child(db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);

    Value value = db.value(node, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value.asUTF8String(), "value1");
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::OpenTest7(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("XMLTreeDBTests_OpenTest7.xml");

    XMLTreeDB db;

    Error error;
    db.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    XMLTreeDBNode node1 = db.child(db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);
    
    XMLTreeDBNode node2 = db.child(db.root(), "key2", error);

    ISHIKO_TEST_FAIL_IF(error);

    Value value1 = db.value(node1, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value1.asUTF8String(), "value1");

    Value value2 = db.value(node2, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value2.asUTF8String(), "value2");
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::OpenTest8(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("XMLTreeDBTests_OpenTest8.xml");

    Error error;

    XMLTreeDB db;
    db.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    XMLTreeDBNode node = db.child(db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);

    Value value = db.value(node, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value.asUnsignedInt64(), 123);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::OpenTest9(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("XMLTreeDBTests_OpenTest9.xml");

    Error error;

    XMLTreeDB db;
    db.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    XMLTreeDBNode node = db.child(db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);

    Value value = db.value(node, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value.asDouble(), 123.45);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::OpenTest10(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("XMLTreeDBTests_OpenTest10.xml");

    Error error;

    XMLTreeDB db;
    db.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    XMLTreeDBNode node = db.child(db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);

    Value value = db.value(node, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value.asDate(), boost::gregorian::date(2021, 12, 25));
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::ParentTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("EmptyXMLTreeDB.xml");

    DiplodocusDB::XMLTreeDB db;

    Error error;
    db.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::XMLTreeDBNode parent = db.parent(db.root(), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF(parent);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::ParentTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("XMLTreeDBTests_ParentTest2.xml");

    DiplodocusDB::XMLTreeDB db;

    Error error;
    db.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::XMLTreeDBNode childNode = db.child(db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(childNode);
    
    DiplodocusDB::XMLTreeDBNode parentNode = db.parent(childNode, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(parentNode, db.root());
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::ChildNodesTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("EmptyXMLTreeDB.xml");

    DiplodocusDB::XMLTreeDB db;

    Error error;
    db.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    std::vector<DiplodocusDB::XMLTreeDBNode> children = db.childNodes(db.root(), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(children.empty());
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::ChildNodesTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("XMLTreeDBTests_ChildNodesTest2.xml");

    DiplodocusDB::XMLTreeDB db;

    Error error;
    db.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF((bool)error);
    
    std::vector<DiplodocusDB::XMLTreeDBNode> children = db.childNodes(db.root(), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(children.size(), 1);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::NextSiblingTest1(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("EmptyXMLTreeDB.xml");

    DiplodocusDB::XMLTreeDB db;

    Error error;
    db.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::XMLTreeDBNode nextSibling = db.nextSibling(db.root(), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF(nextSibling);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::NextSiblingTest2(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("XMLTreeDBTests_NextSiblingTest2.xml");

    XMLTreeDB db;

    Error error;
    db.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    XMLTreeDBNode key1Node = db.child(db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(key1Node);

    XMLTreeDBNode nextSibling = db.nextSibling(key1Node, error);
    
    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF(nextSibling);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::NextSiblingTest3(Test& test)
{
    boost::filesystem::path inputPath = test.context().getDataPath("XMLTreeDBTests_NextSiblingTest3.xml");

    XMLTreeDB db;

    Error error;
    db.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    XMLTreeDBNode key1Node = db.child(db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(key1Node);

    XMLTreeDBNode nextSibling = db.nextSibling(key1Node, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(nextSibling);

    Value value = db.value(nextSibling, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value.type(), DiplodocusDB::PrimitiveDataType::null);
    
    nextSibling = db.nextSibling(nextSibling, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF(nextSibling);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::InsertChildNodeTest1(Test& test)
{
    const char* outputName = "XMLTreeDBTests_InsertChildNodeTest1.xml";

    Error error;

    DiplodocusDB::XMLTreeDB db;
    db.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::XMLTreeDBNode node = db.insertChildNode(db.root(), 0, "key1", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest1(Test& test)
{
    const char* outputName = "XMLTreeDBTests_AppendChildNodeTest1.xml";

    Error error;

    DiplodocusDB::XMLTreeDB db;
    db.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::XMLTreeDBNode node = db.appendChildNode(db.root(), "key1", error);
        
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest2(Test& test)
{
    const char* outputName = "XMLTreeDBTests_AppendChildNodeTest2.xml";

    Error error;

    DiplodocusDB::XMLTreeDB db;
    db.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::XMLTreeDBNode node1 = db.appendChildNode(db.root(), "key1", error);
    
    ISHIKO_TEST_FAIL_IF(error);
        
    DiplodocusDB::XMLTreeDBNode node2 = db.appendChildNode(db.root(), "key2", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest3(Test& test)
{
    const char* outputName = "XMLTreeDBTests_AppendChildNodeTest3.xml";

    Error error;

    XMLTreeDB db;
    db.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    XMLTreeDBNode node = db.appendChildNode(db.root(), "key1", Value::UTF8String("value1"), error);

    ISHIKO_TEST_FAIL_IF(error);
   
    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest4(Test& test)
{
    const char* outputName = "XMLTreeDBTests_AppendChildNodeTest4.xml";

    Error error;

    XMLTreeDB db;
    db.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    XMLTreeDBNode node1 = db.appendChildNode(db.root(), "key1", Value::UTF8String("value1"), error);

    ISHIKO_TEST_FAIL_IF(error);
        
    XMLTreeDBNode node2 = db.appendChildNode(db.root(), "key2", Value::UTF8String("value2"), error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest5(Test& test)
{
    const char* outputName = "XMLTreeDBTests_AppendChildNodeTest5.xml";

    Error error;

    XMLTreeDB db;
    db.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    for (size_t i = 0; i < 523; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        XMLTreeDBNode node = db.appendChildNode(db.root(), key.str(), error);
        if (error)
        {
            break;
        }
    }
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest6(Test& test)
{
    const char* outputName = "XMLTreeDBTests_AppendChildNodeTest6.xml";
    boost::filesystem::path inputPath = test.context().getDataPath("EmptyXMLTreeDB.xml");
    boost::filesystem::path outputPath = test.context().getOutputPath(outputName);

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Error error;

    DiplodocusDB::XMLTreeDB db;
    db.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::XMLTreeDBNode node1 = db.appendChildNode(db.root(), "key1", error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::XMLTreeDBNode node2 = db.appendChildNode(node1, "key2", error);

    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest7(Test& test)
{
    const char* outputName = "XMLTreeDBTests_AppendChildNodeTest7.xml";

    Error error;

    XMLTreeDB db;
    db.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    XMLTreeDBNode node1 = db.appendChildNode(db.root(), "key1", Value::UTF8String("value1"), error);

    ISHIKO_TEST_FAIL_IF(error);

    XMLTreeDBNode node2 = db.appendChildNode(node1, "key2", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest8(Test& test)
{
    const char* outputName = "XMLTreeDBTests_AppendChildNodeTest8.xml";

    Error error;

    XMLTreeDB db;
    db.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_ABORT_IF(error);

    XMLTreeDBNode node = db.appendChildNode(db.root(), "key1", Value::UnsignedInt64(123), error);

    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest9(Test& test)
{
    const char* outputName = "XMLTreeDBTests_AppendChildNodeTest9.xml";

    Error error;

    XMLTreeDB db;
    db.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_ABORT_IF(error);

    XMLTreeDBNode node = db.appendChildNode(db.root(), "key1", Value::Double(123.45), error);

    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::AppendChildNodeTest10(Test& test)
{
    const char* outputName = "XMLTreeDBTests_AppendChildNodeTest10.xml";

    Error error;

    XMLTreeDB db;
    db.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_ABORT_IF(error);

    XMLTreeDBNode node = db.appendChildNode(db.root(), "key1", Value::Date(boost::gregorian::date(2021, 12, 25)), error);

    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::SetChildNodeTest1(Test& test)
{
    const char* outputName = "XMLTreeDBTests_SetChildNodeTest1.xml";

    Error error;

    DiplodocusDB::XMLTreeDB db;
    db.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::XMLTreeDBNode node = db.setChildNode(db.root(), "key1", error);
        
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::SetChildNodeTest2(Test& test)
{
    const char* outputName = "XMLTreeDBTests_SetChildNodeTest2.xml";

    Error error;

    DiplodocusDB::XMLTreeDB db;
    db.create(test.context().getOutputPath(outputName), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    DiplodocusDB::XMLTreeDBNode node1 = db.setChildNode(db.root(), "key1", error);
   
    ISHIKO_TEST_FAIL_IF(error);
        
    DiplodocusDB::XMLTreeDBNode node2 = db.setChildNode(db.root(), "key1", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

void XMLTreeDBTests::RemoveAllChildNodesTest1(Test& test)
{
    const char* outputName = "XMLTreeDBTests_RemoveAllChildNodesTest1.xml";
    boost::filesystem::path inputPath = test.context().getDataPath(outputName);
    boost::filesystem::path outputPath = test.context().getOutputPath(outputName);

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Error error;

    DiplodocusDB::XMLTreeDB db;
    db.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    db.removeAllChildNodes(db.root(), error);

    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(outputName);
    ISHIKO_TEST_PASS();
}

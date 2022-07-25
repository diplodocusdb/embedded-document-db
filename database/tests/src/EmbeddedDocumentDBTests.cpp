/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "EmbeddedDocumentDBTests.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/EmbeddedDocumentDB.hpp"
#include <boost/filesystem/operations.hpp>
#include <sstream>

using namespace DiplodocusDB;
using namespace Ishiko;

EmbeddedDocumentDBTests::EmbeddedDocumentDBTests(const TestNumber& number, const TestContext& context)
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

void EmbeddedDocumentDBTests::CreationTest1(Test& test)
{
    EmbeddedDocumentDB db;

    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::CreateTest1(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_CreateTest1.dpdb";

    Error error;

    EmbeddedDocumentDB db;
    db.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_FAIL_IF(error);
    
    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::OpenTest1(Test& test)
{
    Error error;

    EmbeddedDocumentDB db;
    db.open(test.context().getDataPath("EmptyEmbeddedTreeDB.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    TreeDBNode& node = db.root();

    ISHIKO_TEST_FAIL_IF_NOT(node.isRoot());
   
    std::vector<TreeDBNode> children = db.childNodes(node, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(children.size(), 0);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::OpenTest2(Test& test)
{
    Error error;

    EmbeddedDocumentDB db;
    db.open(test.context().getDataPath("EmbeddedTreeDBTests_OpenTest2.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    TreeDBNode node = db.child(db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);

    Value value = db.value(node, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value.type(), DiplodocusDB::PrimitiveDataType::null);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::OpenTest3(Test& test)
{
    EmbeddedDocumentDB db;

    Error error;
    db.open(test.context().getDataPath("EmbeddedTreeDBTests_OpenTest3.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    TreeDBNode node1 = db.child(db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);

    Value value1 = db.value(node1, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value1.type(), PrimitiveDataType::null);

    TreeDBNode node2 = db.child(db.root(), "key2", error);

    ISHIKO_TEST_FAIL_IF(error);

    Value value2 = db.value(node2, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value2.type(), PrimitiveDataType::null);

    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::OpenTest4(Test& test)
{
    Error error;

    EmbeddedDocumentDB db;
    db.open(test.context().getDataPath("EmbeddedTreeDBTests_OpenTest4.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    // TODO: fix crash
    /*DiplodocusDB::TreeDBNode node = db.child(db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);

    DiplodocusDB::TreeDBValue value = db.value(node, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value.asUTF8String(), "value1");
    ISHIKO_TEST_PASS();
    */
}

void EmbeddedDocumentDBTests::OpenTest5(Test& test)
{
    EmbeddedDocumentDB db;

    Error error;
    db.open(test.context().getDataPath("EmbeddedTreeDBTests_OpenTest5.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    // TODO: fix crash
    /*DiplodocusDB::TreeDBNode node1 = db.child(db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);

    DiplodocusDB::TreeDBValue value1 = db.value(node1, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value1.asUTF8String(), "value1");
    
    DiplodocusDB::TreeDBNode node2 = db.child(db.root(), "key2", error);

    ISHIKO_TEST_FAIL_IF(error);

    DiplodocusDB::TreeDBValue value2 = db.value(node2, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(value2.asUTF8String(), "value2");
        
    ISHIKO_TEST_PASS();
    */
}

void EmbeddedDocumentDBTests::ChildNodesTest1(Test& test)
{
    EmbeddedDocumentDB db;

    Error error;
    db.open(test.context().getDataPath("EmptyEmbeddedTreeDB.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    std::vector<TreeDBNode> children = db.childNodes(db.root(), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(children.size(), 0);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::ChildNodesTest2(Test& test)
{
    EmbeddedDocumentDB db;

    Error error;
    db.open(test.context().getDataPath("EmbeddedTreeDBTests_ChildNodesTest2.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    std::vector<DiplodocusDB::TreeDBNode> children = db.childNodes(db.root(), error);
 
    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(children.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(children[0].name(), "key1");
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::InsertChildNodeTest1(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_InsertChildNodeTest1.dpdb";
    
    Error error;

    EmbeddedDocumentDB db;
    db.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    TreeDBNode node = db.insertChildNode(db.root(), 0, "key1", error);
        
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::InsertChildNodeBeforeTest1(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_InsertChildNodeBeforeTest1.dpdb";
    boost::filesystem::path inputPath = test.context().getDataPath(testName);
    boost::filesystem::path outputPath = test.context().getOutputPath(testName);

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Error error;

    EmbeddedDocumentDB db;
    db.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    TreeDBNode node = db.child(db.root(), "key1", error);

    ISHIKO_TEST_ABORT_IF(error);
        
    TreeDBNode newNode = db.insertChildNodeBefore(db.root(), node, "key0", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::InsertChildNodeBeforeTest2(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_InsertChildNodeBeforeTest2.dpdb";
    boost::filesystem::path inputPath = test.context().getDataPath(testName);
    boost::filesystem::path outputPath = test.context().getOutputPath(testName);

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Error error;

    EmbeddedDocumentDB db;
    db.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    TreeDBNode node = db.child(db.root(), "key2", error);

    ISHIKO_TEST_ABORT_IF(error);
        
    TreeDBNode newNode1 = db.insertChildNodeBefore(db.root(), node, "key1", error);
    
    ISHIKO_TEST_ABORT_IF(error);
            
    TreeDBNode newNode2 = db.insertChildNodeBefore(db.root(), newNode1, "key0", error);

    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::InsertChildNodeBeforeTest3(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_InsertChildNodeBeforeTest3.dpdb";
    boost::filesystem::path inputPath = test.context().getDataPath(testName);
    boost::filesystem::path outputPath = test.context().getOutputPath(testName);

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Error error;

    EmbeddedDocumentDB db;
    db.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    TreeDBNode node = db.child(db.root(), "key2", error);

    ISHIKO_TEST_ABORT_IF(error);
    
    TreeDBNode newNode1 = db.insertChildNodeBefore(db.root(), node, "key1", error);

    ISHIKO_TEST_ABORT_IF(error);

    TreeDBNode newNode2 = db.insertChildNodeBefore(db.root(), newNode1, "key0", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::InsertChildNodeAfterTest1(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_InsertChildNodeAfterTest1.dpdb";
    boost::filesystem::path inputPath = test.context().getDataPath(testName);
    boost::filesystem::path outputPath = test.context().getOutputPath(testName);

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Error error;

    EmbeddedDocumentDB db;
    db.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    TreeDBNode node = db.child(db.root(), "key1", error);
    
    ISHIKO_TEST_ABORT_IF(error);

    TreeDBNode newNode = db.insertChildNodeAfter(db.root(), node, "key2", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::InsertChildNodeAfterTest2(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_InsertChildNodeAfterTest2.dpdb";
    boost::filesystem::path inputPath = test.context().getDataPath(testName);
    boost::filesystem::path outputPath = test.context().getOutputPath(testName);

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Error error;

    EmbeddedDocumentDB db;
    db.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    TreeDBNode node = db.child(db.root(), "key1", error);
    
    ISHIKO_TEST_ABORT_IF(error);

    TreeDBNode newNode = db.insertChildNodeAfter(db.root(), node, "key2", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::AppendChildNodeTest1(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_AppendChildNodeTest1.dpdb";

    Error error;

    EmbeddedDocumentDB db;
    db.create(test.context().getOutputPath("EmbeddedTreeDBTests_AppendChildNodeTest1.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    TreeDBNode node = db.appendChildNode(db.root(), "key1", error);
    
    ISHIKO_TEST_FAIL_IF(error);
    
    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::AppendChildNodeTest2(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_AppendChildNodeTest2.dpdb";
    
    Error error;

    EmbeddedDocumentDB db;
    db.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    TreeDBNode node1 = db.appendChildNode(db.root(), "key1", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    TreeDBNode node2 = db.appendChildNode(db.root(), "key2", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::AppendChildNodeTest3(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_AppendChildNodeTest3.dpdb";

    Error error;

    EmbeddedDocumentDB db;
    db.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    TreeDBNode node = db.appendChildNode(db.root(), "key1", Value::UTF8String("value1"), error);

    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::AppendChildNodeTest4(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_AppendChildNodeTest4.dpdb";

    Error error;

    EmbeddedDocumentDB db;
    db.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    TreeDBNode node1 = db.appendChildNode(db.root(), "key1", Value::UTF8String("value1"), error);

    ISHIKO_TEST_FAIL_IF(error);

    TreeDBNode node2 = db.appendChildNode(db.root(), "key2", Value::UTF8String("value2"), error);

    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::AppendChildNodeTest5(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_AppendChildNodeTest5.dpdb";

    Error error;

    EmbeddedDocumentDB db;
    db.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    for (size_t i = 0; i < 523; ++i)
    {
        std::stringstream key;
        key << "key" << i;
        TreeDBNode node = db.appendChildNode(db.root(), key.str(), error);
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

void EmbeddedDocumentDBTests::AppendChildNodeTest6(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_AppendChildNodeTest6.dpdb";
    boost::filesystem::path outputPath = test.context().getOutputPath(testName);

    boost::filesystem::copy_file(test.context().getDataPath("EmptyEmbeddedTreeDB.dpdb"), outputPath,
        boost::filesystem::copy_option::overwrite_if_exists);

    Error error;

    EmbeddedDocumentDB db;
    db.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    TreeDBNode node1 = db.appendChildNode(db.root(), "key1", error);

    ISHIKO_TEST_ABORT_IF(error);

    TreeDBNode node2 = db.appendChildNode(node1, "key2", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::RemoveChildNodeTest1(Test& test)
{
    const char* testName = "EmbeddedTreeDBTests_RemoveChildNodeTest1.dpdb";
    boost::filesystem::path inputPath = test.context().getDataPath(testName);
    boost::filesystem::path outputPath = test.context().getOutputPath(testName);

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Error error;

    EmbeddedDocumentDB db;
    db.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    db.removeChildNode(db.root(), "key1", error);
    
    ISHIKO_TEST_FAIL_IF(error);

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void EmbeddedDocumentDBTests::RemoveAllChildNodesTest1(Test& test)
{
}

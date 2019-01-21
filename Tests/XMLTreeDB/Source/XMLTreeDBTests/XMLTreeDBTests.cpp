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
#include <sstream>

using namespace Ishiko::TestFramework;

void XMLTreeDBTests::AddTests(TestHarness& theTestHarness)
{
    TestSequence& xmlTreeDBTestSequence = theTestHarness.appendTestSequence("XMLTreeDB tests");

    new HeapAllocationErrorsTest("Creation test 1", CreationTest1, xmlTreeDBTestSequence);

    new FileComparisonTest("create test 1", CreateTest1, xmlTreeDBTestSequence);

    new HeapAllocationErrorsTest("open test 1", OpenTest1, xmlTreeDBTestSequence);
    new HeapAllocationErrorsTest("open test 2", OpenTest2, xmlTreeDBTestSequence);
    new HeapAllocationErrorsTest("open test 3", OpenTest3, xmlTreeDBTestSequence);
    new HeapAllocationErrorsTest("open test 4", OpenTest4, xmlTreeDBTestSequence);

    new FileComparisonTest("insert test 1", InsertTest1, xmlTreeDBTestSequence);

    new FileComparisonTest("append test 1", AppendTest1, xmlTreeDBTestSequence);
    new FileComparisonTest("append test 2", AppendTest2, xmlTreeDBTestSequence);
    new FileComparisonTest("append test 3", AppendTest3, xmlTreeDBTestSequence);
    new FileComparisonTest("append test 4", AppendTest4, xmlTreeDBTestSequence);
    new FileComparisonTest("append test 5", AppendTest5, xmlTreeDBTestSequence);
}

TestResult::EOutcome XMLTreeDBTests::CreationTest1()
{
    DiplodocusDB::XMLTreeDB db;
    return TestResult::ePassed;
}

TestResult::EOutcome XMLTreeDBTests::CreateTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_CreateTest1.xml");

    Ishiko::Error error;

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);
    if (!error)
    {
        result = TestResult::ePassed;
    }
    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_CreateTest1.xml");

    return result;
}

TestResult::EOutcome XMLTreeDBTests::OpenTest1(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmptyXMLTreeDB.xml");

    Ishiko::Error error;

    DiplodocusDB::XMLTreeDB db;
    db.open(inputPath, error);
    if (!error)
    {
        DiplodocusDB::TreeDBNode& node = db.root();
        if (node.isRoot())
        {
            std::vector<DiplodocusDB::TreeDBNode> children;
            node.children(children, error);
            if (!error && (children.size() == 0))
            {
                result = TestResult::ePassed;
            }
        }
    }

    return result;
}

TestResult::EOutcome XMLTreeDBTests::OpenTest2(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_OpenTest2.xml");

    Ishiko::Error error;

    DiplodocusDB::XMLTreeDB db;
    db.open(inputPath, error);
    if (!error)
    {
        DiplodocusDB::TreeDBNode node = db.root().child("key1", error);
        if (!error)
        {
            if (node.value().type() == DiplodocusDB::EPrimitiveDataType::eNULL)
            {
                result = TestResult::ePassed;
            }
        }
    }
    
    return result;
}

TestResult::EOutcome XMLTreeDBTests::OpenTest3(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_OpenTest3.xml");

    DiplodocusDB::XMLTreeDB db;

    Ishiko::Error error;
    db.open(inputPath, error);
    if (!error)
    {
        DiplodocusDB::TreeDBNode node1 = db.root().child("key1", error);
        if (!error)
        {
            DiplodocusDB::TreeDBNode node2 = db.root().child("key2", error);
            if (!error)
            {
                if ((node1.value().type() == DiplodocusDB::EPrimitiveDataType::eNULL) &&
                    (node2.value().type() == DiplodocusDB::EPrimitiveDataType::eNULL))
                {
                    result = TestResult::ePassed;
                }
            }
        }
    }

    return result;
}

TestResult::EOutcome XMLTreeDBTests::OpenTest4(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "XMLTreeDBTests_OpenTest4.xml");

    Ishiko::Error error;

    DiplodocusDB::XMLTreeDB db;
    db.open(inputPath, error);
    if (!error)
    {
        DiplodocusDB::TreeDBNode node = db.root().child("key1", error);
        if (!error)
        {
            if (node.value().asString() == "value1")
            {
                result = TestResult::ePassed;
            }
        }
    }

    return result;
}

TestResult::EOutcome XMLTreeDBTests::InsertTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_InsertTest1.xml");

    Ishiko::Error error;

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);
    if (!error)
    {
        DiplodocusDB::TreeDBNode node = db.root().insert("key1", 0);
        node.commit(error);
        if (!error)
        {
            result = TestResult::ePassed;
        }

        db.close();
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_InsertTest1.xml");

    return result;
}

TestResult::EOutcome XMLTreeDBTests::AppendTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendTest1.xml");

    Ishiko::Error error;

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);
    if (!error)
    {
        DiplodocusDB::TreeDBNode node = db.root().append("key1");
        node.commit(error);
        if (!error)
        {
            result = TestResult::ePassed;
        }

        db.close();
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendTest1.xml");

    return result;
}

TestResult::EOutcome XMLTreeDBTests::AppendTest2(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendTest2.xml");

    Ishiko::Error error;

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);
    if (!error)
    {
        DiplodocusDB::TreeDBNode node1 = db.root().append("key1");
        node1.commit(error);
        if (!error)
        {
            DiplodocusDB::TreeDBNode node2 = db.root().append("key2");
            node2.commit(error);
            if (!error)
            {
                result = TestResult::ePassed;
            }
        }

        db.close();
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendTest2.xml");

    return result;
}

TestResult::EOutcome XMLTreeDBTests::AppendTest3(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendTest3.xml");

    Ishiko::Error error;

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);
    if (!error)
    {
        DiplodocusDB::TreeDBNode node = db.root().append("key1");
        node.value().setString("value1");
        node.commit(error);
        if (!error)
        {
            result = TestResult::ePassed;
        }

        db.close();
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendTest3.xml");

    return result;
}

TestResult::EOutcome XMLTreeDBTests::AppendTest4(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendTest4.xml");

    Ishiko::Error error;

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);
    if (!error)
    {
        DiplodocusDB::TreeDBNode node1 = db.root().append("key1");
        node1.value().setString("value1");
        node1.commit(error);
        if (!error)
        {
            DiplodocusDB::TreeDBNode node2 = db.root().append("key2");
            node2.value().setString("value2");
            node2.commit(error);
            if (!error)
            {
                result = TestResult::ePassed;
            }
        }

        db.close();
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendTest4.xml");

    return result;
}

TestResult::EOutcome XMLTreeDBTests::AppendTest5(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "XMLTreeDBTests_AppendTest5.xml");

    Ishiko::Error error;

    DiplodocusDB::XMLTreeDB db;
    db.create(outputPath, error);
    if (!error)
    {
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
        if (!error)
        {
            result = TestResult::ePassed;
        }

        db.close();
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "XMLTreeDBTests_AppendTest5.xml");

    return result;
}

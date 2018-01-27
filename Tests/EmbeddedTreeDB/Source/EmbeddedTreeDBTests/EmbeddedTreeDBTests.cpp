/*
    Copyright (c) 2018 Xavier Leclercq

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

void AddEmbeddedTreeDBTests(TestHarness& theTestHarness)
{
    TestSequence& embeddedTreeDBTestSequence = theTestHarness.appendTestSequence("EmbeddedTreeDB tests");

    new HeapAllocationErrorsTest("Creation test 1", EmbeddedTreeDBCreationTest1, embeddedTreeDBTestSequence);

    new FileComparisonTest("create test 1", EmbeddedTreeDBCreateTest1, embeddedTreeDBTestSequence);

    new HeapAllocationErrorsTest("open test 1", EmbeddedTreeDBOpenTest1, embeddedTreeDBTestSequence);
    new HeapAllocationErrorsTest("open test 2", EmbeddedTreeDBOpenTest2, embeddedTreeDBTestSequence);
    new HeapAllocationErrorsTest("open test 3", EmbeddedTreeDBOpenTest3, embeddedTreeDBTestSequence);
    new HeapAllocationErrorsTest("open test 4", EmbeddedTreeDBOpenTest4, embeddedTreeDBTestSequence);

    new FileComparisonTest("insert test 1", EmbeddedTreeDBNodeInsertTest1, embeddedTreeDBTestSequence);

    new FileComparisonTest("insertBefore test 1", EmbeddedTreeDBNodeInsertBeforeTest1, embeddedTreeDBTestSequence);

    new FileComparisonTest("insertAfter test 1", EmbeddedTreeDBNodeInsertAfterTest1, embeddedTreeDBTestSequence);
    new FileComparisonTest("insertAfter test 2", EmbeddedTreeDBNodeInsertAfterTest2, embeddedTreeDBTestSequence);

    new FileComparisonTest("append test 1", EmbeddedTreeDBNodeAppendTest1, embeddedTreeDBTestSequence);
    new FileComparisonTest("append test 2", EmbeddedTreeDBNodeAppendTest2, embeddedTreeDBTestSequence);
    new FileComparisonTest("append test 3", EmbeddedTreeDBNodeAppendTest3, embeddedTreeDBTestSequence);
    new FileComparisonTest("append test 4", EmbeddedTreeDBNodeAppendTest4, embeddedTreeDBTestSequence);
    new FileComparisonTest("append test 5", EmbeddedTreeDBNodeAppendTest5, embeddedTreeDBTestSequence);

    new FileComparisonTest("remove test 1", EmbeddedTreeDBNodeRemoveTest1, embeddedTreeDBTestSequence);
}

TestResult::EOutcome EmbeddedTreeDBCreationTest1()
{
    DiplodocusDB::EmbeddedTreeDB db;
    return TestResult::ePassed;
}

TestResult::EOutcome EmbeddedTreeDBCreateTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBCreateTest1.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);
    if (!error)
    {
        result = TestResult::ePassed;
    }
    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBCreateTest1.dpdb");

    return result;
}

TestResult::EOutcome EmbeddedTreeDBOpenTest1(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBOpenTest1.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(inputPath, error);
    if (!error)
    {
        std::shared_ptr<DiplodocusDB::TreeDBNode> node = db.root().child("key1", error);
        if (node && !error)
        {
            if (node->value().type() == DiplodocusDB::EPrimitiveDataType::eNULL)
            {
                result = TestResult::ePassed;
            }
        }
    }
    
    return result;
}

TestResult::EOutcome EmbeddedTreeDBOpenTest2(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBOpenTest2.dpdb");

    DiplodocusDB::EmbeddedTreeDB db;

    Ishiko::Error error;
    db.open(inputPath, error);
    if (!error)
    {
        std::shared_ptr<DiplodocusDB::TreeDBNode> node1 = db.root().child("key1", error);
        std::shared_ptr<DiplodocusDB::TreeDBNode> node2 = db.root().child("key2", error);
        if (node1 && node2 && !error)
        {
            if ((node1->value().type() == DiplodocusDB::EPrimitiveDataType::eNULL) &&
                (node2->value().type() == DiplodocusDB::EPrimitiveDataType::eNULL))
            {
                result = TestResult::ePassed;
            }
        }
    }

    return result;
}

TestResult::EOutcome EmbeddedTreeDBOpenTest3(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBOpenTest3.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(inputPath, error);
    if (!error)
    {
        std::shared_ptr<DiplodocusDB::TreeDBNode> node = db.root().child("key1", error);
        if (node && !error)
        {
            if (node->value().asString() == "value1")
            {
                result = TestResult::ePassed;
            }
        }
    }

    return result;
}

TestResult::EOutcome EmbeddedTreeDBOpenTest4(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBOpenTest4.dpdb");

    DiplodocusDB::EmbeddedTreeDB db;

    Ishiko::Error error;
    db.open(inputPath, error);
    if (!error)
    {
        std::shared_ptr<DiplodocusDB::TreeDBNode> node1 = db.root().child("key1", error);
        std::shared_ptr<DiplodocusDB::TreeDBNode> node2 = db.root().child("key2", error);
        if (node1 && node2 && !error)
        {
            if ((node1->value().asString() == "value1") &&
                (node2->value().asString() == "value2"))
            {
                result = TestResult::ePassed;
            }
        }
    }

    return result;
}

TestResult::EOutcome EmbeddedTreeDBNodeInsertTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeInsertTest1.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);
    if (!error)
    {
        std::shared_ptr<DiplodocusDB::TreeDBNode> node = db.root().append("key1");
        node->commit(error);
        if (!error)
        {
            result = TestResult::ePassed;
        }

        db.close();
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeInsertTest1.dpdb");

    return result;
}

TestResult::EOutcome EmbeddedTreeDBNodeInsertBeforeTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBNodeInsertBeforeTest1.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeInsertBeforeTest1.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);
    if (!error)
    {
        std::shared_ptr<DiplodocusDB::TreeDBNode> node = db.root().child("key1", error);
        if (node && !error)
        {
            std::shared_ptr<DiplodocusDB::TreeDBNode> newNode = node->insertBefore("key0", node);
            if (newNode)
            {
                newNode->commit(error);
                if (!error)
                {
                    result = TestResult::ePassed;
                }
            }
        }
    }
    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeInsertBeforeTest1.dpdb");

    return result;
}

TestResult::EOutcome EmbeddedTreeDBNodeInsertAfterTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBNodeInsertAfterTest1.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeInsertAfterTest1.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);
    if (!error)
    {
        std::shared_ptr<DiplodocusDB::TreeDBNode> node = db.root().child("key1", error);
        if (node && !error)
        {
            std::shared_ptr<DiplodocusDB::TreeDBNode> newNode = node->insertAfter("key2", node);
            if (newNode)
            {
                newNode->commit(error);
                if (!error)
                {
                    result = TestResult::ePassed;
                }
            }
        }
    }
    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeInsertAfterTest1.dpdb");

    return result;
}

TestResult::EOutcome EmbeddedTreeDBNodeInsertAfterTest2(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBNodeInsertAfterTest2.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeInsertAfterTest2.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);
    if (!error)
    {
        std::shared_ptr<DiplodocusDB::TreeDBNode> node = db.root().child("key1", error);
        if (node && !error)
        {
            std::shared_ptr<DiplodocusDB::TreeDBNode> newNode = node->insertAfter("key2", node);
            if (newNode)
            {
                newNode->commit(error);
                if (!error)
                {
                    result = TestResult::ePassed;
                }
            }
        }
    }
    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeInsertAfterTest2.dpdb");

    return result;
}

TestResult::EOutcome EmbeddedTreeDBNodeAppendTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeAppendTest1.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);
    if (!error)
    {
        std::shared_ptr<DiplodocusDB::TreeDBNode> node = db.root().append("key1");
        node->commit(error);
        if (!error)
        {
            result = TestResult::ePassed;
        }

        db.close();
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeAppendTest1.dpdb");

    return result;
}

TestResult::EOutcome EmbeddedTreeDBNodeAppendTest2(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeAppendTest2.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);
    if (!error)
    {
        std::shared_ptr<DiplodocusDB::TreeDBNode> node1 = db.root().append("key1");
        node1->commit(error);
        if (!error)
        {
            std::shared_ptr<DiplodocusDB::TreeDBNode> node2 = db.root().append("key2");
            node2->commit(error);
            if (!error)
            {
                result = TestResult::ePassed;
            }
        }

        db.close();
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeAppendTest2.dpdb");

    return result;
}

TestResult::EOutcome EmbeddedTreeDBNodeAppendTest3(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeAppendTest3.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);
    if (!error)
    {
        std::shared_ptr<DiplodocusDB::TreeDBNode> node = db.root().append("key1");
        node->value().setString("value1");
        node->commit(error);
        if (!error)
        {
            result = TestResult::ePassed;
        }

        db.close();
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeAppendTest3.dpdb");

    return result;
}

TestResult::EOutcome EmbeddedTreeDBNodeAppendTest4(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeAppendTest4.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);
    if (!error)
    {
        std::shared_ptr<DiplodocusDB::TreeDBNode> node1 = db.root().append("key1");
        node1->value().setString("value1");
        node1->commit(error);
        if (!error)
        {
            std::shared_ptr<DiplodocusDB::TreeDBNode> node2 = db.root().append("key2");
            node2->value().setString("value2");
            node2->commit(error);
            if (!error)
            {
                result = TestResult::ePassed;
            }
        }

        db.close();
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeAppendTest4.dpdb");

    return result;
}

TestResult::EOutcome EmbeddedTreeDBNodeAppendTest5(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeAppendTest5.dpdb");

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);
    if (!error)
    {
        for (size_t i = 0; i < 523; ++i)
        {
            std::stringstream key;
            key << "key" << i;
            std::shared_ptr<DiplodocusDB::TreeDBNode> node = db.root().append(key.str());
            node->commit(error);
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
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeAppendTest5.dpdb");

    return result;
}

TestResult::EOutcome EmbeddedTreeDBNodeRemoveTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "EmbeddedTreeDBNodeRemoveTest1.dpdb");
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "EmbeddedTreeDBNodeRemoveTest1.dpdb");

    boost::filesystem::copy_file(inputPath, outputPath, boost::filesystem::copy_option::overwrite_if_exists);

    Ishiko::Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.open(outputPath, error);
    if (!error)
    {
        db.root().remove("key1", error);
        if (!error)
        {
            result = TestResult::ePassed;
        }
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBNodeRemoveTest1.dpdb");

    return result;
}

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

void AddEmbeddedTreeDBTests(TestHarness& theTestHarness)
{
    TestSequence& embeddedTreeDBTestSequence = theTestHarness.appendTestSequence("EmbeddedTreeDB tests");

    new HeapAllocationErrorsTest("Creation test 1", EmbeddedTreeDBCreationTest1, embeddedTreeDBTestSequence);

    new FileComparisonTest("create test 1", EmbeddedTreeDBCreateTest1, embeddedTreeDBTestSequence);

    new HeapAllocationErrorsTest("open test 1", EmbeddedTreeDBOpenTest1, embeddedTreeDBTestSequence);
    new HeapAllocationErrorsTest("open test 2", EmbeddedTreeDBOpenTest2, embeddedTreeDBTestSequence);

    new FileComparisonTest("append test 1", EmbeddedTreeDBNodeAppendTest1, embeddedTreeDBTestSequence);
    new FileComparisonTest("append test 2", EmbeddedTreeDBNodeAppendTest2, embeddedTreeDBTestSequence);
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
        if (db.root().child("key1", error))
        {
            if (!error)
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
        if ((db.root().child("key1", error)) &&
            (db.root().child("key2", error)))
        {
            if (!error)
            {
                result = TestResult::ePassed;
            }
        }
    }

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

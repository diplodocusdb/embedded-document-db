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

using namespace Ishiko::TestFramework;

void XMLTreeDBTests::AddTests(TestHarness& theTestHarness)
{
    TestSequence& xmlTreeDBTestSequence = theTestHarness.appendTestSequence("XMLTreeDB tests");

    new HeapAllocationErrorsTest("Creation test 1", CreationTest1, xmlTreeDBTestSequence);

    new FileComparisonTest("create test 1", CreateTest1, xmlTreeDBTestSequence);

    new HeapAllocationErrorsTest("open test 1", OpenTest1, xmlTreeDBTestSequence);
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

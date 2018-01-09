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

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "EmbeddedTreeDBCreateTest1.dpdb");

    return result;
}

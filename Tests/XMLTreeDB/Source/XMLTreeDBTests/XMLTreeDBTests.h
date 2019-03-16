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

#ifndef _DIPLODOCUSDB_TEST_TREEDB_XMLTREEDBTESTS_XMLTREEDBTESTS_H_
#define _DIPLODOCUSDB_TEST_TREEDB_XMLTREEDBTESTS_XMLTREEDBTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class XMLTreeDBTests : public Ishiko::Tests::TestSequence
{
public:
    XMLTreeDBTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void CreationTest1(Ishiko::Tests::Test& test);
    static void CreateTest1(Ishiko::Tests::FileComparisonTest& test);
    static void OpenTest1(Ishiko::Tests::Test& test);
    static void OpenTest2(Ishiko::Tests::Test& test);
    static void OpenTest3(Ishiko::Tests::Test& test);
    static void OpenTest4(Ishiko::Tests::Test& test);
    static void OpenTest5(Ishiko::Tests::Test& test);
    static void OpenTest6(Ishiko::Tests::Test& test);
    static void ParentTest1(Ishiko::Tests::Test& test);
    static void ParentTest2(Ishiko::Tests::Test& test);
    static void ChildrenTest1(Ishiko::Tests::Test& test);
    static void ChildrenTest2(Ishiko::Tests::Test& test);
    static void NextSiblingTest1(Ishiko::Tests::Test& test);
    static void NextSiblingTest2(Ishiko::Tests::Test& test);
    static void NextSiblingTest3(Ishiko::Tests::Test& test);
    static void InsertTest1(Ishiko::Tests::FileComparisonTest& test);
    static void AppendTest1(Ishiko::Tests::FileComparisonTest& test);
    static void AppendTest2(Ishiko::Tests::FileComparisonTest& test);
    static void AppendTest3(Ishiko::Tests::FileComparisonTest& test);
    static void AppendTest4(Ishiko::Tests::FileComparisonTest& test);
    static void AppendTest5(Ishiko::Tests::FileComparisonTest& test);
    static void AppendTest6(Ishiko::Tests::FileComparisonTest& test);
    static void AppendTest7(Ishiko::Tests::FileComparisonTest& test);
    static void SetTest1(Ishiko::Tests::FileComparisonTest& test);
    static void SetTest2(Ishiko::Tests::FileComparisonTest& test);
    static void RemoveAllTest1(Ishiko::Tests::FileComparisonTest& test);
};

#endif

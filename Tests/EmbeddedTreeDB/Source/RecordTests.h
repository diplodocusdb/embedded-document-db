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

#ifndef _DIPLODOCUSDB_TREEDB_TESTS_EMBEDDEDTREEDB_RECORDTESTS_H_
#define _DIPLODOCUSDB_TREEDB_TESTS_EMBEDDEDTREEDB_RECORDTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class RecordTests : public Ishiko::Tests::TestSequence
{
public:
    RecordTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructionTest1(Ishiko::Tests::Test& test);
    static void ReadMasterFileMetadataTest1(Ishiko::Tests::Test& test);
    static void ReadDataStartTest1(Ishiko::Tests::Test& test);
    static void ReadDataEndTest1(Ishiko::Tests::Test& test);
    static void ReadNodeStartTest1(Ishiko::Tests::Test& test);
    static void ReadNodeEndTest1(Ishiko::Tests::Test& test);
    static void ReadParentNodeIDTest1(Ishiko::Tests::Test& test);
    static void ReadNodeNameTest1(Ishiko::Tests::Test& test);
    static void ReadNodeNameTest2(Ishiko::Tests::Test& test);
    static void ReadNodeIDTest1(Ishiko::Tests::Test& test);
    static void ReadNodeIDTest2(Ishiko::Tests::Test& test);
    static void ReadPersistentNodeIDTest1(Ishiko::Tests::Test& test);
    static void ReadInlineValueBinaryTest1(Ishiko::Tests::Test& test);
    static void ReadInlineValueBooleanTest1(Ishiko::Tests::Test& test);
    static void ReadInlineValueUTF8StringTest1(Ishiko::Tests::Test& test);
    static void WriteMasterFileMetadataTest1(Ishiko::Tests::FileComparisonTest& test);
    static void WriteDataStartTest1(Ishiko::Tests::FileComparisonTest& test);
    static void WriteDataEndTest1(Ishiko::Tests::FileComparisonTest& test);
    static void WriteNodeStartTest1(Ishiko::Tests::FileComparisonTest& test);
    static void WriteNodeEndTest1(Ishiko::Tests::FileComparisonTest& test);
    static void WriteParentNodeIDTest1(Ishiko::Tests::FileComparisonTest& test);
    static void WriteNodeNameTest1(Ishiko::Tests::FileComparisonTest& test);
    static void WriteNodeNameTest2(Ishiko::Tests::FileComparisonTest& test);
    static void WriteNodeIDTest1(Ishiko::Tests::FileComparisonTest& test);
    static void WriteNodeIDTest2(Ishiko::Tests::FileComparisonTest& test);
    static void WritePersistentNodeIDTest1(Ishiko::Tests::FileComparisonTest& test);
    static void WriteInlineValueBinaryTest1(Ishiko::Tests::FileComparisonTest& test);
    static void WriteInlineValueBooleanTest1(Ishiko::Tests::FileComparisonTest& test);
    static void WriteInlineValueUTF8StringTest1(Ishiko::Tests::FileComparisonTest& test);
};

#endif

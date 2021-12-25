/*
    Copyright (c) 2019-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TEST_TREEDB_CORE_TREEDBVALUETESTS_H_
#define _DIPLODOCUSDB_TEST_TREEDB_CORE_TREEDBVALUETESTS_H_

#include <Ishiko/Tests.h>

class TreeDBValueTests : public Ishiko::Tests::TestSequence
{
public:
    TreeDBValueTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void Int8Test1(Ishiko::Tests::Test& test);
    static void Int32Test1(Ishiko::Tests::Test& test);
    static void DoubleTest1(Ishiko::Tests::Test& test);
    static void UTF8StringTest1(Ishiko::Tests::Test& test);
    static void DateTest1(Ishiko::Tests::Test& test);
    static void SetInt8Test1(Ishiko::Tests::Test& test);
    static void SetInt32Test1(Ishiko::Tests::Test& test);
    static void SetDoubleTest1(Ishiko::Tests::Test& test);
    static void SetUTF8StringTest1(Ishiko::Tests::Test& test);
    static void SetDateTest1(Ishiko::Tests::Test& test);
};

#endif

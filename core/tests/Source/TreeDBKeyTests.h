/*
    Copyright (c) 2018-2021 Xavier Leclercq

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

#ifndef _DIPLODOCUSDB_TEST_TREEDB_CORE_TREEDBKEYTESTS_H_
#define _DIPLODOCUSDB_TEST_TREEDB_CORE_TREEDBKEYTESTS_H_

#include <Ishiko/Tests.h>

class TreeDBKeyTests : public Ishiko::Tests::TestSequence
{
public:
    TreeDBKeyTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructionTest1(Ishiko::Tests::Test& test);
    static void ParentKeyTest1(Ishiko::Tests::Test& test);
    static void ParentKeyTest2(Ishiko::Tests::Test& test);
    static void ParentKeyTest3(Ishiko::Tests::Test& test);
    static void BaseTest1(Ishiko::Tests::Test& test);
    static void BaseTest2(Ishiko::Tests::Test& test);
    static void BaseTest3(Ishiko::Tests::Test& test);
    static void BaseTest4(Ishiko::Tests::Test& test);
};

#endif

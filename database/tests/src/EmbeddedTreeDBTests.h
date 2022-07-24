/*
    Copyright (c) 2018-2022 Xavier Leclercq

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

#ifndef _DIPLODOCUSDB_TEST_TREEDB_EMBEDDEDTREEDBTESTS_H_
#define _DIPLODOCUSDB_TEST_TREEDB_EMBEDDEDTREEDBTESTS_H_

#include <Ishiko/TestFramework.hpp>

class EmbeddedTreeDBTests : public Ishiko::TestSequence
{
public:
    EmbeddedTreeDBTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void CreationTest1(Ishiko::Test& test);
    static void CreateTest1(Ishiko::Test& test);
    static void OpenTest1(Ishiko::Test& test);
    static void OpenTest2(Ishiko::Test& test);
    static void OpenTest3(Ishiko::Test& test);
    static void OpenTest4(Ishiko::Test& test);
    static void OpenTest5(Ishiko::Test& test);
    static void ChildNodesTest1(Ishiko::Test& test);
    static void ChildNodesTest2(Ishiko::Test& test);
    static void InsertChildNodeTest1(Ishiko::Test& test);
    static void InsertChildNodeBeforeTest1(Ishiko::Test& test);
    static void InsertChildNodeBeforeTest2(Ishiko::Test& test);
    static void InsertChildNodeBeforeTest3(Ishiko::Test& test);
    static void InsertChildNodeAfterTest1(Ishiko::Test& test);
    static void InsertChildNodeAfterTest2(Ishiko::Test& test);
    static void AppendChildNodeTest1(Ishiko::Test& test);
    static void AppendChildNodeTest2(Ishiko::Test& test);
    static void AppendChildNodeTest3(Ishiko::Test& test);
    static void AppendChildNodeTest4(Ishiko::Test& test);
    static void AppendChildNodeTest5(Ishiko::Test& test);
    static void AppendChildNodeTest6(Ishiko::Test& test);
    static void RemoveChildNodeTest1(Ishiko::Test& test);
    static void RemoveAllChildNodesTest1(Ishiko::Test& test);
};

#endif

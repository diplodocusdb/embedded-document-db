/*
    Copyright (c) 2018-2019 Xavier Leclercq

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

#include "TreeDBKeyTests.h"
#include "DiplodocusDB/TreeDB/Core/TreeDBKey.h"

using namespace Ishiko::Tests;

TreeDBKeyTests::TreeDBKeyTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "TreeDBKey tests", environment)
{
    append<HeapAllocationErrorsTest>("Construction test 1", ConstructionTest1);
    append<HeapAllocationErrorsTest>("parentKey test 1", ParentKeyTest1);
    append<HeapAllocationErrorsTest>("parentKey test 2", ParentKeyTest2);
    append<HeapAllocationErrorsTest>("parentKey test 3", ParentKeyTest3);
    append<HeapAllocationErrorsTest>("base test 1", BaseTest1);
    append<HeapAllocationErrorsTest>("base test 2", BaseTest2);
    append<HeapAllocationErrorsTest>("base test 3", BaseTest3);
    append<HeapAllocationErrorsTest>("base test 4", BaseTest4);
}

void TreeDBKeyTests::ConstructionTest1(Test& test)
{
    DiplodocusDB::TreeDBKey key("/");

    ISHTF_FAIL_UNLESS(key.value() == "/");
    ISHTF_PASS();
}

void TreeDBKeyTests::ParentKeyTest1(Test& test)
{
    DiplodocusDB::TreeDBKey key("/key1/key2");

    ISHTF_FAIL_UNLESS(key.parentKey() == "/key1");
    ISHTF_PASS();
}

void TreeDBKeyTests::ParentKeyTest2(Test& test)
{
    DiplodocusDB::TreeDBKey key("/key1");

    ISHTF_FAIL_UNLESS(key.parentKey() == "/");
    ISHTF_PASS();
}

void TreeDBKeyTests::ParentKeyTest3(Test& test)
{
    DiplodocusDB::TreeDBKey key("/");

    ISHTF_FAIL_UNLESS(key.parentKey().isNull());
    ISHTF_PASS();
}

void TreeDBKeyTests::BaseTest1(Test& test)
{
    DiplodocusDB::TreeDBKey key("/key1/key2");

    ISHTF_FAIL_UNLESS(key.base() == "key2");
    ISHTF_PASS();
}

void TreeDBKeyTests::BaseTest2(Test& test)
{
    DiplodocusDB::TreeDBKey key("/key1");

    ISHTF_FAIL_UNLESS(key.base() == "key1");
    ISHTF_PASS();
}

void TreeDBKeyTests::BaseTest3(Test& test)
{
    DiplodocusDB::TreeDBKey key("/");

    ISHTF_FAIL_UNLESS(key.base() == "");
    ISHTF_PASS();
}

void TreeDBKeyTests::BaseTest4(Test& test)
{
    DiplodocusDB::TreeDBKey key("key1");

    ISHTF_FAIL_UNLESS(key.base() == "key1");
    ISHTF_PASS();
}

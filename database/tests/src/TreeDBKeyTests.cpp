/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "TreeDBKeyTests.h"
#include "DiplodocusDB/EmbeddedDocumentDB/TreeDBKey.hpp"

using namespace Ishiko;

TreeDBKeyTests::TreeDBKeyTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "TreeDBKey tests", context)
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

    ISHIKO_TEST_FAIL_IF_NEQ(key.value(), "/");
    ISHIKO_TEST_PASS();
}

void TreeDBKeyTests::ParentKeyTest1(Test& test)
{
    DiplodocusDB::TreeDBKey key("/key1/key2");

    ISHIKO_TEST_FAIL_IF_NEQ(key.parentKey(), "/key1");
    ISHIKO_TEST_PASS();
}

void TreeDBKeyTests::ParentKeyTest2(Test& test)
{
    DiplodocusDB::TreeDBKey key("/key1");

    ISHIKO_TEST_FAIL_IF_NEQ(key.parentKey(), "/");
    ISHIKO_TEST_PASS();
}

void TreeDBKeyTests::ParentKeyTest3(Test& test)
{
    DiplodocusDB::TreeDBKey key("/");

    ISHIKO_TEST_FAIL_IF_NOT(key.parentKey().isNull());
    ISHIKO_TEST_PASS();
}

void TreeDBKeyTests::BaseTest1(Test& test)
{
    DiplodocusDB::TreeDBKey key("/key1/key2");

    ISHIKO_TEST_FAIL_IF_NEQ(key.base(), "key2");
    ISHIKO_TEST_PASS();
}

void TreeDBKeyTests::BaseTest2(Test& test)
{
    DiplodocusDB::TreeDBKey key("/key1");

    ISHIKO_TEST_FAIL_IF_NEQ(key.base(), "key1");
    ISHIKO_TEST_PASS();
}

void TreeDBKeyTests::BaseTest3(Test& test)
{
    DiplodocusDB::TreeDBKey key("/");

    ISHIKO_TEST_FAIL_IF_NEQ(key.base(), "");
    ISHIKO_TEST_PASS();
}

void TreeDBKeyTests::BaseTest4(Test& test)
{
    DiplodocusDB::TreeDBKey key("key1");

    ISHIKO_TEST_FAIL_IF_NEQ(key.base(), "key1");
    ISHIKO_TEST_PASS();
}

/*
    Copyright (c) 2019-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "TreeDBValueTests.h"
#include "DiplodocusDB/TreeDB/Core/TreeDBValue.h"

using namespace Ishiko::Tests;

TreeDBValueTests::TreeDBValueTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "TreeDBValue tests", environment)
{
    append<HeapAllocationErrorsTest>("Construction test 1", ConstructionTest1);
    append<HeapAllocationErrorsTest>("Int8 test 1", Int8Test1);
    append<HeapAllocationErrorsTest>("Int32 test 1", Int32Test1);
    append<HeapAllocationErrorsTest>("UTF8String test 1", UTF8StringTest1);
    append<HeapAllocationErrorsTest>("setInt8 test 1", SetInt8Test1);
    append<HeapAllocationErrorsTest>("setInt32 test 1", SetInt32Test1);
    append<HeapAllocationErrorsTest>("setUTF8String test 1", SetUTF8StringTest1);
}

void TreeDBValueTests::ConstructionTest1(Test& test)
{
    DiplodocusDB::TreeDBValue value;

    ISHIKO_FAIL_IF_NEQ(value.type().primitiveType(), DiplodocusDB::PrimitiveDataType::null);
    ISHIKO_FAIL_IF_NEQ(value.type().modifier(), DiplodocusDB::DataTypeModifier::none);
    ISHIKO_PASS();
}

void TreeDBValueTests::Int8Test1(Test& test)
{
    DiplodocusDB::TreeDBValue value = DiplodocusDB::TreeDBValue::Int8(123);

    ISHIKO_ABORT_IF_NEQ(value.type().primitiveType(), DiplodocusDB::PrimitiveDataType::int8bit);
    ISHIKO_ABORT_IF_NEQ(value.type().modifier(), DiplodocusDB::DataTypeModifier::none);
    ISHIKO_FAIL_IF_NEQ(value.asInt8(), 123);
    ISHIKO_PASS();
}

void TreeDBValueTests::Int32Test1(Test& test)
{
    DiplodocusDB::TreeDBValue value = DiplodocusDB::TreeDBValue::Int32(123);

    ISHIKO_ABORT_IF_NEQ(value.type().primitiveType(), DiplodocusDB::PrimitiveDataType::int32bit);
    ISHIKO_ABORT_IF_NEQ(value.type().modifier(), DiplodocusDB::DataTypeModifier::none);
    ISHIKO_FAIL_IF_NEQ(value.asInt32(), 123);
    ISHIKO_PASS();
}

void TreeDBValueTests::UTF8StringTest1(Test& test)
{
    DiplodocusDB::TreeDBValue value = DiplodocusDB::TreeDBValue::UTF8String("string1");

    ISHIKO_ABORT_IF_NEQ(value.type().primitiveType(), DiplodocusDB::PrimitiveDataType::unicodeString);
    ISHIKO_ABORT_IF_NEQ(value.type().modifier(), DiplodocusDB::DataTypeModifier::none);
    ISHIKO_FAIL_IF_NEQ(value.asUTF8String(), "string1");
    ISHIKO_PASS();
}

void TreeDBValueTests::SetInt32Test1(Test& test)
{
    DiplodocusDB::TreeDBValue value;
    value.setInt32(123);

    ISHIKO_FAIL_IF_NEQ(value.asInt32(), 123);
    ISHIKO_PASS();
}

void TreeDBValueTests::SetInt8Test1(Test& test)
{
    DiplodocusDB::TreeDBValue value;
    value.setInt8(123);

    ISHIKO_FAIL_IF_NEQ(value.asInt8(), 123);
    ISHIKO_PASS();
}

void TreeDBValueTests::SetUTF8StringTest1(Test& test)
{
    DiplodocusDB::TreeDBValue value;
    value.setUTF8String("text");

    ISHIKO_FAIL_IF_NEQ(value.asUTF8String(), "text");
    ISHIKO_PASS();
}

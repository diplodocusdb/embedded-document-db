/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "TreeDBValueTests.h"
#include "DiplodocusDB/EmbeddedDocumentDB/TreeDBValue.hpp"
#include <boost/date_time.hpp>

using namespace boost::gregorian;
using namespace Ishiko;

TreeDBValueTests::TreeDBValueTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "TreeDBValue tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Int8 test 1", Int8Test1);
    append<HeapAllocationErrorsTest>("Int32 test 1", Int32Test1);
    append<HeapAllocationErrorsTest>("UnsignedInt64 test 1", UnsignedInt64Test1);
    append<HeapAllocationErrorsTest>("Double test 1", DoubleTest1);
    append<HeapAllocationErrorsTest>("UTF8String test 1", UTF8StringTest1);
    append<HeapAllocationErrorsTest>("Date test 1", DateTest1);
    append<HeapAllocationErrorsTest>("setInt8 test 1", SetInt8Test1);
    append<HeapAllocationErrorsTest>("setInt32 test 1", SetInt32Test1);
    append<HeapAllocationErrorsTest>("setUnsignedInt64 test 1", SetUnsignedInt64Test1);
    append<HeapAllocationErrorsTest>("setDouble test 1", SetDoubleTest1);
    append<HeapAllocationErrorsTest>("setUTF8String test 1", SetUTF8StringTest1);
    append<HeapAllocationErrorsTest>("setDate test 1", SetDateTest1);
}

void TreeDBValueTests::ConstructorTest1(Test& test)
{
    DiplodocusDB::TreeDBValue value;

    ISHIKO_TEST_FAIL_IF_NEQ(value.type().primitiveType(), DiplodocusDB::PrimitiveDataType::null);
    ISHIKO_TEST_FAIL_IF_NEQ(value.type().modifier(), DiplodocusDB::DataTypeModifier::none);
    ISHIKO_TEST_PASS();
}

void TreeDBValueTests::Int8Test1(Test& test)
{
    DiplodocusDB::TreeDBValue value = DiplodocusDB::TreeDBValue::Int8(123);

    ISHIKO_TEST_ABORT_IF_NEQ(value.type().primitiveType(), DiplodocusDB::PrimitiveDataType::int8bit);
    ISHIKO_TEST_ABORT_IF_NEQ(value.type().modifier(), DiplodocusDB::DataTypeModifier::none);
    ISHIKO_TEST_FAIL_IF_NEQ(value.asInt8(), 123);
    ISHIKO_TEST_PASS();
}

void TreeDBValueTests::Int32Test1(Test& test)
{
    DiplodocusDB::TreeDBValue value = DiplodocusDB::TreeDBValue::Int32(123);

    ISHIKO_TEST_ABORT_IF_NEQ(value.type().primitiveType(), DiplodocusDB::PrimitiveDataType::int32bit);
    ISHIKO_TEST_ABORT_IF_NEQ(value.type().modifier(), DiplodocusDB::DataTypeModifier::none);
    ISHIKO_TEST_FAIL_IF_NEQ(value.asInt32(), 123);
    ISHIKO_TEST_PASS();
}

void TreeDBValueTests::UnsignedInt64Test1(Test& test)
{
    DiplodocusDB::TreeDBValue value = DiplodocusDB::TreeDBValue::UnsignedInt64(123);

    ISHIKO_TEST_ABORT_IF_NEQ(value.type().primitiveType(), DiplodocusDB::PrimitiveDataType::unsignedInt64bit);
    ISHIKO_TEST_ABORT_IF_NEQ(value.type().modifier(), DiplodocusDB::DataTypeModifier::none);
    ISHIKO_TEST_FAIL_IF_NEQ(value.asUnsignedInt64(), 123);
    ISHIKO_TEST_PASS();
}

void TreeDBValueTests::DoubleTest1(Test& test)
{
    DiplodocusDB::TreeDBValue value = DiplodocusDB::TreeDBValue::Double(123.45);

    ISHIKO_TEST_ABORT_IF_NEQ(value.type().primitiveType(), DiplodocusDB::PrimitiveDataType::IEEE754Binary64);
    ISHIKO_TEST_ABORT_IF_NEQ(value.type().modifier(), DiplodocusDB::DataTypeModifier::none);
    ISHIKO_TEST_FAIL_IF_NEQ(value.asDouble(), 123.45);
    ISHIKO_TEST_PASS();
}

void TreeDBValueTests::UTF8StringTest1(Test& test)
{
    DiplodocusDB::TreeDBValue value = DiplodocusDB::TreeDBValue::UTF8String("string1");

    ISHIKO_TEST_ABORT_IF_NEQ(value.type().primitiveType(), DiplodocusDB::PrimitiveDataType::unicodeString);
    ISHIKO_TEST_ABORT_IF_NEQ(value.type().modifier(), DiplodocusDB::DataTypeModifier::none);
    ISHIKO_TEST_FAIL_IF_NEQ(value.asUTF8String(), "string1");
    ISHIKO_TEST_PASS();
}

void TreeDBValueTests::DateTest1(Test& test)
{
    DiplodocusDB::TreeDBValue value = DiplodocusDB::TreeDBValue::Date(date(2021, 12, 25));

    ISHIKO_TEST_ABORT_IF_NEQ(value.type().primitiveType(), DiplodocusDB::PrimitiveDataType::date);
    ISHIKO_TEST_ABORT_IF_NEQ(value.type().modifier(), DiplodocusDB::DataTypeModifier::none);
    ISHIKO_TEST_FAIL_IF_NEQ(value.asDate(), date(2021, 12, 25));
    ISHIKO_TEST_PASS();
}

void TreeDBValueTests::SetInt8Test1(Test& test)
{
    DiplodocusDB::TreeDBValue value;
    value.setInt8(123);

    ISHIKO_TEST_FAIL_IF_NEQ(value.asInt8(), 123);
    ISHIKO_TEST_PASS();
}

void TreeDBValueTests::SetInt32Test1(Test& test)
{
    DiplodocusDB::TreeDBValue value;
    value.setInt32(123);

    ISHIKO_TEST_FAIL_IF_NEQ(value.asInt32(), 123);
    ISHIKO_TEST_PASS();
}

void TreeDBValueTests::SetUnsignedInt64Test1(Test& test)
{
    DiplodocusDB::TreeDBValue value;
    value.setUnsignedInt64(123);

    ISHIKO_TEST_FAIL_IF_NEQ(value.asUnsignedInt64(), 123);
    ISHIKO_TEST_PASS();
}

void TreeDBValueTests::SetDoubleTest1(Test& test)
{
    DiplodocusDB::TreeDBValue value;
    value.setDouble(123.45);

    ISHIKO_TEST_FAIL_IF_NEQ(value.asDouble(), 123.45);
    ISHIKO_TEST_PASS();
}

void TreeDBValueTests::SetUTF8StringTest1(Test& test)
{
    DiplodocusDB::TreeDBValue value;
    value.setUTF8String("text");

    ISHIKO_TEST_FAIL_IF_NEQ(value.asUTF8String(), "text");
    ISHIKO_TEST_PASS();
}

void TreeDBValueTests::SetDateTest1(Test& test)
{
    DiplodocusDB::TreeDBValue value;
    value.setDate(date(2021, 12, 15));

    ISHIKO_TEST_FAIL_IF_NEQ(value.asDate(), date(2021, 12, 15));
    ISHIKO_TEST_PASS();
}

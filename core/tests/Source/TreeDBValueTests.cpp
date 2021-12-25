/*
    Copyright (c) 2019-2021 Xavier Leclercq

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

    ISHIKO_FAIL_IF_NEQ(value.type().primitiveType(), DiplodocusDB::EPrimitiveDataType::eNULL);
    ISHIKO_FAIL_IF_NEQ(value.type().modifier(), DiplodocusDB::EDataTypeModifier::eNone);
    ISHIKO_PASS();
}

void TreeDBValueTests::Int8Test1(Test& test)
{
    DiplodocusDB::TreeDBValue value = DiplodocusDB::TreeDBValue::Int8(123);

    ISHIKO_ABORT_IF_NEQ(value.type().primitiveType(), DiplodocusDB::EPrimitiveDataType::eInt8);
    ISHIKO_ABORT_IF_NEQ(value.type().modifier(), DiplodocusDB::EDataTypeModifier::eNone);
    ISHIKO_FAIL_IF_NEQ(value.asInt8(), 123);
    ISHIKO_PASS();
}

void TreeDBValueTests::Int32Test1(Test& test)
{
    DiplodocusDB::TreeDBValue value = DiplodocusDB::TreeDBValue::Int32(123);

    ISHIKO_ABORT_IF_NEQ(value.type().primitiveType(), DiplodocusDB::EPrimitiveDataType::eInt32);
    ISHIKO_ABORT_IF_NEQ(value.type().modifier(), DiplodocusDB::EDataTypeModifier::eNone);
    ISHIKO_FAIL_IF_NEQ(value.asInt32(), 123);
    ISHIKO_PASS();
}

void TreeDBValueTests::UTF8StringTest1(Test& test)
{
    DiplodocusDB::TreeDBValue value = DiplodocusDB::TreeDBValue::UTF8String("string1");

    ISHIKO_ABORT_IF_NEQ(value.type().primitiveType(), DiplodocusDB::EPrimitiveDataType::eUTF8String);
    ISHIKO_ABORT_IF_NEQ(value.type().modifier(), DiplodocusDB::EDataTypeModifier::eNone);
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

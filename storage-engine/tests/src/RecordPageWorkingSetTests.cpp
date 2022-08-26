/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "RecordPageWorkingSetTests.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/RecordPageWorkingSet.hpp"

using namespace DiplodocusDB::EDDBImpl;
using namespace Ishiko;

RecordPageWorkingSetTests::RecordPageWorkingSetTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "RecordPageWorkingSet tests", context)
{
    append<HeapAllocationErrorsTest>("ConstructorTest1 test 1", ConstructorTest1);
}

void RecordPageWorkingSetTests::ConstructorTest1(Test& test)
{
    RecordPageWorkingSet working_set;

    ISHIKO_TEST_PASS();
}

/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "SecondaryFileTests.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/SecondaryFile.hpp"

using namespace DiplodocusDB;
using namespace Ishiko;

SecondaryFileTests::SecondaryFileTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "SecondaryFile tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructionTest1);
}

void SecondaryFileTests::ConstructionTest1(Test& test)
{
    SecondaryFile secondaryFile;

    ISHIKO_TEST_PASS();
}

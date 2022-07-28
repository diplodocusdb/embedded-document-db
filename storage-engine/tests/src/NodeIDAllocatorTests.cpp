/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "NodeIDAllocatorTests.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/NodeIDAllocator.hpp"

using namespace DiplodocusDB;
using namespace Ishiko;

NodeIDAllocatorTests::NodeIDAllocatorTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "NodeIDAllocator tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructionTest1);
}

void NodeIDAllocatorTests::ConstructionTest1(Test& test)
{
    NodeIDAllocator nodeIDAllocator;

    ISHIKO_TEST_PASS();
}

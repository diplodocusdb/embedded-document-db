/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "NodeIDTests.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/NodeID.hpp"

using namespace DiplodocusDB;
using namespace Ishiko;

NodeIDTests::NodeIDTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "NodeID tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructionTest1);
}

void NodeIDTests::ConstructionTest1(Test& test)
{
    NodeID id(0);

    ISHIKO_TEST_PASS();
}

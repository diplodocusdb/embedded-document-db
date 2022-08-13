/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "SiblingNodesRecordGroupCacheTests.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/SiblingNodesRecordGroupCache.hpp"

using namespace DiplodocusDB::EDDBImpl;
using namespace Ishiko;

SiblingNodesRecordGroupCacheTests::SiblingNodesRecordGroupCacheTests(const TestNumber& number,
    const TestContext& context)
    : TestSequence(number, "SiblingNodesRecordGroupCache tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructionTest1);
    append<HeapAllocationErrorsTest>("operator[] test 1", SubscriptOperatorTest1);
    append<HeapAllocationErrorsTest>("operator[] test 2", SubscriptOperatorTest2);
    append<HeapAllocationErrorsTest>("find test 1", FindTest1);
    append<HeapAllocationErrorsTest>("find test 2", FindTest2);
    append<HeapAllocationErrorsTest>("erase test 1", EraseTest1);
}

void SiblingNodesRecordGroupCacheTests::ConstructionTest1(Test& test)
{
    SiblingNodesRecordGroupCache cache;

    ISHIKO_TEST_PASS();
}

void SiblingNodesRecordGroupCacheTests::SubscriptOperatorTest1(Test& test)
{
    SiblingNodesRecordGroupCache cache;
    std::shared_ptr<SiblingNodesRecordGroup>& group = cache[NodeID(1)];

    ISHIKO_TEST_FAIL_IF_NEQ(group->parentNodeID(), NodeID(1));
    ISHIKO_TEST_FAIL_IF_NEQ(group->size(), 0);
    ISHIKO_TEST_PASS();
}

void SiblingNodesRecordGroupCacheTests::SubscriptOperatorTest2(Test& test)
{
    SiblingNodesRecordGroupCache cache;
    
    std::shared_ptr<SiblingNodesRecordGroup>& group1 = cache[NodeID(1)];

    ISHIKO_TEST_FAIL_IF_NEQ(group1->parentNodeID(), NodeID(1));
    ISHIKO_TEST_FAIL_IF_NEQ(group1->size(), 0);

    std::shared_ptr<SiblingNodesRecordGroup>& group2 = cache[NodeID(1)];

    // Make sure we return the group that was created during the first call
    ISHIKO_TEST_FAIL_IF_NEQ(&group1, &group2);

    ISHIKO_TEST_PASS();
}

void SiblingNodesRecordGroupCacheTests::FindTest1(Test& test)
{
    SiblingNodesRecordGroupCache cache;
    std::shared_ptr<SiblingNodesRecordGroup> group;
    bool found = cache.find(NodeID(1), group);

    ISHIKO_TEST_FAIL_IF(found);
    ISHIKO_TEST_FAIL_IF(group);
    ISHIKO_TEST_PASS();
}

void SiblingNodesRecordGroupCacheTests::FindTest2(Test& test)
{
    SiblingNodesRecordGroupCache cache;

    std::shared_ptr<SiblingNodesRecordGroup>& group1 = cache[NodeID(1)];

    ISHIKO_TEST_FAIL_IF_NEQ(group1->parentNodeID(), NodeID(1));
    ISHIKO_TEST_FAIL_IF_NEQ(group1->size(), 0);

    std::shared_ptr<SiblingNodesRecordGroup> group2;
    bool found = cache.find(NodeID(1), group2);

    ISHIKO_TEST_FAIL_IF_NOT(found);
    // Make sure we return the group that was created during the first call
    ISHIKO_TEST_FAIL_IF_NEQ(group1.get(), group2.get());
    ISHIKO_TEST_PASS();
}

void SiblingNodesRecordGroupCacheTests::EraseTest1(Test& test)
{
    SiblingNodesRecordGroupCache cache;
    std::shared_ptr<SiblingNodesRecordGroup>& group1 = cache[NodeID(1)];

    ISHIKO_TEST_FAIL_IF_NEQ(group1->parentNodeID(), NodeID(1));
    ISHIKO_TEST_FAIL_IF_NEQ(group1->size(), 0);

    cache.erase(NodeID(1));

    std::shared_ptr<SiblingNodesRecordGroup> group2;
    bool found = cache.find(NodeID(1), group2);

    ISHIKO_TEST_FAIL_IF(found);
    ISHIKO_TEST_PASS();
}

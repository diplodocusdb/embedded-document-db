/*
    Copyright (c) 2019 Xavier Leclercq

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

#include "SiblingNodesRecordGroupCacheTests.h"
#include "SiblingNodesRecordGroupCache.h"

using namespace Ishiko::Tests;

SiblingNodesRecordGroupCacheTests::SiblingNodesRecordGroupCacheTests(const TestNumber& number,
    const TestEnvironment& environment)
    : TestSequence(number, "SiblingNodesRecordGroupCache tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructionTest1);
    append<HeapAllocationErrorsTest>("find test 1", FindTest1);
}

void SiblingNodesRecordGroupCacheTests::ConstructionTest1(Test& test)
{
    DiplodocusDB::SiblingNodesRecordGroupCache cache;

    ISHTF_PASS();
}

void SiblingNodesRecordGroupCacheTests::FindTest1(Test& test)
{
    DiplodocusDB::SiblingNodesRecordGroupCache cache;
    std::shared_ptr<DiplodocusDB::SiblingNodesRecordGroup> group;
    bool found = cache.find(DiplodocusDB::NodeID(1), group);

    ISHTF_FAIL_IF(found);
    ISHTF_FAIL_IF((bool)group);
    ISHTF_PASS();
}

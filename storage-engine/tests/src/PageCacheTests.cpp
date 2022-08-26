/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "PageCacheTests.h"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/PageCache.h"

using namespace DiplodocusDB::EDDBImpl;
using namespace Ishiko;

PageCacheTests::PageCacheTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "PageCache tests", context)
{
    append<HeapAllocationErrorsTest>("ConstructorTest1 test 1", ConstructorTest1);
}

void PageCacheTests::ConstructorTest1(Test& test)
{
    PageCache pageCache;

    ISHIKO_TEST_PASS();
}

/*
    Copyright (c) 2018-2019 Xavier Leclercq

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

#include "KeyCacheTests.h"
#include "KeyCache.h"
#include <sstream>
#include <vector>

using namespace Ishiko::Tests;

KeyCacheTests::KeyCacheTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "KeyCache tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("operator[] test 1", SubscriptOperatorTest1);
    append<HeapAllocationErrorsTest>("operator[] test 2", SubscriptOperatorTest2);
    append<HeapAllocationErrorsTest>("operator[] test 3", SubscriptOperatorTest3);
    append<HeapAllocationErrorsTest>("operator[] test 4", SubscriptOperatorTest4);
    append<HeapAllocationErrorsTest>("operator[] test 5", SubscriptOperatorTest5);
    append<HeapAllocationErrorsTest>("operator[] test 6", SubscriptOperatorTest6);
    append<HeapAllocationErrorsTest>("operator[] test 7", SubscriptOperatorTest7);
    append<HeapAllocationErrorsTest>("operator[] test 8", SubscriptOperatorTest8);
}

void KeyCacheTests::CreationTest1(Test& test)
{
    DiplodocusDB::KeyCache cache;

    ISHTF_PASS();
}

void KeyCacheTests::SubscriptOperatorTest1(Test& test)
{
    DiplodocusDB::KeyCache cache;
    DiplodocusDB::CachedKeyId id = cache["/"];

    ISHTF_FAIL_UNLESS(cache["/"] == id);
    ISHTF_FAIL_UNLESS(cache.key(id) == "/");
    ISHTF_PASS();
}

void KeyCacheTests::SubscriptOperatorTest2(Test& test)
{
    DiplodocusDB::KeyCache cache;
    DiplodocusDB::CachedKeyId id = cache["/key1"];

    ISHTF_FAIL_UNLESS(cache["/key1"] == id);
    ISHTF_FAIL_UNLESS(cache.key(id) == "/key1");
    ISHTF_PASS();
}

void KeyCacheTests::SubscriptOperatorTest3(Test& test)
{
    DiplodocusDB::KeyCache cache;
    DiplodocusDB::CachedKeyId id = cache["/key1/key2"];

    ISHTF_FAIL_UNLESS(cache["/key1/key2"] == id);
    ISHTF_FAIL_UNLESS(cache.key(id) == "/key1/key2");
    ISHTF_PASS();
}

void KeyCacheTests::SubscriptOperatorTest4(Test& test)
{
    DiplodocusDB::KeyCache cache;
    DiplodocusDB::CachedKeyId id1 = cache["/key1"];
    DiplodocusDB::CachedKeyId id2 = cache["/key2"];
    DiplodocusDB::CachedKeyId id3 = cache["/key3"];
    DiplodocusDB::CachedKeyId id4 = cache["/key4"];

    ISHTF_FAIL_UNLESS(cache["/key1"] == id1);
    ISHTF_FAIL_UNLESS(cache["/key2"] == id2);
    ISHTF_FAIL_UNLESS(cache["/key3"] == id3);
    ISHTF_FAIL_UNLESS(cache["/key4"] == id4);
    ISHTF_FAIL_UNLESS(cache.key(id1) == "/key1");
    ISHTF_FAIL_UNLESS(cache.key(id2) == "/key2");
    ISHTF_FAIL_UNLESS(cache.key(id3) == "/key3");
    ISHTF_FAIL_UNLESS(cache.key(id4) == "/key4");
    ISHTF_PASS();
}

void KeyCacheTests::SubscriptOperatorTest5(Test& test)
{
    DiplodocusDB::KeyCache cache;

    std::vector<DiplodocusDB::CachedKeyId> ids;
    for (size_t i = 0; i < 1000000; ++i)
    {
        std::stringstream key;
        key << "/key" << i;
        DiplodocusDB::CachedKeyId id = cache[key.str()];
        ids.push_back(id);
    }

    for (size_t i = 0; i < 1000000; ++i)
    {
        std::stringstream key;
        key << "/key" << i;
        DiplodocusDB::CachedKeyId id = cache[key.str()];

        ISHTF_ABORT_UNLESS(id != ids[i]);
        ISHTF_ABORT_UNLESS(cache.key(id).value() != key.str());
    }

    ISHTF_PASS();
}

void KeyCacheTests::SubscriptOperatorTest6(Test& test)
{
    DiplodocusDB::KeyCache cache;

    std::stringstream key;
    for (size_t i = 0; i < 1000; ++i)
    {
        key << "/key" << i;
    }

    DiplodocusDB::CachedKeyId id = cache[key.str()];

    ISHTF_FAIL_UNLESS(cache[key.str()] == id);
    ISHTF_PASS();
}

void KeyCacheTests::SubscriptOperatorTest7(Test& test)
{
    DiplodocusDB::KeyCache cache;

    std::stringstream key;
    for (size_t i = 0; i < 1000000; ++i)
    {
        key << "/key" << i;
    }

    DiplodocusDB::CachedKeyId id = cache[key.str()];
    
    ISHTF_FAIL_UNLESS(cache[key.str()] == id);
    ISHTF_PASS();
}

void KeyCacheTests::SubscriptOperatorTest8(Test& test)
{
    DiplodocusDB::KeyCache cache;

    std::vector<DiplodocusDB::CachedKeyId> ids;
    for (size_t i = 0; i < 1000; ++i)
    {
        std::stringstream key;
        key << "/key" << i;
        DiplodocusDB::CachedKeyId id = cache[key.str()];
        ids.push_back(id);
        for (size_t j = 0; j < 1000; ++j)
        {
            std::stringstream key;
            key << "/key" << i << "/key" << j;
            DiplodocusDB::CachedKeyId id = cache[key.str()];
            ids.push_back(id);
        }
    }
    
    size_t index = 0;
    for (size_t i = 0; i < 1000; ++i)
    {
        std::stringstream key;
        key << "/key" << i;
        DiplodocusDB::CachedKeyId id = cache[key.str()];

        ISHTF_ABORT_UNLESS(id == ids[index++]);
        ISHTF_ABORT_UNLESS(cache.key(id).value() == key.str());
        
        for (size_t j = 0; j < 1000; ++j)
        {
            std::stringstream key;
            key << "/key" << i << "/key" << j;
            DiplodocusDB::CachedKeyId id = cache[key.str()];

            ISHTF_ABORT_UNLESS(id == ids[index++]);
            ISHTF_ABORT_UNLESS(cache.key(id).value() == key.str());
        }
    }

    ISHTF_PASS();
}

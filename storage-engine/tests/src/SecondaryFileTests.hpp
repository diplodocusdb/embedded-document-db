/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_SECONDARYFILETESTS_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_SECONDARYFILETESTS_HPP_

#include <Ishiko/TestFramework.hpp>

class SecondaryFileTests : public Ishiko::TestSequence
{
public:
    SecondaryFileTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructionTest1(Ishiko::Test& test);
};

#endif

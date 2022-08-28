/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_RECORDFILESSETTESTS_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_TESTS_RECORDFILESSETTESTS_HPP_

#include <Ishiko/TestFramework.hpp>

class RecordFilesSetTests : public Ishiko::TestSequence
{
public:
    RecordFilesSetTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);
};

#endif

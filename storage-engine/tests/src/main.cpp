/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "NodeIDTests.hpp"
#include "SecondaryFileTests.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/linkoptions.hpp"
#include <Ishiko/TestFramework.hpp>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("DiplodocusEmbeddedDocumentDBStorageEngine Library Tests");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<NodeIDTests>();
    theTests.append<SecondaryFileTests>();

    return theTestHarness.run();
}

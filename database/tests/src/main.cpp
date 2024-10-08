/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "EmbeddedDocumentDBTests.hpp"
#include "TreeDBKeyTests.h"
#include "TransactionTests.h"
#include "XMLTreeDBTests/XMLTreeDBTests.h"
#include "DiplodocusDB/EmbeddedDocumentDB/linkoptions.hpp"
#include <Ishiko/TestFramework.hpp>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("DiplodocusEmbeddedDocumentDB Library Tests");

    theTestHarness.context().setDataDirectory("../../data");
    theTestHarness.context().setOutputDirectory("../../output");
    theTestHarness.context().setReferenceDirectory("../../reference");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<TreeDBKeyTests>();
    theTests.append<EmbeddedDocumentDBTests>();
    theTests.append<TransactionTests>();
    theTests.append<XMLTreeDBTests>();

    return theTestHarness.run();
}

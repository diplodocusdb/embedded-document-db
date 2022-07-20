/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "TreeDBKeyTests.h"
#include "TreeDBValueTests.h"
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
    theTests.append<TreeDBValueTests>();
    theTests.append<XMLTreeDBTests>();

    return theTestHarness.run();
}

/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "XMLTreeDBTests/XMLTreeDBTests.h"
#include <DiplodocusDB/TreeDB/XMLTreeDB/linkoptions.hpp>
#include <Ishiko/Tests.h>

using namespace Ishiko::Tests;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("DiplodocusXMLTreeDB");

    theTestHarness.environment().setTestDataDirectory("../../data");
    theTestHarness.environment().setTestOutputDirectory("../../output");
    theTestHarness.environment().setReferenceDataDirectory("../../reference");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<XMLTreeDBTests>();

    return theTestHarness.run();
}

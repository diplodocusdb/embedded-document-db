/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "XMLTreeDBTests/XMLTreeDBTests.h"
#include <DiplodocusDB/TreeDB/XMLTreeDB/linkoptions.hpp>
#include <Ishiko/Tests.hpp>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("DiplodocusXMLTreeDB");

    theTestHarness.context().setTestDataDirectory("../../data");
    theTestHarness.context().setTestOutputDirectory("../../output");
    theTestHarness.context().setReferenceDataDirectory("../../reference");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<XMLTreeDBTests>();

    return theTestHarness.run();
}

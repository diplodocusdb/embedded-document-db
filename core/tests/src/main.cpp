/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "TreeDBKeyTests.h"
#include "TreeDBValueTests.h"
#include <DiplodocusDB/TreeDB/Core/linkoptions.hpp>
#include <Ishiko/Tests.hpp>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("DiplodocusTreeDBCore");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<TreeDBKeyTests>();
    theTests.append<TreeDBValueTests>();

    return theTestHarness.run();
}

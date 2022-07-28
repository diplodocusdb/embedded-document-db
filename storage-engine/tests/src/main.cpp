/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "MasterFileTests.hpp"
#include "NodeIDTests.hpp"
#include "NodeIDAllocatorTests.hpp"
#include "RecordTests.hpp"
#include "SecondaryFileTests.hpp"
#include "SiblingNodesRecordGroupTests.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/linkoptions.hpp"
#include <Ishiko/TestFramework.hpp>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("DiplodocusEmbeddedDocumentDBStorageEngine Library Tests");

    theTestHarness.context().setDataDirectory("../../data");
    theTestHarness.context().setOutputDirectory("../../output");
    theTestHarness.context().setReferenceDirectory("../../reference");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<NodeIDTests>();
    theTests.append<NodeIDAllocatorTests>();
    theTests.append<RecordTests>();
    theTests.append<SiblingNodesRecordGroupTests>();
    theTests.append<MasterFileTests>();
    theTests.append<SecondaryFileTests>();

    return theTestHarness.run();
}

/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "MasterFileTests.hpp"
#include "NodeIDTests.hpp"
#include "NodeIDAllocatorTests.hpp"
#include "RecordFilesSetTests.hpp"
#include "RecordRepositoryReaderTests.hpp"
#include "RecordRepositoryWriterTests.hpp"
#include "RecordTests.hpp"
#include "SecondaryFileTests.hpp"
#include "SiblingNodesRecordGroupCacheTests.hpp"
#include "SiblingNodesRecordGroupTests.hpp"
#include "StorageEngineTests.hpp"
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
    theTests.append<RecordRepositoryReaderTests>();
    theTests.append<RecordRepositoryWriterTests>();
    theTests.append<NodeIDTests>();
    theTests.append<NodeIDAllocatorTests>();
    theTests.append<RecordTests>();
    theTests.append<SiblingNodesRecordGroupTests>();
    theTests.append<SiblingNodesRecordGroupCacheTests>();
    theTests.append<MasterFileTests>();
    theTests.append<SecondaryFileTests>();
    theTests.append<RecordFilesSetTests>();
    theTests.append<StorageEngineTests>();

    return theTestHarness.run();
}

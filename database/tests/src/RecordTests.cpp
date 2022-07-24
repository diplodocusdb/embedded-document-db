/*
    Copyright (c) 2019-2022 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "RecordTests.h"
#include "DiplodocusDB/EmbeddedDocumentDB/Record.h"
#include "DiplodocusDB/PhysicalStorage/PageRepository/PageFileRepository.h"

using namespace Ishiko;

RecordTests::RecordTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Record tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructionTest1);
    append<HeapAllocationErrorsTest>("read (eMasterFileMetadata) test 1", ReadMasterFileMetadataTest1);
    append<HeapAllocationErrorsTest>("read (eDataStart) test 1", ReadDataStartTest1);
    append<HeapAllocationErrorsTest>("read (eDataEnd) test 1", ReadDataEndTest1);
    append<HeapAllocationErrorsTest>("read (eNodeStart) test 1", ReadNodeStartTest1);
    append<HeapAllocationErrorsTest>("read (eNodeEnd) test 1", ReadNodeEndTest1);
    append<HeapAllocationErrorsTest>("read (eParentNodeID) test 1", ReadParentNodeIDTest1);
    append<HeapAllocationErrorsTest>("read (eNodeName) test 1", ReadNodeNameTest1);
    append<HeapAllocationErrorsTest>("read (eNodeName) test 2", ReadNodeNameTest2);
    append<HeapAllocationErrorsTest>("read (eNodeID) test 1", ReadNodeIDTest1);
    append<HeapAllocationErrorsTest>("read (eNodeID) test 2", ReadNodeIDTest2);
    append<HeapAllocationErrorsTest>("read (ePersistentNodeID) test 1", ReadPersistentNodeIDTest1);
    append<HeapAllocationErrorsTest>("read (eInlineValue, eBinary) test 1", ReadInlineValueBinaryTest1);
    append<HeapAllocationErrorsTest>("read (eInlineValue, eBoolean) test 1", ReadInlineValueBooleanTest1);
    append<HeapAllocationErrorsTest>("read (eInlineValue, eUTF8String) test 1", ReadInlineValueUTF8StringTest1);
    append<HeapAllocationErrorsTest>("write (eMasterFileMetadata) test 1", WriteMasterFileMetadataTest1);
    append<HeapAllocationErrorsTest>("write (eDataStart) test 1", WriteDataStartTest1);
    append<HeapAllocationErrorsTest>("write (eDataEnd) test 1", WriteDataEndTest1);
    append<HeapAllocationErrorsTest>("write (eNodeStart) test 1", WriteNodeStartTest1);
    append<HeapAllocationErrorsTest>("write (eNodeEnd) test 1", WriteNodeEndTest1);
    append<HeapAllocationErrorsTest>("write (eParentNodeID) test 1", WriteParentNodeIDTest1);
    append<HeapAllocationErrorsTest>("write (eNodeName) test 1", WriteNodeNameTest1);
    append<HeapAllocationErrorsTest>("write (eNodeName) test 2", WriteNodeNameTest2);
    append<HeapAllocationErrorsTest>("write (eNodeID) test 1", WriteNodeIDTest1);
    append<HeapAllocationErrorsTest>("write (eNodeID) test 2", WriteNodeIDTest2);
    append<HeapAllocationErrorsTest>("write (ePersistentNodeID) test 1", WritePersistentNodeIDTest1);
    append<HeapAllocationErrorsTest>("write (eInlineValue, eBinary) test 1", WriteInlineValueBinaryTest1);
    append<HeapAllocationErrorsTest>("write (eInlineValue, eBoolean) test 1", WriteInlineValueBooleanTest1);
    append<HeapAllocationErrorsTest>("write (eInlineValue, eUTF8String) test 1", WriteInlineValueUTF8StringTest1);
}

void RecordTests::ConstructionTest1(Test& test)
{
    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);

    ISHIKO_TEST_PASS();
}

void RecordTests::ReadMasterFileMetadataTest1(Test& test)
{
    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.open(test.context().getDataPath("RecordTests_ReadMasterFileMetadataTest1.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHTF_FAIL_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eMasterFileMetadata);
    ISHIKO_TEST_PASS();
}

void RecordTests::ReadDataStartTest1(Test& test)
{
    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.open(test.context().getDataPath("RecordTests_ReadDataStartTest1.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(record.type(), DiplodocusDB::Record::ERecordType::eDataStart);
    ISHIKO_TEST_PASS();
}

void RecordTests::ReadDataEndTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory()
        / "RecordTests_ReadDataEndTest1.dpdb");

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHTF_FAIL_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eDataEnd);
    ISHIKO_TEST_PASS();
}

void RecordTests::ReadNodeStartTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory()
        / "RecordTests_ReadNodeStartTest1.dpdb");

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHTF_FAIL_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eSiblingNodesStart);
    ISHIKO_TEST_PASS();
}

void RecordTests::ReadNodeEndTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory()
        / "RecordTests_ReadNodeEndTest1.dpdb");

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHTF_FAIL_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eSiblingNodesEnd);
    ISHIKO_TEST_PASS();
}

void RecordTests::ReadParentNodeIDTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory()
        / "RecordTests_ReadParentNodeIDTest1.dpdb");

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eParentNodeID);
    ISHTF_FAIL_UNLESS(record.asNodeID() == DiplodocusDB::NodeID(123));
    ISHIKO_TEST_PASS();
}

void RecordTests::ReadNodeNameTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory()
        / "RecordTests_ReadNodeNameTest1.dpdb");

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eNodeName);
    ISHTF_FAIL_UNLESS(record.asString() == "key1");
    ISHIKO_TEST_PASS();
}

void RecordTests::ReadNodeNameTest2(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory()
        / "RecordTests_ReadNodeNameTest2.dpdb");

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eNodeName);
    std::string key = "key";
    key.resize(300, '1');
    ISHTF_FAIL_UNLESS(record.asString() == key);
    ISHIKO_TEST_PASS();
}

void RecordTests::ReadNodeIDTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory()
        / "RecordTests_ReadNodeIDTest1.dpdb");

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eNodeID);
    ISHTF_FAIL_UNLESS(record.asNodeID() == DiplodocusDB::NodeID(123));
    ISHIKO_TEST_PASS();
}

void RecordTests::ReadNodeIDTest2(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory()
        / "RecordTests_ReadNodeIDTest2.dpdb");

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eNodeID);
    ISHTF_FAIL_UNLESS(record.asNodeID() == DiplodocusDB::NodeID(300));
    ISHIKO_TEST_PASS();
}

void RecordTests::ReadPersistentNodeIDTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory()
        / "RecordTests_ReadPersistentNodeIDTest1.dpdb");

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::ePersistentNodeID);
    ISHTF_FAIL_UNLESS(record.asNodeID() == DiplodocusDB::NodeID(123));
    ISHIKO_TEST_PASS();
}

void RecordTests::ReadInlineValueBinaryTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory()
        / "RecordTests_ReadInlineValueBinaryTest1.dpdb");

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eInlineValue);
    ISHTF_FAIL_UNLESS(record.asValue() == DiplodocusDB::TreeDBValue::Binary("binary"));
    ISHIKO_TEST_PASS();
}

void RecordTests::ReadInlineValueBooleanTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory()
        / "RecordTests_ReadInlineValueBooleanTest1.dpdb");

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eInlineValue);
    ISHTF_FAIL_UNLESS(record.asValue() == DiplodocusDB::TreeDBValue::Boolean(true));
    ISHIKO_TEST_PASS();
}

void RecordTests::ReadInlineValueUTF8StringTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory()
        / "RecordTests_ReadInlineValueUTF8StringTest1.dpdb");

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHIKO_TEST_ABORT_IF(error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eInlineValue);
    ISHTF_FAIL_UNLESS(record.asValue() == DiplodocusDB::TreeDBValue::UTF8String("text"));
    ISHIKO_TEST_PASS();
}

void RecordTests::WriteMasterFileMetadataTest1(Test& test)
{
    const char* testName = "RecordTests_WriteMasterFileMetadataTest1.dpdb";

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record = DiplodocusDB::MasterFileMetadata();
    record.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void RecordTests::WriteDataStartTest1(Test& test)
{
    const char* testName = "RecordTests_WriteDataStartTest1.dpdb";
   
    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eDataStart);
    record.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void RecordTests::WriteDataEndTest1(Test& test)
{
    const char* testName = "RecordTests_WriteDataEndTest1.dpdb";

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eDataEnd);
    record.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void RecordTests::WriteNodeStartTest1(Test& test)
{
    const char* testName = "RecordTests_WriteNodeStartTest1.dpdb";

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eSiblingNodesStart);
    record.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void RecordTests::WriteNodeEndTest1(Test& test)
{
    const char* testName = "RecordTests_WriteNodeEndTest1.dpdb";
   
    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eSiblingNodesEnd);
    record.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void RecordTests::WriteParentNodeIDTest1(Test& test)
{
    const char* testName = "RecordTests_WriteParentNodeIDTest1.dpdb";

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eParentNodeID, DiplodocusDB::NodeID(123));
    record.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void RecordTests::WriteNodeNameTest1(Test& test)
{
    const char* testName = "RecordTests_WriteNodeNameTest1.dpdb";

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record("key1");
    record.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void RecordTests::WriteNodeNameTest2(Test& test)
{
    const char* testName = "RecordTests_WriteNodeNameTest2.dpdb";
    
    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    std::string key = "key";
    key.resize(300, '1');
    DiplodocusDB::Record record(key);
    record.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void RecordTests::WriteNodeIDTest1(Test& test)
{
    const char* testName = "RecordTests_WriteNodeIDTest1.dpdb";

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eNodeID, DiplodocusDB::NodeID(123));
    record.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void RecordTests::WriteNodeIDTest2(Test& test)
{
    const char* testName = "RecordTests_WriteNodeIDTest2.dpdb";

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eNodeID, DiplodocusDB::NodeID(300));
    record.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void RecordTests::WritePersistentNodeIDTest1(Test& test)
{
    const char* testName = "RecordTests_WritePersistentNodeIDTest1.dpdb";

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::ePersistentNodeID, DiplodocusDB::NodeID(123));
    record.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void RecordTests::WriteInlineValueBinaryTest1(Test& test)
{
    const char* testName = "RecordTests_WriteInlineValueBinaryTest1.dpdb";

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInlineValue,
        DiplodocusDB::TreeDBValue::Binary("binary"));
    record.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void RecordTests::WriteInlineValueBooleanTest1(Test& test)
{
    const char* testName = "RecordTests_WriteInlineValueBooleanTest1.dpdb";

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInlineValue,
        DiplodocusDB::TreeDBValue::Boolean(true));
    record.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void RecordTests::WriteInlineValueUTF8StringTest1(Test& test)
{
    const char* testName = "RecordTests_WriteInlineValueUTF8StringTest1.dpdb";

    Error error;

    DiplodocusDB::PageFileRepository repository;
    repository.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_ABORT_IF(error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHIKO_TEST_ABORT_IF(error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInlineValue, 
        DiplodocusDB::TreeDBValue::UTF8String("text"));
    record.write(writer, error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.save(*page, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

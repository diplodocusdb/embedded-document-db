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

    ISHTF_PASS();
}

void RecordTests::ReadMasterFileMetadataTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getTestDataDirectory()
        / "RecordTests_ReadMasterFileMetadataTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHTF_ABORT_IF((bool)error);
    ISHTF_FAIL_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eMasterFileMetadata);
    ISHTF_PASS();
}

void RecordTests::ReadDataStartTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory()
        / "RecordTests_ReadDataStartTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHTF_ABORT_IF((bool)error);
    ISHTF_FAIL_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eDataStart);
    ISHTF_PASS();
}

void RecordTests::ReadDataEndTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory()
        / "RecordTests_ReadDataEndTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHTF_ABORT_IF((bool)error);
    ISHTF_FAIL_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eDataEnd);
    ISHTF_PASS();
}

void RecordTests::ReadNodeStartTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory()
        / "RecordTests_ReadNodeStartTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHTF_ABORT_IF((bool)error);
    ISHTF_FAIL_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eSiblingNodesStart);
    ISHTF_PASS();
}

void RecordTests::ReadNodeEndTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory()
        / "RecordTests_ReadNodeEndTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHTF_ABORT_IF((bool)error);
    ISHTF_FAIL_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eSiblingNodesEnd);
    ISHTF_PASS();
}

void RecordTests::ReadParentNodeIDTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory()
        / "RecordTests_ReadParentNodeIDTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHTF_ABORT_IF((bool)error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eParentNodeID);
    ISHTF_FAIL_UNLESS(record.asNodeID() == DiplodocusDB::NodeID(123));
    ISHTF_PASS();
}

void RecordTests::ReadNodeNameTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory()
        / "RecordTests_ReadNodeNameTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHTF_ABORT_IF((bool)error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eNodeName);
    ISHTF_FAIL_UNLESS(record.asString() == "key1");
    ISHTF_PASS();
}

void RecordTests::ReadNodeNameTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory()
        / "RecordTests_ReadNodeNameTest2.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHTF_ABORT_IF((bool)error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eNodeName);
    std::string key = "key";
    key.resize(300, '1');
    ISHTF_FAIL_UNLESS(record.asString() == key);
    ISHTF_PASS();
}

void RecordTests::ReadNodeIDTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory()
        / "RecordTests_ReadNodeIDTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHTF_ABORT_IF((bool)error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eNodeID);
    ISHTF_FAIL_UNLESS(record.asNodeID() == DiplodocusDB::NodeID(123));
    ISHTF_PASS();
}

void RecordTests::ReadNodeIDTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory()
        / "RecordTests_ReadNodeIDTest2.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHTF_ABORT_IF((bool)error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eNodeID);
    ISHTF_FAIL_UNLESS(record.asNodeID() == DiplodocusDB::NodeID(300));
    ISHTF_PASS();
}

void RecordTests::ReadPersistentNodeIDTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory()
        / "RecordTests_ReadPersistentNodeIDTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHTF_ABORT_IF((bool)error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::ePersistentNodeID);
    ISHTF_FAIL_UNLESS(record.asNodeID() == DiplodocusDB::NodeID(123));
    ISHTF_PASS();
}

void RecordTests::ReadInlineValueBinaryTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory()
        / "RecordTests_ReadInlineValueBinaryTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHTF_ABORT_IF((bool)error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eInlineValue);
    ISHTF_FAIL_UNLESS(record.asValue() == DiplodocusDB::TreeDBValue::Binary("binary"));
    ISHTF_PASS();
}

void RecordTests::ReadInlineValueBooleanTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory()
        / "RecordTests_ReadInlineValueBooleanTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHTF_ABORT_IF((bool)error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eInlineValue);
    ISHTF_FAIL_UNLESS(record.asValue() == DiplodocusDB::TreeDBValue::Boolean(true));
    ISHTF_PASS();
}

void RecordTests::ReadInlineValueUTF8StringTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory()
        / "RecordTests_ReadInlineValueUTF8StringTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.open(inputPath, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryReader reader = repository.read(0, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);
    record.read(reader, error);

    ISHTF_ABORT_IF((bool)error);
    ISHTF_ABORT_UNLESS(record.type() == DiplodocusDB::Record::ERecordType::eInlineValue);
    ISHTF_FAIL_UNLESS(record.asValue() == DiplodocusDB::TreeDBValue::UTF8String("text"));
    ISHTF_PASS();
}

void RecordTests::WriteMasterFileMetadataTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "RecordTests_WriteMasterFileMetadataTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record = DiplodocusDB::MasterFileMetadata();
    record.write(writer, error);

    ISHTF_FAIL_IF((bool)error);

    repository.save(*page, error);

    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "RecordTests_WriteMasterFileMetadataTest1.dpdb");

    ISHTF_PASS();
}

void RecordTests::WriteDataStartTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "RecordTests_WriteDataStartTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eDataStart);
    record.write(writer, error);

    ISHTF_FAIL_IF((bool)error);

    repository.save(*page, error);

    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "RecordTests_WriteDataStartTest1.dpdb");

    ISHTF_PASS();
}

void RecordTests::WriteDataEndTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "RecordTests_WriteDataEndTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eDataEnd);
    record.write(writer, error);

    ISHTF_FAIL_IF((bool)error);

    repository.save(*page, error);

    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "RecordTests_WriteDataEndTest1.dpdb");

    ISHTF_PASS();
}

void RecordTests::WriteNodeStartTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "RecordTests_WriteNodeStartTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eSiblingNodesStart);
    record.write(writer, error);

    ISHTF_FAIL_IF((bool)error);

    repository.save(*page, error);

    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "RecordTests_WriteNodeStartTest1.dpdb");

    ISHTF_PASS();
}

void RecordTests::WriteNodeEndTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "RecordTests_WriteNodeEndTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eSiblingNodesEnd);
    record.write(writer, error);

    ISHTF_FAIL_IF((bool)error);

    repository.save(*page, error);

    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "RecordTests_WriteNodeEndTest1.dpdb");

    ISHTF_PASS();
}

void RecordTests::WriteParentNodeIDTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "RecordTests_WriteParentNodeIDTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eParentNodeID, DiplodocusDB::NodeID(123));
    record.write(writer, error);

    ISHTF_FAIL_IF((bool)error);

    repository.save(*page, error);

    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "RecordTests_WriteParentNodeIDTest1.dpdb");

    ISHTF_PASS();
}

void RecordTests::WriteNodeNameTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "RecordTests_WriteNodeNameTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record("key1");
    record.write(writer, error);

    ISHTF_FAIL_IF((bool)error);

    repository.save(*page, error);

    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "RecordTests_WriteNodeNameTest1.dpdb");

    ISHTF_PASS();
}

void RecordTests::WriteNodeNameTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "RecordTests_WriteNodeNameTest2.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHTF_ABORT_IF((bool)error);

    std::string key = "key";
    key.resize(300, '1');
    DiplodocusDB::Record record(key);
    record.write(writer, error);

    ISHTF_FAIL_IF((bool)error);

    repository.save(*page, error);

    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "RecordTests_WriteNodeNameTest2.dpdb");

    ISHTF_PASS();
}

void RecordTests::WriteNodeIDTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "RecordTests_WriteNodeIDTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eNodeID, DiplodocusDB::NodeID(123));
    record.write(writer, error);

    ISHTF_FAIL_IF((bool)error);

    repository.save(*page, error);

    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "RecordTests_WriteNodeIDTest1.dpdb");

    ISHTF_PASS();
}

void RecordTests::WriteNodeIDTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "RecordTests_WriteNodeIDTest2.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eNodeID, DiplodocusDB::NodeID(300));
    record.write(writer, error);

    ISHTF_FAIL_IF((bool)error);

    repository.save(*page, error);

    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "RecordTests_WriteNodeIDTest2.dpdb");

    ISHTF_PASS();
}

void RecordTests::WritePersistentNodeIDTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "RecordTests_WritePersistentNodeIDTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::ePersistentNodeID, DiplodocusDB::NodeID(123));
    record.write(writer, error);

    ISHTF_FAIL_IF((bool)error);

    repository.save(*page, error);

    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "RecordTests_WritePersistentNodeIDTest1.dpdb");

    ISHTF_PASS();
}

void RecordTests::WriteInlineValueBinaryTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "RecordTests_WriteInlineValueBinaryTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInlineValue,
        DiplodocusDB::TreeDBValue::Binary("binary"));
    record.write(writer, error);

    ISHTF_FAIL_IF((bool)error);

    repository.save(*page, error);

    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "RecordTests_WriteInlineValueBinaryTest1.dpdb");

    ISHTF_PASS();
}

void RecordTests::WriteInlineValueBooleanTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "RecordTests_WriteInlineValueBooleanTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInlineValue,
        DiplodocusDB::TreeDBValue::Boolean(true));
    record.write(writer, error);

    ISHTF_FAIL_IF((bool)error);

    repository.save(*page, error);

    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "RecordTests_WriteInlineValueBooleanTest1.dpdb");

    ISHTF_PASS();
}

void RecordTests::WriteInlineValueUTF8StringTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "RecordTests_WriteInlineValueUTF8StringTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInlineValue, 
        DiplodocusDB::TreeDBValue::UTF8String("text"));
    record.write(writer, error);

    ISHTF_FAIL_IF((bool)error);

    repository.save(*page, error);

    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "RecordTests_WriteInlineValueUTF8StringTest1.dpdb");

    ISHTF_PASS();
}

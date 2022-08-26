/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "RecordRepositoryWriterTests.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/RecordRepositoryWriter.hpp"
#include "DiplodocusDB/EmbeddedDocumentDB/StorageEngine/RecordFile.hpp"
#include <boost/filesystem/operations.hpp>

using namespace DiplodocusDB::EDDBImpl;
using namespace Ishiko;

RecordRepositoryWriterTests::RecordRepositoryWriterTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "RecordRepositoryWriter tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("write test 1", WriteTest1);
    append<HeapAllocationErrorsTest>("write test 2", WriteTest2);
    append<HeapAllocationErrorsTest>("write test 3", WriteTest3);
    append<HeapAllocationErrorsTest>("write test 4", WriteTest4);
    append<HeapAllocationErrorsTest>("write test 5", WriteTest5);
    append<HeapAllocationErrorsTest>("write test 6", WriteTest6);
    append<HeapAllocationErrorsTest>("write test 7", WriteTest7);
    append<HeapAllocationErrorsTest>("write test 8", WriteTest8);
    append<HeapAllocationErrorsTest>("writeLEB128 test 1", WriteLEB128Test1);
    append<HeapAllocationErrorsTest>("writeLEB128 test 2", WriteLEB128Test2);
    append<HeapAllocationErrorsTest>("writeLEB128 test 3", WriteLEB128Test3);
    append<HeapAllocationErrorsTest>("writeLEB128 test 4", WriteLEB128Test4);
    append<HeapAllocationErrorsTest>("writeLEB128 test 5", WriteLEB128Test5);
}

void RecordRepositoryWriterTests::ConstructorTest1(Test& test)
{
    Error error;

    RecordFile repository;
    repository.open(test.context().getDataPath("RecordRepositoryWriter_ConstructorTest1.dpdb"), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    RecordPage page = repository.page(0, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    RecordRepositoryWriter writer{repository, page, 0};

    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().page(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().offset(), 0);
    ISHIKO_TEST_PASS();
}

void RecordRepositoryWriterTests::WriteTest1(Test& test)
{
    const char* basename = "RecordRepositoryWriter_WriteTest1.dpdb";
    
    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);
    
    RecordPage page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);
        
    RecordRepositoryWriter writer{repository, page, 0};
    writer.write("value1", 6, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().page(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().offset(), 6);
    
    writer.save(error);
    
    ISHIKO_TEST_FAIL_IF(error);

    repository.close();
    
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordRepositoryWriterTests::WriteTest2(Test& test)
{
    const char* basename = "RecordRepositoryWriterTests_WriteTest2.dpdb";
    
    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);
    
    RecordRepositoryWriter writer{repository, page, 0};
    writer.write("value1", 6, error);

    ISHIKO_TEST_FAIL_IF(error);
    
    writer.write("value2", 6, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().page(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().offset(), 12);
        
    writer.save(error);
        
    ISHIKO_TEST_FAIL_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordRepositoryWriterTests::WriteTest3(Test& test)
{
    const char* basename = "RecordRepositoryWriterTests_WriteTest3.dpdb";
    boost::filesystem::path outputPath = test.context().getOutputPath(basename);
    
    boost::filesystem::copy_file(test.context().getDataPath(basename), outputPath,
        boost::filesystem::copy_option::overwrite_if_exists);

    Error error;

    RecordFile repository;
    repository.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.page(0,error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordRepositoryWriter writer{repository, page, 0};
    writer.write("value0", 6, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().page(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().offset(), 6);
    
    writer.save(error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordRepositoryWriterTests::WriteTest4(Test& test)
{
    const char* basename = "PageRepositoryWriterWriteTest4.dpdb";
    boost::filesystem::path outputPath = test.context().getOutputPath(basename);

    boost::filesystem::copy_file(test.context().getDataPath("PageRepositoryWriterWriteTest4.dpdb"), outputPath,
        boost::filesystem::copy_option::overwrite_if_exists);

    Error error;

    RecordFile repository;
    repository.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.page(0, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    RecordRepositoryWriter writer{repository, page, 6};
    writer.write("value2", 6, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().page(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().offset(), 12);

    writer.save(error);
    
    ISHIKO_TEST_FAIL_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordRepositoryWriterTests::WriteTest5(Test& test)
{
    const char* basename = "PageRepositoryWriterWriteTest5.dpdb";
    boost::filesystem::path outputPath = test.context().getOutputPath(basename);

    boost::filesystem::copy_file(test.context().getDataPath("PageRepositoryWriterWriteTest5.dpdb"), outputPath,
        boost::filesystem::copy_option::overwrite_if_exists);

    Error error;

    RecordFile repository;
    repository.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.page(0, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    RecordRepositoryWriter writer{repository, page, 0};
    for (size_t i = 0; i < 409; ++i)
    {
        writer.write("0123456789", 10, error);
    }

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().page(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().offset(), 10);

    writer.save(error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordRepositoryWriterTests::WriteTest6(Test& test)
{
    const char* basename = "PageRepositoryWriterWriteTest6.dpdb";
    boost::filesystem::path outputPath = test.context().getOutputPath(basename);

    boost::filesystem::copy_file(test.context().getDataPath("PageRepositoryWriterWriteTest6.dpdb"), outputPath,
        boost::filesystem::copy_option::overwrite_if_exists);

    Error error;

    RecordFile repository;
    repository.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.page(0, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    RecordRepositoryWriter writer{repository, page, 0};
    for (size_t i = 0; i < 409; ++i)
    {
        writer.write("01234567890123456789", 20, error);
    }

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().page(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().offset(), 20);

    writer.save(error);
    
    ISHIKO_TEST_FAIL_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordRepositoryWriterTests::WriteTest7(Test& test)
{
    const char* basename = "PageRepositoryWriterWriteTest7.dpdb";
    boost::filesystem::path outputPath = test.context().getOutputPath(basename);

    boost::filesystem::copy_file(test.context().getDataPath("PageRepositoryWriterWriteTest7.dpdb"), outputPath,
        boost::filesystem::copy_option::overwrite_if_exists);

    Error error;

    RecordFile repository;
    repository.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.page(0, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordRepositoryWriter writer{repository, page, 0};
    for (size_t i = 0; i < 407; ++i)
    {
        writer.write("0123456789", 10, error);
    }
    writer.write("01234567890", 11, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().page(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().offset(), 1);

    writer.save(error);
    
    ISHIKO_TEST_FAIL_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordRepositoryWriterTests::WriteTest8(Test& test)
{
    const char* basename = "PageRepositoryWriterWriteTest8.dpdb";
    boost::filesystem::path outputPath = test.context().getOutputPath(basename);

    boost::filesystem::copy_file(test.context().getDataPath("PageRepositoryWriterWriteTest8.dpdb"), outputPath,
        boost::filesystem::copy_option::overwrite_if_exists);

    Error error;

    RecordFile repository;
    repository.open(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.page(0, error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordRepositoryWriter writer{repository, page, 0};
    for (size_t i = 0; i < 409; ++i)
    {
        writer.write("0123456789", 10, error);
    }

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().page(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().offset(), 10);

    writer.save(error);
    
    ISHIKO_TEST_FAIL_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordRepositoryWriterTests::WriteLEB128Test1(Test& test)
{
    const char* basename = "PageRepositoryWriterWriteLEB128Test1.dpdb";
   
    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordRepositoryWriter writer{repository, page, 0};
    writer.writeLEB128(0, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().page(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().offset(), 1);

    writer.save(error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordRepositoryWriterTests::WriteLEB128Test2(Test& test)
{
    const char* basename = "PageRepositoryWriterWriteLEB128Test2.dpdb";
    
    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordRepositoryWriter writer{repository, page, 0};
    writer.writeLEB128(1, error);

    ISHIKO_TEST_FAIL_IF((bool)error);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().page(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().offset(), 1);

    writer.save(error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordRepositoryWriterTests::WriteLEB128Test3(Test& test)
{
    const char* basename = "PageRepositoryWriterWriteLEB128Test3.dpdb";
   
    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordRepositoryWriter writer{repository, page, 0};
    writer.writeLEB128(127, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().page(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().offset(), 1);

    writer.save(error);

    ISHIKO_TEST_FAIL_IF((bool)error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordRepositoryWriterTests::WriteLEB128Test4(Test& test)
{
    const char* basename = "PageRepositoryWriterWriteLEB128Test4.dpdb";
    
    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordRepositoryWriter writer{repository, page, 0};
    writer.writeLEB128(128, error);

    ISHIKO_TEST_FAIL_IF((bool)error);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().page(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().offset(), 2);

    writer.save(error);

    ISHIKO_TEST_FAIL_IF((bool)error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

void RecordRepositoryWriterTests::WriteLEB128Test5(Test& test)
{
    const char* basename = "PageRepositoryWriterWriteLEB128Test5.dpdb";
   
    Error error;

    RecordFile repository;
    repository.create(test.context().getOutputPath(basename), error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordPage page = repository.allocatePage(error);

    ISHIKO_TEST_ABORT_IF(error);

    RecordRepositoryWriter writer{repository, page, 0};
    writer.writeLEB128(16384, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().page(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(writer.currentPosition().offset(), 3);

    writer.save(error);

    ISHIKO_TEST_FAIL_IF(error);

    repository.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(basename);
    ISHIKO_TEST_PASS();
}

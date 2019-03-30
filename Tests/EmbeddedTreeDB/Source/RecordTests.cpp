/*
    Copyright (c) 2019 Xavier Leclercq

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
#include "Record.h"
#include "DiplodocusDB/PhysicalStorage/PageRepository/PageFileRepository.h"

using namespace Ishiko::Tests;

RecordTests::RecordTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Record tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", ConstructionTest1);
    append<FileComparisonTest>("write test 1", WriteTest1);
}

void RecordTests::ConstructionTest1(Test& test)
{
    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eInvalid);

    ISHTF_PASS();
}

void RecordTests::WriteTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "RecordTests_WriteTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::PageFileRepository repository;
    repository.create(outputPath, error);

    ISHTF_ABORT_IF((bool)error);

    std::shared_ptr<DiplodocusDB::Page> page = repository.allocatePage(error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::PageRepositoryWriter writer = repository.insert(page, 0, error);

    ISHTF_ABORT_IF((bool)error);

    DiplodocusDB::Record record(DiplodocusDB::Record::ERecordType::eMasterFileMetadata);
    record.write(writer, error);

    ISHTF_FAIL_IF((bool)error);

    page->save(error);

    ISHTF_FAIL_IF((bool)error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "RecordTests_WriteTest1.dpdb");

    ISHTF_PASS();
}

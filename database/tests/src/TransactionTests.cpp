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

#include "TransactionTests.h"
#include "DiplodocusDB/TreeDB/EmbeddedTreeDB/EmbeddedTreeDB.h"

using namespace Ishiko::Tests;

TransactionTests::TransactionTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Transaction tests", environment)
{
    append<FileComparisonTest>("createTransaction test 1", CreateTransactionTest1);
    append<FileComparisonTest>("commitTransaction test 1", CommitTransactionTest1);
    append<FileComparisonTest>("appendChildNode test 1", AppendChildNodeTest1);
    append<FileComparisonTest>("appendChildNode test 2", AppendChildNodeTest2);
    append<FileComparisonTest>("rollbackTransaction test 1", RollbackTransactionTest1);
}

void TransactionTests::CreateTransactionTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "TransactionTests_CreateTransactionTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::TreeDBTransaction transaction = db.createTransaction(error);

    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "TransactionTests_CreateTransactionTest1.dpdb");

    ISHTF_PASS();
}

void TransactionTests::CommitTransactionTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "TransactionTests_CommitTransactionTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::TreeDBTransaction transaction = db.createTransaction(error);

    ISHTF_FAIL_IF((bool)error);

    db.commitTransaction(transaction, error);

    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "TransactionTests_CommitTransactionTest1.dpdb");

    ISHTF_PASS();
}

void TransactionTests::AppendChildNodeTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "TransactionTests_AppendChildNodeTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::TreeDBTransaction transaction = db.createTransaction(error);

    ISHTF_FAIL_IF((bool)error);

    db.appendChildNode(transaction, db.root(), "key1", error);

    ISHTF_FAIL_IF((bool)error);

    db.commitTransaction(transaction, error);

    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "TransactionTests_AppendChildNodeTest1.dpdb");

    ISHTF_PASS();
}

void TransactionTests::AppendChildNodeTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "TransactionTests_AppendChildNodeTest2.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::TreeDBTransaction transaction = db.createTransaction(error);

    ISHTF_FAIL_IF((bool)error);

    db.appendChildNode(transaction, db.root(), "key1", error);

    ISHTF_FAIL_IF((bool)error);

    db.appendChildNode(transaction, db.root(), "key2", error);

    ISHTF_FAIL_IF((bool)error);

    db.commitTransaction(transaction, error);

    ISHTF_FAIL_IF((bool)error);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "TransactionTests_AppendChildNodeTest2.dpdb");

    ISHTF_PASS();
}

void TransactionTests::RollbackTransactionTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory()
        / "TransactionTests_RollbackTransactionTest1.dpdb");

    Ishiko::Error error(0);

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(outputPath, error);

    ISHTF_FAIL_IF((bool)error);

    DiplodocusDB::TreeDBTransaction transaction = db.createTransaction(error);

    ISHTF_FAIL_IF((bool)error);

    db.rollbackTransaction(transaction);

    db.close();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "TransactionTests_RollbackTransactionTest1.dpdb");

    ISHTF_PASS();
}

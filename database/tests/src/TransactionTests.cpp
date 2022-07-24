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

#include "TransactionTests.h"
#include "DiplodocusDB/EmbeddedDocumentDB/EmbeddedTreeDB.h"

using namespace Ishiko;

TransactionTests::TransactionTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Transaction tests", context)
{
    append<HeapAllocationErrorsTest>("createTransaction test 1", CreateTransactionTest1);
    append<HeapAllocationErrorsTest>("commitTransaction test 1", CommitTransactionTest1);
    append<HeapAllocationErrorsTest>("appendChildNode test 1", AppendChildNodeTest1);
    append<HeapAllocationErrorsTest>("appendChildNode test 2", AppendChildNodeTest2);
    append<HeapAllocationErrorsTest>("rollbackTransaction test 1", RollbackTransactionTest1);
}

void TransactionTests::CreateTransactionTest1(Test& test)
{
    const char* testName = "TransactionTests_CreateTransactionTest1.dpdb";
   
    Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_FAIL_IF(error);

    DiplodocusDB::TreeDBTransaction transaction = db.createTransaction(error);

    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void TransactionTests::CommitTransactionTest1(Test& test)
{
    const char* testName = "TransactionTests_CommitTransactionTest1.dpdb";
   
    Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_FAIL_IF(error);

    DiplodocusDB::TreeDBTransaction transaction = db.createTransaction(error);

    ISHIKO_TEST_FAIL_IF(error);

    db.commitTransaction(transaction, error);

    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void TransactionTests::AppendChildNodeTest1(Test& test)
{
    const char* testName = "TransactionTests_AppendChildNodeTest1.dpdb";
   
    Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_FAIL_IF(error);

    DiplodocusDB::TreeDBTransaction transaction = db.createTransaction(error);

    ISHIKO_TEST_FAIL_IF(error);

    db.appendChildNode(transaction, db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);

    db.commitTransaction(transaction, error);

    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void TransactionTests::AppendChildNodeTest2(Test& test)
{
    const char* testName = "TransactionTests_AppendChildNodeTest2.dpdb";

    Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_FAIL_IF(error);

    DiplodocusDB::TreeDBTransaction transaction = db.createTransaction(error);

    ISHIKO_TEST_FAIL_IF(error);

    db.appendChildNode(transaction, db.root(), "key1", error);

    ISHIKO_TEST_FAIL_IF(error);

    db.appendChildNode(transaction, db.root(), "key2", error);

    ISHIKO_TEST_FAIL_IF(error);

    db.commitTransaction(transaction, error);

    ISHIKO_TEST_FAIL_IF(error);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

void TransactionTests::RollbackTransactionTest1(Test& test)
{
    const char* testName = "TransactionTests_RollbackTransactionTest1.dpdb";

    Error error;

    DiplodocusDB::EmbeddedTreeDB db;
    db.create(test.context().getOutputPath(testName), error);

    ISHIKO_TEST_FAIL_IF(error);

    DiplodocusDB::TreeDBTransaction transaction = db.createTransaction(error);

    ISHIKO_TEST_FAIL_IF(error);

    db.rollbackTransaction(transaction);

    db.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(testName);
    ISHIKO_TEST_PASS();
}

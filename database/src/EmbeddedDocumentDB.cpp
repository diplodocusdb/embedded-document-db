/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#include "EmbeddedDocumentDB.hpp"
#include "EmbeddedDocumentDBImpl.hpp"

namespace DiplodocusDB
{

EmbeddedDocumentDB::EmbeddedDocumentDB()
    : m_impl(std::make_shared<EmbeddedDocumentDBImpl>())
{
}

void EmbeddedDocumentDB::create(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_impl->create(path, error);
}

void EmbeddedDocumentDB::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_impl->open(path, error);
}

void EmbeddedDocumentDB::close()
{
    m_impl->close();
}

TreeDBNode& EmbeddedDocumentDB::root()
{
    return m_impl->root();
}

Value EmbeddedDocumentDB::value(TreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->value(node, error);
}

Value EmbeddedDocumentDB::value(TreeDBNode& node, const DataType& type, Ishiko::Error& error)
{
    return m_impl->value(node, type, error);
}

Value EmbeddedDocumentDB::childValue(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->childValue(parent, name, error);
}

Value EmbeddedDocumentDB::childValue(TreeDBNode& parent, const std::string& name, const DataType& type,
    Ishiko::Error& error)
{
    return m_impl->childValue(parent, name, type, error);
}

TreeDBNode EmbeddedDocumentDB::parent(TreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->parent(node, error);
}

std::vector<TreeDBNode> EmbeddedDocumentDB::childNodes(TreeDBNode& parent, Ishiko::Error& error)
{
    return m_impl->childNodes(parent, error);
}

TreeDBNode EmbeddedDocumentDB::child(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->child(parent, name, error);
}

TreeDBNode EmbeddedDocumentDB::previousSibling(TreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->previousSibling(node, error);
}

TreeDBNode EmbeddedDocumentDB::previousSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    return m_impl->previousSibling(node, name, error);
}

TreeDBNode EmbeddedDocumentDB::nextSibling(TreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->nextSibling(node, error);
}

TreeDBNode EmbeddedDocumentDB::nextSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    return m_impl->nextSibling(node, name, error);
}

void EmbeddedDocumentDB::traverse(TreeDBNode& node, ETreeTraversalOrder order,
    void (*callback)(TreeDB& db, TreeDBNode& node), void* callbackData)
{
    return m_impl->traverse(node, order, callback, callbackData);
}

TreeDBTransaction EmbeddedDocumentDB::createTransaction(Ishiko::Error& error)
{
    return m_impl->createTransaction(error);
}

void EmbeddedDocumentDB::commitTransaction(TreeDBTransaction& transaction, Ishiko::Error& error)
{
    m_impl->commitTransaction(transaction, error);
}

void EmbeddedDocumentDB::rollbackTransaction(TreeDBTransaction& transaction)
{
    m_impl->rollbackTransaction(transaction);
}

void EmbeddedDocumentDB::setValue(TreeDBNode& node, const Value& value, Ishiko::Error& error)
{
    m_impl->setValue(node, value, error);
}

TreeDBNode EmbeddedDocumentDB::insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
    Ishiko::Error& error)
{
    return m_impl->insertChildNode(parent, index, name, error);
}

TreeDBNode EmbeddedDocumentDB::insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
    const Value& value, Ishiko::Error& error)
{
    return m_impl->insertChildNode(parent, index, name, value, error);
}

TreeDBNode EmbeddedDocumentDB::insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
    Ishiko::Error& error)
{
    return m_impl->insertChildNodeBefore(parent, nextChild, name, error);
}

TreeDBNode EmbeddedDocumentDB::insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
    const Value& value, Ishiko::Error& error)
{
    return m_impl->insertChildNodeBefore(parent, nextChild, name, value, error);
}

TreeDBNode EmbeddedDocumentDB::insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
    Ishiko::Error& error)
{
    return m_impl->insertChildNodeAfter(parent, previousChild, name, error);
}

TreeDBNode EmbeddedDocumentDB::insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
    const Value& value, Ishiko::Error& error)
{
    return m_impl->insertChildNodeAfter(parent, previousChild, name, value, error);
}

TreeDBNode EmbeddedDocumentDB::appendChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->appendChildNode(parent, name, error);
}

TreeDBNode EmbeddedDocumentDB::appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent, const std::string& name,
    Ishiko::Error& error)
{
    return m_impl->appendChildNode(transaction, parent, name, error);
}

TreeDBNode EmbeddedDocumentDB::appendChildNode(TreeDBNode& parent, const std::string& name, const Value& value,
    Ishiko::Error& error)
{
    return m_impl->appendChildNode(parent, name, value, error);
}

TreeDBNode EmbeddedDocumentDB::appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent, const std::string& name,
    const Value& value, Ishiko::Error& error)
{
    return m_impl->appendChildNode(transaction, parent, name, value, error);
}

TreeDBNode EmbeddedDocumentDB::setChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->setChildNode(parent, name, error);
}

TreeDBNode EmbeddedDocumentDB::setChildNode(TreeDBNode& parent, const std::string& name, const Value& value,
    Ishiko::Error& error)
{
    return m_impl->setChildNode(parent, name, value, error);
}

size_t EmbeddedDocumentDB::removeChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->removeChildNode(parent, name, error);
}

size_t EmbeddedDocumentDB::removeAllChildNodes(TreeDBNode& parent, Ishiko::Error& error)
{
    return m_impl->removeAllChildNodes(parent, error);
}

}

/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#include "XMLTreeDB.hpp"
#include "XMLTreeDBImpl.hpp"

namespace DiplodocusDB
{

XMLTreeDB::XMLTreeDB()
    : m_impl(std::make_shared<XMLTreeDBImpl>())
{
}

XMLTreeDB::~XMLTreeDB()
{
    close();
}

void XMLTreeDB::create(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_impl->create(path, error);
}

void XMLTreeDB::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_impl->open(path, error);
}

void XMLTreeDB::close()
{
    m_impl->close();
}

TreeDBNode& XMLTreeDB::root()
{
    return m_impl->root();
}

Value XMLTreeDB::value(TreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->value(node, error);
}

Value XMLTreeDB::value(TreeDBNode& node, const DataType& type, Ishiko::Error& error)
{
    return m_impl->value(node, type, error);
}

Value XMLTreeDB::childValue(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->childValue(parent, name, error);
}

Value XMLTreeDB::childValue(TreeDBNode& parent, const std::string& name, const DataType& type, Ishiko::Error& error)
{
    return m_impl->childValue(parent, name, type, error);
}

TreeDBNode XMLTreeDB::parent(TreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->parent(node, error);
}

std::vector<TreeDBNode> XMLTreeDB::childNodes(TreeDBNode& parent, Ishiko::Error& error)
{
    return m_impl->childNodes(parent, error);
}

TreeDBNode XMLTreeDB::child(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->child(parent, name, error);
}

TreeDBNode XMLTreeDB::previousSibling(TreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->previousSibling(node, error);
}

TreeDBNode XMLTreeDB::previousSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    return m_impl->previousSibling(node, name, error);
}

TreeDBNode XMLTreeDB::nextSibling(TreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->nextSibling(node, error);
}

TreeDBNode XMLTreeDB::nextSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    return m_impl->nextSibling(node, name, error);
}

void XMLTreeDB::setValue(TreeDBNode& node, const Value& value, Ishiko::Error& error)
{
    m_impl->setValue(node, value, error);
}

TreeDBNode XMLTreeDB::insertChildNode(TreeDBNode& parent, size_t index, const std::string& name, Ishiko::Error& error)
{
    return m_impl->insertChildNode(parent, index, name, error);
}

TreeDBNode XMLTreeDB::insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
    const Value& value, Ishiko::Error& error)
{
    return m_impl->insertChildNode(parent, index, name, value, error);
}

TreeDBNode XMLTreeDB::insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
    Ishiko::Error& error)
{
    return m_impl->insertChildNodeBefore(parent, nextChild, name, error);
}

TreeDBNode XMLTreeDB::insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
    const Value& value, Ishiko::Error& error)
{
    return m_impl->insertChildNodeBefore(parent, nextChild, name, value, error);
}

TreeDBNode XMLTreeDB::insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
    Ishiko::Error& error)
{
    return m_impl->insertChildNodeAfter(parent, previousChild, name, error);
}

TreeDBNode XMLTreeDB::insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
    const Value& value, Ishiko::Error& error)
{
    return m_impl->insertChildNodeAfter(parent, previousChild, name, value, error);
}

TreeDBNode XMLTreeDB::appendChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->appendChildNode(parent, name, error);
}

TreeDBNode XMLTreeDB::appendChildNode(TreeDBNode& parent, const std::string& name, const Value& value,
    Ishiko::Error& error)
{
    return m_impl->appendChildNode(parent, name, value, error);
}

TreeDBNode XMLTreeDB::setChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->setChildNode(parent, name, error);
}

TreeDBNode XMLTreeDB::setChildNode(TreeDBNode& parent, const std::string& name, const Value& value,
    Ishiko::Error& error)
{
    return m_impl->setChildNode(parent, name, value, error);
}

size_t XMLTreeDB::removeChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->removeChildNode(parent, name, error);
}

size_t XMLTreeDB::removeAllChildNodes(TreeDBNode& parent, Ishiko::Error& error)
{
    return m_impl->removeAllChildNodes(parent, error);
}

}

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

XMLTreeDBNode& XMLTreeDB::root()
{
    return m_impl->root();
}

Value XMLTreeDB::value(XMLTreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->value(node, error);
}

Value XMLTreeDB::value(XMLTreeDBNode& node, const DataType& type, Ishiko::Error& error)
{
    return m_impl->value(node, type, error);
}

Value XMLTreeDB::childValue(XMLTreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->childValue(parent, name, error);
}

Value XMLTreeDB::childValue(XMLTreeDBNode& parent, const std::string& name, const DataType& type, Ishiko::Error& error)
{
    return m_impl->childValue(parent, name, type, error);
}

XMLTreeDBNode XMLTreeDB::parent(XMLTreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->parent(node, error);
}

std::vector<XMLTreeDBNode> XMLTreeDB::childNodes(XMLTreeDBNode& parent, Ishiko::Error& error)
{
    return m_impl->childNodes(parent, error);
}

XMLTreeDBNode XMLTreeDB::child(XMLTreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->child(parent, name, error);
}

XMLTreeDBNode XMLTreeDB::previousSibling(XMLTreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->previousSibling(node, error);
}

XMLTreeDBNode XMLTreeDB::previousSibling(XMLTreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    return m_impl->previousSibling(node, name, error);
}

XMLTreeDBNode XMLTreeDB::nextSibling(XMLTreeDBNode& node, Ishiko::Error& error)
{
    return m_impl->nextSibling(node, error);
}

XMLTreeDBNode XMLTreeDB::nextSibling(XMLTreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    return m_impl->nextSibling(node, name, error);
}

void XMLTreeDB::setValue(XMLTreeDBNode& node, const Value& value, Ishiko::Error& error)
{
    m_impl->setValue(node, value, error);
}

XMLTreeDBNode XMLTreeDB::insertChildNode(XMLTreeDBNode& parent, size_t index, const std::string& name,
    Ishiko::Error& error)
{
    return m_impl->insertChildNode(parent, index, name, error);
}

XMLTreeDBNode XMLTreeDB::insertChildNode(XMLTreeDBNode& parent, size_t index, const std::string& name,
    const Value& value, Ishiko::Error& error)
{
    return m_impl->insertChildNode(parent, index, name, value, error);
}

XMLTreeDBNode XMLTreeDB::appendChildNode(XMLTreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->appendChildNode(parent, name, error);
}

XMLTreeDBNode XMLTreeDB::appendChildNode(XMLTreeDBNode& parent, const std::string& name, const Value& value,
    Ishiko::Error& error)
{
    return m_impl->appendChildNode(parent, name, value, error);
}

XMLTreeDBNode XMLTreeDB::setChildNode(XMLTreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->setChildNode(parent, name, error);
}

XMLTreeDBNode XMLTreeDB::setChildNode(XMLTreeDBNode& parent, const std::string& name, const Value& value,
    Ishiko::Error& error)
{
    return m_impl->setChildNode(parent, name, value, error);
}

size_t XMLTreeDB::removeChildNode(XMLTreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    return m_impl->removeChildNode(parent, name, error);
}

size_t XMLTreeDB::removeAllChildNodes(XMLTreeDBNode& parent, Ishiko::Error& error)
{
    return m_impl->removeAllChildNodes(parent, error);
}

}

/*
    Copyright (c) 2019 Xavier Leclercq
    Released under the MIT License
    See https://github.com/DiplodocusDB/TreeDB/blob/master/LICENSE.txt
*/

#include "XMLTreeDBImpl.h"
#include "XMLTreeDBNodeImpl.h"
#include "XMLTreeDBTransactionImpl.h"
#include <fstream>

namespace DiplodocusDB
{

static const char* rootElementName = "diplodocusdb-xmltreedb";

void XMLTreeDBImpl::create(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_path = path;
    pugi::xml_node rootNode = m_document.append_child(rootElementName);
    if (rootNode)
    {
        m_root = TreeDBNode(std::make_shared<XMLTreeDBNodeImpl>(nullptr, rootNode));

        std::ofstream file(m_path.string());
        m_document.save(file);
    }
}

void XMLTreeDBImpl::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_path = path;
    m_document.load_file(m_path.string().c_str());
    m_root = TreeDBNode(std::make_shared<XMLTreeDBNodeImpl>(nullptr, m_document.child(rootElementName)));
}

void XMLTreeDBImpl::close()
{
}

TreeDBNode& XMLTreeDBImpl::root()
{
    return m_root;
}

TreeDBValue XMLTreeDBImpl::value(TreeDBNode& node, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    return nodeImpl.value();
}

TreeDBValue XMLTreeDBImpl::value(TreeDBNode& node, const DataType& type, Ishiko::Error& error)
{
    TreeDBValue result;
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    if (nodeImpl.value().type() == type)
    {
        result = nodeImpl.value();
    }
    return result;
}

TreeDBValue XMLTreeDBImpl::childValue(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    TreeDBValue result;
    TreeDBNode childNode = child(parent, name, error);
    if (!error)
    {
        result = value(childNode, error);
    }
    return result;
}

TreeDBValue XMLTreeDBImpl::childValue(TreeDBNode& parent, const std::string& name, const DataType& type,
    Ishiko::Error& error)
{
    TreeDBValue result;
    TreeDBNode childNode = child(parent, name, error);
    if (!error)
    {
        result = value(childNode, type, error);
    }
    return result;
}

TreeDBNode XMLTreeDBImpl::parent(TreeDBNode& node, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    return nodeImpl.parent(error);
}

std::vector<TreeDBNode> XMLTreeDBImpl::childNodes(TreeDBNode& parent, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    return parentNodeImpl.childNodes(error);
}

TreeDBNode XMLTreeDBImpl::child(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    return parentNodeImpl.child(name, error);
}

TreeDBNode XMLTreeDBImpl::previousSibling(TreeDBNode& node, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    return nodeImpl.previousSibling(error);
}

TreeDBNode XMLTreeDBImpl::previousSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    return nodeImpl.previousSibling(name, error);
}

TreeDBNode XMLTreeDBImpl::nextSibling(TreeDBNode& node, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    return nodeImpl.nextSibling(error);
}

TreeDBNode XMLTreeDBImpl::nextSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    return nodeImpl.nextSibling(name, error);
}

void XMLTreeDBImpl::traverse(TreeDBNode& node, ETreeTraversalOrder order,
    void(*callback)(TreeDB& db, TreeDBNode& node), void* callbackData)
{
    // TODO
}

TreeDBTransaction XMLTreeDBImpl::createTransaction(Ishiko::Error& error)
{
    // TODO
    return TreeDBTransaction(std::make_shared<XMLTreeDBTransactionImpl>());
}

void XMLTreeDBImpl::commitTransaction(TreeDBTransaction& transaction, Ishiko::Error& error)
{
    // TODO
}

void XMLTreeDBImpl::rollbackTransaction(TreeDBTransaction& transaction)
{
    // TODO
}

void XMLTreeDBImpl::setValue(TreeDBNode& node, const TreeDBValue& value, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    nodeImpl.value() = value;
    commitNode(nodeImpl, error);
}

TreeDBNode XMLTreeDBImpl::insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
    Ishiko::Error& error)
{
    TreeDBValue value;
    return insertChildNode(parent, index, name, value, error);
}

TreeDBNode XMLTreeDBImpl::insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
    const TreeDBValue& value, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    TreeDBNode result = parentNodeImpl.insertChildNode(index, name, value, error);
    commitNode(parentNodeImpl, error);
    return result;
}

TreeDBNode XMLTreeDBImpl::insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
    Ishiko::Error& error)
{
    TreeDBValue value;
    return insertChildNodeBefore(parent, nextChild, name, value, error);
}

TreeDBNode XMLTreeDBImpl::insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
    const TreeDBValue& value, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    TreeDBNode result = parentNodeImpl.insertChildNodeBefore(nextChild, name, value, error);
    commitNode(parentNodeImpl, error);
    return result;
}

TreeDBNode XMLTreeDBImpl::insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild,
    const std::string& name, Ishiko::Error& error)
{
    TreeDBValue value;
    return insertChildNodeAfter(parent, previousChild, name, value, error);
}

TreeDBNode XMLTreeDBImpl::insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
    const TreeDBValue& value, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    TreeDBNode result = parentNodeImpl.insertChildNodeAfter(previousChild, name, value, error);
    commitNode(parentNodeImpl, error);
    return result;
}

TreeDBNode XMLTreeDBImpl::appendChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    TreeDBValue value;
    return appendChildNode(parent, name, value, error);
}

TreeDBNode XMLTreeDBImpl::appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent, const std::string& name,
    Ishiko::Error& error)
{
    TreeDBValue value;
    return appendChildNode(transaction, parent, name, value, error);
}

TreeDBNode XMLTreeDBImpl::appendChildNode(TreeDBNode& parent, const std::string& name, const TreeDBValue& value,
    Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    TreeDBNode result = parentNodeImpl.appendChildNode(name, value, error);
    commitNode(parentNodeImpl, error);
    return result;
}

TreeDBNode XMLTreeDBImpl::appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent, const std::string& name,
    const TreeDBValue& value, Ishiko::Error& error)
{
    // TODO : make this a transaction!!!
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    TreeDBNode result = parentNodeImpl.appendChildNode(name, value, error);
    commitNode(parentNodeImpl, error);
    return result;
}

TreeDBNode XMLTreeDBImpl::setChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    TreeDBValue value;
    return setChildNode(parent, name, value, error);
}

TreeDBNode XMLTreeDBImpl::setChildNode(TreeDBNode& parent, const std::string& name, const TreeDBValue& value,
    Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    TreeDBNode result = parentNodeImpl.setChildNode(name, value, error);
    commitNode(parentNodeImpl, error);
    return result;
}

size_t XMLTreeDBImpl::removeChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    size_t result = parentNodeImpl.removeChildNode(name, error);
    commitNode(parentNodeImpl, error);
    return result;
}

size_t XMLTreeDBImpl::removeAllChildNodes(TreeDBNode& parent, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    size_t result = parentNodeImpl.removeAllChildNodes(error);
    commitNode(parentNodeImpl, error);
    return result;
}

void XMLTreeDBImpl::commitNode(XMLTreeDBNodeImpl& node, Ishiko::Error& error)
{
    node.updateValue();
    std::ofstream file(m_path.string());
    m_document.save(file, "  ");
}

}

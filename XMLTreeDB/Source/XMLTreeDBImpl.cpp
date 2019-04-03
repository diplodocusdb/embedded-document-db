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

TreeDBNode XMLTreeDBImpl::parent(TreeDBNode& node, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    return nodeImpl.parent(error);
}

std::vector<TreeDBNode> XMLTreeDBImpl::childNodes(TreeDBNode& node, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    return nodeImpl.childNodes(error);
}

TreeDBNode XMLTreeDBImpl::child(TreeDBNode& node, const std::string& name, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& nodeImpl = static_cast<XMLTreeDBNodeImpl&>(*node.impl());
    return nodeImpl.child(name, error);
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

TreeDBTransaction XMLTreeDBImpl::createTransaction()
{
    // TODO
    return TreeDBTransaction(std::make_shared<XMLTreeDBTransactionImpl>());
}

TreeDBTransaction XMLTreeDBImpl::commitTransaction(TreeDBTransaction& transaction)
{
    // TODO
    return TreeDBTransaction(std::make_shared<XMLTreeDBTransactionImpl>());
}

TreeDBTransaction XMLTreeDBImpl::rollbackTransaction(TreeDBTransaction& transaction)
{
    // TODO
    return TreeDBTransaction(std::make_shared<XMLTreeDBTransactionImpl>());
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

TreeDBNode XMLTreeDBImpl::appendChildNode(TreeDBNode& parent, const std::string& name, const TreeDBValue& value,
    Ishiko::Error& error)
{
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

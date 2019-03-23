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

TreeDBNode XMLTreeDBImpl::insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
    Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    TreeDBNode result = parentNodeImpl.insertChildNode(index, name, error);
    commitNode(parentNodeImpl, error);
    return result;
}

TreeDBNode XMLTreeDBImpl::insertChildNodeBefore(TreeDBNode& parent, const TreeDBNode& nextChild,
    const std::string& name, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    TreeDBNode result = parentNodeImpl.insertChildNodeBefore(nextChild, name, error);
    commitNode(parentNodeImpl, error);
    return result;
}

TreeDBNode XMLTreeDBImpl::insertChildNodeAfter(TreeDBNode& parent, const TreeDBNode& previousChild,
    const std::string& name, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    TreeDBNode result = parentNodeImpl.insertChildNodeAfter(previousChild, name, error);
    commitNode(parentNodeImpl, error);
    return result;
}

TreeDBNode XMLTreeDBImpl::appendChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    TreeDBNode result = parentNodeImpl.appendChildNode(name, error);
    commitNode(parentNodeImpl, error);
    return result;
}

TreeDBNode XMLTreeDBImpl::setChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error)
{
    XMLTreeDBNodeImpl& parentNodeImpl = static_cast<XMLTreeDBNodeImpl&>(*parent.impl());
    TreeDBNode result = parentNodeImpl.setChildNode(name, error);
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

void XMLTreeDBImpl::commitNode(XMLTreeDBNodeImpl& node, Ishiko::Error& error)
{
    node.updateValue();
    std::ofstream file(m_path.string());
    m_document.save(file, "  ");
}

}

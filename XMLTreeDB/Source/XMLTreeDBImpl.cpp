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
        m_root = TreeDBNode(std::make_shared<XMLTreeDBNodeImpl>(shared_from_this(), nullptr, rootNode));

        std::ofstream file(m_path.string());
        m_document.save(file);
    }
}

void XMLTreeDBImpl::open(const boost::filesystem::path& path, Ishiko::Error& error)
{
    m_path = path;
    m_document.load_file(m_path.string().c_str());
    m_root = TreeDBNode(std::make_shared<XMLTreeDBNodeImpl>(shared_from_this(), nullptr, m_document.child(rootElementName)));
}

void XMLTreeDBImpl::close()
{
}

TreeDBNode& XMLTreeDBImpl::root()
{
    return m_root;
}

TreeDBNode XMLTreeDBImpl::insert(TreeDBNode& parent, size_t index, const TreeDBKey& key, Ishiko::Error& error)
{
    TreeDBNodeImpl& parentNodeImpl = *parent.impl();
    TreeDBNode result = parentNodeImpl.insert(index, key, error);
    commitNode(static_cast<XMLTreeDBNodeImpl&>(parentNodeImpl), error);
    return result;
}

TreeDBNode XMLTreeDBImpl::insertBefore(TreeDBNode& parent, const TreeDBNode& child, const TreeDBKey& key,
    Ishiko::Error& error)
{
    TreeDBNodeImpl& parentNodeImpl = *parent.impl();
    TreeDBNode result = parentNodeImpl.insertBefore(child, key, error);
    commitNode(static_cast<XMLTreeDBNodeImpl&>(parentNodeImpl), error);
    return result;
}

TreeDBNode XMLTreeDBImpl::insertAfter(TreeDBNode& parent, const TreeDBNode& child, const TreeDBKey& key,
    Ishiko::Error& error)
{
    TreeDBNodeImpl& parentNodeImpl = *parent.impl();
    TreeDBNode result = parentNodeImpl.insertAfter(child, key, error);
    commitNode(static_cast<XMLTreeDBNodeImpl&>(parentNodeImpl), error);
    return result;
}

void XMLTreeDBImpl::commitNode(XMLTreeDBNodeImpl& node, Ishiko::Error& error)
{
    node.updateValue();
    std::ofstream file(m_path.string());
    m_document.save(file, "  ");
}

}

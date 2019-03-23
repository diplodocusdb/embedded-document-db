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

#ifndef _DIPLODOCUSDB_TREEDB_XMLTREEDB_XMLTREEDBIMPL_H_
#define _DIPLODOCUSDB_TREEDB_XMLTREEDB_XMLTREEDBIMPL_H_

#include "XMLTreeDBNodeImpl.h"
#include "DiplodocusDB/TreeDB/Core/TreeDBNode.h"
#include "Ishiko/Errors/Error.h"
#include <pugixml.hpp>
#include <boost/filesystem/path.hpp>

namespace DiplodocusDB
{

class XMLTreeDBImpl : public std::enable_shared_from_this<XMLTreeDBImpl>
{
public:
    void create(const boost::filesystem::path& path, Ishiko::Error& error);
    void open(const boost::filesystem::path& path, Ishiko::Error& error);
    void close();

    TreeDBNode& root();

    TreeDBNode insertChildNode(TreeDBNode& parent, size_t index, const std::string& name, Ishiko::Error& error);
    TreeDBNode insertChildNodeBefore(TreeDBNode& parent, const TreeDBNode& child, const std::string& name,
        Ishiko::Error& error);
    TreeDBNode insertAfter(TreeDBNode& parent, const TreeDBNode& child, const TreeDBKey& key, Ishiko::Error& error);
    TreeDBNode append(TreeDBNode& parent, const TreeDBKey& key, Ishiko::Error& error);

    void commitNode(XMLTreeDBNodeImpl& node, Ishiko::Error& error);

private:
    boost::filesystem::path m_path;
    pugi::xml_document m_document;
    TreeDBNode m_root;
};

}

#endif

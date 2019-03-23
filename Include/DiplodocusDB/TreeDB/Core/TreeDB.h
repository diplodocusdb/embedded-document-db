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

#ifndef _DIPLODOCUSDB_TREEDB_CORE_TREEDB_H_
#define _DIPLODOCUSDB_TREEDB_CORE_TREEDB_H_

#include "TreeDBNode.h"
#include "Ishiko/Errors/Error.h"

namespace DiplodocusDB
{

/// Base class for the different hierarchical databases.
/**
    This class defines a common API for all the DiplodocusDB hierarchical databases.
*/
class TreeDB
{
public:
    /// Destructor.
    virtual ~TreeDB() = default;

    /// Returns the root of the tree.
    virtual TreeDBNode& root() = 0;

    /// Inserts a new child node at a given position and returns a handle to the new child.
    /**
        The new node has no value.

        This operation commits the changes to the database immediately.

        @param parent The parent of the new child node.
        @param index The position of the new child node in the sequence of existing children.
        @param name The name of the new child node. This is not a complete key, only the name of the new child since
        we specify the parent in another argument.
        @param error The result of the operation.
        @returns A handle to the new child node.
    */
    virtual TreeDBNode insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
        Ishiko::Error& error) = 0;
    /// Inserts a new child node before an existing child node and returns a handle to the new child.
    /**
        The new node has no value.

        This operation commits the changes to the database immediately.

        @param parent The parent of the new child node.
        @param nextChild The new node will be inserted before this child.
        @param name The name of the new child node. This is not a complete key, only the name of the new child since
        we specify the parent in another argument.
        @param error The result of the operation.
        @returns A handle to the new child node.
    */
    virtual TreeDBNode insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
        Ishiko::Error& error) = 0;
    /// Inserts a new child node after an existing child node and returns a handle to the new child.
    /**
        The new node has no value.

        This operation commits the changes to the database immediately.

        @param parent The parent of the new child node.
        @param previousChild The new node will be inserted after this child.
        @param name The name of the new child node. This is not a complete key, only the name of the new child since
        we specify the parent in another argument.
        @param error The result of the operation.
        @returns A handle to the new child node.
    */
    virtual TreeDBNode insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
        Ishiko::Error& error) = 0;
    /// Inserts a new child node after the last existing child node and returns a handle to the new child.
    /**
        The new node has no value.

        This operation commits the changes to the database immediately.

        @param parent The parent of the new child node.
        @param name The name of the new child node. This is not a complete key, only the name of the new child since
        we specify the parent in another argument.
        @param error The result of the operation.
        @returns A handle to the new child node.
    */
    virtual TreeDBNode appendChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error) = 0;
    /// Clears the value of the first node with the given name or appends a new node if no node with this name exists.
    /**
        If a node with the given name exists then its value is cleared and a handle to this node is returned. If
        multiple nodes with the same name exists then only the first node is taken into account.

        If no node with the given name exists then this function is equivalent to appendChildNode().

        This operation commits the changes to the database immediately.

        @param parent The parent of the child node.
        @param name The name of the child node. This is not a complete key, only the name of the new child since
        we specify the parent in another argument.
        @param error The result of the operation.
        @returns A handle to the new child node.
    */
    virtual TreeDBNode setChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error) = 0;
    /// Removes the first child node with the given name.
    /**
        If no node with this name exists then this function does nothing and no error is reported.

        If multiple children with the same name exist only the first one is removed.

        This operation commits the changes to the database immediately.

        @param parent The parent of the child node.
        @param name The name of the child node. This is not a complete key, only the name of the new child since
        we specify the parent in another argument.
        @param error The result of the operation.
        @returns The number of nodes removed: 0 or 1.
    */
    virtual size_t removeChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error) = 0;
    /// Removes all child nodes.
    /**
        This operation commits the changes to the database immediately.

        @param parent The parent of the child node.
        @param error The result of the operation.
        @returns The number of nodes removed.
    */
    virtual size_t removeAllChildNodes(TreeDBNode& parent, Ishiko::Error& error) = 0;

    // TODO : this is temporary until I have migrated all the node functions here
    virtual void commitNode(TreeDBNode& node, Ishiko::Error& error) = 0;
};

}

#endif

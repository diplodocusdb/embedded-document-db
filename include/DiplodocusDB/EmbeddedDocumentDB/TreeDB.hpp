/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/tree-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_TREEDB_CORE_TREEDB_HPP_
#define _DIPLODOCUSDB_TREEDB_CORE_TREEDB_HPP_

#include "TreeDBNode.hpp"
#include "TreeDBTransaction.hpp"
#include <DiplodocusDB/Core.hpp>
#include <Ishiko/Errors.hpp>

namespace DiplodocusDB
{

enum ETreeTraversalOrder
{
    eDepthFirstInorderTraversal,
    eDepthFirstPreorderTraversal,
    eDepthFirstPostorderTraversal,
    eBreadthFirstTraversal
};

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

    virtual Value value(TreeDBNode& node, Ishiko::Error& error) = 0;
    virtual Value value(TreeDBNode& node, const DataType& type, Ishiko::Error& error) = 0;
    virtual Value childValue(TreeDBNode& parent, const std::string& name, Ishiko::Error& error) = 0;
    virtual Value childValue(TreeDBNode& parent, const std::string& name, const DataType& type,
        Ishiko::Error& error) = 0;

    virtual TreeDBNode parent(TreeDBNode& node, Ishiko::Error& error) = 0;
    virtual std::vector<TreeDBNode> childNodes(TreeDBNode& parent, Ishiko::Error& error) = 0;
    virtual TreeDBNode child(TreeDBNode& parent, const std::string& name, Ishiko::Error& error) = 0;
    virtual TreeDBNode previousSibling(TreeDBNode& node, Ishiko::Error& error) = 0;
    virtual TreeDBNode previousSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error) = 0;
    virtual TreeDBNode nextSibling(TreeDBNode& node, Ishiko::Error& error) = 0;
    virtual TreeDBNode nextSibling(TreeDBNode& node, const std::string& name, Ishiko::Error& error) = 0;

    virtual void traverse(TreeDBNode& node, ETreeTraversalOrder order,  void (*callback)(TreeDB& db, TreeDBNode& node),
        void* callbackData) = 0;

    virtual TreeDBTransaction createTransaction(Ishiko::Error& error) = 0;
    virtual void commitTransaction(TreeDBTransaction& transaction, Ishiko::Error& error) = 0;
    virtual void rollbackTransaction(TreeDBTransaction& transaction) = 0;

    /// Sets the value of the node.
    /**
        This operation commits the changes to the database immediately.

        @param node The node to update.
        @param value The new value of the node.
        @param error The result of the operation.
    */
    virtual void setValue(TreeDBNode& node, const Value& value, Ishiko::Error& error) = 0;

    /// Inserts a new child node at a given position and returns a handle to the new child.
    /**
        The new node has a NULL value.

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
    /// Inserts a new child node at a given position and returns a handle to the new child.
    /**
        This operation commits the changes to the database immediately.

        @param parent The parent of the new child node.
        @param index The position of the new child node in the sequence of existing children.
        @param name The name of the new child node. This is not a complete key, only the name of the new child since
        we specify the parent in another argument.
        @param value The value of the new node.
        @param error The result of the operation.
        @returns A handle to the new child node.
    */
    virtual TreeDBNode insertChildNode(TreeDBNode& parent, size_t index, const std::string& name,
        const Value& value, Ishiko::Error& error) = 0;
    /// Inserts a new child node before an existing child node and returns a handle to the new child.
    /**
        The new node has a NULL value.

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
    /// Inserts a new child node before an existing child node and returns a handle to the new child.
    /**
        This operation commits the changes to the database immediately.

        @param parent The parent of the new child node.
        @param nextChild The new node will be inserted before this child.
        @param name The name of the new child node. This is not a complete key, only the name of the new child since
        we specify the parent in another argument.
        @param value The value of the new node.
        @param error The result of the operation.
        @returns A handle to the new child node.
    */
    virtual TreeDBNode insertChildNodeBefore(TreeDBNode& parent, TreeDBNode& nextChild, const std::string& name,
        const Value& value, Ishiko::Error& error) = 0;
    /// Inserts a new child node after an existing child node and returns a handle to the new child.
    /**
        The new node has a NULL value.

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
    /// Inserts a new child node after an existing child node and returns a handle to the new child.
    /**
        This operation commits the changes to the database immediately.

        @param parent The parent of the new child node.
        @param previousChild The new node will be inserted after this child.
        @param name The name of the new child node. This is not a complete key, only the name of the new child since
        we specify the parent in another argument.
        @param value The value of the new node.
        @param error The result of the operation.
        @returns A handle to the new child node.
    */
    virtual TreeDBNode insertChildNodeAfter(TreeDBNode& parent, TreeDBNode& previousChild, const std::string& name,
        const Value& value, Ishiko::Error& error) = 0;
    /// Inserts a new child node after the last existing child node and returns a handle to the new child.
    /**
        The new node has a NULL value.

        This operation commits the changes to the database immediately.

        @param parent The parent of the new child node.
        @param name The name of the new child node. This is not a complete key, only the name of the new child since
        we specify the parent in another argument.
        @param error The result of the operation.
        @returns A handle to the new child node.
    */
    virtual TreeDBNode appendChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error) = 0;
    virtual TreeDBNode appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent, const std::string& name,
        Ishiko::Error& error) = 0;
    /// Inserts a new child node after the last existing child node and returns a handle to the new child.
    /**
        This operation commits the changes to the database immediately.

        @param parent The parent of the new child node.
        @param name The name of the new child node. This is not a complete key, only the name of the new child since
        we specify the parent in another argument.
        @param value The value of the new node.
        @param error The result of the operation.
        @returns A handle to the new child node.
    */
    virtual TreeDBNode appendChildNode(TreeDBNode& parent, const std::string& name, const Value& value,
        Ishiko::Error& error) = 0;
    virtual TreeDBNode appendChildNode(TreeDBTransaction& transaction, TreeDBNode& parent, const std::string& name,
        const Value& value, Ishiko::Error& error) = 0;
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
        @returns A handle to the child node.
    */
    virtual TreeDBNode setChildNode(TreeDBNode& parent, const std::string& name, Ishiko::Error& error) = 0;
    /// Replaces the value of the first node with the given name or appends a new node if no node with this name exists.
    /**
        If a node with the given name exists then its value is set to the value given as argument and a handle to this
        node is returned. If multiple nodes with the same name exists then only the first node is taken into account.

        If no node with the given name exists then this function is equivalent to appendChildNode().

        This operation commits the changes to the database immediately.

        @param parent The parent of the child node.
        @param name The name of the child node. This is not a complete key, only the name of the new child since
        we specify the parent in another argument.
        @param value The value of the node.
        @param error The result of the operation.
        @returns A handle to the child node.
    */
    virtual TreeDBNode setChildNode(TreeDBNode& parent, const std::string& name, const Value& value,
        Ishiko::Error& error) = 0;
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
};

}

#endif

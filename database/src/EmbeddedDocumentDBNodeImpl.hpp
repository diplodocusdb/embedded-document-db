/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_EMBEDDEDDOCUMENTDBNODEIMPL_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_EMBEDDEDDOCUMENTDBNODEIMPL_HPP_

#include <DiplodocusDB/EmbeddedDocumentDB/StorageEngine.hpp>

namespace DiplodocusDB
{

class EmbeddedDocumentDBNodeImpl
{
public:
    EmbeddedDocumentDBNodeImpl();
    EmbeddedDocumentDBNodeImpl(const NodeID& parentNodeID, const NodeID& nodeID, const std::string& name);
    EmbeddedDocumentDBNodeImpl(const NodeID& parentNodeID, const SiblingNodeRecordGroup& node);

    const std::string& name() const;
    const Value& value() const;
    Value& value();
    bool isRoot() const;

    const NodeID& parentNodeID() const;
    const NodeID& nodeID() const;
    
private:
    std::string m_name;
    Value m_value;
    NodeID m_parentNodeID;
    NodeID m_nodeID;
};

}

#endif

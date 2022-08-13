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
    EmbeddedDocumentDBNodeImpl(const EDDBImpl::NodeID& parentNodeID, const EDDBImpl::NodeID& nodeID,
        const std::string& name);
    EmbeddedDocumentDBNodeImpl(const EDDBImpl::NodeID& parentNodeID, const EDDBImpl::SiblingNodeRecordGroup& node);

    const std::string& name() const;
    const Value& value() const;
    Value& value();
    bool isRoot() const;

    const EDDBImpl::NodeID& parentNodeID() const;
    const EDDBImpl::NodeID& nodeID() const;
    
private:
    std::string m_name;
    Value m_value;
    EDDBImpl::NodeID m_parentNodeID;
    EDDBImpl::NodeID m_nodeID;
};

}

#endif

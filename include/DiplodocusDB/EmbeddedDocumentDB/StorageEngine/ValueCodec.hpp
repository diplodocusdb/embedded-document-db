/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_VALUECODEC_HPP_
#define _DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_VALUECODEC_HPP_

#include <DiplodocusDB/Core.hpp>
#include <DiplodocusDB/PhysicalStorage/PageRepository.hpp>
#include <Ishiko/Errors.hpp>

namespace DiplodocusDB
{

class ValueCodec
{
public:
    static Value readInlineValue(PageRepositoryReader& reader, Ishiko::Error& error);
    static void writeInlineValue(PageRepositoryWriter& writer, const Value& value, Ishiko::Error& error);
    static DataType readDataType(PageRepositoryReader& reader, Ishiko::Error& error);
    static void writeDataType(PageRepositoryWriter& writer, const DataType& dataType, Ishiko::Error& error);
    static bool readBoolean(PageRepositoryReader& reader, Ishiko::Error& error);
    static void writeBoolean(PageRepositoryWriter& writer, bool data, Ishiko::Error& error);
    static std::string readString(PageRepositoryReader& reader, Ishiko::Error& error);
    static void writeString(PageRepositoryWriter& writer, const std::string& data, Ishiko::Error& error);
};

}

#endif

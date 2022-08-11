/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_VALUECODEC_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_VALUECODEC_HPP

#include <DiplodocusDB/Core.hpp>
#include <DiplodocusDB/PhysicalStorage.hpp>
#include <Ishiko/Errors.hpp>

namespace DiplodocusDB
{

class ValueCodec
{
public:
    static Value ReadInlineValue(PageRepositoryReader& reader, Ishiko::Error& error);
    static void WriteInlineValue(PageRepositoryWriter& writer, const Value& value, Ishiko::Error& error);
    static DataType ReadDataType(PageRepositoryReader& reader, Ishiko::Error& error);
    static void WriteDataType(PageRepositoryWriter& writer, const DataType& dataType, Ishiko::Error& error);
    static bool ReadBoolean(PageRepositoryReader& reader, Ishiko::Error& error);
    static void WriteBoolean(PageRepositoryWriter& writer, bool data, Ishiko::Error& error);
    static std::string ReadString(PageRepositoryReader& reader, Ishiko::Error& error);
    static void WriteString(PageRepositoryWriter& writer, const std::string& data, Ishiko::Error& error);
};

}

#endif

/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/embedded-document-db/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_VALUECODEC_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_VALUECODEC_HPP

#include "RecordRepositoryReader.hpp"
#include "RecordRepositoryWriter.hpp"
#include <DiplodocusDB/Core.hpp>
#include <Ishiko/Errors.hpp>

namespace DiplodocusDB
{
namespace EDDBImpl
{

class ValueCodec
{
public:
    static Value ReadInlineValue(RecordRepositoryReader& reader, Ishiko::Error& error);
    static void WriteInlineValue(RecordRepositoryWriter& writer, const Value& value, Ishiko::Error& error);
    static DataType ReadDataType(RecordRepositoryReader& reader, Ishiko::Error& error);
    static void WriteDataType(RecordRepositoryWriter& writer, const DataType& dataType, Ishiko::Error& error);
    static bool ReadBoolean(RecordRepositoryReader& reader, Ishiko::Error& error);
    static void WriteBoolean(RecordRepositoryWriter& writer, bool data, Ishiko::Error& error);
    static std::string ReadString(RecordRepositoryReader& reader, Ishiko::Error& error);
    static void WriteString(RecordRepositoryWriter& writer, const std::string& data, Ishiko::Error& error);
};

}
}

#endif

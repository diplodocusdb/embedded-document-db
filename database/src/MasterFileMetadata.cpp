/*
    Copyright (c) 2018-2019 Xavier Leclercq

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

#include "MasterFileMetadata.h"
#include "DiplodocusDB/PhysicalStorage/PageRepository/Page.h"

namespace DiplodocusDB
{

MasterFileMetadata::MasterFileMetadata()
    : m_fileFormatVersion(1, 0, 0)
{
}

void MasterFileMetadata::read(PageRepositoryReader& reader, Ishiko::Error& error)
{
    // TODO: this needs to decode LEB128
    uint8_t size;
    reader.read((char*)&size, 1, error);
    if (!error)
    {
        // TODO
        char buffer[12];
        reader.read(buffer, 12, error);
    }
}

void MasterFileMetadata::write(PageRepositoryWriter& writer, Ishiko::Error& error) const
{
    writer.writeLEB128(12, error);
    if (!error)
    {
        for (unsigned int v : m_fileFormatVersion.value())
        {
            writer.write((char*)&v, 4, error);
            if (error)
            {
                break;
            }
        }
    }
}

}

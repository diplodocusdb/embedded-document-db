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

#include "SiblingNodesRecordGroupCache.h"

namespace DiplodocusDB
{

bool SiblingNodesRecordGroupCache::find(const NodeID& key,
    std::shared_ptr<SiblingNodesRecordGroup>& siblingNodes)
{
    std::map<NodeID, std::shared_ptr<SiblingNodesRecordGroup>>::iterator it = m_groups.find(key);
    if (it != m_groups.end())
    {
        siblingNodes = it->second;
        return true;
    }
    else
    {
        return false;
    }
}

std::shared_ptr<SiblingNodesRecordGroup>& SiblingNodesRecordGroupCache::operator[](const NodeID& key)
{
    std::shared_ptr<SiblingNodesRecordGroup>& result = m_groups[key];
    if (!result)
    {
        result = std::make_shared<SiblingNodesRecordGroup>(key);
    }
    return result;
}

}

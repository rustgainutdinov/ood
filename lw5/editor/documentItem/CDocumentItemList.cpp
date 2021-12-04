//
// Created by rustam.gainutdinov on 28.11.2021.
//

#include "CDocumentItemList.h"
#include "CDocumentItem.h"

using namespace std;

void CDocumentItemList::Add(unique_ptr<CDocumentItem> item, optional<size_t> position)
{
    if (position == nullopt)
    {
        m_itemsList.push_back(move(item));
        return;
    }
    if (position > m_itemsList.size())
    {
        throw invalid_argument("Impossible position to insert");
    }
    m_itemsList.insert(m_itemsList.begin() + position.value(), move(item));
}

void CDocumentItemList::Delete(size_t position)
{
    AssertPositionInStructureExists(position);
    m_itemsList.erase(m_itemsList.begin() + position);
}

CDocumentItem &CDocumentItemList::Get(size_t position)
{
    AssertPositionInStructureExists(position);
    m_itemsList[position];
    return *m_itemsList[position];
}

void CDocumentItemList::AssertPositionInStructureExists(size_t position) const
{
    if (position >= m_itemsList.size())
    {
        throw invalid_argument("Position is not exist");
    }
}

size_t CDocumentItemList::GetSize()
{
    return m_itemsList.size();
}

std::unique_ptr<CDocumentItem> CDocumentItemList::GetPtr(size_t position)
{
    AssertPositionInStructureExists(position);
    return move(m_itemsList[position]);
}

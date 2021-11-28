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

std::unique_ptr<CDocumentItem> CDocumentItemList::Delete(size_t position)
{
    AssertPositionInStructureExists(position);
    auto item = move(m_itemsList[position]);
    m_itemsList.erase(m_itemsList.begin() + position);
    return item;
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

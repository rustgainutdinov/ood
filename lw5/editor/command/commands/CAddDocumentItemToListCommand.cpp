//
// Created by rustam.gainutdinov on 28.11.2021.
//

#include "CAddDocumentItemToListCommand.h"

#include <utility>
#include "lw5/editor/documentItem/IDocumentItemList.h"
#include "lw5/editor/documentItem/CDocumentItem.h"
#include "lw5/editor/content/IImageResource.h"

using namespace std;


CAddDocumentItemToListCommand::CAddDocumentItemToListCommand(IDocumentItemList &list,
                                                             unique_ptr<CDocumentItem> item,
                                                             optional<size_t> position) :
        m_list(list), m_item(move(item)), m_position(position)
{
    m_item->TryToCapture();
}

CAddDocumentItemToListCommand::~CAddDocumentItemToListCommand()
{
    if (m_item != nullptr)
    {
        m_item->TryToRelease();
        return;
    }
    m_list.Get(GetPosition()).TryToRelease();
}

void CAddDocumentItemToListCommand::Execute()
{
    if (m_item == nullptr)
    {
        return;
    }
    m_item->TryToMarkAsNotDeleted();
    m_list.Add(move(m_item), m_position);
}

void CAddDocumentItemToListCommand::CancelExecution()
{
    if (m_item != nullptr)
    {
        return;
    }
    auto position = GetPosition();
    m_item = m_list.GetPtr(position);
    m_list.Delete(position);
    m_item->TryToMarkAsDeleted();
}

size_t CAddDocumentItemToListCommand::GetPosition()
{
    return m_position != nullopt ? m_position.value() : m_list.GetSize() - 1;
}

//
// Created by rustam.gainutdinov on 28.11.2021.
//

#include "CAddDocumentItemToListCommand.h"
#include "lw5/editor/documentItem/IDocumentItemList.h"
#include "lw5/editor/documentItem/CDocumentItem.h"
#include "lw5/editor/content/IResource.h"
#include "lw5/editor/content/IImageResource.h"

using namespace std;


CAddDocumentItemToListCommand::CAddDocumentItemToListCommand(IDocumentItemList &list,
                                                             unique_ptr<CDocumentItem> item,
                                                             optional<size_t> position) :
        m_list(list), m_item(move(item)), m_position(position)
{
    if (m_item->GetResource() != nullopt)
    {
        m_item->GetResource().value()->Capture();
    }
}

CAddDocumentItemToListCommand::~CAddDocumentItemToListCommand()
{
    if (m_item != nullptr)
    {
        if (m_item->GetResource() == nullopt)
        {
            return;
        }
        m_item->GetResource().value()->Release();
        return;
    }
    auto position = m_position != nullopt ? m_position.value() : m_list.GetSize() - 1;
    if (m_list.Get(position).GetResource() != nullopt)
    {
        m_list.Get(position).GetResource().value()->Release();
        return;
    }
}

void CAddDocumentItemToListCommand::Execute()
{
    if (m_item == nullptr)
    {
        return;
    }
    if (m_item->GetResource() != nullopt)
    {
        m_item->GetResource().value()->MarkAsNotDeleted();
    }
    m_list.Add(move(m_item), m_position);
}

void CAddDocumentItemToListCommand::CancelExecution()
{
    auto position = m_position != nullopt ? m_position.value() : m_list.GetSize() - 1;
    m_item = m_list.Delete(position);
    if (m_item->GetResource() != nullopt)
    {
        m_item->GetResource().value()->MarkAsDeleted();
    }
}

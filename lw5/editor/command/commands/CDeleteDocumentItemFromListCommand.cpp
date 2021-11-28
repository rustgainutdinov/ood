//
// Created by rustam.gainutdinov on 29.11.2021.
//

#include "CDeleteDocumentItemFromListCommand.h"
#include "lw5/editor/documentItem/IDocumentItemList.h"
#include "lw5/editor/documentItem/CDocumentItem.h"
#include "lw5/editor/content/IResource.h"
#include "lw5/editor/content/IImageResource.h"

using namespace std;

CDeleteDocumentItemFromListCommand::CDeleteDocumentItemFromListCommand(IDocumentItemList &list,
                                                                       size_t position) :
        m_list(list), m_position(position)
{
    if (m_list.Get(m_position).GetResource() != nullopt)
    {
        m_list.Get(m_position).GetResource().value()->Capture();
    }
}

CDeleteDocumentItemFromListCommand::~CDeleteDocumentItemFromListCommand()
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
    if (m_list.Get(m_position).GetResource() != nullopt)
    {
        m_list.Get(m_position).GetResource().value()->Release();
    }
}

void CDeleteDocumentItemFromListCommand::Execute()
{
    m_item = m_list.Delete(m_position);
    if (m_item->GetResource() != nullopt)
    {
        m_item->GetResource().value()->MarkAsDeleted();
    }
}

void CDeleteDocumentItemFromListCommand::CancelExecution()
{
    if (m_item->GetResource() != nullopt)
    {
        m_item->GetResource().value()->MarkAsNotDeleted();
    }
    m_list.Add(move(m_item), m_position);
}

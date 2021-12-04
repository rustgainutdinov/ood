//
// Created by rustam.gainutdinov on 29.11.2021.
//

#include "CDeleteDocumentItemFromListCommand.h"

#include <utility>
#include "lw5/editor/documentItem/IDocumentItemList.h"
#include "lw5/editor/documentItem/CDocumentItem.h"
#include "lw5/editor/content/IImageResource.h"

using namespace std;

CDeleteDocumentItemFromListCommand::CDeleteDocumentItemFromListCommand(std::shared_ptr<IDocumentItemList> list,
                                                                       size_t position) :
        m_list(move(list)), m_position(position)
{
    m_list->Get(m_position).TryToCapture();
}

CDeleteDocumentItemFromListCommand::~CDeleteDocumentItemFromListCommand()
{
    if (m_item != nullptr)
    {
        m_item->TryToRelease();
        return;
    }
    m_list->Get(m_position).TryToRelease();
}

void CDeleteDocumentItemFromListCommand::Execute()
{
    m_item = m_list->GetPtr(m_position);
    m_list->Delete(m_position);
    m_item->TryToMarkAsDeleted();
}

void CDeleteDocumentItemFromListCommand::CancelExecution()
{
    m_item->TryToMarkAsNotDeleted();
    m_list->Add(move(m_item), m_position);
}

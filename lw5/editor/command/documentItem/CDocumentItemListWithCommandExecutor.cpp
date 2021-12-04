//
// Created by rustam.gainutdinov on 04.12.2021.
//

#include "CDocumentItemListWithCommandExecutor.h"

#include <utility>
#include "lw5/editor/command/ICommandExecutor.h"
#include "lw5/editor/command/commands/CDeleteDocumentItemFromListCommand.h"
#include "lw5/editor/command/commands/CAddDocumentItemToListCommand.h"
#include "lw5/editor/documentItem/CDocumentItem.h"

using namespace std;

CDocumentItemListWithCommandExecutor::CDocumentItemListWithCommandExecutor(
        shared_ptr<IDocumentItemList> documentItemList, ICommandExecutor &commandExecutor) :
        m_documentItemList(move(documentItemList)), m_commandExecutor(commandExecutor)
{
}

void CDocumentItemListWithCommandExecutor::Add(unique_ptr<CDocumentItem> item, optional<size_t> position)
{
    auto command = make_unique<CAddDocumentItemToListCommand>(m_documentItemList, move(item), position);
    m_commandExecutor.Add(move(command));
}

void CDocumentItemListWithCommandExecutor::Delete(size_t position)
{
    auto command = make_unique<CDeleteDocumentItemFromListCommand>(m_documentItemList, position);
    m_commandExecutor.Add(move(command));
}

CDocumentItem &CDocumentItemListWithCommandExecutor::Get(size_t position)
{
    return m_documentItemList->Get(position);
}

size_t CDocumentItemListWithCommandExecutor::GetSize()
{
    return m_documentItemList->GetSize();
}

unique_ptr<CDocumentItem> CDocumentItemListWithCommandExecutor::GetPtr(size_t position)
{
    return move(m_documentItemList->GetPtr(position));
}

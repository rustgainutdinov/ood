//
// Created by rustam.gainutdinov on 21.11.2021.
//

#include "CInsertParagraphCommand.h"
#include <lw5/editor/IDocument.h>

#include <utility>

using namespace std;

void CInsertParagraphCommand::Execute()
{
    m_document->InsertParagraph(m_text, m_position);
}

void CInsertParagraphCommand::CancelExecution()
{
    m_document->DeleteItem(m_position);
}

CInsertParagraphCommand::CInsertParagraphCommand(shared_ptr<IDocument> document, string text,
                                                 optional<size_t> position) : m_document(move(document)),
                                                                              m_text(move(text)),
                                                                              m_position(position)
{
}

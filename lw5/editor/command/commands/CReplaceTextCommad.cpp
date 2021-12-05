//
// Created by rustam.gainutdinov on 05.12.2021.
//

#include "CReplaceTextCommad.h"
#include "lw5/editor/content/IParagraph.h"

using namespace std;

CReplaceTextCommand::CReplaceTextCommand(std::shared_ptr<IParagraph> paragraph, const std::string &text) : m_paragraph(
        move(paragraph)), m_baseText(m_paragraph->GetText()), m_text(text)
{
}

void CReplaceTextCommand::Execute()
{
    m_paragraph->SetText(m_text);
}

void CReplaceTextCommand::CancelExecution()
{
    m_paragraph->SetText(m_baseText);
}

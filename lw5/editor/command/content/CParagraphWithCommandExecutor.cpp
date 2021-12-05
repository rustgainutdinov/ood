//
// Created by rustam.gainutdinov on 05.12.2021.
//

#include "CParagraphWithCommandExecutor.h"
#include "lw5/editor/command/commands/CReplaceTextCommad.h"
#include "lw5/editor/command/ICommandExecutor.h"

using namespace std;

CParagraphWithCommandExecutor::CParagraphWithCommandExecutor(std::shared_ptr<IParagraph> paragraph,
                                                             ICommandExecutor &commandExecutor) : m_commandExecutor(
        commandExecutor), m_paragraph(move(paragraph))
{
}

std::string CParagraphWithCommandExecutor::GetText() const
{
    return m_paragraph->GetText();
}

void CParagraphWithCommandExecutor::SetText(const std::string &text)
{
    auto command = make_unique<CReplaceTextCommand>(m_paragraph, text);
    m_commandExecutor.Add(move(command));
}

//
// Created by rustam.gainutdinov on 05.12.2021.
//

#ifndef OOD_CREPLACETEXTCOMMAD_H
#define OOD_CREPLACETEXTCOMMAD_H


#include "lw5/editor/command/ICommand.h"
#include "memory"

class IParagraph;

class CReplaceTextCommand : public ICommand
{
public:
    CReplaceTextCommand(std::shared_ptr<IParagraph> paragraph, const std::string& text);

    void Execute() override;

    void CancelExecution() override;

private:
    std::shared_ptr<IParagraph> m_paragraph;
    std::string m_text;
    std::string m_baseText;
};


#endif //OOD_CREPLACETEXTCOMMAD_H

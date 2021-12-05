//
// Created by rustam.gainutdinov on 05.12.2021.
//

#ifndef OOD_CPARAGRAPHWITHCOMMANDEXECUTOR_H
#define OOD_CPARAGRAPHWITHCOMMANDEXECUTOR_H


#include "lw5/editor/content/IParagraph.h"
#include "memory"

class ICommandExecutor;

class CParagraphWithCommandExecutor : public IParagraph
{
public:
    CParagraphWithCommandExecutor(std::shared_ptr<IParagraph> paragraph, ICommandExecutor &commandExecutor);

    std::string GetText() const override;

    void SetText(const std::string &text) override;

private:
    std::shared_ptr<IParagraph> m_paragraph;
    ICommandExecutor &m_commandExecutor;
};


#endif //OOD_CPARAGRAPHWITHCOMMANDEXECUTOR_H

//
// Created by rustam.gainutdinov on 21.11.2021.
//

#ifndef OOD_CINSERTPARAGRAPHCOMMAND_H
#define OOD_CINSERTPARAGRAPHCOMMAND_H


#include "ICommand.h"
#include "memory"
#include "optional"
#include "string"

class IDocument;

class CInsertParagraphCommand : public ICommand
{
public:
    CInsertParagraphCommand(std::shared_ptr<IDocument> document, std::string text,
                            std::optional<size_t> position = std::nullopt);

    void Execute() override;

    void CancelExecution() override;

private:
    std::shared_ptr<IDocument> m_document;
    std::string m_text;
    std::optional<size_t> m_position;
};


#endif //OOD_CINSERTPARAGRAPHCOMMAND_H

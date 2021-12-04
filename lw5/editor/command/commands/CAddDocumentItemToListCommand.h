//
// Created by rustam.gainutdinov on 28.11.2021.
//

#ifndef OOD_CADDDOCUMENTITEMTOLISTCOMMAND_H
#define OOD_CADDDOCUMENTITEMTOLISTCOMMAND_H


#include <lw5/editor/command/ICommand.h>
#include "memory"
#include "optional"

class IImageResource;

class CDocumentItem;

class IDocumentItemList;

class CAddDocumentItemToListCommand : public ICommand
{
public:
    CAddDocumentItemToListCommand(std::shared_ptr<IDocumentItemList> list, std::unique_ptr<CDocumentItem> item,
                                  std::optional<size_t> position = std::nullopt);

    ~CAddDocumentItemToListCommand() override;

    void Execute() override;

    void CancelExecution() override;

private:
    size_t GetPosition();

    std::shared_ptr<IDocumentItemList> m_list;
    std::unique_ptr<CDocumentItem> m_item;
    std::optional<size_t> m_position;
};


#endif //OOD_CADDDOCUMENTITEMTOLISTCOMMAND_H

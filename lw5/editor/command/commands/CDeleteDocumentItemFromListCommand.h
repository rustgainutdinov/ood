//
// Created by rustam.gainutdinov on 29.11.2021.
//

#ifndef OOD_CDELETEDOCUMENTITEMFROMLISTCOMMAND_H
#define OOD_CDELETEDOCUMENTITEMFROMLISTCOMMAND_H


#include <lw5/editor/command/ICommand.h>
#include "memory"
#include "optional"

class IImageResource;

class CDocumentItem;

class IDocumentItemList;

class CDeleteDocumentItemFromListCommand : public ICommand
{
public:
    CDeleteDocumentItemFromListCommand(std::shared_ptr<IDocumentItemList> list, size_t position);

    ~CDeleteDocumentItemFromListCommand() override;

    void Execute() override;

    void CancelExecution() override;

private:
    std::shared_ptr<IDocumentItemList> m_list;
    std::unique_ptr<CDocumentItem> m_item{};
    size_t m_position;
};


#endif //OOD_CDELETEDOCUMENTITEMFROMLISTCOMMAND_H

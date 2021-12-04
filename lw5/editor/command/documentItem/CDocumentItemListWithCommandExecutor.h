//
// Created by rustam.gainutdinov on 04.12.2021.
//

#ifndef OOD_CDOCUMENTITEMLISTWITHCOMMANDEXECUTOR_H
#define OOD_CDOCUMENTITEMLISTWITHCOMMANDEXECUTOR_H


#include "lw5/editor/documentItem/IDocumentItemList.h"
#include "memory"

class ICommandExecutor;

class CDocumentItemListWithCommandExecutor : public IDocumentItemList
{
public:
    CDocumentItemListWithCommandExecutor(IDocumentItemList &documentItemList,
                                         ICommandExecutor &commandExecutor);

    void Add(std::unique_ptr<CDocumentItem> item, std::optional<size_t> position = std::nullopt) override;

    void Delete(size_t position) override;

    CDocumentItem &Get(size_t position) override;

    std::unique_ptr<CDocumentItem> GetPtr(size_t position) override;

    size_t GetSize() override;

private:
    IDocumentItemList &m_documentItemList;
    ICommandExecutor &m_commandExecutor;
};


#endif //OOD_CDOCUMENTITEMLISTWITHCOMMANDEXECUTOR_H

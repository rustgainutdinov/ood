//
// Created by rustam.gainutdinov on 28.11.2021.
//

#ifndef OOD_CDOCUMENTITEMLIST_H
#define OOD_CDOCUMENTITEMLIST_H


#include "IDocumentItemList.h"
#include "vector"

class CDocumentItemList : public IDocumentItemList
{
public:
    void Add(std::unique_ptr<CDocumentItem> item, std::optional<size_t> position = std::nullopt) override;

    std::unique_ptr<CDocumentItem> Delete(size_t position) override;

    CDocumentItem &Get(size_t position) override;

    size_t GetSize() override;

private:
    void AssertPositionInStructureExists(size_t position) const;

    std::vector<std::unique_ptr<CDocumentItem>> m_itemsList{};
};


#endif //OOD_CDOCUMENTITEMLIST_H

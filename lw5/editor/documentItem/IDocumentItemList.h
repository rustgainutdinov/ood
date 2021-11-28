//
// Created by rustam.gainutdinov on 28.11.2021.
//

#ifndef OOD_IDOCUMENTITEMLIST_H
#define OOD_IDOCUMENTITEMLIST_H


#include "optional"
#include "memory"

class CDocumentItem;

class IDocumentItemList
{
public:
    virtual ~IDocumentItemList() = default;

    virtual void Add(std::unique_ptr<CDocumentItem> item, std::optional<size_t> position = std::nullopt) = 0;

    virtual std::unique_ptr<CDocumentItem> Delete(size_t position) = 0;

    virtual CDocumentItem &Get(size_t position) = 0;

    virtual size_t GetSize() = 0;
};


#endif //OOD_IDOCUMENTITEMLIST_H

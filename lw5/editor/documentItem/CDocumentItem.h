//
// Created by rustam.gainutdinov on 20.11.2021.
//

#ifndef OOD_CDOCUMENTITEM_H
#define OOD_CDOCUMENTITEM_H

#include <optional>
#include "CConstDocumentItem.h"

class CParagraph;

class CImage;

class CDocumentItem : public CConstDocumentItem
{
public:
    explicit CDocumentItem(std::optional<std::shared_ptr<CParagraph>> paragraph = std::nullopt,
                           std::optional<std::shared_ptr<CImage>> image = std::nullopt);

    std::shared_ptr<IImage> GetImage();

    std::shared_ptr<IParagraph> GetParagraph();
};


#endif //OOD_CDOCUMENTITEM_H

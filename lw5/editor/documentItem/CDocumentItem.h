//
// Created by rustam.gainutdinov on 20.11.2021.
//

#ifndef OOD_CDOCUMENTITEM_H
#define OOD_CDOCUMENTITEM_H

#include "memory"
#include "IDocumentItem.h"
#include <optional>

class CParagraph;

class IParagraph;

class IImageResource;

class IImage;

class IImageResource;

class CDocumentItem : public IDocumentItem
{
public:
    explicit CDocumentItem(std::optional<std::shared_ptr<CParagraph>> paragraph = std::nullopt,
                           std::optional<std::shared_ptr<IImageResource>> image = std::nullopt);

    std::optional<std::shared_ptr<IImage>> GetImage() override;

    std::optional<std::shared_ptr<IParagraph>> GetParagraph() override;

    void TryToCapture();

    void TryToRelease();

    void TryToMarkAsDeleted();

    void TryToMarkAsNotDeleted();

protected:
    std::optional<std::shared_ptr<CParagraph>> m_paragraph;
    std::optional<std::shared_ptr<IImageResource>> m_image;
};


#endif //OOD_CDOCUMENTITEM_H

//
// Created by rustam.gainutdinov on 20.11.2021.
//

#ifndef OOD_CDOCUMENTITEM_H
#define OOD_CDOCUMENTITEM_H

#include "memory"
#include <optional>

class CParagraph;

class IParagraph;

class CImage;

class IImage;

class IResource;

class CDocumentItem
{
public:
    explicit CDocumentItem(std::optional<std::shared_ptr<CParagraph>> paragraph = std::nullopt,
                           std::optional<std::shared_ptr<CImage>> image = std::nullopt);

    std::optional<std::shared_ptr<IImage>> GetImage();

    std::optional<std::shared_ptr<IParagraph>> GetParagraph();

    std::optional<std::shared_ptr<IResource>> GetResource();

private:
    std::optional<std::shared_ptr<CParagraph>> m_paragraph;
    std::optional<std::shared_ptr<CImage>> m_image;
};


#endif //OOD_CDOCUMENTITEM_H

//
// Created by rustam.gainutdinov on 20.11.2021.
//

#ifndef OOD_CCONSTDOCUMENTITEM_H
#define OOD_CCONSTDOCUMENTITEM_H


#include "memory"
#include <optional>

class CParagraph;

class IParagraph;

class IImage;

class CImage;

class CConstDocumentItem
{
public:
    explicit CConstDocumentItem(std::optional<std::shared_ptr<CParagraph>> paragraph = std::nullopt,
                                std::optional<std::shared_ptr<CImage>> image = std::nullopt);

    std::shared_ptr<const IImage> GetImage() const;

    std::shared_ptr<const IParagraph> GetParagraph() const;

protected:
    std::optional<std::shared_ptr<CParagraph>> m_paragraph;
    std::optional<std::shared_ptr<CImage>> m_image;
};


#endif //OOD_CCONSTDOCUMENTITEM_H

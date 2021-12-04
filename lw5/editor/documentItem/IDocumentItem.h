//
// Created by rustam.gainutdinov on 04.12.2021.
//

#ifndef OOD_IDOCUMENTITEM_H
#define OOD_IDOCUMENTITEM_H

#include "memory"
#include <optional>

class CParagraph;

class IParagraph;

class CImage;

class IImage;

class IDocumentItem
{
public:
    virtual ~IDocumentItem() = default;

    virtual std::optional<std::shared_ptr<IImage>> GetImage() = 0;

    virtual std::optional<std::shared_ptr<IParagraph>> GetParagraph() = 0;
};

#endif //OOD_IDOCUMENTITEM_H

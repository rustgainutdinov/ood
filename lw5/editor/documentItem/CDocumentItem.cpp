//
// Created by rustam.gainutdinov on 20.11.2021.
//

#include <lw5/editor/content/CParagraph.h>
#include <lw5/editor/content/IImage.h>
#include <lw5/editor/content/IParagraph.h>
#include "CDocumentItem.h"

using namespace std;

shared_ptr<IImage> CDocumentItem::GetImage()
{
    return m_image != nullopt ? reinterpret_cast<shared_ptr<IImage> &>(m_image) : nullptr;
}

shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
    return m_paragraph != nullopt ? reinterpret_cast<shared_ptr<IParagraph> &>(m_paragraph) : nullptr;
}

CDocumentItem::CDocumentItem(std::optional<std::shared_ptr<CParagraph>> paragraph,
                             std::optional<std::shared_ptr<CImage>> image) : CConstDocumentItem(move(paragraph),
                                                                                                move(image))
{
}

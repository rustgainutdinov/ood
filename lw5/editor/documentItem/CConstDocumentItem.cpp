//
// Created by rustam.gainutdinov on 20.11.2021.
//

#include "CConstDocumentItem.h"
#include <lw5/editor/content/IImage.h>
#include <lw5/editor/content/IParagraph.h>

using namespace std;


std::shared_ptr<const IParagraph> CConstDocumentItem::GetParagraph() const
{
    return m_paragraph != nullopt ? reinterpret_cast<const shared_ptr<IParagraph> &>(m_paragraph) : nullptr;
}

std::shared_ptr<const IImage> CConstDocumentItem::GetImage() const
{
    return m_image != nullopt ? reinterpret_cast<const shared_ptr<IImage> &>(m_image) : nullptr;

}

CConstDocumentItem::CConstDocumentItem(std::optional<std::shared_ptr<CParagraph>> paragraph,
                                       std::optional<std::shared_ptr<CImage>> image) : m_image(move(image)),
                                                                                       m_paragraph(move(paragraph))
{
    if (m_paragraph == nullopt && m_image == nullopt || m_paragraph != nullopt && m_image != nullopt)
    {
        throw invalid_argument("paragraph can contain only one content item");
    }
}


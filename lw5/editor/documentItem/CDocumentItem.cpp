//
// Created by rustam.gainutdinov on 20.11.2021.
//

#include <lw5/editor/content/CParagraph.h>
#include <lw5/editor/content/IImage.h>
#include <lw5/editor/content/IImageResource.h>
#include <lw5/editor/content/IParagraph.h>

#include <utility>
#include <lw5/editor/content/CImage.h>
#include "CDocumentItem.h"

using namespace std;

optional<shared_ptr<IImage>> CDocumentItem::GetImage()
{
    return reinterpret_cast<optional<shared_ptr<IImageResource>> &>(m_image);
}

optional<shared_ptr<IParagraph>> CDocumentItem::GetParagraph()
{
    return reinterpret_cast<optional<shared_ptr<IParagraph>> &>(m_paragraph);
}

optional<shared_ptr<IResource>> CDocumentItem::GetResource()
{
    return reinterpret_cast<optional<shared_ptr<IImageResource>> &>(m_image);
}

CDocumentItem::CDocumentItem(optional<shared_ptr<CParagraph>> paragraph,
                             optional<shared_ptr<CImage>> image) : m_image(move(image)),
                                                                   m_paragraph(move(paragraph))
{
    if (m_paragraph == nullopt && m_image == nullopt || m_paragraph != nullopt && m_image != nullopt)
    {
        throw invalid_argument("paragraph can contain only one content item");
    }
}

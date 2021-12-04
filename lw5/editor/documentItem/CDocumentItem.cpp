//
// Created by rustam.gainutdinov on 20.11.2021.
//

#include <lw5/editor/content/CParagraph.h>
#include <lw5/editor/content/IImage.h>
#include <lw5/editor/content/IImageResource.h>
#include <lw5/editor/content/IParagraph.h>

#include <utility>
#include "CDocumentItem.h"

using namespace std;

optional<shared_ptr<IImage>> CDocumentItem::GetImage()
{
    return reinterpret_cast<optional<shared_ptr<IImage>> &>(m_image);
}

optional<shared_ptr<IParagraph>> CDocumentItem::GetParagraph()
{
    return reinterpret_cast<optional<shared_ptr<IParagraph>> &>(m_paragraph);
}

CDocumentItem::CDocumentItem(optional<shared_ptr<CParagraph>> paragraph,
                             optional<shared_ptr<IImageResource>> image) : m_image(move(image)),
                                                                   m_paragraph(move(paragraph))
{
    if (m_paragraph == nullopt && m_image == nullopt || m_paragraph != nullopt && m_image != nullopt)
    {
        throw invalid_argument("paragraph can contain only one content item");
    }
}

void CDocumentItem::TryToCapture()
{
    if (m_image != nullopt)
    {
        m_image.value()->Capture();
    }
}

void CDocumentItem::TryToRelease()
{
    if (m_image != nullopt)
    {
        m_image.value()->Release();
    }
}

void CDocumentItem::TryToMarkAsDeleted()
{
    if (m_image != nullopt)
    {
        m_image.value()->MarkAsDeleted();
    }
}

void CDocumentItem::TryToMarkAsNotDeleted()
{
    if (m_image != nullopt)
    {
        m_image.value()->MarkAsNotDeleted();
    }
}

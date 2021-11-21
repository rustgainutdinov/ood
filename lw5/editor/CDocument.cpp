#include <lw5/editor/content/CParagraph.h>
#include <lw5/editor/content/CImage.h>
#include "CDocument.h"
#include "memory"

using namespace std;

shared_ptr<IParagraph> CDocument::InsertParagraph(const string &text, optional<size_t> position)
{
    auto paragraph = make_shared<CParagraph>(text);
    CDocumentItem item = CDocumentItem(paragraph);
    InsertDocumentItem(item, position);
    return paragraph;
}

shared_ptr<IImage> CDocument::InsertImage(const Path &path, int width, int height, optional<size_t> position)
{
    auto image = make_shared<CImage>(path, width, height);
    CDocumentItem item = CDocumentItem(nullopt, image);
    InsertDocumentItem(item, position);
    return image;
}

size_t CDocument::GetItemsCount() const
{
    return m_structure.size();
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{
    AssertPositionInStructureExists(index);
    return m_structure[index];
}

CDocumentItem CDocument::GetItem(size_t index)
{
    AssertPositionInStructureExists(index);
    return m_structure[index];
}

void CDocument::DeleteItem(optional<size_t> index)
{
    if (index == nullopt)
    {
        index = GetItemsCount() - 1;
    }
    AssertPositionInStructureExists(index.value());
    m_structure.erase(m_structure.begin() + index.value());
}

string CDocument::GetTitle() const
{
    return m_title;
}

void CDocument::SetTitle(const string &title)
{
    m_title = title;
}

void CDocument::Save(const Path &path) const
{
}

void CDocument::InsertDocumentItem(CDocumentItem item, optional<size_t> position)
{
    if (position == nullopt)
    {
        m_structure.push_back(item);
        return;
    }
    if (position > GetItemsCount())
    {
        throw invalid_argument("Impossible position to insert");
    }
    m_structure.insert(m_structure.begin() + position.value(), item);
}

void CDocument::AssertPositionInStructureExists(size_t position) const
{
    if (position >= GetItemsCount())
    {
        throw invalid_argument("Position is not exist");
    }
}

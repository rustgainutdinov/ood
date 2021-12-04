#include <lw5/editor/content/CParagraph.h>
#include <lw5/editor/content/CImage.h>
#include "CDocument.h"
#include "memory"
#include "lw5/editor/documentItem/CDocumentItemList.h"
#include "lw5/editor/command/CUndoableCommandExecutor.h"
#include "lw5/editor/command/documentItem/CDocumentItemListWithCommandExecutor.h"

using namespace std;

string CDocument::GetTitle() const
{
    return m_title;
}

void CDocument::SetTitle(const string &title)
{
    m_title = title;
}

std::shared_ptr<IParagraph> CDocument::InsertParagraph(const string &text, std::optional<size_t> position)
{
    return std::shared_ptr<IParagraph>();
}

std::shared_ptr<IImage> CDocument::InsertImage(const Path &path, int width, int height, std::optional<size_t> position)
{
    return std::shared_ptr<IImage>();
}

size_t CDocument::GetItemsCount() const
{
    return 0;
}

IDocumentItem CDocument::GetItem(size_t index)
{
    return IDocumentItem();
}

void CDocument::DeleteItem(std::optional<size_t> position)
{

}

CDocument::CDocument()
{
    auto list = make_unique<CDocumentItemList>();
    m_executor = make_unique<CUndoableCommandExecutor>();
    m_list = make_unique<CDocumentItemListWithCommandExecutor>(*list, *m_executor);
}

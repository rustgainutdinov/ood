#include <lw5/editor/content/CParagraph.h>
#include <lw5/editor/content/CImage.h>
#include "CDocument.h"
#include "memory"
#include "lw5/editor/documentItem/CDocumentItemList.h"
#include "lw5/editor/documentItem/CDocumentItem.h"
#include "lw5/editor/command/CUndoableCommandExecutor.h"
#include "lw5/editor/command/documentItem/CDocumentItemListWithCommandExecutor.h"
#include "lw5/editor/command/content/CImageWithCommandExecutor.h"
#include "lw5/editor/command/ICommand.h"
#include "lw5/editor/command/content/CParagraphWithCommandExecutor.h"

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
    auto baseParagraph = make_shared<CParagraph>(text);
    auto paragraph = make_shared<CParagraphWithCommandExecutor>(baseParagraph, *m_executor);
    auto item = make_unique<CDocumentItem>(paragraph);
    m_list->Add(move(item), position);
    return paragraph;
}

std::shared_ptr<IImage> CDocument::InsertImage(const Path &path, int width, int height, std::optional<size_t> position)
{
    auto baseImage = make_shared<CImage>(path, 1, 2);
    auto image = make_shared<CImageWithCommandExecutor>(baseImage, *m_executor);
    auto item = make_unique<CDocumentItem>(nullopt, image);
    m_list->Add(move(item), position);
    return image;
}

size_t CDocument::GetItemsCount() const
{
    return m_list->GetSize();
}

IDocumentItem &CDocument::GetItem(size_t index)
{
    return m_list->Get(index);
}

void CDocument::DeleteItem(size_t position)
{
    m_list->Delete(position);
}

CDocument::CDocument()
{
    auto list = make_shared<CDocumentItemList>();
    m_executor = make_unique<CUndoableCommandExecutor>();
    m_list = make_unique<CDocumentItemListWithCommandExecutor>(list, *m_executor);
}

void CDocument::Undo()
{
    m_executor->Undo();
}

void CDocument::Redo()
{
    m_executor->Redo();
}

bool CDocument::CanUndo()
{
    return m_executor->CanUndo();
}

bool CDocument::CanRedo()
{
    return m_executor->CanRedo();
}

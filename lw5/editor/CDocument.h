#ifndef OOD_CDOCUMENT_H
#define OOD_CDOCUMENT_H


#include "IDocument.h"
#include "vector"

class IDocumentItemList;

class IUndoableCommandExecutor;

class CDocument : public IDocument
{
public:
    CDocument();

    std::shared_ptr<IParagraph>
    InsertParagraph(const std::string &text, std::optional<size_t> position = std::nullopt) override;

    std::shared_ptr<IImage>
    InsertImage(const Path &path, int width, int height, std::optional<size_t> position = std::nullopt) override;

    size_t GetItemsCount() const override;

    IDocumentItem &GetItem(size_t index) override;

    void DeleteItem(size_t position) override;

    std::string GetTitle() const override;

    void SetTitle(const std::string &title) override;

    void Undo() override;

    void Redo() override;

    bool CanUndo() override;

    bool CanRedo() override;

private:
    std::string m_title{};
    std::unique_ptr<IDocumentItemList> m_list;
    std::unique_ptr<IUndoableCommandExecutor> m_executor;

};


#endif //OOD_CDOCUMENT_H

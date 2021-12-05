#ifndef OOD_IDOCUMENT_H
#define OOD_IDOCUMENT_H


#include "string"
#include "optional"
#include "memory"

class IParagraph;

class IImage;

class IDocumentItem;

typedef std::string Path;

class IDocument
{
public:
    virtual std::shared_ptr<IParagraph>
    InsertParagraph(const std::string &text, std::optional<size_t> position= std::nullopt) = 0;

    virtual std::shared_ptr<IImage>
    InsertImage(const Path &path, int width, int height, std::optional<size_t> position = std::nullopt) = 0;

    virtual size_t GetItemsCount() const = 0;

    virtual IDocumentItem &GetItem(size_t index) = 0;

    virtual void DeleteItem(size_t position) = 0;

    virtual std::string GetTitle() const = 0;

    virtual void SetTitle(const std::string &title) = 0;

    virtual void Undo() = 0;

    virtual void Redo() = 0;

    virtual bool CanUndo() = 0;

    virtual bool CanRedo() = 0;

    virtual ~IDocument() = default;
};

#endif

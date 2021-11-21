#include <lw5/editor/documentItem/CDocumentItem.h>
#include "IDocument.h"
#include "vector"

#ifndef OOD_CDOCUMENT_H
#define OOD_CDOCUMENT_H

class CDocument : public IDocument
{
public:
    std::shared_ptr<IParagraph>
    InsertParagraph(const std::string &text, std::optional<size_t> position = std::nullopt) override;

    std::shared_ptr<IImage>
    InsertImage(const Path &path, int width, int height, std::optional<size_t> position = std::nullopt) override;

    size_t GetItemsCount() const override;

    CConstDocumentItem GetItem(size_t index) const override;

    CDocumentItem GetItem(size_t index) override;

    void DeleteItem(size_t index) override;

    std::string GetTitle() const override;

    void SetTitle(const std::string &title) override;

    void Save(const Path &path) const override;

private:
    void InsertDocumentItem(CDocumentItem item, std::optional<size_t> position);

    void AssertPositionInStructureExists(size_t position) const;

    std::vector<CDocumentItem> m_structure{};
    std::string m_title{};
};


#endif //OOD_CDOCUMENT_H

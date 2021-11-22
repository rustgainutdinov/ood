#include "IPictureDraftInfo.h"

class CShape;

class CPictureDraft : public IPictureDraftInfo
{
public:
    void AddShape(std::shared_ptr<CShape> shape);

    std::shared_ptr<CShape> GetShape(int index) const override;

    size_t GetShapeCount() const override;

    ~CPictureDraft() override;

private:
    std::vector<std::shared_ptr<CShape>> m_shapes{};
};
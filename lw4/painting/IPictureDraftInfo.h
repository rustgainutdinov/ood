#include <vector>
#include <memory>

class CShape;

class IPictureDraftInfo
{
public:
    virtual ~IPictureDraftInfo() = default;

    virtual size_t GetShapeCount() = 0;

    virtual std::shared_ptr<CShape> GetShape(int index) = 0;

private:
    std::vector<std::shared_ptr<CShape>> m_shapes{};
};
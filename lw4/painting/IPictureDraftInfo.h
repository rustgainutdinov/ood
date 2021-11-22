#include <vector>
#include <memory>

class CShape;

class IPictureDraftInfo
{
public:
    virtual ~IPictureDraftInfo() = default;

    virtual size_t GetShapeCount() const = 0;

    virtual std::shared_ptr<CShape> GetShape(int index) const = 0;
};
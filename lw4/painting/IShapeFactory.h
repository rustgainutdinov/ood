#include <string>
#include <memory>

class CShape;

class IShapeFactory
{
public:
    virtual ~IShapeFactory() = default;

    virtual std::unique_ptr<CShape> CreateShape(std::string description) const = 0;
};
#include "IShapeFactory.h"

class CShape;

class CShapeFactory : public IShapeFactory
{
public:
    std::unique_ptr<CShape> CreateShape(std::string descriptionStr) const override;

    ~CShapeFactory() override;
};
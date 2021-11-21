#include "Shape.h"

class CEllipse : public CShape
{
public:
    CEllipse(Color color, Point center, int horizontalRadius, int verticalRadius);

    void Draw(ICanvas &canvas) const override;

private:
    Point m_center;
    int m_horizontalRadius;
    int m_verticalRadius;
};
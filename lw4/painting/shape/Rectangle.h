#include "Shape.h"

class CRectangle : public CShape
{
public:
    CRectangle(Color color, Point leftTop, Point rightBottom);

    void Draw(ICanvas &canvas) const override;

private:
    Point m_leftTop;
    Point m_leftBottom{};
    Point m_rightBottom;
    Point m_rightTop{};
};
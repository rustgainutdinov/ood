#include <painting/lib/Point.h>
#include <painting/ICanvas.h>
#include "Rectangle.h"

CRectangle::CRectangle(Color color, Point leftTop, Point rightBottom) :
        m_leftTop(leftTop), m_rightBottom(rightBottom), CShape(color)
{
    m_leftBottom = Point{leftTop.x, rightBottom.y};
    m_rightTop = Point{rightBottom.x, leftTop.y};
}

void CRectangle::Draw(ICanvas &canvas) const
{
    canvas.SetColor(GetColor());
    canvas.DrawLine(m_leftTop, m_leftBottom);
    canvas.DrawLine(m_leftBottom, m_rightBottom);
    canvas.DrawLine(m_rightBottom, m_rightTop);
    canvas.DrawLine(m_rightTop, m_leftTop);
}
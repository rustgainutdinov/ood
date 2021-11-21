#include <painting/lib/Point.h>
#include <painting/ICanvas.h>
#include "Ellipse.h"

CEllipse::CEllipse(Color color, Point center, int horizontalRadius, int verticalRadius) :
        CShape(color), m_center(center), m_horizontalRadius(horizontalRadius), m_verticalRadius(verticalRadius)
{
}

void CEllipse::Draw(ICanvas &canvas) const
{
    canvas.SetColor(GetColor());
    canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
}
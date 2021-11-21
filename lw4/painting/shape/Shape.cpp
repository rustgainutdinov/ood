#include "Shape.h"
#include "lw4/painting/lib/Point.h"
#include "lw4/painting/ICanvas.h"

CShape::CShape(Color color) : m_color(color)
{
}

CShape::~CShape() = default;

Color CShape::GetColor() const
{
    return m_color;
};
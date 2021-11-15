#include "Canvas.h"
#include <string>
#include <functional>
#include <memory>

using namespace std;

class CShape
{
public:
    explicit CShape(Color color) : m_color(color)
    {}

    Color GetColor() const
    {
        return m_color;
    }

    virtual function<void(ICanvas &canvas)> getDrawMethod() const = 0;

protected:
    Color m_color;
};

class CRectangle : public CShape
{
public:
    CRectangle(Color color, Point leftTop, Point rightBottom) :
            m_leftTop(leftTop), m_rightBottom(rightBottom), CShape(color)
    {
        m_leftBottom = Point{leftTop.x, rightBottom.y};
        m_rightTop = Point{rightBottom.x, leftTop.y};
    }

    function<void(ICanvas &canvas)> getDrawMethod() const override
    {
        return [this](ICanvas &canvas) -> void
        {
            canvas.SetColor(m_color);
            canvas.DrawLine(m_leftTop, m_leftBottom);
            canvas.DrawLine(m_leftBottom, m_rightBottom);
            canvas.DrawLine(m_rightBottom, m_rightTop);
            canvas.DrawLine(m_rightTop, m_leftTop);
        };
    }

private:
    Point m_leftTop;
    Point m_leftBottom{};
    Point m_rightBottom;
    Point m_rightTop{};
};

class CEllipse : public CShape
{
public:
    CEllipse(Color color, Point center, int horizontalRadius, int verticalRadius) :
            CShape(color), m_center(center), m_horizontalRadius(horizontalRadius), m_verticalRadius(verticalRadius)
    {
    }

    function<void(ICanvas &canvas)> getDrawMethod() const override
    {
        return [this](ICanvas &canvas) -> void
        {
            canvas.SetColor(m_color);
            canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
        };
    }

private:
    Point m_center;
    int m_horizontalRadius;
    int m_verticalRadius;
};
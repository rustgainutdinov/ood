#include "ImageCanvas.h"

#include <utility>
#include "lib/Color.h"
#include "lib/Point.h"
#include "string"

using namespace std;

cv::Scalar ConvertColorToScalar(Color color)
{
    switch (color)
    {
        case Color::Red:
            return {0, 0, 255};
        case Color::Green:
            return {0, 255, 0};
        case Color::Blue:
            return {255, 0, 0};
        case Color::Yellow:
            return {0, 255, 255};
        default:
            return {0, 0, 0};
    }
}

CImageCanvas::CImageCanvas(string imagePath) : m_imagePath(std::move(imagePath))
{
    m_image = cv::Mat(500, 500, CV_8UC3, cv::Scalar(0, 0, 0));
    m_currentScalarColor = cv::Scalar(0, 0, 0);
}

void CImageCanvas::SetColor(Color color)
{
    m_currentScalarColor = ConvertColorToScalar(color);
}

void CImageCanvas::DrawLine(Point from, Point to)
{
    line(m_image, cv::Point(from.x, from.y), cv::Point(to.x, to.y), m_currentScalarColor, m_lineThickness,
         m_lineType);
}

void CImageCanvas::DrawEllipse(Point center, int horizontalRadius, int verticalRadius)
{
    ellipse(m_image, cv::Point(center.x, center.y),
            cv::Size(horizontalRadius, verticalRadius), 0, 0,
            360, m_currentScalarColor,
            m_lineThickness, m_lineType);
}

CImageCanvas::~CImageCanvas()
{
    cv::imwrite(m_imagePath, m_image);
}
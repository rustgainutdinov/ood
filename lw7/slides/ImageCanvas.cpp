#include "ImageCanvas.h"

#include <utility>
#include <iostream>
#include "Style.h"
#include "Point.h"

using namespace std;

CImageCanvas::CImageCanvas(string imagePath) : m_imagePath(std::move(imagePath))
{
    m_image = cv::Mat(1000, 1000, CV_8UC3, cv::Scalar(0, 0, 0));
    m_currentScalarLineColor = cv::Scalar(255, 0, 0);
    m_currentScalarFillColor = cv::Scalar(0, 255, 0);
}

void CImageCanvas::SetLineColor(Color color)
{
    m_currentScalarLineColor = {color.r, color.g, color.b};
}

void CImageCanvas::BeginFill(Color color)
{
    m_currentScalarFillColor = {color.r, color.g, color.b};
    m_pointsToFill.clear();
}

void CImageCanvas::EndFill()
{
    cv::fillPoly(m_image, m_pointsToFill, m_currentScalarFillColor);
}

void CImageCanvas::MoveTo(Point p)
{
    m_currentPoint = p;
    m_pointsToFill.emplace_back(p.x, p.y);
}

void CImageCanvas::LineTo(Point p)
{
    line(m_image, cv::Point(m_currentPoint.x, m_currentPoint.y), cv::Point(p.x, p.y), m_currentScalarLineColor,
         m_lineThickness,
         m_lineType);
    MoveTo(p);
}

void CImageCanvas::DrawEllipse(Point center, int horizontalRadius, int verticalRadius)
{
    ellipse(m_image, cv::Point(center.x, center.y),
            cv::Size(horizontalRadius, verticalRadius), 0, 0,
            360, m_currentScalarLineColor,
            m_lineThickness, m_lineType);
}

CImageCanvas::~CImageCanvas()
{
    cv::imwrite(m_imagePath, m_image);
}
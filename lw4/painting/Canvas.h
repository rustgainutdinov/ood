#include "lib/Color.h"
#include "lib/Point.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

class ICanvas
{
public:
    virtual ~ICanvas() = default;

    virtual void SetColor(Color color) = 0;

    virtual void DrawLine(Point from, Point to) = 0;

    virtual void DrawEllipse(Point center, int horizontalRadius, int verticalRadius) = 0;
};

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

class CImageCanvas : public ICanvas
{
public:
    CImageCanvas()
    {
        m_image = cv::Mat(500, 500, CV_8UC3, cv::Scalar(0, 0, 0));
        m_currentScalarColor = cv::Scalar(0, 0, 0);
    }

    void SetColor(Color color) override
    {
        m_currentScalarColor = ConvertColorToScalar(color);
    }

    void DrawLine(Point from, Point to) override
    {
        line(m_image, cv::Point(from.x, from.y), cv::Point(to.x, to.y), m_currentScalarColor, m_lineThickness,
             m_lineType);
    }

    void DrawEllipse(Point center, int horizontalRadius, int verticalRadius) override
    {
        ellipse(m_image, cv::Point(center.x, center.y),
                cv::Size(horizontalRadius, verticalRadius), 0, 0,
                360, m_currentScalarColor,
                m_lineThickness, m_lineType);
    }

    ~CImageCanvas() override
    {
        imshow("Output", m_image);
        cv::waitKey(0);
    }

private:
    cv::Scalar m_currentScalarColor;
    cv::Mat m_image;
    static const int m_lineThickness = 2;
    static const int m_lineType = cv::LINE_8;
};
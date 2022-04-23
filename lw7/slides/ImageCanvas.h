#include "ICanvas.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Point.h"

class CImageCanvas : public ICanvas
{
public:
    explicit CImageCanvas(std::string imagePath);

    void SetLineColor(Color color) override;

    void BeginFill(Color color) override;

    void EndFill() override;

    void MoveTo(Point p) override;

    void LineTo(Point p) override;

    void DrawEllipse(Point center, int horizontalRadius, int verticalRadius) override;

    ~CImageCanvas() override;

private:
    cv::Scalar m_currentScalarLineColor;
    cv::Scalar m_currentScalarFillColor;
    cv::Mat m_image;
    static const int m_lineThickness = 2;
    static const int m_lineType = cv::LINE_8;
    std::string m_imagePath;
    std::vector<Point> pointsToFill;
    Point m_currentPoint = {0, 0};
};
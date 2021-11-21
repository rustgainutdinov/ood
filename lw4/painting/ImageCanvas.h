#include "ICanvas.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class CImageCanvas : public ICanvas
{
public:
    explicit CImageCanvas(std::string imagePath);

    void SetColor(Color color) override;

    void DrawLine(Point from, Point to) override;

    void DrawEllipse(Point center, int horizontalRadius, int verticalRadius) override;

    ~CImageCanvas() override;

private:
    cv::Scalar m_currentScalarColor;
    cv::Mat m_image;
    static const int m_lineThickness = 2;
    static const int m_lineType = cv::LINE_8;
    std::string m_imagePath;
};
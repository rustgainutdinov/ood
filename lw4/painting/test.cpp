#include <gtest/gtest.h>
#include <painting/lib/Point.h>
#include "ShapeFactory.h"
#include "ICanvas.h"
#include "shape/Shape.h"
#include "string"
#include <vector>
#include <algorithm>
#include "stdexcept"

using namespace std;

const char *const ellipseElementFormat = "ellipse %m_executor %d %d %d %d";
const char *const lineElementFormat = "line %m_executor %d %d %d %d";

string GetColorFromString(const Color color)
{
    if (color == Color::Green)
    {
        return "green";
    }
    if (color == Color::Red)
    {
        return "red";
    }
    if (color == Color::Blue)
    {
        return "blue";
    }
    if (color == Color::Yellow)
    {
        return "yellow";
    }
    if (color == Color::Pink)
    {
        return "pink";
    }
    if (color == Color::Black)
    {
        return "black";
    }
    throw invalid_argument("Non-existent color");
}

class CMockCanvas : public ICanvas
{
public:
    void SetColor(Color color) override
    {
        m_currentColor = color;
    }

    void DrawLine(Point from, Point to) override
    {
        char s[100];
        auto color = GetColorFromString(m_currentColor);
        sprintf(s, lineElementFormat, color.c_str(), from.x, from.y, to.x, to.y);
        m_drawnElements.emplace_back(s);
    }

    void DrawEllipse(Point center, int horizontalRadius, int verticalRadius) override
    {
        char s[100];
        auto color = GetColorFromString(m_currentColor);
        sprintf(s, ellipseElementFormat, color.c_str(), center.x, center.y, horizontalRadius, verticalRadius);
        m_drawnElements.emplace_back(s);
    }

    vector<string> GetDrawnElements()
    {
        return m_drawnElements;
    }

private:
    vector<string> m_drawnElements{};
    Color m_currentColor{};
};

class TestShapeFactory : public ::testing::Test
{
};

TEST_F(TestShapeFactory, shouldCreateRectangle)
{
    auto canvas = make_unique<CMockCanvas>();
    auto shapeFactory = make_unique<CShapeFactory>();
    auto shape = shapeFactory->CreateShape("rectangle red 20 0 100 150");
    shape->Draw(*canvas);
    auto drawnElements = canvas->GetDrawnElements();
    ASSERT_TRUE(find(drawnElements.begin(), drawnElements.end(), "line red 20 0 20 150") != drawnElements.end());
    ASSERT_TRUE(find(drawnElements.begin(), drawnElements.end(), "line red 20 150 100 150") != drawnElements.end());
    ASSERT_TRUE(find(drawnElements.begin(), drawnElements.end(), "line red 100 150 100 0") != drawnElements.end());
    ASSERT_TRUE(find(drawnElements.begin(), drawnElements.end(), "line red 100 0 20 0") != drawnElements.end());
}

TEST_F(TestShapeFactory, shouldCreateEllipse)
{
    auto canvas = make_unique<CMockCanvas>();
    auto shapeFactory = make_unique<CShapeFactory>();
    auto shape = shapeFactory->CreateShape("ellipse black 20 30 100 150");
    shape->Draw(*canvas);
    auto drawnElements = canvas->GetDrawnElements();
    ASSERT_TRUE(find(drawnElements.begin(), drawnElements.end(), "ellipse black 20 30 100 150") != drawnElements.end());
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
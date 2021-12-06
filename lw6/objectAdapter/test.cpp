#include <gtest/gtest.h>
#include "main.cpp"

class TestICanvas : public ::testing::Test
{
};

class CTestCanvas : public graphics_lib::CCanvas
{
public:
    void MoveTo(int x, int y) override
    {
        graphics_lib::CCanvas::MoveTo(x, y);
        m_actions.push_back("move " + to_string(x) + " " + to_string(y));
    }

    void LineTo(int x, int y) override
    {
        graphics_lib::CCanvas::LineTo(x, y);
        m_actions.push_back("line " + to_string(x) + " " + to_string(y));
    }

    vector<string> GetDrawnElements()
    {
        return m_actions;
    }

private:
    vector<string> m_actions{};
};

TEST_F(TestICanvas, shouldDrawLines)
{
    graphics_lib::CCanvas simpleCanvas;
    TestDrawLinesOnCanvas()
}

void DrawLinesOnCanvas(graphics_lib::ICanvas &canvas)
{
    canvas.MoveTo(1, 1);
    canvas.LineTo(1, 2);
    canvas.LineTo(2, 2);
    canvas.LineTo(1, 1);
    canvas.MoveTo(3, 3);
    canvas.LineTo(4, 4);
}
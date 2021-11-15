#include <gtest/gtest.h>
#include "Designer.h"
#include "string"

using namespace std;

template<typename Base, typename T>
inline bool instanceof(const T *)
{
    return is_base_of<Base, T>::value;
}

class CMockCanvas : public ICanvas
{
public:
    void SetColor(Color color) override
    {
    }

    void DrawLine(Point from, Point to) override
    {
        m_linePoints.push_back(vector<Point>{from, to});
    }

    void DrawEllipse(Point center, int horizontalRadius, int verticalRadius) override
    {

    }

    bool BelongsToDrawnLine(Point point)
    {
        for (auto &m_linePoint: m_linePoints)
        {
            if (((point.x - m_linePoint[0].x) * (point.y - m_linePoint[1].y)) ==
                ((point.x - m_linePoint[1].x) * (point.y - m_linePoint[0].y)))
            {
                cout << ((point.x - m_linePoint[0].x) * (point.y - m_linePoint[1].y))
                     << ", " << ((point.x - m_linePoint[1].x) * (point.y - m_linePoint[0].y)) << endl;
                return true;
            }
        }
        return false;
    }

    vector<vector<Point>> m_linePoints{};
};

class TestShapeFactory : public ::testing::Test
{
};

TEST_F(TestShapeFactory, shouldCreateRectangle)
{
    auto canvas = make_unique<CMockCanvas>();
    unique_ptr<IShapeFactory> shapeFactory = make_unique<CShapeFactory>();
    auto shape = shapeFactory->CreateShape("rectangle red 0 0 100 100");
    auto draw = shape->getDrawMethod();
    draw(*canvas);
    ASSERT_TRUE(canvas->BelongsToDrawnLine({50, 0}));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
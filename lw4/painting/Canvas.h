#include "lib/Color.h"
#include "lib/Point.h"

class ICanvas
{
public:
    virtual void SetColor(Color color) = 0;

    virtual void DrawLine(Point from, Point to) = 0;

    virtual void DrawEllipse(Point center, int width, int height) = 0;
};
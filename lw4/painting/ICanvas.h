#include "lib/Color.h"

class Point;

#ifndef OOD_ICANVAS_H
#define OOD_ICANVAS_H

class ICanvas
{
public:
    virtual ~ICanvas() = default;

    virtual void SetColor(Color color) = 0;

    virtual void DrawLine(Point from, Point to) = 0;

    virtual void DrawEllipse(Point center, int horizontalRadius, int verticalRadius) = 0;
};

#endif //OOD_ICANVAS_H
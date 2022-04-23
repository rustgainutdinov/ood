#ifndef OOD_ICANVAS_H
#define OOD_ICANVAS_H

#include "Style.h"

class Point;

class ICanvas
{
public:
    virtual ~ICanvas() = default;

    virtual void SetLineColor(Color color) = 0;

    virtual void BeginFill(Color color) = 0;

    virtual void MoveTo(Point p) = 0;

    virtual void LineTo(Point p) = 0;

    virtual void DrawEllipse(Point center, int horizontalRadius, int verticalRadius) = 0;

    virtual void FillEllipse(Point center, int horizontalRadius, int verticalRadius) = 0;

    virtual void EndFill() = 0;
};

#endif //OOD_ICANVAS_H
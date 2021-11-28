#include "lw4/painting/lib/Color.h"

#ifndef OOD_SHAPE_H
#define OOD_SHAPE_H

class ICanvas;

class CShape
{
public:
    virtual ~CShape();

    explicit CShape(Color color);

    virtual void Draw(ICanvas &canvas) const = 0;

protected:
    Color GetColor() const;

private:
    Color m_color;
};

#endif //OOD_SHAPE_H
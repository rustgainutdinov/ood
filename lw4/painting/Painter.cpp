#include "Painter.h"
#include "IPictureDraftInfo.h"
#include "ICanvas.h"
#include "shape/Shape.h"

CPainter::~CPainter() = default;

void CPainter::DrawPicture(const IPictureDraftInfo &draft, ICanvas &canvas)
{
    for (int i = 0; i < draft.GetShapeCount(); i++)
    {
        auto shape = draft.GetShape(i);
        shape->Draw(canvas);
    }
}
#include "Painter.h"
#include <iostream>
#include <memory>

class IShapeFactory;

class ICanvas;

class CDesigner : CPainter
{
public:
    ~CDesigner();

    explicit CDesigner(IShapeFactory &factory);

    std::unique_ptr<IPictureDraftInfo> CreatePicture(std::istream &stream, ICanvas &canvas);

private:
    IShapeFactory &m_factory;
};
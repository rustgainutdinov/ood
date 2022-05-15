//
// Created by Рустам Гайнутдинов on 18.04.2022.
//

#ifndef OOD_ISHAPE_H
#define OOD_ISHAPE_H

#include "RectFrame.h"
#include "Style.h"
#include "ICanvas.h"
#include <memory>
#include "optional"

class IGroup;

class IShape
{
public:
    virtual ~IShape() = default;

    virtual int Id() const = 0;

    virtual std::optional<RectFrame> GetFrame() const = 0;

    virtual void SetFrame(RectFrame rect) = 0;

    //сделать возврат мутабельной структуры
    virtual std::optional<Style> GetLineStyle() const = 0;

    virtual void SetLineStyle(Style style) = 0;

    virtual std::optional<Style> GetFillStyle() const = 0;

    virtual void SetFillStyle(Style style) = 0;

    virtual void Draw(ICanvas &canvas) const = 0;

    virtual IGroup *GetGroup() const = 0;
};

#endif //OOD_ISHAPE_H

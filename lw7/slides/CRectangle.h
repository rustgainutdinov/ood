//
// Created by Рустам Гайнутдинов on 18.04.2022.
//

#ifndef OOD_CRECTANGLE_H
#define OOD_CRECTANGLE_H


#include "CShape.h"

class CRectangle : public CShape
{
public:
    explicit CRectangle(int i) : CShape(i)
    {}

    void Draw(ICanvas &canvas) const override;
};


#endif //OOD_CRECTANGLE_H

//
// Created by Рустам Гайнутдинов on 23.04.2022.
//

#ifndef OOD_CELLIPSE_H
#define OOD_CELLIPSE_H

#include "CShape.h"

class CEllipse : public CShape
{
public:
    explicit CEllipse(int i) : CShape(i)
    {}

    void Draw(ICanvas &canvas) const override;
};


#endif //OOD_CELLIPSE_H

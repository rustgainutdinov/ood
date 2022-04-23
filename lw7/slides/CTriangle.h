//
// Created by Рустам Гайнутдинов on 23.04.2022.
//

#ifndef OOD_CTRIANGLE_H
#define OOD_CTRIANGLE_H



#include "CShape.h"

class CTriangle : public CShape
{
public:
    explicit CTriangle(int i) : CShape(i)
    {}

    void Draw(ICanvas &canvas) const override;
};


#endif //OOD_CTRIANGLE_H

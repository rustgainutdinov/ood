//
// Created by Рустам Гайнутдинов on 18.04.2022.
//

#include "CShape.h"
#include "IGroup.h"
#include <iostream>

void CShape::SetFrame(RectFrame rect)
{
    m_rect = rect;
}

std::optional<RectFrame> CShape::GetFrame() const
{
    return m_rect;
}

std::optional<Style> CShape::GetLineStyle() const
{
    return m_lineStyle;
}

void CShape::SetLineStyle(Style style)
{
    m_lineStyle = style;
}

std::optional<Style> CShape::GetFillStyle() const
{
    return m_fillStyle;
}

void CShape::SetFillStyle(Style style)
{
    m_fillStyle = style;
}

IGroup *CShape::GetGroup() const
{
    return nullptr;
}

int CShape::Id() const
{
    return m_id;
}

CShape::CShape(int id)
{
    m_id = id;
}

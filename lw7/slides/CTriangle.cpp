//
// Created by Рустам Гайнутдинов on 23.04.2022.
//

#include "CTriangle.h"

void CTriangle::Draw(ICanvas &canvas) const
{
    if (m_lineStyle.isEnabled)
    {
        canvas.SetLineColor(m_lineStyle.color);
    }
    if (m_fillStyle.isEnabled)
    {
        canvas.BeginFill(m_fillStyle.color);
    }
    canvas.MoveTo({m_rect.leftTop.x + (m_rect.rightBottom.x - m_rect.leftTop.x) / 2, m_rect.leftTop.y});
    canvas.LineTo({.x =  m_rect.leftTop.x, .y =  m_rect.rightBottom.y});
    canvas.LineTo(m_rect.rightBottom);
    canvas.LineTo({m_rect.leftTop.x + (m_rect.rightBottom.x - m_rect.leftTop.x) / 2, m_rect.leftTop.y});
    if (m_fillStyle.isEnabled)
    {
        canvas.EndFill();
    }
}
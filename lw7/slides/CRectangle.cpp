//
// Created by Рустам Гайнутдинов on 18.04.2022.
//

#include "CRectangle.h"

void CRectangle::Draw(ICanvas &canvas) const
{
    if (m_lineStyle.isEnabled)
    {
        canvas.SetLineColor(m_lineStyle.color);
    }
    if (m_fillStyle.isEnabled)
    {
        canvas.BeginFill(m_fillStyle.color);
    }
    canvas.MoveTo(m_rect.leftTop);
    canvas.LineTo({.x =  m_rect.leftTop.x, .y =  m_rect.rightBottom.y});
    canvas.LineTo(m_rect.rightBottom);
    canvas.LineTo({.x =  m_rect.rightBottom.x, .y =  m_rect.leftTop.y});
    canvas.LineTo(m_rect.leftTop);
    if (m_fillStyle.isEnabled)
    {
        canvas.EndFill();
    }
}

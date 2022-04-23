//
// Created by Рустам Гайнутдинов on 23.04.2022.
//

#include "CEllipse.h"

void CEllipse::Draw(ICanvas &canvas) const
{
    if (m_lineStyle.isEnabled)
    {
        canvas.SetLineColor(m_lineStyle.color);
    }
    if (m_fillStyle.isEnabled)
    {
        canvas.BeginFill(m_fillStyle.color);
    }
    canvas.DrawEllipse({m_rect.leftTop.x + (m_rect.rightBottom.x - m_rect.leftTop.x) / 2,
                        m_rect.leftTop.y + (m_rect.rightBottom.y - m_rect.leftTop.y) / 2},
                       (m_rect.rightBottom.x - m_rect.leftTop.x) / 2,
                       (m_rect.rightBottom.y - m_rect.leftTop.y) / 2);
    canvas.FillEllipse({m_rect.leftTop.x + (m_rect.rightBottom.x - m_rect.leftTop.x) / 2,
                        m_rect.leftTop.y + (m_rect.rightBottom.y - m_rect.leftTop.y) / 2},
                       (m_rect.rightBottom.x - m_rect.leftTop.x) / 2,
                       (m_rect.rightBottom.y - m_rect.leftTop.y) / 2);
}

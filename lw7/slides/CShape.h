//
// Created by Рустам Гайнутдинов on 18.04.2022.
//

#ifndef OOD_CSHAPE_H
#define OOD_CSHAPE_H


#include "IShape.h"

class CShape : public IShape
{
public:
    explicit CShape(int id);

    int Id() const override;

    std::optional<RectFrame> GetFrame() const override;

    void SetFrame(RectFrame rect) override;

    std::optional<Style> GetLineStyle() const override;

    void SetLineStyle(Style style) override;

    std::optional<Style> GetFillStyle() const override;

    void SetFillStyle(Style style) override;

    IGroup *GetGroup() const override;

protected:
    RectFrame m_rect = {0,
                        0,
                        100,
                        100};
    Style m_lineStyle = {true, {255, 0, 0}};
    Style m_fillStyle = {true, {0, 255, 0}};
    int m_id;
};


#endif //OOD_CSHAPE_H

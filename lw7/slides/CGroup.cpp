//
// Created by Рустам Гайнутдинов on 19.04.2022.
//

#include "CGroup.h"

#include <utility>
#include <iostream>

std::optional<RectFrame> CGroup::GetFrame() const
{
    if (GetShapesCount() == 0)
    {
        return std::nullopt;
    }
    RectFrame result = {0, 0, 0, 0};
    for (auto &shape : m_shapes)
    {
        if (shape->GetFrame()->leftTop.x < result.leftTop.x)
        {
            result.leftTop.x = shape->GetFrame()->leftTop.x;
        }
        if (shape->GetFrame()->leftTop.y < result.leftTop.y)
        {
            result.leftTop.y = shape->GetFrame()->leftTop.y;
        }
        if (shape->GetFrame()->rightBottom.x > result.rightBottom.x)
        {
            result.rightBottom.x = shape->GetFrame()->rightBottom.x;
        }
        if (shape->GetFrame()->rightBottom.y > result.rightBottom.y)
        {
            result.rightBottom.y = shape->GetFrame()->rightBottom.y;
        }
    }
    return result;
}

void CGroup::SetFrame(RectFrame rect)
{
    auto currentFrame = GetFrame();
    if (currentFrame == std::nullopt)
    {
        return;
    }
    double widthMultiplier =
            (rect.rightBottom.x - rect.leftTop.x) / (currentFrame->rightBottom.x - currentFrame->leftTop.x);
    double heightMultiplier =
            (rect.rightBottom.y - rect.leftTop.y) / (currentFrame->rightBottom.y - currentFrame->leftTop.y);
    double leftTopXShift = rect.leftTop.x - currentFrame->leftTop.x;
    double leftTopYShift = rect.leftTop.y - currentFrame->leftTop.y;
    for (auto &shape : m_shapes)
    {
        double leftTopX = shape->GetFrame()->leftTop.x * widthMultiplier + leftTopXShift;
        double leftTopY = shape->GetFrame()->leftTop.y * heightMultiplier + leftTopYShift;
        double rightBottomX =
                leftTopX + (shape->GetFrame()->rightBottom.x - shape->GetFrame()->leftTop.x) *
                           widthMultiplier;
        double rightBottomY =
                leftTopY + (shape->GetFrame()->rightBottom.y - shape->GetFrame()->leftTop.y) *
                           heightMultiplier;
        shape->SetFrame({leftTopX, leftTopY, rightBottomX, rightBottomY});
    }
}

std::optional<Style> CGroup::GetLineStyle() const
{
    if (GetShapesCount() == 0)
    {
        return std::nullopt;
    }
    for (auto &shape : m_shapes)
    {
        if (!CGroup::AreStylesEqual(shape->GetLineStyle(), m_shapes.at(0)->GetLineStyle()))
        {
            return std::nullopt;
        }
    }
    return m_shapes.at(0)->GetLineStyle();
}

void CGroup::SetLineStyle(Style style)
{
    for (auto &shape : m_shapes)
    {
        shape->SetLineStyle(style);
    }
}

std::optional<Style> CGroup::GetFillStyle() const
{
    if (GetShapesCount() == 0)
    {
        return std::nullopt;
    }
    for (auto &shape : m_shapes)
    {
        if (!CGroup::AreStylesEqual(shape->GetFillStyle(), m_shapes.at(0)->GetFillStyle()))
        {
            return std::nullopt;
        }
    }
    return m_shapes.at(0)->GetFillStyle();
}

int CGroup::GetShapesCount() const
{
    return m_shapes.size();
}

std::shared_ptr<IShape> CGroup::GetShape(int index) const
{
    for (auto shape: m_shapes)
    {
        if (shape->Id() == index)
        {
            return shape;
        }
    }
    throw std::invalid_argument("not found");
}

void CGroup::InsertShape(std::shared_ptr<IShape> shape)
{
    m_shapes.push_back(std::move(shape));
}

void CGroup::RemoveShape(int index)
{
    for (int i = 0; i < m_shapes.size(); i++)
    {
        if (m_shapes[i]->Id() == index)
        {
            m_shapes.erase(m_shapes.begin() + i);
        }
    }
}

void CGroup::SetFillStyle(Style style)
{
    for (auto &shape : m_shapes)
    {
        shape->SetFillStyle(style);
    }
}

void CGroup::Draw(ICanvas &canvas) const
{
    for (auto &shape : m_shapes)
    {
        shape->Draw(canvas);
    }
}

bool CGroup::AreStylesEqual(std::optional<Style> s1, std::optional<Style> s2)
{
    if (s1 == std::nullopt || s2 == std::nullopt)
    {
        return false;
    }
    if ((*s1).isEnabled != (*s2).isEnabled || (*s1).color.r != (*s2).color.r || (*s1).color.g != (*s2).color.g ||
        (*s1).color.b != (*s2).color.b)
    {
        return false;
    }
    return true;
}

IGroup *CGroup::GetGroup() const
{
    return (IGroup *) this;
}

bool CGroup::IsShapeThere(int index) const
{
    for (const auto &shape : m_shapes)
    {
        if (shape->Id() == index)
        {
            return true;
        }

    }
    return false;
}

bool CGroup::IsShapeInChildrenTree(int index) const
{
    for (auto &shape : m_shapes)
    {
        if (shape->Id() == index)
        {
            return true;
        }
        auto shapeGroup = shape->GetGroup();
        if (shapeGroup != nullptr && shapeGroup->IsShapeInChildrenTree(index))
        {
            return true;
        }
    }
    return false;
}

CGroup::CGroup(int id)
{
    m_id = id;
}

int CGroup::Id() const
{
    return m_id;
}

std::vector<std::shared_ptr<IShape>> CGroup::GetShapes() const
{
    return m_shapes;
}

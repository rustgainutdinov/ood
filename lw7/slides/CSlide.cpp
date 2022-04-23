//
// Created by Рустам Гайнутдинов on 20.04.2022.
//

#include "CSlide.h"

#include <utility>
#include <iostream>
#include "IGroup.h"
#include "CGroup.h"

int CSlide::GetShapesCount() const
{
    return m_root->GetShapesCount();
}

std::shared_ptr<IShape> CSlide::GetShape(int index) const
{
    return GetShapeFromTree(m_root, index);
}

void CSlide::InsertShape(std::shared_ptr<IShape> shape, std::optional<int> index)
{
    if (index == std::nullopt)
    {
        m_root->InsertShape(shape);
        return;
    }
    auto parentShape = GetShapeFromTree(m_root, *index);
    if (parentShape->GetGroup() == nullptr)
    {
        throw std::invalid_argument("parent element is not a group");
    }
    parentShape->GetGroup()->InsertShape(shape);
}

void CSlide::RemoveShape(int index)
{
    auto parent = GetShapeParent(m_root, index);
    if (parent == std::nullopt)
    {
        throw std::invalid_argument("parent is not found");
    }
    (*parent)->GetGroup()->RemoveShape(index);
}

void CSlide::GroupShapes(const std::vector<int> &shapeIds, int groupId)
{
    auto commonParent = GetCommonParent(shapeIds);
    auto group = std::make_unique<CGroup>(groupId);
    for (auto &shapeId : shapeIds)
    {
        auto shape = commonParent->GetGroup()->GetShape(shapeId);
        commonParent->GetGroup()->RemoveShape(shapeId);
        group->InsertShape(shape);
    }
    commonParent->GetGroup()->InsertShape(std::move(group));
}

std::shared_ptr<IShape> CSlide::GetShapeFromTree(std::shared_ptr<IShape> root, int index) const
{
    auto parent = GetShapeParent(std::move(root), index);
    if (parent == std::nullopt)
    {
        throw std::invalid_argument("root is not found");
    }
    return (*parent)->GetGroup()->GetShape(index);
}

std::optional<std::shared_ptr<IShape>>
CSlide::GetShapeParent(std::shared_ptr<IShape> root, int index) const
{
    if (root->GetGroup() == nullptr)
    {
        return std::nullopt;
    }
    if (root->GetGroup()->IsShapeThere(index))
    {
        return root;
    }
    for (auto &shapeItem : root->GetGroup()->GetShapes())
    {
        auto parent = GetShapeParent(shapeItem, index);
        if (parent != std::nullopt)
        {
            return parent;
        }
    }
    return std::nullopt;
}

std::shared_ptr<IShape>
CSlide::GetCommonParent(const std::vector<int> &shapeIds) const
{
    if (shapeIds.empty())
    {
        throw std::invalid_argument("shape ids list must not be empty");
    }
    auto commonParent = GetShapeParent(m_root, shapeIds[0]);
    if (commonParent == std::nullopt)
    {
        throw std::invalid_argument("commonParent is not found");
    }
    for (int i = 1; i < shapeIds.size(); i++)
    {
        if (!(*commonParent)->GetGroup()->IsShapeThere(shapeIds[i]))
        {
            throw std::invalid_argument("commonParent must be common");
        }
    }
    return *commonParent;
}

CSlide::CSlide()
{
    m_root = std::make_unique<CGroup>(0);
}

void CSlide::Draw(ICanvas &canvas) const
{
    m_root->Draw(canvas);
}

std::shared_ptr<IShape> CSlide::GetRoot() const
{
    return m_root;
}

std::vector<std::shared_ptr<IShape>> CSlide::GetShapes() const
{
    return m_root->GetShapes();
}

//
// Created by Рустам Гайнутдинов on 20.04.2022.
//

#ifndef OOD_CSLIDE_H
#define OOD_CSLIDE_H

#include "IShape.h"
#include "IGroup.h"
#include <vector>

class CSlide
{
public:
    CSlide();

    int GetShapesCount() const;

    std::shared_ptr<IShape> GetShape(int index) const;

    std::shared_ptr<IShape> GetRoot() const;

    std::vector<std::shared_ptr<IShape>> GetShapes() const;

    void InsertShape(std::shared_ptr<IShape> shape, std::optional<int> index);

    void RemoveShape(int index);

    void GroupShapes(const std::vector<int> &shapeIds, int groupId);

    void Draw(ICanvas &canvas) const;

private:
    std::shared_ptr<IGroup> m_root;

    std::optional<std::shared_ptr<IShape>> GetShapeParent(std::shared_ptr<IShape> root, int index) const;

    std::shared_ptr<IShape> GetShapeFromTree(std::shared_ptr<IShape> root, int index) const;

    std::shared_ptr<IShape> GetCommonParent(const std::vector<int> &shapeIds) const;
};


#endif //OOD_CSLIDE_H

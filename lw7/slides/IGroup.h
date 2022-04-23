//
// Created by Рустам Гайнутдинов on 18.04.2022.
//

#ifndef OOD_IGROUP_H
#define OOD_IGROUP_H

#include "IShape.h"
#include <vector>

class IGroup : public IShape
{
public:
    virtual ~IGroup() = default;

    virtual int GetShapesCount() const = 0;

    virtual std::shared_ptr<IShape> GetShape(int index) const = 0;

    virtual void InsertShape(std::shared_ptr<IShape> shape) = 0;

    virtual void RemoveShape(int index) = 0;

    virtual bool IsShapeThere(int index) const = 0;

    virtual bool IsShapeInChildrenTree(int index) const = 0;

    virtual std::vector<std::shared_ptr<IShape>> GetShapes() const = 0;
};

#endif //OOD_IGROUP_H

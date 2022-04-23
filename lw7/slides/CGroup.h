//
// Created by Рустам Гайнутдинов on 19.04.2022.
//

#ifndef OOD_CGROUP_H
#define OOD_CGROUP_H


#include "IGroup.h"
#include "map"

class CGroup : public IGroup
{
public:
    explicit CGroup(int i);

    int Id() const override;

    std::optional<RectFrame> GetFrame() const override;

    void SetFrame(RectFrame rect) override;

    std::optional<Style> GetLineStyle() const override;

    void SetLineStyle(Style style) override;

    std::optional<Style> GetFillStyle() const override;

    void SetFillStyle(Style style) override;

    void Draw(ICanvas &canvas) const override;

    int GetShapesCount() const override;

    std::shared_ptr<IShape> GetShape(int index) const override;

    void InsertShape(std::shared_ptr<IShape> shape) override;

    void RemoveShape(int index) override;

    bool IsShapeThere(int index) const override;

    IGroup *GetGroup() const override;

    bool IsShapeInChildrenTree(int index) const override;

    std::vector<std::shared_ptr<IShape>> GetShapes() const override;


private:
    std::vector<std::shared_ptr<IShape>> m_shapes{};

    static bool AreStylesEqual(std::optional<Style> s1, std::optional<Style> s2);

    int m_id;
};


#endif //OOD_CGROUP_H

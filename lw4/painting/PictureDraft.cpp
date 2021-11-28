#include "PictureDraft.h"
#include <utility>
#include "memory"
#include "vector"

using namespace std;

CPictureDraft::~CPictureDraft() = default;

void CPictureDraft::AddShape(std::shared_ptr<CShape> shape)
{
    return m_shapes.push_back(move(shape));
}

shared_ptr<CShape> CPictureDraft::GetShape(int index) const
{
    return m_shapes[index];
}

size_t CPictureDraft::GetShapeCount() const
{
    return m_shapes.size();
}

#include "Designer.h"
#include "PictureDraft.h"
#include "ShapeFactory.h"
#include "shape/Shape.h"

using namespace std;

CDesigner::~CDesigner() = default;

CDesigner::CDesigner(IShapeFactory &factory)
        : m_factory(factory)
{
}

unique_ptr<IPictureDraftInfo> CDesigner::CreatePicture(istream &stream, ICanvas &canvas)
{
    auto pictureDraft = make_unique<CPictureDraft>();
    string s;
    while (getline(stream, s))
    {
        pictureDraft->AddShape(m_factory.CreateShape(s));
    }
    DrawPicture(*pictureDraft, canvas);
    return pictureDraft;
}
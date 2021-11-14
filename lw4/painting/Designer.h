#include "ShapeFactory.h"
#include "PictureDraft.h"
#include <sstream>
#include <iostream>

using namespace std;

class IDesigner
{
public:
    virtual unique_ptr<CPictureDraft> CreateDraft(istream &stream) = 0;
};

class CDesigner : IDesigner
{
public:
    explicit CDesigner(unique_ptr<CShapeFactory> factory) : m_factory(move(factory))
    {}

    unique_ptr<CPictureDraft> CreateDraft(istream &stream) override
    {
        auto pictureDraft = make_unique<CPictureDraft>();
        string s;
        while (getline(stream, s))
        {
            pictureDraft->AddShape(m_factory->CreateShape(s));
        }
        return pictureDraft;
    }

private:
    unique_ptr<CShapeFactory> m_factory;
};
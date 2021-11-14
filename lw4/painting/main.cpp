#include "Designer.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fs;
    fs.open("/home/rustamgainutdinov/CLionProjects/ood/lw4/painting/files/instructions.txt", ios::in);
    auto factory = make_unique<CShapeFactory>();
    auto designer = make_unique<CDesigner>(move(factory));
    auto draft = designer->CreateDraft(fs);
    unique_ptr<ICanvas> canvas = make_unique<CImageCanvas>();
    for (int i = 0; i < draft->GetShapeCount(); i++)
    {
        auto shape = draft->GetShape(i);
        auto draw = shape->getDrawMethod();
        draw(*canvas);
    }
    return 0;
}
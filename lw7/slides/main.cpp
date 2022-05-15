//
// Created by Рустам Гайнутдинов on 18.04.2022.
//

#include "ImageCanvas.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CEllipse.h"
#include "CGroup.h"
#include "CSlide.h"
#include "memory"
#include "iostream"

using namespace std;

int main()
{
    auto canvas = make_unique<CImageCanvas>("./files/a.jpg");
    auto slide = make_unique<CSlide>();
    auto rect = make_shared<CRectangle>(3);
    rect->SetLineStyle({true, 255, 255, 0});
    auto triangle = make_shared<CTriangle>(4);
    triangle->SetFillStyle({false, 0, 0, 255});
    triangle->SetFrame({50, 50, 200, 150});
    auto ellipse = make_shared<CEllipse>(5);
    ellipse->SetFillStyle({true, 255, 0, 255});
    ellipse->SetFrame({150, 150, 250, 250});
    slide->InsertShape(rect, nullopt);
    slide->InsertShape(triangle, nullopt);
    slide->InsertShape(ellipse, nullopt);
    slide->GroupShapes(std::vector<int>{3, 4, 5}, 0);
    auto root = slide->GetRoot();
    slide->Draw(*canvas);
    root->SetFrame({200, 200, 900, 300});
    root->SetLineStyle({true, {0, 255, 255}});
    root->SetFillStyle({true, {255, 255, 255}});
    slide->Draw(*canvas);
}
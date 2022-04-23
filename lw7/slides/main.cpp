//
// Created by Рустам Гайнутдинов on 18.04.2022.
//

#include "ImageCanvas.h"
#include "CRectangle.h"
#include "CGroup.h"
#include "CSlide.h"
#include "memory"
#include "iostream"

using namespace std;

int main()
{
    auto canvas = make_unique<CImageCanvas>(
            "/Users/rustamgajnutdinov/Documents/study/ood/lw7/slides/files/a.jpg");

    auto slide = make_unique<CSlide>();
    auto rect = make_shared<CRectangle>(3);
    rect->SetLineStyle({true, 255, 255, 0});
    auto rect2 = make_shared<CRectangle>(4);
    rect2->SetFrame({50, 50, 200, 150});
    slide->InsertShape(rect, nullopt);
    slide->InsertShape(rect2, nullopt);
    slide->GroupShapes(std::vector<int>{3, 4}, 0);
    auto root = slide->GetRoot();
    slide->Draw(*canvas);
    root->SetFrame({200, 200, 900, 300});
    root->SetLineStyle({true, {0, 255, 255}});
    slide->Draw(*canvas);
}
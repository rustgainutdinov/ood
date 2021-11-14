#include "Designer.h"
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>

// Drawing shapes
#include <opencv2/imgproc.hpp>

#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

//using namespace std;

//int main()
//{
//    ifstream fs;
//    fs.open("/home/rustamgainutdinov/CLionProjects/ood/lw4/painting/instructions.txt", ios::in);
//    auto factory = make_unique<CShapeFactory>();
//    auto designer = make_unique<CDesigner>(move(factory));
//    auto draft = designer->CreateDraft(fs);
//    cout << "count: " << draft->GetShapeCount() << endl;
//}

using namespace cv;

int main(){
    Mat img=imread("myImage.jpg");

    Rect r=Rect(10,20,40,60);
//create a Rect with top-left vertex at (10,20), of width 40 and height 60 pixels.

    rectangle(img,r,Scalar(255,0,0),1,8,0);
//draw the rect defined by r with line thickness 1 and Blue color

    imwrite("myImageWithRect.jpg",img);


    return
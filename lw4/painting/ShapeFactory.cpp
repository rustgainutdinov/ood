#include <vector>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "ShapeFactory.h"
#include <painting/lib/Color.h>
#include <painting/lib/Point.h>
#include <painting/shape/Rectangle.h>
#include <painting/shape/Ellipse.h>

using namespace std;

vector<string> SplitByChar(const string &str, char ch)
{
    stringstream stringStream(str);
    vector<string> arr;
    string segment;
    while (getline(stringStream, segment, ch))
    {
        arr.push_back(segment);
    }
    return arr;
}

Color GetColorFromString(const string &str)
{
    if (str == "green")
    {
        return Color::Green;
    }
    if (str == "red")
    {
        return Color::Red;
    }
    if (str == "blue")
    {
        return Color::Blue;
    }
    if (str == "yellow")
    {
        return Color::Yellow;
    }
    if (str == "pink")
    {
        return Color::Pink;
    }
    if (str == "black")
    {
        return Color::Black;
    }
    throw invalid_argument("Non-existent color");
}

CShapeFactory::~CShapeFactory() = default;

unique_ptr<CShape> CShapeFactory::CreateShape(string descriptionStr) const
{
    vector<string> description = SplitByChar(descriptionStr, ' ');
    string name = description[0];
    Color color = GetColorFromString(description[1]);
    if (name == "rectangle")
    {
        return make_unique<CRectangle>(color, Point{stoi(description[2]), stoi(description[3])},
                                       Point{stoi(description[4]), stoi(description[5])});
    }
    if (name == "ellipse")
    {
        return make_unique<CEllipse>(color, Point{stoi(description[2]), stoi(description[3])},
                                     stoi(description[4]), stoi(description[5]));
    }
    throw invalid_argument("Non-existent shape");
}
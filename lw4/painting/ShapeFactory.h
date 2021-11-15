#include "Shapes.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <sstream>

using namespace std;

vector<string> splitByChar(const string &str, char ch)
{
    stringstream stringStream(str);
    vector<string> arr;
    std::string segment;
    while (getline(stringStream, segment, ch))
    {
        arr.push_back(segment);
    }
    return arr;
}

Color getColorFromString(const string &str)
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

class IShapeFactory
{
public:
    virtual ~IShapeFactory() = default;

    virtual unique_ptr<CShape> CreateShape(string description) const = 0;
};

class CShapeFactory : public IShapeFactory
{
public:
    unique_ptr<CShape> CreateShape(string descriptionStr) const override
    {
        vector<string> description = splitByChar(descriptionStr, ' ');
        string name = description[0];
        Color color = getColorFromString(description[1]);
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
};
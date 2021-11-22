#include "ShapeFactory.h"
#include "Designer.h"
#include "Client.h"

using namespace std;

int main()
{
    auto factory = make_unique<CShapeFactory>();
    auto designer = make_unique<CDesigner>(*factory);
    auto painter = make_unique<CPainter>();
    auto client = make_unique<CClient>(*designer, *painter);
    client->GetPicture();
    return 0;
}
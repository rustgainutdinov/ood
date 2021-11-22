#include <fstream>
#include "Client.h"
#include "Designer.h"
#include "ICanvas.h"
#include "IPictureDraftInfo.h"
#include "ImageCanvas.h"

using namespace std;

CClient::~CClient() = default;

CClient::CClient(CDesigner &designer, CPainter &painter) : m_designer(designer), m_painter(painter)
{}

void CClient::GetPicture()
{
    ifstream fs;
//    fs.open("/home/rustamgainutdinov/CLionProjects/ood/lw4/painting/files/instructions.txt", ios::in);
//    unique_ptr<ICanvas> canvas = make_unique<CImageCanvas>(
//            "/home/rustamgainutdinov/CLionProjects/ood/lw4/painting/files/a.jpg");
    fs.open("/Users/rustamgajnutdinov/Documents/study/ood/lw4/painting/files/instructions.txt", ios::in);
    unique_ptr<ICanvas> canvas = make_unique<CImageCanvas>(
            "/Users/rustamgajnutdinov/Documents/study/ood/lw4/painting/files/a.jpg");
    m_designer.CreatePicture(fs, *canvas);
    auto pictureDraft = m_designer.CreatePicture(fs, *canvas);
}
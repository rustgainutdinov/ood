//
// Created by rustam.gainutdinov on 27.11.2021.
//

#include "CResizeImageCommand.h"
#include "lw5/editor/content/IImageResource.h"

using namespace std;

CResizeImageCommand::CResizeImageCommand(shared_ptr<IImageResource> image, int width, int height) :
        m_image(move(image)), m_width(width),
        m_height(height),
        m_baseWidth(m_image->GetWidth()),
        m_baseHeight(m_image->GetHeight())
{
    m_image->Retain();
}

void CResizeImageCommand::Execute()
{
    m_image->Resize(m_width, m_height);
}

void CResizeImageCommand::CancelExecution()
{
    m_image->Resize(m_baseWidth, m_baseHeight);
}

CResizeImageCommand::~CResizeImageCommand()
{
    m_image->Release();
}

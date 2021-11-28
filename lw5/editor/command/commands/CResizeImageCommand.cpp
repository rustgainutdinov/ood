//
// Created by rustam.gainutdinov on 27.11.2021.
//

#include "CResizeImageCommand.h"
#include "lw5/editor/content/IImageResource.h"

CResizeImageCommand::CResizeImageCommand(IImageResource &image, int width, int height) : m_image(image), m_width(width),
                                                                                       m_height(height),
                                                                                       m_baseWidth(image.GetWidth()),
                                                                                       m_baseHeight(image.GetHeight())
{
    m_image.Capture();
}

void CResizeImageCommand::Execute()
{
    m_image.Resize(m_width, m_height);
}

void CResizeImageCommand::CancelExecution()
{
    m_image.Resize(m_baseWidth, m_baseHeight);
}

CResizeImageCommand::~CResizeImageCommand()
{
    m_image.Release();
}

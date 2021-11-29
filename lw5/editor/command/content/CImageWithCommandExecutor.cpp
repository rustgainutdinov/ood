//
// Created by rustam.gainutdinov on 27.11.2021.
//

#include "CImageWithCommandExecutor.h"
#include "lw5/editor/command/commands/CResizeImageCommand.h"
#include "lw5/editor/command/ICommandExecutor.h"

using namespace std;

CImageWithCommandExecutor::CImageWithCommandExecutor(std::shared_ptr<IImageResource> imageSource,
                                                     ICommandExecutor &commandExecutor) :
        m_imageSource(move(imageSource)), m_commandExecutor(commandExecutor)
{}

Path CImageWithCommandExecutor::GetPath() const
{
    return m_imageSource->GetPath();
}

int CImageWithCommandExecutor::GetWidth() const
{
    return m_imageSource->GetWidth();
}

int CImageWithCommandExecutor::GetHeight() const
{
    return m_imageSource->GetHeight();
}

void CImageWithCommandExecutor::Resize(int width, int height)
{
    auto command = make_unique<CResizeImageCommand>(m_imageSource, width, height);
    m_commandExecutor.Add(move(command));
}

void CImageWithCommandExecutor::Capture()
{
    m_imageSource->Capture();
}

void CImageWithCommandExecutor::Release()
{
    m_imageSource->Release();
}

void CImageWithCommandExecutor::MarkAsDeleted()
{
    m_imageSource->MarkAsDeleted();
}

void CImageWithCommandExecutor::MarkAsNotDeleted()
{
    m_imageSource->MarkAsNotDeleted();
}

bool CImageWithCommandExecutor::IsResourceExist()
{
    return m_imageSource->IsResourceExist();
}

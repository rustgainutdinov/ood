//
// Created by rustam.gainutdinov on 27.11.2021.
//

#ifndef OOD_CIMAGEWITHCOMMANDEXECUTOR_H
#define OOD_CIMAGEWITHCOMMANDEXECUTOR_H


#include "lw5/editor/content/IImageResource.h"
#include "memory"

class ICommandExecutor;

class CImageWithCommandExecutor : public IImageResource
{
public:
    CImageWithCommandExecutor(std::unique_ptr<IImageResource> imageSource, ICommandExecutor &commandExecutor);

    Path GetPath() const override;

    int GetWidth() const override;

    int GetHeight() const override;

    void Resize(int width, int height) override;

    void Capture() override;

    void Release() override;

    void MarkAsDeleted() override;

private:
    std::unique_ptr<IImageResource> m_imageSource;
    ICommandExecutor &m_commandExecutor;
};


#endif //OOD_CIMAGEWITHCOMMANDEXECUTOR_H

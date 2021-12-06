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
    CImageWithCommandExecutor(std::shared_ptr<IImageResource> imageSource, ICommandExecutor &commandExecutor);

    Path GetPath() const override;

    int GetWidth() const override;

    int GetHeight() const override;

    void Resize(int width, int height) override;

    void Retain() override;

    void Release() override;

    void MarkAsDeleted() override;

    void MarkAsNotDeleted() override;

    bool IsResourceExist() const override;

private:
    std::shared_ptr<IImageResource> m_imageSource;
    ICommandExecutor &m_commandExecutor;
};


#endif //OOD_CIMAGEWITHCOMMANDEXECUTOR_H

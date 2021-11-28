//
// Created by rustam.gainutdinov on 27.11.2021.
//

#ifndef OOD_CRESIZEIMAGECOMMAND_H
#define OOD_CRESIZEIMAGECOMMAND_H


#include "lw5/editor/command/ICommand.h"

class IImageResource;

class CResizeImageCommand : public ICommand
{
public:
    CResizeImageCommand(IImageResource &image, int width, int height);

    ~CResizeImageCommand() override;

    void Execute() override;

    void CancelExecution() override;

private:
    IImageResource &m_image;
    int m_width;
    int m_height;
    int m_baseWidth;
    int m_baseHeight;
};


#endif //OOD_CRESIZEIMAGECOMMAND_H

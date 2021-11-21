//
// Created by rustam.gainutdinov on 20.11.2021.
//

#ifndef OOD_CIMAGE_H
#define OOD_CIMAGE_H


#include "IImage.h"
#include "string"

class CImage : public IImage
{
public:
    Path GetPath() const override;

    int GetWidth() const override;

    int GetHeight() const override;

    void Resize(int width, int height) override;

    CImage(const Path &path, int width, int height);

private:
    int m_width;
    int m_height;
    Path m_path;
};


#endif //OOD_CIMAGE_H

//
// Created by rustam.gainutdinov on 20.11.2021.
//

#ifndef OOD_CIMAGE_H
#define OOD_CIMAGE_H


#include "IImageResource.h"
#include "string"

class CImage : public IImageResource
{
public:
    CImage(Path path, int width, int height);

    ~CImage() override;

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
    void AssertResourceExist() const;

    int m_width;
    int m_height;
    Path m_path;
    int m_usesCount = 0;
    bool m_isDeleted = false;
    bool m_resourceExist = true;
};


#endif //OOD_CIMAGE_H

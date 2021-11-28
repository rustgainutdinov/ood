//
// Created by rustam.gainutdinov on 27.11.2021.
//

#ifndef OOD_IIMAGERESOURCE_H
#define OOD_IIMAGERESOURCE_H


#include "lw5/editor/content/IImage.h"
#include "lw5/editor/content/IResource.h"

class IImageResource : public IImage, public IResource
{
public:
    ~IImageResource() override = default;
};

#endif //OOD_IIMAGERESOURCE_H

#ifndef OOD_IIMAGE_H
#define OOD_IIMAGE_H


#include "string"

typedef std::string Path;

class IImage
{
public:
    virtual Path GetPath() const = 0;

    virtual int GetWidth() const = 0;

    virtual int GetHeight() const = 0;

    virtual void Resize(int width, int height) = 0;

    virtual ~IImage() = default;
};

#endif //OOD_IIMAGE_H

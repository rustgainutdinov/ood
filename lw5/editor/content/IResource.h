//
// Created by rustam.gainutdinov on 29.11.2021.
//

#ifndef OOD_IRESOURCE_H
#define OOD_IRESOURCE_H

class IResource
{
public:
    virtual void Capture() = 0;

    virtual void Release() = 0;

    virtual void MarkAsDeleted() = 0;

    virtual void MarkAsNotDeleted() = 0;

    virtual bool IsResourceExist() = 0;
};

#endif //OOD_IRESOURCE_H

#include "string"

#ifndef OOD_IPARAGRAPH_H
#define OOD_IPARAGRAPH_H

class IParagraph
{
public:
    virtual std::string GetText() const = 0;

    virtual void SetText(const std::string &text) = 0;

    virtual ~IParagraph() = default;
};

#endif //OOD_IPARAGRAPH_H

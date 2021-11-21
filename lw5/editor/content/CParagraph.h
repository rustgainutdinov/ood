//
// Created by rustam.gainutdinov on 20.11.2021.
//

#ifndef OOD_CPARAGRAPH_H
#define OOD_CPARAGRAPH_H


#include "IParagraph.h"

class CParagraph : public IParagraph
{
public:
    std::string GetText() const override;

    void SetText(const std::string &text) override;

    explicit CParagraph(std::string text);

private:
    std::string m_text;
};


#endif //OOD_CPARAGRAPH_H

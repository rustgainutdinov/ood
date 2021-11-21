//
// Created by rustam.gainutdinov on 20.11.2021.
//

#include "CParagraph.h"
#include <utility>

using namespace std;

string CParagraph::GetText() const
{
    return m_text;
}

void CParagraph::SetText(const string &text)
{
    m_text = text;
}

CParagraph::CParagraph(string text) : m_text(move(text))
{
}
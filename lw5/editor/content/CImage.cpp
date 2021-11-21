//
// Created by rustam.gainutdinov on 20.11.2021.
//

#include "CImage.h"

Path CImage::GetPath() const
{
    return m_path;
}

int CImage::GetWidth() const
{
    return m_width;
}

int CImage::GetHeight() const
{
    return m_height;
}

void CImage::Resize(int width, int height)
{
    m_width = width;
    m_height = height;
}

CImage::CImage(const Path &path, int width, int height) : m_path(path), m_width(width), m_height(height)
{
}

//
// Created by rustam.gainutdinov on 20.11.2021.
//

#include "CImage.h"

#include <utility>

CImage::~CImage()
{

};

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

CImage::CImage(Path path, int width, int height) : m_path(std::move(path)), m_width(width), m_height(height)
{}

void CImage::Capture()
{
    m_placesOfUse++;
}

void CImage::Release()
{
    m_placesOfUse--;
    if (m_placesOfUse == 0 && m_isDeleted)
    {
        m_resourceExist = false;
    }
}

void CImage::MarkAsDeleted()
{
    m_isDeleted = true;
}

void CImage::MarkAsNotDeleted()
{
    m_isDeleted = false;
}

bool CImage::IsResourceExist()
{
    return m_resourceExist;
}


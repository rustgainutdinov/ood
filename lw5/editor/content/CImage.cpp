//
// Created by rustam.gainutdinov on 20.11.2021.
//

#include "CImage.h"

#include <utility>

using namespace std;

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
    AssertResourceExist();
    m_width = width;
    m_height = height;
}

CImage::CImage(Path path, int width, int height) : m_path(move(path)), m_width(width), m_height(height)
{}

void CImage::Retain()
{
    AssertResourceExist();
    m_usesCount++;
}

void CImage::Release()
{
    AssertResourceExist();
    m_usesCount--;
    if (m_usesCount == 0 && m_isDeleted)
    {
        m_resourceExist = false;
    }
}

void CImage::MarkAsDeleted()
{
    AssertResourceExist();
    m_isDeleted = true;
}

void CImage::MarkAsNotDeleted()
{
    AssertResourceExist();
    m_isDeleted = false;
}

bool CImage::IsResourceExist() const
{
    return m_resourceExist;
}

void CImage::AssertResourceExist() const
{
    if (!IsResourceExist())
    {
        throw invalid_argument("Image resource is not exist");
    }
}


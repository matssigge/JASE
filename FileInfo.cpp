#include "StdAfx.h"
#include "FileInfo.h"

CFileInfo::CFileInfo(const wchar_t* szFilename)
{
    m_sFilename = szFilename;
    m_dwAttributes = GetFileAttributes(szFilename);
    if (m_dwAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        if (m_sFilename[m_sFilename.length() - 1] != '\\')
            m_sFilename += '\\';
    }
}

CFileInfo::CFileInfo(const CFileInfo& fileInfo)
{
    m_dwAttributes = fileInfo.m_dwAttributes;
    m_sFilename = fileInfo.m_sFilename;
}

CFileInfo::~CFileInfo(void)
{
}

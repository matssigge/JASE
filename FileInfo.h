#pragma once

#include <string>
#include <list>

using namespace std;

class CFileInfo
{
public:
    CFileInfo(const wchar_t* szFilename);
    CFileInfo(const CFileInfo& fileInfo);
    ~CFileInfo(void);

    __declspec(property(get = GetFilename)) const wchar_t* Filename;
    __declspec(property(get = GetAttributes)) DWORD Attributes;

public:
    const wchar_t* GetFilename()
    {
        return m_sFilename.c_str();
    }
    DWORD GetAttributes()
    {
        return m_dwAttributes;
    }

private:
    wstring  m_sFilename;
    DWORD    m_dwAttributes;
};

typedef list<CFileInfo>     filelist;
typedef filelist::iterator  fileiter;

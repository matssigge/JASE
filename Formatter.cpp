#include "StdAfx.h"
#include "formatter.h"

using namespace std;

CFormatter::CFormatter(void)
{
}

CFormatter::~CFormatter(void)
{
}

int CFormatter::GetSize(CFileInfo& fileInfo)
{
    return (int)Format(fileInfo).length();
}

//--------------------------------------------------------------------

class CLongFormatter : public CFormatter
{
public:
    virtual wstring Format(CFileInfo& fileInfo)
    {
        wchar_t szLong[MAX_PATH];
        GetLongPathName(fileInfo.Filename, szLong, MAX_PATH);
        return wstring(szLong);
    }

    static CLongFormatter Formatter;
};
CLongFormatter CLongFormatter::Formatter;

//--------------------------------------------------------------------

class CShortFormatter : public CFormatter
{
public:
    virtual wstring Format(CFileInfo& fileInfo)
    {
        wchar_t szShort[MAX_PATH];
        GetShortPathName(fileInfo.Filename, szShort, MAX_PATH);
        return wstring(szShort);
    }

    static CShortFormatter Formatter;
};
CShortFormatter CShortFormatter::Formatter;

//--------------------------------------------------------------------

class CUNCFormatter : public CLongFormatter
{
public:
    virtual wstring Format(CFileInfo& fileInfo)
    {
        wchar_t szBuffer[1000];
        DWORD dwBufLen = 1000;
        DWORD dwRes = WNetGetUniversalName(fileInfo.Filename, UNIVERSAL_NAME_INFO_LEVEL, szBuffer, &dwBufLen);
        if (dwRes == 0)
            return wstring(((UNIVERSAL_NAME_INFO*)szBuffer)->lpUniversalName);
        else
            return __super::Format(fileInfo);
    }

    static CUNCFormatter Formatter;
};
CUNCFormatter CUNCFormatter::Formatter;

//--------------------------------------------------------------------

class CUnixFormatter : public CLongFormatter
{
public:
    virtual wstring Format(CFileInfo& fileInfo)
    {
        wstring sLong = __super::Format(fileInfo);
        for (wchar_t* s = (wchar_t*)sLong.c_str(); *s; s++)
            if (*s == '\\')
                *s = '/';
        return sLong;
    }

    static CUnixFormatter Formatter;
};
CUnixFormatter CUnixFormatter::Formatter;

//--------------------------------------------------------------------

class CFilenameOnlyFormatter : public CLongFormatter
{
public:
    virtual wstring Format(CFileInfo& fileInfo)
    {
        wstring sLong = __super::Format(fileInfo);
        return sLong.substr(sLong.find_last_of(L"\\/") + 1);
    }

    static CFilenameOnlyFormatter Formatter;
};
CFilenameOnlyFormatter CFilenameOnlyFormatter::Formatter;

//--------------------------------------------------------------------
// Initalize static members
//--------------------------------------------------------------------

CFormatter&  CFormatter::LongFormatter = CLongFormatter::Formatter;
CFormatter&  CFormatter::ShortFormatter = CShortFormatter::Formatter;
CFormatter&  CFormatter::UNCFormatter = CUNCFormatter::Formatter;
CFormatter&  CFormatter::UnixFormatter = CUnixFormatter::Formatter;
CFormatter&  CFormatter::FilenameOnlyFormatter = CFilenameOnlyFormatter::Formatter;

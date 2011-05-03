#pragma once

#include <string>
#include "FileInfo.h"

class CFormatter
{
public:
    CFormatter(void);
    ~CFormatter(void);

    int GetSize(CFileInfo& fileInfo);
    virtual std::wstring Format(CFileInfo& fileInfo) = 0;

public:
    static CFormatter& LongFormatter;
    static CFormatter& ShortFormatter;
    static CFormatter& UNCFormatter;
    static CFormatter& UnixFormatter;
    static CFormatter& FilenameOnlyFormatter;
};

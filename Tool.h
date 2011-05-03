#pragma once

#include <map>
#include <list>
#include "FileInfo.h"

using namespace std;

class CTool
{
public:
    CTool(const filelist& Files);
    ~CTool();

    int AddCommands(HMENU hMenu, int nFirstCmdId);
    void InvokeCommand(int nCmdId);

protected:
    void AddCommand(int nCommand, const wchar_t* szCaption);
    void AddSubMenu(const wchar_t* szCaption);
    void FinishSubMenu(const wchar_t* szCaption);

    virtual void AddToolCommands() = 0;
    virtual void InvokeToolCommand(int nCommand) = 0;

private:
    int GetCmdId(int nCommand);

protected:
    const filelist& m_Files;

private:
    typedef std::map<int, int> iimap;
    typedef list<HMENU>        menulist;

    HMENU     m_hMenu;
    menulist  m_MenuStack;
    int       m_nNextCmdId;
    iimap     m_CmdMap;
protected:
    void FinishSubMenu(void);
};

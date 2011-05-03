#include "StdAfx.h"
#include "Tool.h"

CTool::CTool(const filelist& Files) :
m_Files(Files)
{
}

CTool::~CTool()
{
}

int CTool::AddCommands(HMENU hMenu, int nFirstCmdId)
{
    m_hMenu = hMenu;
    m_nNextCmdId = nFirstCmdId;
    AddToolCommands();
    return m_nNextCmdId;
}

int CTool::GetCmdId(int nCommand)
{
    int nCmdId = m_nNextCmdId++;
    m_CmdMap[nCmdId] = nCommand;
    return nCmdId;
}

void CTool::InvokeCommand(int nCmdId)
{
    InvokeToolCommand(m_CmdMap[nCmdId]);
}

void CTool::AddCommand(int nCommand, const wchar_t* szCaption)
{
    InsertMenu(m_hMenu, -1, MF_STRING|MF_BYPOSITION, GetCmdId(nCommand), szCaption);
}

void CTool::AddSubMenu(const wchar_t* szCaption)
{
    HMENU subMenu = CreateMenu();
    InsertMenu(m_hMenu, -1, MF_POPUP|MF_BYPOSITION, (UINT_PTR)subMenu, szCaption);
    m_MenuStack.push_front(m_hMenu);
    m_hMenu = subMenu;
}

void CTool::FinishSubMenu(void)
{
    m_hMenu = m_MenuStack.front();
    m_MenuStack.pop_front();
}

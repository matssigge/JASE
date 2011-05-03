// JustMenu64.cpp : Implementation of CJustMenu64

#include "stdafx.h"
#include "JustMenu64.h"


//-------------------------------------------------------------------
// Constants
//-------------------------------------------------------------------

enum FixedMenuCommands
{
    cmdFixedFirst = 0,
    cmdCopyFilename = 0,
    cmdCopyLong,
    cmdCopyShort,
    cmdCopyUNC,
    cmdCopyUnix,
    cmdCopyFilenameOnly,
    cmdAddToPath,
};

wchar_t* pszFixedCommands[] = 
{
    L"&Copy Filename",
    L"&Long filename",
    L"&Short filename",
    L"&UNC filename",
    L"Uni&x filename",
    L"&Filename only",
    L"Add to &path"
};

#define MENU_TEXT L"&Just..."
#define SUBMENU_TEXT L"Copy &other format..."

#define ENV_KEY L"System\\CurrentControlSet\\Control\\Session Manager\\Environment"

//-------------------------------------------------------------------
// CJustMenu
//-------------------------------------------------------------------

HRESULT CJustMenu64::Initialize(LPCITEMIDLIST pidlFolder, 
                                IDataObject*  pdtObj, 
                                HKEY          hkeyProgID)
{
    HRESULT hRes = E_FAIL;

    // No data object
    if (!pdtObj)
        return E_FAIL;

    FORMATETC fmte = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
    STGMEDIUM medium;

    hRes = pdtObj->GetData(&fmte, &medium);
    if (FAILED(hRes))
        return E_FAIL;

    m_Files.clear();

    int nFileCount;
    if ((nFileCount = DragQueryFile((HDROP)medium.hGlobal, -1, 0, 0)) > 0)
    {
        for (int i = 0; i < nFileCount; i++)
        {
            wchar_t szPath[MAX_PATH];
            DragQueryFile((HDROP)medium.hGlobal, i, szPath, MAX_PATH);
            m_Files.push_back(CFileInfo(szPath));
        }
        hRes = S_OK;
    }
    else
        hRes = E_FAIL;

    ReleaseStgMedium(&medium);

    m_pidlFolder = pidlFolder;
    m_hKey = hkeyProgID;
    return hRes;
}

HRESULT CJustMenu64::QueryContextMenu(HMENU hMenu,
                                      UINT indexMenu,
                                      UINT idCmdFirst,
                                      UINT idCmdLast,
                                      UINT uFlags)
{
    UINT idCmd = idCmdFirst;

    // Create submenu
    HMENU hSubMenu = CreateMenu();
    int iSubPos = 0;
    InsertMenu(hSubMenu, iSubPos++, MF_STRING|MF_BYPOSITION, idCmd++, pszFixedCommands[cmdCopyFilename]);

    // Create subsubmenu
    HMENU hSubSubMenu = CreateMenu();
    int iSubSubPos = 0;
    InsertMenu(hSubSubMenu, iSubSubPos++, MF_STRING|MF_BYPOSITION, idCmd++, pszFixedCommands[cmdCopyLong]);
    InsertMenu(hSubSubMenu, iSubSubPos++, MF_STRING|MF_BYPOSITION, idCmd++, pszFixedCommands[cmdCopyShort]);
    InsertMenu(hSubSubMenu, iSubSubPos++, MF_STRING|MF_BYPOSITION, idCmd++, pszFixedCommands[cmdCopyUNC]);
    InsertMenu(hSubSubMenu, iSubSubPos++, MF_STRING|MF_BYPOSITION, idCmd++, pszFixedCommands[cmdCopyUnix]);
    InsertMenu(hSubSubMenu, iSubSubPos++, MF_STRING|MF_BYPOSITION, idCmd++, pszFixedCommands[cmdCopyFilenameOnly]);

    // Insert subsubmenu on submenu
    InsertMenu(hSubMenu, iSubPos++, MF_POPUP|MF_BYPOSITION, (UINT_PTR)hSubSubMenu, SUBMENU_TEXT);

    // Insert path command, but only if target is one folder
    if (m_Files.size() == 1 && ((m_Files.begin()->Attributes) & FILE_ATTRIBUTE_DIRECTORY) != 0)
        InsertMenu(hSubMenu, iSubPos++, MF_STRING|MF_BYPOSITION, idCmd++, pszFixedCommands[cmdAddToPath]);
    else
        idCmd++;  // Keep sync with command id

    // Insert submenu on context menu
    InsertMenu(hMenu,
        indexMenu++,
        MF_POPUP|MF_BYPOSITION,
        (UINT_PTR)hSubMenu,
        MENU_TEXT);

    return ResultFromScode(MAKE_SCODE(SEVERITY_SUCCESS, 0, (USHORT)(idCmd - idCmdFirst)));
}

HRESULT CJustMenu64::GetCommandString(UINT_PTR idCmd,
                                      UINT uFlags,
                                      UINT *pwReserved,
                                      LPSTR pszName,
                                      UINT cchMax)
{
    return E_NOTIMPL;
}

HRESULT CJustMenu64::InvokeCommand(LPCMINVOKECOMMANDINFO pici)
{
    HRESULT hRes = E_FAIL;
    if (HIWORD(pici->lpVerb) == 0)
    {
        int nCmd = LOWORD(pici->lpVerb);
        if (nCmd == cmdCopyFilename)
        {
            return CopyFilenamesToClipboard(CFormatter::LongFormatter);
        }
        else if (nCmd == cmdCopyLong)
        {
            return CopyFilenamesToClipboard(CFormatter::LongFormatter);
        }
        else if (nCmd == cmdCopyShort)
        {
            return CopyFilenamesToClipboard(CFormatter::ShortFormatter);
        }
        else if (nCmd == cmdCopyUNC)
        {
            return CopyFilenamesToClipboard(CFormatter::UNCFormatter);
        }
        else if (nCmd == cmdCopyUnix)
        {
            return CopyFilenamesToClipboard(CFormatter::UnixFormatter);
        }
        else if (nCmd == cmdCopyFilenameOnly)
        {
            return CopyFilenamesToClipboard(CFormatter::FilenameOnlyFormatter);
        }
        else if (nCmd == cmdAddToPath)
        {
            return AddFolderToPath();
        }
        else
        {
        }
    }
    return E_FAIL;
}

HRESULT CJustMenu64::CopyFilenamesToClipboard(CFormatter& formatter)
{
    if (!OpenClipboard(0))
        return E_FAIL;
    EmptyClipboard();

    // Calculate length of required buffer and allocate memory
    int nSize = 1;  // Terminating null
    for (fileiter iter = m_Files.begin(); iter != m_Files.end(); iter++)
        nSize += formatter.GetSize(*iter) + (int)strlen("\n");
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, nSize * 2);

    // Copy filenames to buffer
    wchar_t* szBuf = (wchar_t*)GlobalLock(hMem);
    szBuf[0] = 0;
    for (fileiter iter = m_Files.begin(); iter != m_Files.end(); iter++)
    {
        wcscat_s(szBuf, nSize, formatter.Format(*iter).c_str());
        if (m_Files.size() > 1)
            wcscat_s(szBuf, nSize, L"\n");
    }
    GlobalUnlock(hMem);

    // Set clipboard data
    SetClipboardData(CF_UNICODETEXT, hMem);

    CloseClipboard();
    return S_OK;
}

HRESULT CJustMenu64::AddFolderToPath()
{
    HKEY hEnvKey;
    RegOpenKeyEx(
        HKEY_LOCAL_MACHINE, 
        ENV_KEY, 
        0,
        KEY_ALL_ACCESS,
        &hEnvKey);

    DWORD dwType;
    DWORD dwSize = 0;
    RegQueryValueEx(hEnvKey, L"Path", 0, &dwType, 0, &dwSize);
    auto_ptr<wchar_t> szBuf(new wchar_t[dwSize]);
    RegQueryValueEx(hEnvKey, L"Path", 0, &dwType, (LPBYTE)szBuf.get(), &dwSize);

    RegSetValueEx(hEnvKey, L"Path_backup", 0, dwType, (CONST BYTE*)szBuf.get(), dwSize);

    wstring sPath = szBuf.get();
    if (sPath[sPath.length() - 1] != ';')
        sPath += ';';
    sPath += m_Files.begin()->Filename;

    RegSetValueEx(hEnvKey, L"Path", 0, dwType, (CONST BYTE*)sPath.c_str(), (DWORD)sPath.size() * 2);

    RegCloseKey(hEnvKey);

    // Notify other processes that environment has changed
    try 
    {
        CloseHandle(CreateThread(0, 0, BroadcastThread, 0, 0, 0));
    }
    catch (...)
    {
    }

    return S_OK;
}

DWORD CJustMenu64::BroadcastThread(LPVOID lparam)
{
    // Notify other processes that environment has changed
    DWORD_PTR dwResult;
    SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM) L"Environment", SMTO_ABORTIFHUNG, 5000, &dwResult);
    return 0;
}

/*
HRESULT CJustMenu64::HandleMenuMsg(UINT uMsg,
                              WPARAM wParam,
                              LPARAM lParam)
{
  return S_OK;
}

HRESULT CJustMenu64::HandleMenuMsg2(UINT uMsg,
                               WPARAM wParam,
                               LPARAM lParam,
                               LRESULT *plResult)
{
  return S_OK;
}
*/
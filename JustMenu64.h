// JustMenu64.h : Declaration of the CJustMenu64

#pragma once
#include "resource.h"       // main symbols

#include "JASE64_i.h"
#include <shlobj.h>
#include <list>
#include "FileInfo.h"
#include "Formatter.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CJustMenu64

class ATL_NO_VTABLE CJustMenu64 :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CJustMenu64, &CLSID_JustMenu64>,
	public IDispatchImpl<IJustMenu64, &IID_IJustMenu64, &LIBID_JASE64Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IShellExtInit,
	public IContextMenu
{
public:
	CJustMenu64()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_JUSTMENU64)

DECLARE_NOT_AGGREGATABLE(CJustMenu64)

BEGIN_COM_MAP(CJustMenu64)
	COM_INTERFACE_ENTRY(IJustMenu64)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IContextMenu)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

// IShellExtInit interface
public:
    STDMETHOD(Initialize(
        LPCITEMIDLIST pidlFolder, 
        IDataObject*pdtObj, 
        HKEY hkeyProgID));

// IContextMenu interface
public:
    STDMETHOD(GetCommandString(
        UINT_PTR idCmd,
        UINT uFlags,
        UINT *pwReserved,
        LPSTR pszName,
        UINT cchMax));
    STDMETHOD(InvokeCommand(
        LPCMINVOKECOMMANDINFO pici));
    STDMETHOD(QueryContextMenu(
        HMENU hmenu,
        UINT indexMenu,
        UINT idCmdFirst,
        UINT idCmdLast,
        UINT uFlags));

private:
    HRESULT CopyFilenamesToClipboard(CFormatter& formatter);
    HRESULT AddFolderToPath();
    static DWORD WINAPI BroadcastThread(LPVOID lparam);

private:
    filelist        m_Files;
    LPCITEMIDLIST   m_pidlFolder;
    HKEY            m_hKey;
};

OBJECT_ENTRY_AUTO(__uuidof(JustMenu64), CJustMenu64)

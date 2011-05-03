// dllmain.h : Declaration of module class.

class CJASE64Module : public CAtlDllModuleT< CJASE64Module >
{
public :
	DECLARE_LIBID(LIBID_JASE64Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_JASE64, "{6A512F20-12A8-4AE9-9B6C-9133C8AA56D8}")
};

extern class CJASE64Module _AtlModule;

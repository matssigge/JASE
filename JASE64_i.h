

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Thu Oct 08 08:18:30 2009
 */
/* Compiler settings for .\JASE64.idl:
    Oicf, W1, Zp8, env=Win64 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __JASE64_i_h__
#define __JASE64_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IJustMenu64_FWD_DEFINED__
#define __IJustMenu64_FWD_DEFINED__
typedef interface IJustMenu64 IJustMenu64;
#endif 	/* __IJustMenu64_FWD_DEFINED__ */


#ifndef __JustMenu64_FWD_DEFINED__
#define __JustMenu64_FWD_DEFINED__

#ifdef __cplusplus
typedef class JustMenu64 JustMenu64;
#else
typedef struct JustMenu64 JustMenu64;
#endif /* __cplusplus */

#endif 	/* __JustMenu64_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IJustMenu64_INTERFACE_DEFINED__
#define __IJustMenu64_INTERFACE_DEFINED__

/* interface IJustMenu64 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IJustMenu64;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B3309B32-3053-4093-B952-C2C5CD50C8B4")
    IJustMenu64 : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IJustMenu64Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IJustMenu64 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IJustMenu64 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IJustMenu64 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IJustMenu64 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IJustMenu64 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IJustMenu64 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IJustMenu64 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IJustMenu64Vtbl;

    interface IJustMenu64
    {
        CONST_VTBL struct IJustMenu64Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IJustMenu64_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IJustMenu64_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IJustMenu64_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IJustMenu64_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IJustMenu64_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IJustMenu64_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IJustMenu64_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IJustMenu64_INTERFACE_DEFINED__ */



#ifndef __JASE64Lib_LIBRARY_DEFINED__
#define __JASE64Lib_LIBRARY_DEFINED__

/* library JASE64Lib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_JASE64Lib;

EXTERN_C const CLSID CLSID_JustMenu64;

#ifdef __cplusplus

class DECLSPEC_UUID("4C402385-2370-443F-8E00-21B88EED4B6F")
JustMenu64;
#endif
#endif /* __JASE64Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif



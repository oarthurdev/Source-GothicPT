
#pragma warning( disable: 4049 )  










#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif 

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif 

#ifndef __amstream_h__
#define __amstream_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif



#ifndef __IDirectShowStream_FWD_DEFINED__
#define __IDirectShowStream_FWD_DEFINED__
typedef interface IDirectShowStream IDirectShowStream;
#endif 	


#ifndef __IAMMultiMediaStream_FWD_DEFINED__
#define __IAMMultiMediaStream_FWD_DEFINED__
typedef interface IAMMultiMediaStream IAMMultiMediaStream;
#endif 	


#ifndef __IAMMediaStream_FWD_DEFINED__
#define __IAMMediaStream_FWD_DEFINED__
typedef interface IAMMediaStream IAMMediaStream;
#endif 	


#ifndef __IMediaStreamFilter_FWD_DEFINED__
#define __IMediaStreamFilter_FWD_DEFINED__
typedef interface IMediaStreamFilter IMediaStreamFilter;
#endif 	


#ifndef __IDirectDrawMediaSampleAllocator_FWD_DEFINED__
#define __IDirectDrawMediaSampleAllocator_FWD_DEFINED__
typedef interface IDirectDrawMediaSampleAllocator IDirectDrawMediaSampleAllocator;
#endif 	


#ifndef __IDirectDrawMediaSample_FWD_DEFINED__
#define __IDirectDrawMediaSample_FWD_DEFINED__
typedef interface IDirectDrawMediaSample IDirectDrawMediaSample;
#endif 	


#ifndef __IAMMediaTypeStream_FWD_DEFINED__
#define __IAMMediaTypeStream_FWD_DEFINED__
typedef interface IAMMediaTypeStream IAMMediaTypeStream;
#endif 	


#ifndef __IAMMediaTypeSample_FWD_DEFINED__
#define __IAMMediaTypeSample_FWD_DEFINED__
typedef interface IAMMediaTypeSample IAMMediaTypeSample;
#endif 	


#ifndef __AMMultiMediaStream_FWD_DEFINED__
#define __AMMultiMediaStream_FWD_DEFINED__

#ifdef __cplusplus
typedef class AMMultiMediaStream AMMultiMediaStream;
#else
typedef struct AMMultiMediaStream AMMultiMediaStream;
#endif 

#endif 	



#include "unknwn.h"
#include "mmstream.h"
#include "strmif.h"

#ifdef __cplusplus
extern "C"{
#endif 

	void * __RPC_USER MIDL_user_allocate(size_t);
	void __RPC_USER MIDL_user_free(void *);




#include <ddraw.h>
#include <mmsystem.h>
#include <mmstream.h>
#include <ddstream.h>
#include <austream.h>








	enum __MIDL___MIDL_itf_amstream_0000_0001
	{
		AMMSF_NOGRAPHTHREAD = 0x1
	};

	enum __MIDL___MIDL_itf_amstream_0000_0002
	{
		AMMSF_ADDDEFAULTRENDERER = 0x1,
		AMMSF_CREATEPEER = 0x2,
		AMMSF_STOPIFNOSAMPLES = 0x4,
		AMMSF_NOSTALL = 0x8
	};

	enum __MIDL___MIDL_itf_amstream_0000_0003
	{
		AMMSF_RENDERTYPEMASK = 0x3,
		AMMSF_RENDERTOEXISTING = 0,
		AMMSF_RENDERALLSTREAMS = 0x1,
		AMMSF_NORENDER = 0x2,
		AMMSF_NOCLOCK = 0x4,
		AMMSF_RUN = 0x8
	};
	typedef
		enum __MIDL___MIDL_itf_amstream_0000_0004
	{
		Disabled = 0,
		ReadData2 = 1,
		RenderData = 2
	} 	OUTPUT_STATE;



	extern RPC_IF_HANDLE __MIDL_itf_amstream_0000_v0_0_c_ifspec;
	extern RPC_IF_HANDLE __MIDL_itf_amstream_0000_v0_0_s_ifspec;

#ifndef __IDirectShowStream_INTERFACE_DEFINED__
#define __IDirectShowStream_INTERFACE_DEFINED__





	EXTERN_C const IID IID_IDirectShowStream;

#if defined(__cplusplus) && !defined(CINTERFACE)

	MIDL_INTERFACE("7DB01C96-C0C3-11d0-8FF1-00C04FD9189D")
		IDirectShowStream : public IDispatch
	{
	public:
		virtual  HRESULT STDMETHODCALLTYPE get_FileName(
			 BSTR *pVal) = 0;

		virtual  HRESULT STDMETHODCALLTYPE put_FileName(
			 BSTR newVal) = 0;

		virtual  HRESULT STDMETHODCALLTYPE get_Video(
			 OUTPUT_STATE *pVal) = 0;

		virtual  HRESULT STDMETHODCALLTYPE put_Video(
			 OUTPUT_STATE newVal) = 0;

		virtual  HRESULT STDMETHODCALLTYPE get_Audio(
			 OUTPUT_STATE *pVal) = 0;

		virtual  HRESULT STDMETHODCALLTYPE put_Audio(
			 OUTPUT_STATE newVal) = 0;

	};

#else 	

	typedef struct IDirectShowStreamVtbl
	{
		BEGIN_INTERFACE

			HRESULT(STDMETHODCALLTYPE *QueryInterface)(
				IDirectShowStream * This,
				REFIID riid,
				void **ppvObject);

		ULONG(STDMETHODCALLTYPE *AddRef)(
			IDirectShowStream * This);

		ULONG(STDMETHODCALLTYPE *Release)(
			IDirectShowStream * This);

		HRESULT(STDMETHODCALLTYPE *GetTypeInfoCount)(
			IDirectShowStream * This,
			UINT *pctinfo);

		HRESULT(STDMETHODCALLTYPE *GetTypeInfo)(
			IDirectShowStream * This,
			UINT iTInfo,
			LCID lcid,
			ITypeInfo **ppTInfo);

		HRESULT(STDMETHODCALLTYPE *GetIDsOfNames)(
			IDirectShowStream * This,
			REFIID riid,
			LPOLESTR *rgszNames,
			UINT cNames,
			LCID lcid,
			DISPID *rgDispId);

		HRESULT(STDMETHODCALLTYPE *Invoke)(
			IDirectShowStream * This,
			DISPID dispIdMember,
			REFIID riid,
			LCID lcid,
			WORD wFlags,
			DISPPARAMS *pDispParams,
			VARIANT *pVarResult,
			EXCEPINFO *pExcepInfo,
			UINT *puArgErr);

		HRESULT(STDMETHODCALLTYPE *get_FileName)(
			IDirectShowStream * This,
			BSTR *pVal);

		HRESULT(STDMETHODCALLTYPE *put_FileName)(
			IDirectShowStream * This,
			BSTR newVal);

		HRESULT(STDMETHODCALLTYPE *get_Video)(
			IDirectShowStream * This,
			OUTPUT_STATE *pVal);

		HRESULT(STDMETHODCALLTYPE *put_Video)(
			IDirectShowStream * This,
			OUTPUT_STATE newVal);

		HRESULT(STDMETHODCALLTYPE *get_Audio)(
			IDirectShowStream * This,
			OUTPUT_STATE *pVal);

		HRESULT(STDMETHODCALLTYPE *put_Audio)(
			IDirectShowStream * This,
			OUTPUT_STATE newVal);

		END_INTERFACE
	} IDirectShowStreamVtbl;

	interface IDirectShowStream
	{
		CONST_VTBL struct IDirectShowStreamVtbl *lpVtbl;
	};



#ifdef COBJMACROS


#define IDirectShowStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDirectShowStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDirectShowStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDirectShowStream_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDirectShowStream_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDirectShowStream_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDirectShowStream_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDirectShowStream_get_FileName(This,pVal)	\
    (This)->lpVtbl -> get_FileName(This,pVal)

#define IDirectShowStream_put_FileName(This,newVal)	\
    (This)->lpVtbl -> put_FileName(This,newVal)

#define IDirectShowStream_get_Video(This,pVal)	\
    (This)->lpVtbl -> get_Video(This,pVal)

#define IDirectShowStream_put_Video(This,newVal)	\
    (This)->lpVtbl -> put_Video(This,newVal)

#define IDirectShowStream_get_Audio(This,pVal)	\
    (This)->lpVtbl -> get_Audio(This,pVal)

#define IDirectShowStream_put_Audio(This,newVal)	\
    (This)->lpVtbl -> put_Audio(This,newVal)

#endif 


#endif 	



	HRESULT STDMETHODCALLTYPE IDirectShowStream_get_FileName_Proxy(
		IDirectShowStream * This,
		BSTR *pVal);


	void __RPC_STUB IDirectShowStream_get_FileName_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IDirectShowStream_put_FileName_Proxy(
		IDirectShowStream * This,
		BSTR newVal);


	void __RPC_STUB IDirectShowStream_put_FileName_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IDirectShowStream_get_Video_Proxy(
		IDirectShowStream * This,
		OUTPUT_STATE *pVal);


	void __RPC_STUB IDirectShowStream_get_Video_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IDirectShowStream_put_Video_Proxy(
		IDirectShowStream * This,
		OUTPUT_STATE newVal);


	void __RPC_STUB IDirectShowStream_put_Video_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IDirectShowStream_get_Audio_Proxy(
		IDirectShowStream * This,
		OUTPUT_STATE *pVal);


	void __RPC_STUB IDirectShowStream_get_Audio_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IDirectShowStream_put_Audio_Proxy(
		IDirectShowStream * This,
		OUTPUT_STATE newVal);


	void __RPC_STUB IDirectShowStream_put_Audio_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);



#endif 	


#ifndef __IAMMultiMediaStream_INTERFACE_DEFINED__
#define __IAMMultiMediaStream_INTERFACE_DEFINED__





	EXTERN_C const IID IID_IAMMultiMediaStream;

#if defined(__cplusplus) && !defined(CINTERFACE)

	MIDL_INTERFACE("BEBE595C-9A6F-11d0-8FDE-00C04FD9189D")
		IAMMultiMediaStream : public IMultiMediaStream
	{
	public:
		virtual HRESULT STDMETHODCALLTYPE Initialize(
			 STREAM_TYPE StreamType,
			 DWORD dwFlags,
			 IGraphBuilder *pFilterGraph) = 0;

		virtual HRESULT STDMETHODCALLTYPE GetFilterGraph(
			 IGraphBuilder **ppGraphBuilder) = 0;

		virtual HRESULT STDMETHODCALLTYPE GetFilter(
			 IMediaStreamFilter **ppFilter) = 0;

		virtual HRESULT STDMETHODCALLTYPE AddMediaStream(
			 IUnknown *pStreamObject,
			 const MSPID *PurposeId,
			 DWORD dwFlags,
			 IMediaStream **ppNewStream) = 0;

		virtual HRESULT STDMETHODCALLTYPE OpenFile(
			 LPCWSTR pszFileName,
			 DWORD dwFlags) = 0;

		virtual HRESULT STDMETHODCALLTYPE OpenMoniker(
			 IBindCtx *pCtx,
			 IMoniker *pMoniker,
			 DWORD dwFlags) = 0;

		virtual HRESULT STDMETHODCALLTYPE Render(
			 DWORD dwFlags) = 0;

	};

#else 	

	typedef struct IAMMultiMediaStreamVtbl
	{
		BEGIN_INTERFACE

			HRESULT(STDMETHODCALLTYPE *QueryInterface)(
				IAMMultiMediaStream * This,
				REFIID riid,
				void **ppvObject);

		ULONG(STDMETHODCALLTYPE *AddRef)(
			IAMMultiMediaStream * This);

		ULONG(STDMETHODCALLTYPE *Release)(
			IAMMultiMediaStream * This);

		HRESULT(STDMETHODCALLTYPE *GetInformation)(
			IAMMultiMediaStream * This,
			DWORD *pdwFlags,
			STREAM_TYPE *pStreamType);

		HRESULT(STDMETHODCALLTYPE *GetMediaStream)(
			IAMMultiMediaStream * This,
			REFMSPID idPurpose,
			IMediaStream **ppMediaStream);

		HRESULT(STDMETHODCALLTYPE *EnumMediaStreams)(
			IAMMultiMediaStream * This,
			long Index,
			IMediaStream **ppMediaStream);

		HRESULT(STDMETHODCALLTYPE *GetState)(
			IAMMultiMediaStream * This,
			STREAM_STATE *pCurrentState);

		HRESULT(STDMETHODCALLTYPE *SetState)(
			IAMMultiMediaStream * This,
			STREAM_STATE NewState);

		HRESULT(STDMETHODCALLTYPE *GetTime)(
			IAMMultiMediaStream * This,
			STREAM_TIME *pCurrentTime);

		HRESULT(STDMETHODCALLTYPE *GetDuration)(
			IAMMultiMediaStream * This,
			STREAM_TIME *pDuration);

		HRESULT(STDMETHODCALLTYPE *Seek)(
			IAMMultiMediaStream * This,
			STREAM_TIME SeekTime);

		HRESULT(STDMETHODCALLTYPE *GetEndOfStreamEventHandle)(
			IAMMultiMediaStream * This,
			HANDLE *phEOS);

		HRESULT(STDMETHODCALLTYPE *Initialize)(
			IAMMultiMediaStream * This,
			STREAM_TYPE StreamType,
			DWORD dwFlags,
			IGraphBuilder *pFilterGraph);

		HRESULT(STDMETHODCALLTYPE *GetFilterGraph)(
			IAMMultiMediaStream * This,
			IGraphBuilder **ppGraphBuilder);

		HRESULT(STDMETHODCALLTYPE *GetFilter)(
			IAMMultiMediaStream * This,
			IMediaStreamFilter **ppFilter);

		HRESULT(STDMETHODCALLTYPE *AddMediaStream)(
			IAMMultiMediaStream * This,
			IUnknown *pStreamObject,
			const MSPID *PurposeId,
			DWORD dwFlags,
			IMediaStream **ppNewStream);

		HRESULT(STDMETHODCALLTYPE *OpenFile)(
			IAMMultiMediaStream * This,
			LPCWSTR pszFileName,
			DWORD dwFlags);

		HRESULT(STDMETHODCALLTYPE *OpenMoniker)(
			IAMMultiMediaStream * This,
			IBindCtx *pCtx,
			IMoniker *pMoniker,
			DWORD dwFlags);

		HRESULT(STDMETHODCALLTYPE *Render)(
			IAMMultiMediaStream * This,
			DWORD dwFlags);

		END_INTERFACE
	} IAMMultiMediaStreamVtbl;

	interface IAMMultiMediaStream
	{
		CONST_VTBL struct IAMMultiMediaStreamVtbl *lpVtbl;
	};



#ifdef COBJMACROS


#define IAMMultiMediaStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMMultiMediaStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMMultiMediaStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMMultiMediaStream_GetInformation(This,pdwFlags,pStreamType)	\
    (This)->lpVtbl -> GetInformation(This,pdwFlags,pStreamType)

#define IAMMultiMediaStream_GetMediaStream(This,idPurpose,ppMediaStream)	\
    (This)->lpVtbl -> GetMediaStream(This,idPurpose,ppMediaStream)

#define IAMMultiMediaStream_EnumMediaStreams(This,Index,ppMediaStream)	\
    (This)->lpVtbl -> EnumMediaStreams(This,Index,ppMediaStream)

#define IAMMultiMediaStream_GetState(This,pCurrentState)	\
    (This)->lpVtbl -> GetState(This,pCurrentState)

#define IAMMultiMediaStream_SetState(This,NewState)	\
    (This)->lpVtbl -> SetState(This,NewState)

#define IAMMultiMediaStream_GetTime(This,pCurrentTime)	\
    (This)->lpVtbl -> GetTime(This,pCurrentTime)

#define IAMMultiMediaStream_GetDuration(This,pDuration)	\
    (This)->lpVtbl -> GetDuration(This,pDuration)

#define IAMMultiMediaStream_Seek(This,SeekTime)	\
    (This)->lpVtbl -> Seek(This,SeekTime)

#define IAMMultiMediaStream_GetEndOfStreamEventHandle(This,phEOS)	\
    (This)->lpVtbl -> GetEndOfStreamEventHandle(This,phEOS)


#define IAMMultiMediaStream_Initialize(This,StreamType,dwFlags,pFilterGraph)	\
    (This)->lpVtbl -> Initialize(This,StreamType,dwFlags,pFilterGraph)

#define IAMMultiMediaStream_GetFilterGraph(This,ppGraphBuilder)	\
    (This)->lpVtbl -> GetFilterGraph(This,ppGraphBuilder)

#define IAMMultiMediaStream_GetFilter(This,ppFilter)	\
    (This)->lpVtbl -> GetFilter(This,ppFilter)

#define IAMMultiMediaStream_AddMediaStream(This,pStreamObject,PurposeId,dwFlags,ppNewStream)	\
    (This)->lpVtbl -> AddMediaStream(This,pStreamObject,PurposeId,dwFlags,ppNewStream)

#define IAMMultiMediaStream_OpenFile(This,pszFileName,dwFlags)	\
    (This)->lpVtbl -> OpenFile(This,pszFileName,dwFlags)

#define IAMMultiMediaStream_OpenMoniker(This,pCtx,pMoniker,dwFlags)	\
    (This)->lpVtbl -> OpenMoniker(This,pCtx,pMoniker,dwFlags)

#define IAMMultiMediaStream_Render(This,dwFlags)	\
    (This)->lpVtbl -> Render(This,dwFlags)

#endif 


#endif 	



	HRESULT STDMETHODCALLTYPE IAMMultiMediaStream_Initialize_Proxy(
		IAMMultiMediaStream * This,
		STREAM_TYPE StreamType,
		DWORD dwFlags,
		IGraphBuilder *pFilterGraph);


	void __RPC_STUB IAMMultiMediaStream_Initialize_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMultiMediaStream_GetFilterGraph_Proxy(
		IAMMultiMediaStream * This,
		IGraphBuilder **ppGraphBuilder);


	void __RPC_STUB IAMMultiMediaStream_GetFilterGraph_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMultiMediaStream_GetFilter_Proxy(
		IAMMultiMediaStream * This,
		IMediaStreamFilter **ppFilter);


	void __RPC_STUB IAMMultiMediaStream_GetFilter_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMultiMediaStream_AddMediaStream_Proxy(
		IAMMultiMediaStream * This,
		IUnknown *pStreamObject,
		const MSPID *PurposeId,
		DWORD dwFlags,
		IMediaStream **ppNewStream);


	void __RPC_STUB IAMMultiMediaStream_AddMediaStream_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMultiMediaStream_OpenFile_Proxy(
		IAMMultiMediaStream * This,
		LPCWSTR pszFileName,
		DWORD dwFlags);


	void __RPC_STUB IAMMultiMediaStream_OpenFile_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMultiMediaStream_OpenMoniker_Proxy(
		IAMMultiMediaStream * This,
		IBindCtx *pCtx,
		IMoniker *pMoniker,
		DWORD dwFlags);


	void __RPC_STUB IAMMultiMediaStream_OpenMoniker_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMultiMediaStream_Render_Proxy(
		IAMMultiMediaStream * This,
		DWORD dwFlags);


	void __RPC_STUB IAMMultiMediaStream_Render_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);



#endif 	


#ifndef __IAMMediaStream_INTERFACE_DEFINED__
#define __IAMMediaStream_INTERFACE_DEFINED__





	EXTERN_C const IID IID_IAMMediaStream;

#if defined(__cplusplus) && !defined(CINTERFACE)

	MIDL_INTERFACE("BEBE595D-9A6F-11d0-8FDE-00C04FD9189D")
		IAMMediaStream : public IMediaStream
	{
	public:
		virtual HRESULT STDMETHODCALLTYPE Initialize(
			 IUnknown *pSourceObject,
			 DWORD dwFlags,
			 REFMSPID PurposeId,
			 const STREAM_TYPE StreamType) = 0;

		virtual HRESULT STDMETHODCALLTYPE SetState(
			 FILTER_STATE State) = 0;

		virtual HRESULT STDMETHODCALLTYPE JoinAMMultiMediaStream(
			 IAMMultiMediaStream *pAMMultiMediaStream) = 0;

		virtual HRESULT STDMETHODCALLTYPE JoinFilter(
			 IMediaStreamFilter *pMediaStreamFilter) = 0;

		virtual HRESULT STDMETHODCALLTYPE JoinFilterGraph(
			 IFilterGraph *pFilterGraph) = 0;

	};

#else 	

	typedef struct IAMMediaStreamVtbl
	{
		BEGIN_INTERFACE

			HRESULT(STDMETHODCALLTYPE *QueryInterface)(
				IAMMediaStream * This,
				REFIID riid,
				void **ppvObject);

		ULONG(STDMETHODCALLTYPE *AddRef)(
			IAMMediaStream * This);

		ULONG(STDMETHODCALLTYPE *Release)(
			IAMMediaStream * This);

		HRESULT(STDMETHODCALLTYPE *GetMultiMediaStream)(
			IAMMediaStream * This,
			IMultiMediaStream **ppMultiMediaStream);

		HRESULT(STDMETHODCALLTYPE *GetInformation)(
			IAMMediaStream * This,
			MSPID *pPurposeId,
			STREAM_TYPE *pType);

		HRESULT(STDMETHODCALLTYPE *SetSameFormat)(
			IAMMediaStream * This,
			IMediaStream *pStreamThatHasDesiredFormat,
			DWORD dwFlags);

		HRESULT(STDMETHODCALLTYPE *AllocateSample)(
			IAMMediaStream * This,
			DWORD dwFlags,
			IStreamSample **ppSample);

		HRESULT(STDMETHODCALLTYPE *CreateSharedSample)(
			IAMMediaStream * This,
			IStreamSample *pExistingSample,
			DWORD dwFlags,
			IStreamSample **ppNewSample);

		HRESULT(STDMETHODCALLTYPE *SendEndOfStream)(
			IAMMediaStream * This,
			DWORD dwFlags);

		HRESULT(STDMETHODCALLTYPE *Initialize)(
			IAMMediaStream * This,
			IUnknown *pSourceObject,
			DWORD dwFlags,
			REFMSPID PurposeId,
			const STREAM_TYPE StreamType);

		HRESULT(STDMETHODCALLTYPE *SetState)(
			IAMMediaStream * This,
			FILTER_STATE State);

		HRESULT(STDMETHODCALLTYPE *JoinAMMultiMediaStream)(
			IAMMediaStream * This,
			IAMMultiMediaStream *pAMMultiMediaStream);

		HRESULT(STDMETHODCALLTYPE *JoinFilter)(
			IAMMediaStream * This,
			IMediaStreamFilter *pMediaStreamFilter);

		HRESULT(STDMETHODCALLTYPE *JoinFilterGraph)(
			IAMMediaStream * This,
			IFilterGraph *pFilterGraph);

		END_INTERFACE
	} IAMMediaStreamVtbl;

	interface IAMMediaStream
	{
		CONST_VTBL struct IAMMediaStreamVtbl *lpVtbl;
	};



#ifdef COBJMACROS


#define IAMMediaStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMMediaStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMMediaStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMMediaStream_GetMultiMediaStream(This,ppMultiMediaStream)	\
    (This)->lpVtbl -> GetMultiMediaStream(This,ppMultiMediaStream)

#define IAMMediaStream_GetInformation(This,pPurposeId,pType)	\
    (This)->lpVtbl -> GetInformation(This,pPurposeId,pType)

#define IAMMediaStream_SetSameFormat(This,pStreamThatHasDesiredFormat,dwFlags)	\
    (This)->lpVtbl -> SetSameFormat(This,pStreamThatHasDesiredFormat,dwFlags)

#define IAMMediaStream_AllocateSample(This,dwFlags,ppSample)	\
    (This)->lpVtbl -> AllocateSample(This,dwFlags,ppSample)

#define IAMMediaStream_CreateSharedSample(This,pExistingSample,dwFlags,ppNewSample)	\
    (This)->lpVtbl -> CreateSharedSample(This,pExistingSample,dwFlags,ppNewSample)

#define IAMMediaStream_SendEndOfStream(This,dwFlags)	\
    (This)->lpVtbl -> SendEndOfStream(This,dwFlags)


#define IAMMediaStream_Initialize(This,pSourceObject,dwFlags,PurposeId,StreamType)	\
    (This)->lpVtbl -> Initialize(This,pSourceObject,dwFlags,PurposeId,StreamType)

#define IAMMediaStream_SetState(This,State)	\
    (This)->lpVtbl -> SetState(This,State)

#define IAMMediaStream_JoinAMMultiMediaStream(This,pAMMultiMediaStream)	\
    (This)->lpVtbl -> JoinAMMultiMediaStream(This,pAMMultiMediaStream)

#define IAMMediaStream_JoinFilter(This,pMediaStreamFilter)	\
    (This)->lpVtbl -> JoinFilter(This,pMediaStreamFilter)

#define IAMMediaStream_JoinFilterGraph(This,pFilterGraph)	\
    (This)->lpVtbl -> JoinFilterGraph(This,pFilterGraph)

#endif 


#endif 	



	HRESULT STDMETHODCALLTYPE IAMMediaStream_Initialize_Proxy(
		IAMMediaStream * This,
		IUnknown *pSourceObject,
		DWORD dwFlags,
		REFMSPID PurposeId,
		const STREAM_TYPE StreamType);


	void __RPC_STUB IAMMediaStream_Initialize_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaStream_SetState_Proxy(
		IAMMediaStream * This,
		FILTER_STATE State);


	void __RPC_STUB IAMMediaStream_SetState_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaStream_JoinAMMultiMediaStream_Proxy(
		IAMMediaStream * This,
		IAMMultiMediaStream *pAMMultiMediaStream);


	void __RPC_STUB IAMMediaStream_JoinAMMultiMediaStream_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaStream_JoinFilter_Proxy(
		IAMMediaStream * This,
		IMediaStreamFilter *pMediaStreamFilter);


	void __RPC_STUB IAMMediaStream_JoinFilter_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaStream_JoinFilterGraph_Proxy(
		IAMMediaStream * This,
		IFilterGraph *pFilterGraph);


	void __RPC_STUB IAMMediaStream_JoinFilterGraph_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);



#endif 	


#ifndef __IMediaStreamFilter_INTERFACE_DEFINED__
#define __IMediaStreamFilter_INTERFACE_DEFINED__





	EXTERN_C const IID IID_IMediaStreamFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)

	MIDL_INTERFACE("BEBE595E-9A6F-11d0-8FDE-00C04FD9189D")
		IMediaStreamFilter : public IBaseFilter
	{
	public:
		virtual HRESULT STDMETHODCALLTYPE AddMediaStream(
			 IAMMediaStream *pAMMediaStream) = 0;

		virtual HRESULT STDMETHODCALLTYPE GetMediaStream(
			 REFMSPID idPurpose,
			 IMediaStream **ppMediaStream) = 0;

		virtual HRESULT STDMETHODCALLTYPE EnumMediaStreams(
			 long Index,
			 IMediaStream **ppMediaStream) = 0;

		virtual HRESULT STDMETHODCALLTYPE SupportSeeking(
			 BOOL bRenderer) = 0;

		virtual HRESULT STDMETHODCALLTYPE ReferenceTimeToStreamTime(
			 REFERENCE_TIME *pTime) = 0;

		virtual HRESULT STDMETHODCALLTYPE GetCurrentStreamTime(
			 REFERENCE_TIME *pCurrentStreamTime) = 0;

		virtual HRESULT STDMETHODCALLTYPE WaitUntil(
			 REFERENCE_TIME WaitStreamTime) = 0;

		virtual HRESULT STDMETHODCALLTYPE Flush(
			 BOOL bCancelEOS) = 0;

		virtual HRESULT STDMETHODCALLTYPE EndOfStream(void) = 0;

	};

#else 	

	typedef struct IMediaStreamFilterVtbl
	{
		BEGIN_INTERFACE

			HRESULT(STDMETHODCALLTYPE *QueryInterface)(
				IMediaStreamFilter * This,
				REFIID riid,
				void **ppvObject);

		ULONG(STDMETHODCALLTYPE *AddRef)(
			IMediaStreamFilter * This);

		ULONG(STDMETHODCALLTYPE *Release)(
			IMediaStreamFilter * This);

		HRESULT(STDMETHODCALLTYPE *GetClassID)(
			IMediaStreamFilter * This,
			CLSID *pClassID);

		HRESULT(STDMETHODCALLTYPE *Stop)(
			IMediaStreamFilter * This);

		HRESULT(STDMETHODCALLTYPE *Pause)(
			IMediaStreamFilter * This);

		HRESULT(STDMETHODCALLTYPE *Run)(
			IMediaStreamFilter * This,
			REFERENCE_TIME tStart);

		HRESULT(STDMETHODCALLTYPE *GetState)(
			IMediaStreamFilter * This,
			DWORD dwMilliSecsTimeout,
			FILTER_STATE *State);

		HRESULT(STDMETHODCALLTYPE *SetSyncSource)(
			IMediaStreamFilter * This,
			IReferenceClock *pClock);

		HRESULT(STDMETHODCALLTYPE *GetSyncSource)(
			IMediaStreamFilter * This,
			IReferenceClock **pClock);

		HRESULT(STDMETHODCALLTYPE *EnumPins)(
			IMediaStreamFilter * This,
			IEnumPins **ppEnum);

		HRESULT(STDMETHODCALLTYPE *FindPin)(
			IMediaStreamFilter * This,
			LPCWSTR Id,
			IPin **ppPin);

		HRESULT(STDMETHODCALLTYPE *QueryFilterInfo)(
			IMediaStreamFilter * This,
			FILTER_INFO *pInfo);

		HRESULT(STDMETHODCALLTYPE *JoinFilterGraph)(
			IMediaStreamFilter * This,
			IFilterGraph *pGraph,
			LPCWSTR pName);

		HRESULT(STDMETHODCALLTYPE *QueryVendorInfo)(
			IMediaStreamFilter * This,
			LPWSTR *pVendorInfo);

		HRESULT(STDMETHODCALLTYPE *AddMediaStream)(
			IMediaStreamFilter * This,
			IAMMediaStream *pAMMediaStream);

		HRESULT(STDMETHODCALLTYPE *GetMediaStream)(
			IMediaStreamFilter * This,
			REFMSPID idPurpose,
			IMediaStream **ppMediaStream);

		HRESULT(STDMETHODCALLTYPE *EnumMediaStreams)(
			IMediaStreamFilter * This,
			long Index,
			IMediaStream **ppMediaStream);

		HRESULT(STDMETHODCALLTYPE *SupportSeeking)(
			IMediaStreamFilter * This,
			BOOL bRenderer);

		HRESULT(STDMETHODCALLTYPE *ReferenceTimeToStreamTime)(
			IMediaStreamFilter * This,
			REFERENCE_TIME *pTime);

		HRESULT(STDMETHODCALLTYPE *GetCurrentStreamTime)(
			IMediaStreamFilter * This,
			REFERENCE_TIME *pCurrentStreamTime);

		HRESULT(STDMETHODCALLTYPE *WaitUntil)(
			IMediaStreamFilter * This,
			REFERENCE_TIME WaitStreamTime);

		HRESULT(STDMETHODCALLTYPE *Flush)(
			IMediaStreamFilter * This,
			BOOL bCancelEOS);

		HRESULT(STDMETHODCALLTYPE *EndOfStream)(
			IMediaStreamFilter * This);

		END_INTERFACE
	} IMediaStreamFilterVtbl;

	interface IMediaStreamFilter
	{
		CONST_VTBL struct IMediaStreamFilterVtbl *lpVtbl;
	};



#ifdef COBJMACROS


#define IMediaStreamFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaStreamFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaStreamFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaStreamFilter_GetClassID(This,pClassID)	\
    (This)->lpVtbl -> GetClassID(This,pClassID)


#define IMediaStreamFilter_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IMediaStreamFilter_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IMediaStreamFilter_Run(This,tStart)	\
    (This)->lpVtbl -> Run(This,tStart)

#define IMediaStreamFilter_GetState(This,dwMilliSecsTimeout,State)	\
    (This)->lpVtbl -> GetState(This,dwMilliSecsTimeout,State)

#define IMediaStreamFilter_SetSyncSource(This,pClock)	\
    (This)->lpVtbl -> SetSyncSource(This,pClock)

#define IMediaStreamFilter_GetSyncSource(This,pClock)	\
    (This)->lpVtbl -> GetSyncSource(This,pClock)


#define IMediaStreamFilter_EnumPins(This,ppEnum)	\
    (This)->lpVtbl -> EnumPins(This,ppEnum)

#define IMediaStreamFilter_FindPin(This,Id,ppPin)	\
    (This)->lpVtbl -> FindPin(This,Id,ppPin)

#define IMediaStreamFilter_QueryFilterInfo(This,pInfo)	\
    (This)->lpVtbl -> QueryFilterInfo(This,pInfo)

#define IMediaStreamFilter_JoinFilterGraph(This,pGraph,pName)	\
    (This)->lpVtbl -> JoinFilterGraph(This,pGraph,pName)

#define IMediaStreamFilter_QueryVendorInfo(This,pVendorInfo)	\
    (This)->lpVtbl -> QueryVendorInfo(This,pVendorInfo)


#define IMediaStreamFilter_AddMediaStream(This,pAMMediaStream)	\
    (This)->lpVtbl -> AddMediaStream(This,pAMMediaStream)

#define IMediaStreamFilter_GetMediaStream(This,idPurpose,ppMediaStream)	\
    (This)->lpVtbl -> GetMediaStream(This,idPurpose,ppMediaStream)

#define IMediaStreamFilter_EnumMediaStreams(This,Index,ppMediaStream)	\
    (This)->lpVtbl -> EnumMediaStreams(This,Index,ppMediaStream)

#define IMediaStreamFilter_SupportSeeking(This,bRenderer)	\
    (This)->lpVtbl -> SupportSeeking(This,bRenderer)

#define IMediaStreamFilter_ReferenceTimeToStreamTime(This,pTime)	\
    (This)->lpVtbl -> ReferenceTimeToStreamTime(This,pTime)

#define IMediaStreamFilter_GetCurrentStreamTime(This,pCurrentStreamTime)	\
    (This)->lpVtbl -> GetCurrentStreamTime(This,pCurrentStreamTime)

#define IMediaStreamFilter_WaitUntil(This,WaitStreamTime)	\
    (This)->lpVtbl -> WaitUntil(This,WaitStreamTime)

#define IMediaStreamFilter_Flush(This,bCancelEOS)	\
    (This)->lpVtbl -> Flush(This,bCancelEOS)

#define IMediaStreamFilter_EndOfStream(This)	\
    (This)->lpVtbl -> EndOfStream(This)

#endif 


#endif 	



	HRESULT STDMETHODCALLTYPE IMediaStreamFilter_AddMediaStream_Proxy(
		IMediaStreamFilter * This,
		IAMMediaStream *pAMMediaStream);


	void __RPC_STUB IMediaStreamFilter_AddMediaStream_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IMediaStreamFilter_GetMediaStream_Proxy(
		IMediaStreamFilter * This,
		REFMSPID idPurpose,
		IMediaStream **ppMediaStream);


	void __RPC_STUB IMediaStreamFilter_GetMediaStream_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IMediaStreamFilter_EnumMediaStreams_Proxy(
		IMediaStreamFilter * This,
		long Index,
		IMediaStream **ppMediaStream);


	void __RPC_STUB IMediaStreamFilter_EnumMediaStreams_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IMediaStreamFilter_SupportSeeking_Proxy(
		IMediaStreamFilter * This,
		BOOL bRenderer);


	void __RPC_STUB IMediaStreamFilter_SupportSeeking_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IMediaStreamFilter_ReferenceTimeToStreamTime_Proxy(
		IMediaStreamFilter * This,
		REFERENCE_TIME *pTime);


	void __RPC_STUB IMediaStreamFilter_ReferenceTimeToStreamTime_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IMediaStreamFilter_GetCurrentStreamTime_Proxy(
		IMediaStreamFilter * This,
		REFERENCE_TIME *pCurrentStreamTime);


	void __RPC_STUB IMediaStreamFilter_GetCurrentStreamTime_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IMediaStreamFilter_WaitUntil_Proxy(
		IMediaStreamFilter * This,
		REFERENCE_TIME WaitStreamTime);


	void __RPC_STUB IMediaStreamFilter_WaitUntil_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IMediaStreamFilter_Flush_Proxy(
		IMediaStreamFilter * This,
		BOOL bCancelEOS);


	void __RPC_STUB IMediaStreamFilter_Flush_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IMediaStreamFilter_EndOfStream_Proxy(
		IMediaStreamFilter * This);


	void __RPC_STUB IMediaStreamFilter_EndOfStream_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);



#endif 	


#ifndef __IDirectDrawMediaSampleAllocator_INTERFACE_DEFINED__
#define __IDirectDrawMediaSampleAllocator_INTERFACE_DEFINED__





	EXTERN_C const IID IID_IDirectDrawMediaSampleAllocator;

#if defined(__cplusplus) && !defined(CINTERFACE)

	MIDL_INTERFACE("AB6B4AFC-F6E4-11d0-900D-00C04FD9189D")
		IDirectDrawMediaSampleAllocator : public IUnknown
	{
	public:
		virtual HRESULT STDMETHODCALLTYPE GetDirectDraw(
			IDirectDraw **ppDirectDraw) = 0;

	};

#else 	

	typedef struct IDirectDrawMediaSampleAllocatorVtbl
	{
		BEGIN_INTERFACE

			HRESULT(STDMETHODCALLTYPE *QueryInterface)(
				IDirectDrawMediaSampleAllocator * This,
				REFIID riid,
				void **ppvObject);

		ULONG(STDMETHODCALLTYPE *AddRef)(
			IDirectDrawMediaSampleAllocator * This);

		ULONG(STDMETHODCALLTYPE *Release)(
			IDirectDrawMediaSampleAllocator * This);

		HRESULT(STDMETHODCALLTYPE *GetDirectDraw)(
			IDirectDrawMediaSampleAllocator * This,
			IDirectDraw **ppDirectDraw);

		END_INTERFACE
	} IDirectDrawMediaSampleAllocatorVtbl;

	interface IDirectDrawMediaSampleAllocator
	{
		CONST_VTBL struct IDirectDrawMediaSampleAllocatorVtbl *lpVtbl;
	};



#ifdef COBJMACROS


#define IDirectDrawMediaSampleAllocator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDirectDrawMediaSampleAllocator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDirectDrawMediaSampleAllocator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDirectDrawMediaSampleAllocator_GetDirectDraw(This,ppDirectDraw)	\
    (This)->lpVtbl -> GetDirectDraw(This,ppDirectDraw)

#endif 


#endif 	



	HRESULT STDMETHODCALLTYPE IDirectDrawMediaSampleAllocator_GetDirectDraw_Proxy(
		IDirectDrawMediaSampleAllocator * This,
		IDirectDraw **ppDirectDraw);


	void __RPC_STUB IDirectDrawMediaSampleAllocator_GetDirectDraw_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);



#endif 	


#ifndef __IDirectDrawMediaSample_INTERFACE_DEFINED__
#define __IDirectDrawMediaSample_INTERFACE_DEFINED__





	EXTERN_C const IID IID_IDirectDrawMediaSample;

#if defined(__cplusplus) && !defined(CINTERFACE)

	MIDL_INTERFACE("AB6B4AFE-F6E4-11d0-900D-00C04FD9189D")
		IDirectDrawMediaSample : public IUnknown
	{
	public:
		virtual HRESULT STDMETHODCALLTYPE GetSurfaceAndReleaseLock(
			 IDirectDrawSurface **ppDirectDrawSurface,
			 RECT *pRect) = 0;

		virtual HRESULT STDMETHODCALLTYPE LockMediaSamplePointer(void) = 0;

	};

#else 	

	typedef struct IDirectDrawMediaSampleVtbl
	{
		BEGIN_INTERFACE

			HRESULT(STDMETHODCALLTYPE *QueryInterface)(
				IDirectDrawMediaSample * This,
				REFIID riid,
				void **ppvObject);

		ULONG(STDMETHODCALLTYPE *AddRef)(
			IDirectDrawMediaSample * This);

		ULONG(STDMETHODCALLTYPE *Release)(
			IDirectDrawMediaSample * This);

		HRESULT(STDMETHODCALLTYPE *GetSurfaceAndReleaseLock)(
			IDirectDrawMediaSample * This,
			IDirectDrawSurface **ppDirectDrawSurface,
			RECT *pRect);

		HRESULT(STDMETHODCALLTYPE *LockMediaSamplePointer)(
			IDirectDrawMediaSample * This);

		END_INTERFACE
	} IDirectDrawMediaSampleVtbl;

	interface IDirectDrawMediaSample
	{
		CONST_VTBL struct IDirectDrawMediaSampleVtbl *lpVtbl;
	};



#ifdef COBJMACROS


#define IDirectDrawMediaSample_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDirectDrawMediaSample_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDirectDrawMediaSample_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDirectDrawMediaSample_GetSurfaceAndReleaseLock(This,ppDirectDrawSurface,pRect)	\
    (This)->lpVtbl -> GetSurfaceAndReleaseLock(This,ppDirectDrawSurface,pRect)

#define IDirectDrawMediaSample_LockMediaSamplePointer(This)	\
    (This)->lpVtbl -> LockMediaSamplePointer(This)

#endif 


#endif 	



	HRESULT STDMETHODCALLTYPE IDirectDrawMediaSample_GetSurfaceAndReleaseLock_Proxy(
		IDirectDrawMediaSample * This,
		IDirectDrawSurface **ppDirectDrawSurface,
		RECT *pRect);


	void __RPC_STUB IDirectDrawMediaSample_GetSurfaceAndReleaseLock_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IDirectDrawMediaSample_LockMediaSamplePointer_Proxy(
		IDirectDrawMediaSample * This);


	void __RPC_STUB IDirectDrawMediaSample_LockMediaSamplePointer_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);



#endif 	


#ifndef __IAMMediaTypeStream_INTERFACE_DEFINED__
#define __IAMMediaTypeStream_INTERFACE_DEFINED__





	EXTERN_C const IID IID_IAMMediaTypeStream;

#if defined(__cplusplus) && !defined(CINTERFACE)

	MIDL_INTERFACE("AB6B4AFA-F6E4-11d0-900D-00C04FD9189D")
		IAMMediaTypeStream : public IMediaStream
	{
	public:
		virtual HRESULT STDMETHODCALLTYPE GetFormat(
			 AM_MEDIA_TYPE *pMediaType,
			 DWORD dwFlags) = 0;

		virtual HRESULT STDMETHODCALLTYPE SetFormat(
			 AM_MEDIA_TYPE *pMediaType,
			 DWORD dwFlags) = 0;

		virtual HRESULT STDMETHODCALLTYPE CreateSample(
			 long lSampleSize,
			 BYTE *pbBuffer,
			 DWORD dwFlags,
			 IUnknown *pUnkOuter,
			 IAMMediaTypeSample **ppAMMediaTypeSample) = 0;

		virtual HRESULT STDMETHODCALLTYPE GetStreamAllocatorRequirements(
			 ALLOCATOR_PROPERTIES *pProps) = 0;

		virtual HRESULT STDMETHODCALLTYPE SetStreamAllocatorRequirements(
			 ALLOCATOR_PROPERTIES *pProps) = 0;

	};

#else 	

	typedef struct IAMMediaTypeStreamVtbl
	{
		BEGIN_INTERFACE

			HRESULT(STDMETHODCALLTYPE *QueryInterface)(
				IAMMediaTypeStream * This,
				REFIID riid,
				void **ppvObject);

		ULONG(STDMETHODCALLTYPE *AddRef)(
			IAMMediaTypeStream * This);

		ULONG(STDMETHODCALLTYPE *Release)(
			IAMMediaTypeStream * This);

		HRESULT(STDMETHODCALLTYPE *GetMultiMediaStream)(
			IAMMediaTypeStream * This,
			IMultiMediaStream **ppMultiMediaStream);

		HRESULT(STDMETHODCALLTYPE *GetInformation)(
			IAMMediaTypeStream * This,
			MSPID *pPurposeId,
			STREAM_TYPE *pType);

		HRESULT(STDMETHODCALLTYPE *SetSameFormat)(
			IAMMediaTypeStream * This,
			IMediaStream *pStreamThatHasDesiredFormat,
			DWORD dwFlags);

		HRESULT(STDMETHODCALLTYPE *AllocateSample)(
			IAMMediaTypeStream * This,
			DWORD dwFlags,
			IStreamSample **ppSample);

		HRESULT(STDMETHODCALLTYPE *CreateSharedSample)(
			IAMMediaTypeStream * This,
			IStreamSample *pExistingSample,
			DWORD dwFlags,
			IStreamSample **ppNewSample);

		HRESULT(STDMETHODCALLTYPE *SendEndOfStream)(
			IAMMediaTypeStream * This,
			DWORD dwFlags);

		HRESULT(STDMETHODCALLTYPE *GetFormat)(
			IAMMediaTypeStream * This,
			AM_MEDIA_TYPE *pMediaType,
			DWORD dwFlags);

		HRESULT(STDMETHODCALLTYPE *SetFormat)(
			IAMMediaTypeStream * This,
			AM_MEDIA_TYPE *pMediaType,
			DWORD dwFlags);

		HRESULT(STDMETHODCALLTYPE *CreateSample)(
			IAMMediaTypeStream * This,
			long lSampleSize,
			BYTE *pbBuffer,
			DWORD dwFlags,
			IUnknown *pUnkOuter,
			IAMMediaTypeSample **ppAMMediaTypeSample);

		HRESULT(STDMETHODCALLTYPE *GetStreamAllocatorRequirements)(
			IAMMediaTypeStream * This,
			ALLOCATOR_PROPERTIES *pProps);

		HRESULT(STDMETHODCALLTYPE *SetStreamAllocatorRequirements)(
			IAMMediaTypeStream * This,
			ALLOCATOR_PROPERTIES *pProps);

		END_INTERFACE
	} IAMMediaTypeStreamVtbl;

	interface IAMMediaTypeStream
	{
		CONST_VTBL struct IAMMediaTypeStreamVtbl *lpVtbl;
	};



#ifdef COBJMACROS


#define IAMMediaTypeStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMMediaTypeStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMMediaTypeStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMMediaTypeStream_GetMultiMediaStream(This,ppMultiMediaStream)	\
    (This)->lpVtbl -> GetMultiMediaStream(This,ppMultiMediaStream)

#define IAMMediaTypeStream_GetInformation(This,pPurposeId,pType)	\
    (This)->lpVtbl -> GetInformation(This,pPurposeId,pType)

#define IAMMediaTypeStream_SetSameFormat(This,pStreamThatHasDesiredFormat,dwFlags)	\
    (This)->lpVtbl -> SetSameFormat(This,pStreamThatHasDesiredFormat,dwFlags)

#define IAMMediaTypeStream_AllocateSample(This,dwFlags,ppSample)	\
    (This)->lpVtbl -> AllocateSample(This,dwFlags,ppSample)

#define IAMMediaTypeStream_CreateSharedSample(This,pExistingSample,dwFlags,ppNewSample)	\
    (This)->lpVtbl -> CreateSharedSample(This,pExistingSample,dwFlags,ppNewSample)

#define IAMMediaTypeStream_SendEndOfStream(This,dwFlags)	\
    (This)->lpVtbl -> SendEndOfStream(This,dwFlags)


#define IAMMediaTypeStream_GetFormat(This,pMediaType,dwFlags)	\
    (This)->lpVtbl -> GetFormat(This,pMediaType,dwFlags)

#define IAMMediaTypeStream_SetFormat(This,pMediaType,dwFlags)	\
    (This)->lpVtbl -> SetFormat(This,pMediaType,dwFlags)

#define IAMMediaTypeStream_CreateSample(This,lSampleSize,pbBuffer,dwFlags,pUnkOuter,ppAMMediaTypeSample)	\
    (This)->lpVtbl -> CreateSample(This,lSampleSize,pbBuffer,dwFlags,pUnkOuter,ppAMMediaTypeSample)

#define IAMMediaTypeStream_GetStreamAllocatorRequirements(This,pProps)	\
    (This)->lpVtbl -> GetStreamAllocatorRequirements(This,pProps)

#define IAMMediaTypeStream_SetStreamAllocatorRequirements(This,pProps)	\
    (This)->lpVtbl -> SetStreamAllocatorRequirements(This,pProps)

#endif 


#endif 	



	HRESULT STDMETHODCALLTYPE IAMMediaTypeStream_GetFormat_Proxy(
		IAMMediaTypeStream * This,
		AM_MEDIA_TYPE *pMediaType,
		DWORD dwFlags);


	void __RPC_STUB IAMMediaTypeStream_GetFormat_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeStream_SetFormat_Proxy(
		IAMMediaTypeStream * This,
		AM_MEDIA_TYPE *pMediaType,
		DWORD dwFlags);


	void __RPC_STUB IAMMediaTypeStream_SetFormat_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeStream_CreateSample_Proxy(
		IAMMediaTypeStream * This,
		long lSampleSize,
		BYTE *pbBuffer,
		DWORD dwFlags,
		IUnknown *pUnkOuter,
		IAMMediaTypeSample **ppAMMediaTypeSample);


	void __RPC_STUB IAMMediaTypeStream_CreateSample_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeStream_GetStreamAllocatorRequirements_Proxy(
		IAMMediaTypeStream * This,
		ALLOCATOR_PROPERTIES *pProps);


	void __RPC_STUB IAMMediaTypeStream_GetStreamAllocatorRequirements_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeStream_SetStreamAllocatorRequirements_Proxy(
		IAMMediaTypeStream * This,
		ALLOCATOR_PROPERTIES *pProps);


	void __RPC_STUB IAMMediaTypeStream_SetStreamAllocatorRequirements_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);



#endif 	


#ifndef __IAMMediaTypeSample_INTERFACE_DEFINED__
#define __IAMMediaTypeSample_INTERFACE_DEFINED__





	EXTERN_C const IID IID_IAMMediaTypeSample;

#if defined(__cplusplus) && !defined(CINTERFACE)

	MIDL_INTERFACE("AB6B4AFB-F6E4-11d0-900D-00C04FD9189D")
		IAMMediaTypeSample : public IStreamSample
	{
	public:
		virtual HRESULT STDMETHODCALLTYPE SetPointer(
			 BYTE *pBuffer,
			 long lSize) = 0;

		virtual HRESULT STDMETHODCALLTYPE GetPointer(
			 BYTE **ppBuffer) = 0;

		virtual long STDMETHODCALLTYPE GetSize(void) = 0;

		virtual HRESULT STDMETHODCALLTYPE GetTime(
			 REFERENCE_TIME *pTimeStart,
			 REFERENCE_TIME *pTimeEnd) = 0;

		virtual HRESULT STDMETHODCALLTYPE SetTime(
			 REFERENCE_TIME *pTimeStart,
			 REFERENCE_TIME *pTimeEnd) = 0;

		virtual HRESULT STDMETHODCALLTYPE IsSyncPoint(void) = 0;

		virtual HRESULT STDMETHODCALLTYPE SetSyncPoint(
			BOOL bIsSyncPoint) = 0;

		virtual HRESULT STDMETHODCALLTYPE IsPreroll(void) = 0;

		virtual HRESULT STDMETHODCALLTYPE SetPreroll(
			BOOL bIsPreroll) = 0;

		virtual long STDMETHODCALLTYPE GetActualDataLength(void) = 0;

		virtual HRESULT STDMETHODCALLTYPE SetActualDataLength(
			long __MIDL_0020) = 0;

		virtual HRESULT STDMETHODCALLTYPE GetMediaType(
			AM_MEDIA_TYPE **ppMediaType) = 0;

		virtual HRESULT STDMETHODCALLTYPE SetMediaType(
			AM_MEDIA_TYPE *pMediaType) = 0;

		virtual HRESULT STDMETHODCALLTYPE IsDiscontinuity(void) = 0;

		virtual HRESULT STDMETHODCALLTYPE SetDiscontinuity(
			BOOL bDiscontinuity) = 0;

		virtual HRESULT STDMETHODCALLTYPE GetMediaTime(
			 LONGLONG *pTimeStart,
			 LONGLONG *pTimeEnd) = 0;

		virtual HRESULT STDMETHODCALLTYPE SetMediaTime(
			 LONGLONG *pTimeStart,
			 LONGLONG *pTimeEnd) = 0;

	};

#else 	

	typedef struct IAMMediaTypeSampleVtbl
	{
		BEGIN_INTERFACE

			HRESULT(STDMETHODCALLTYPE *QueryInterface)(
				IAMMediaTypeSample * This,
				REFIID riid,
				void **ppvObject);

		ULONG(STDMETHODCALLTYPE *AddRef)(
			IAMMediaTypeSample * This);

		ULONG(STDMETHODCALLTYPE *Release)(
			IAMMediaTypeSample * This);

		HRESULT(STDMETHODCALLTYPE *GetMediaStream)(
			IAMMediaTypeSample * This,
			IMediaStream **ppMediaStream);

		HRESULT(STDMETHODCALLTYPE *GetSampleTimes)(
			IAMMediaTypeSample * This,
			STREAM_TIME *pStartTime,
			STREAM_TIME *pEndTime,
			STREAM_TIME *pCurrentTime);

		HRESULT(STDMETHODCALLTYPE *SetSampleTimes)(
			IAMMediaTypeSample * This,
			const STREAM_TIME *pStartTime,
			const STREAM_TIME *pEndTime);

		HRESULT(STDMETHODCALLTYPE *Update)(
			IAMMediaTypeSample * This,
			DWORD dwFlags,
			HANDLE hEvent,
			PAPCFUNC pfnAPC,
			DWORD_PTR dwAPCData);

		HRESULT(STDMETHODCALLTYPE *CompletionStatus)(
			IAMMediaTypeSample * This,
			DWORD dwFlags,
			DWORD dwMilliseconds);

		HRESULT(STDMETHODCALLTYPE *SetPointer)(
			IAMMediaTypeSample * This,
			BYTE *pBuffer,
			long lSize);

		HRESULT(STDMETHODCALLTYPE *GetPointer)(
			IAMMediaTypeSample * This,
			BYTE **ppBuffer);

		long (STDMETHODCALLTYPE *GetSize)(
			IAMMediaTypeSample * This);

		HRESULT(STDMETHODCALLTYPE *GetTime)(
			IAMMediaTypeSample * This,
			REFERENCE_TIME *pTimeStart,
			REFERENCE_TIME *pTimeEnd);

		HRESULT(STDMETHODCALLTYPE *SetTime)(
			IAMMediaTypeSample * This,
			REFERENCE_TIME *pTimeStart,
			REFERENCE_TIME *pTimeEnd);

		HRESULT(STDMETHODCALLTYPE *IsSyncPoint)(
			IAMMediaTypeSample * This);

		HRESULT(STDMETHODCALLTYPE *SetSyncPoint)(
			IAMMediaTypeSample * This,
			BOOL bIsSyncPoint);

		HRESULT(STDMETHODCALLTYPE *IsPreroll)(
			IAMMediaTypeSample * This);

		HRESULT(STDMETHODCALLTYPE *SetPreroll)(
			IAMMediaTypeSample * This,
			BOOL bIsPreroll);

		long (STDMETHODCALLTYPE *GetActualDataLength)(
			IAMMediaTypeSample * This);

		HRESULT(STDMETHODCALLTYPE *SetActualDataLength)(
			IAMMediaTypeSample * This,
			long __MIDL_0020);

		HRESULT(STDMETHODCALLTYPE *GetMediaType)(
			IAMMediaTypeSample * This,
			AM_MEDIA_TYPE **ppMediaType);

		HRESULT(STDMETHODCALLTYPE *SetMediaType)(
			IAMMediaTypeSample * This,
			AM_MEDIA_TYPE *pMediaType);

		HRESULT(STDMETHODCALLTYPE *IsDiscontinuity)(
			IAMMediaTypeSample * This);

		HRESULT(STDMETHODCALLTYPE *SetDiscontinuity)(
			IAMMediaTypeSample * This,
			BOOL bDiscontinuity);

		HRESULT(STDMETHODCALLTYPE *GetMediaTime)(
			IAMMediaTypeSample * This,
			LONGLONG *pTimeStart,
			LONGLONG *pTimeEnd);

		HRESULT(STDMETHODCALLTYPE *SetMediaTime)(
			IAMMediaTypeSample * This,
			LONGLONG *pTimeStart,
			LONGLONG *pTimeEnd);

		END_INTERFACE
	} IAMMediaTypeSampleVtbl;

	interface IAMMediaTypeSample
	{
		CONST_VTBL struct IAMMediaTypeSampleVtbl *lpVtbl;
	};



#ifdef COBJMACROS


#define IAMMediaTypeSample_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMMediaTypeSample_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMMediaTypeSample_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMMediaTypeSample_GetMediaStream(This,ppMediaStream)	\
    (This)->lpVtbl -> GetMediaStream(This,ppMediaStream)

#define IAMMediaTypeSample_GetSampleTimes(This,pStartTime,pEndTime,pCurrentTime)	\
    (This)->lpVtbl -> GetSampleTimes(This,pStartTime,pEndTime,pCurrentTime)

#define IAMMediaTypeSample_SetSampleTimes(This,pStartTime,pEndTime)	\
    (This)->lpVtbl -> SetSampleTimes(This,pStartTime,pEndTime)

#define IAMMediaTypeSample_Update(This,dwFlags,hEvent,pfnAPC,dwAPCData)	\
    (This)->lpVtbl -> Update(This,dwFlags,hEvent,pfnAPC,dwAPCData)

#define IAMMediaTypeSample_CompletionStatus(This,dwFlags,dwMilliseconds)	\
    (This)->lpVtbl -> CompletionStatus(This,dwFlags,dwMilliseconds)


#define IAMMediaTypeSample_SetPointer(This,pBuffer,lSize)	\
    (This)->lpVtbl -> SetPointer(This,pBuffer,lSize)

#define IAMMediaTypeSample_GetPointer(This,ppBuffer)	\
    (This)->lpVtbl -> GetPointer(This,ppBuffer)

#define IAMMediaTypeSample_GetSize(This)	\
    (This)->lpVtbl -> GetSize(This)

#define IAMMediaTypeSample_GetTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> GetTime(This,pTimeStart,pTimeEnd)

#define IAMMediaTypeSample_SetTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> SetTime(This,pTimeStart,pTimeEnd)

#define IAMMediaTypeSample_IsSyncPoint(This)	\
    (This)->lpVtbl -> IsSyncPoint(This)

#define IAMMediaTypeSample_SetSyncPoint(This,bIsSyncPoint)	\
    (This)->lpVtbl -> SetSyncPoint(This,bIsSyncPoint)

#define IAMMediaTypeSample_IsPreroll(This)	\
    (This)->lpVtbl -> IsPreroll(This)

#define IAMMediaTypeSample_SetPreroll(This,bIsPreroll)	\
    (This)->lpVtbl -> SetPreroll(This,bIsPreroll)

#define IAMMediaTypeSample_GetActualDataLength(This)	\
    (This)->lpVtbl -> GetActualDataLength(This)

#define IAMMediaTypeSample_SetActualDataLength(This,__MIDL_0020)	\
    (This)->lpVtbl -> SetActualDataLength(This,__MIDL_0020)

#define IAMMediaTypeSample_GetMediaType(This,ppMediaType)	\
    (This)->lpVtbl -> GetMediaType(This,ppMediaType)

#define IAMMediaTypeSample_SetMediaType(This,pMediaType)	\
    (This)->lpVtbl -> SetMediaType(This,pMediaType)

#define IAMMediaTypeSample_IsDiscontinuity(This)	\
    (This)->lpVtbl -> IsDiscontinuity(This)

#define IAMMediaTypeSample_SetDiscontinuity(This,bDiscontinuity)	\
    (This)->lpVtbl -> SetDiscontinuity(This,bDiscontinuity)

#define IAMMediaTypeSample_GetMediaTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> GetMediaTime(This,pTimeStart,pTimeEnd)

#define IAMMediaTypeSample_SetMediaTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> SetMediaTime(This,pTimeStart,pTimeEnd)

#endif 


#endif 	



	HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_SetPointer_Proxy(
		IAMMediaTypeSample * This,
		BYTE *pBuffer,
		long lSize);


	void __RPC_STUB IAMMediaTypeSample_SetPointer_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_GetPointer_Proxy(
		IAMMediaTypeSample * This,
		BYTE **ppBuffer);


	void __RPC_STUB IAMMediaTypeSample_GetPointer_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	long STDMETHODCALLTYPE IAMMediaTypeSample_GetSize_Proxy(
		IAMMediaTypeSample * This);


	void __RPC_STUB IAMMediaTypeSample_GetSize_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_GetTime_Proxy(
		IAMMediaTypeSample * This,
		REFERENCE_TIME *pTimeStart,
		REFERENCE_TIME *pTimeEnd);


	void __RPC_STUB IAMMediaTypeSample_GetTime_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_SetTime_Proxy(
		IAMMediaTypeSample * This,
		REFERENCE_TIME *pTimeStart,
		REFERENCE_TIME *pTimeEnd);


	void __RPC_STUB IAMMediaTypeSample_SetTime_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_IsSyncPoint_Proxy(
		IAMMediaTypeSample * This);


	void __RPC_STUB IAMMediaTypeSample_IsSyncPoint_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_SetSyncPoint_Proxy(
		IAMMediaTypeSample * This,
		BOOL bIsSyncPoint);


	void __RPC_STUB IAMMediaTypeSample_SetSyncPoint_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_IsPreroll_Proxy(
		IAMMediaTypeSample * This);


	void __RPC_STUB IAMMediaTypeSample_IsPreroll_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_SetPreroll_Proxy(
		IAMMediaTypeSample * This,
		BOOL bIsPreroll);


	void __RPC_STUB IAMMediaTypeSample_SetPreroll_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	long STDMETHODCALLTYPE IAMMediaTypeSample_GetActualDataLength_Proxy(
		IAMMediaTypeSample * This);


	void __RPC_STUB IAMMediaTypeSample_GetActualDataLength_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_SetActualDataLength_Proxy(
		IAMMediaTypeSample * This,
		long __MIDL_0020);


	void __RPC_STUB IAMMediaTypeSample_SetActualDataLength_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_GetMediaType_Proxy(
		IAMMediaTypeSample * This,
		AM_MEDIA_TYPE **ppMediaType);


	void __RPC_STUB IAMMediaTypeSample_GetMediaType_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_SetMediaType_Proxy(
		IAMMediaTypeSample * This,
		AM_MEDIA_TYPE *pMediaType);


	void __RPC_STUB IAMMediaTypeSample_SetMediaType_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_IsDiscontinuity_Proxy(
		IAMMediaTypeSample * This);


	void __RPC_STUB IAMMediaTypeSample_IsDiscontinuity_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_SetDiscontinuity_Proxy(
		IAMMediaTypeSample * This,
		BOOL bDiscontinuity);


	void __RPC_STUB IAMMediaTypeSample_SetDiscontinuity_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_GetMediaTime_Proxy(
		IAMMediaTypeSample * This,
		LONGLONG *pTimeStart,
		LONGLONG *pTimeEnd);


	void __RPC_STUB IAMMediaTypeSample_GetMediaTime_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);


	HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_SetMediaTime_Proxy(
		IAMMediaTypeSample * This,
		LONGLONG *pTimeStart,
		LONGLONG *pTimeEnd);


	void __RPC_STUB IAMMediaTypeSample_SetMediaTime_Stub(
		IRpcStubBuffer *This,
		IRpcChannelBuffer *_pRpcChannelBuffer,
		PRPC_MESSAGE _pRpcMessage,
		DWORD *_pdwStubPhase);



#endif 	



#ifndef __DirectShowStreamLib_LIBRARY_DEFINED__
#define __DirectShowStreamLib_LIBRARY_DEFINED__





	EXTERN_C const IID LIBID_DirectShowStreamLib;

	EXTERN_C const CLSID CLSID_AMMultiMediaStream;

#ifdef __cplusplus

	class DECLSPEC_UUID("49c47ce5-9ba4-11d0-8212-00c04fc32c45")
		AMMultiMediaStream;
#endif
#endif 




#ifndef __cplusplus
	EXTERN_C const CLSID CLSID_AMMultiMediaStream;
#endif
	DEFINE_GUID(CLSID_AMDirectDrawStream,
				0x49c47ce4, 0x9ba4, 0x11d0, 0x82, 0x12, 0x00, 0xc0, 0x4f, 0xc3, 0x2c, 0x45);
	DEFINE_GUID(CLSID_AMAudioStream,
				0x8496e040, 0xaf4c, 0x11d0, 0x82, 0x12, 0x00, 0xc0, 0x4f, 0xc3, 0x2c, 0x45);
	DEFINE_GUID(CLSID_AMAudioData,
				0xf2468580, 0xaf8a, 0x11d0, 0x82, 0x12, 0x00, 0xc0, 0x4f, 0xc3, 0x2c, 0x45);
	DEFINE_GUID(CLSID_AMMediaTypeStream,
				0xcf0f2f7c, 0xf7bf, 0x11d0, 0x90, 0xd, 0x0, 0xc0, 0x4f, 0xd9, 0x18, 0x9d);


	extern RPC_IF_HANDLE __MIDL_itf_amstream_0418_v0_0_c_ifspec;
	extern RPC_IF_HANDLE __MIDL_itf_amstream_0418_v0_0_s_ifspec;



	unsigned long             __RPC_USER  BSTR_UserSize(unsigned long *, unsigned long, BSTR *);
	unsigned char * __RPC_USER  BSTR_UserMarshal(unsigned long *, unsigned char *, BSTR *);
	unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR *);
	void                      __RPC_USER  BSTR_UserFree(unsigned long *, BSTR *);



#ifdef __cplusplus
}
#endif

#endif



#pragma once
#include "oaidl.h"
#include <ExDispid.h>
#include <Exdisp.h>  //如果提示重复定义的话 把这个删掉

class CWebBrwoser2EventListener : public IDispatch      //DWebBrowserEvents2
{
private:
	void _stdcall BeforeNavigate2(IDispatch *pDisp,
		VARIANT &URL, VARIANT &Flags, VARIANT &TargetFrameName,
		VARIANT &PostData, VARIANT &Headers, VARIANT_BOOL &Cancel);
	void _stdcall DocumentComplete(IDispatch *pDisp, VARIANT &URL);
	void _stdcall DownloadBegin();
	void _stdcall DownloadComplete();
	void _stdcall ProgressChange(int Progress, int ProgressMax);
	void _stdcall NewWindow3(VARIANT_BOOL* Cannel,BSTR url);

public: // IDispatch methods
	STDMETHOD(QueryInterface)( REFIID riid, void **ppvObject)
	{
		HRESULT hr = E_NOINTERFACE;
		if (riid == __uuidof(IDispatch))
		{
			*ppvObject = (IDispatch*)this;
			AddRef();
			hr = S_OK;
		}
		else if (riid == __uuidof(DWebBrowserEvents2))
		{
			*ppvObject = (IDispatch*)this;     // DWebBrowserEvents2*
			AddRef();
			hr = S_OK;
		}

		return hr;
	}
	STDMETHODIMP_(ULONG) AddRef(void)
	{
		return 1;
	};
	STDMETHODIMP_(ULONG) Release(void)
	{
		return 1;
	}
	STDMETHOD(GetTypeInfoCount)(UINT*)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetTypeInfo)(UINT, LCID, ITypeInfo**)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetIDsOfNames)(REFIID, LPOLESTR *rgszNames, UINT, LCID, DISPID *rgDispId)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(Invoke)(DISPID dispIdMember,REFIID riid,LCID lcid,WORD wFlags,DISPPARAMS FAR* pDispParams,VARIANT FAR* pVarResult,EXCEPINFO FAR* pExcepInfo,unsigned int FAR* puArgErr)
	{
		HRESULT hr = S_OK;

		if (dispIdMember == DISPID_BEFORENAVIGATE2)
		{
			VARIANT_BOOL Cancel=false;
			IDispatch *pDisp=pDispParams->rgvarg[6].pdispVal;
			VARIANT* pURL = pDispParams->rgvarg[5].pvarVal;
			VARIANT* pFlags = pDispParams->rgvarg[4].pvarVal;
			VARIANT* pTargetFrameName = pDispParams->rgvarg[3].pvarVal;
			VARIANT* pPostData = pDispParams->rgvarg[2].pvarVal;
			VARIANT* pHeaders = pDispParams->rgvarg[1].pvarVal;
			BeforeNavigate2(pDisp, *pURL,* pFlags,*pTargetFrameName,*pPostData,*pHeaders, Cancel);
			*pDispParams->rgvarg[0].pboolVal= Cancel? TRUE:FALSE;
		}
		if (dispIdMember == DISPID_DOCUMENTCOMPLETE)
		{;
			VARIANT* pURL = pDispParams->rgvarg[0].pvarVal;
			DocumentComplete(pDispParams->rgvarg[1].pdispVal, *pURL);
		}
		if (dispIdMember == DISPID_DOWNLOADBEGIN)
		{
			DownloadBegin();
		}
		if (dispIdMember == DISPID_DOWNLOADCOMPLETE)
		{
			DownloadComplete();
		}
		if (dispIdMember == DISPID_PROGRESSCHANGE)
		{
			ProgressChange(pDispParams->rgvarg[1].lVal,pDispParams->rgvarg[0].lVal);
		}
		if (dispIdMember == DISPID_NEWWINDOW3)
		{
			NewWindow3((pDispParams->rgvarg[3].pboolVal),(pDispParams->rgvarg->bstrVal));
		}

		return hr;
	}
};

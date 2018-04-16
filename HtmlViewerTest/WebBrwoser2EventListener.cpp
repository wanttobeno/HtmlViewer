#include <string.h>
#include <tchar.h>
#include "WebBrwoser2EventListener.h"


void _stdcall CWebBrwoser2EventListener::BeforeNavigate2(IDispatch *pDisp,
														VARIANT &URL, VARIANT &Flags, VARIANT &TargetFrameName,
														VARIANT &PostData, VARIANT &Headers, VARIANT_BOOL &Cancel)
{
	if (_tcsstr(URL.bstrVal,_T("news")) )
	{
		OutputDebugStringW(L"No Access To Baidu\t");
		Cancel = TRUE;
	}
}
//---------------------------------------------------------------------------
void _stdcall CWebBrwoser2EventListener::DocumentComplete(IDispatch *pDisp, VARIANT &URL)
{
	IWebBrowser2 *po=(IWebBrowser2 *)pDisp;
	BSTR str[MAX_PATH]={0};
	po->get_LocationName(str);
#ifdef _DEBUG
	OutputDebugStringW(L"DocumentComplete\t");
	OutputDebugStringW(URL.bstrVal);
	OutputDebugStringW(L"\n");
#endif // _DEBUG
}

//---------------------------------------------------------------------------
void _stdcall CWebBrwoser2EventListener::DownloadBegin()
{
	//
}

//---------------------------------------------------------------------------
void _stdcall CWebBrwoser2EventListener::DownloadComplete()
{
	//
}

//---------------------------------------------------------------------------
void _stdcall CWebBrwoser2EventListener::ProgressChange(int Progress, int ProgressMax)
{
	//Form1->Memo1->Lines->Add((String)Progress+"  "+(String)ProgressMax);    //TEST
}

void _stdcall CWebBrwoser2EventListener::NewWindow3(VARIANT_BOOL* Cannel,BSTR url)
{

}
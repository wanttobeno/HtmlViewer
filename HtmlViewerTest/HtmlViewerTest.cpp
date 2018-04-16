#include <tchar.h>
#include <Windows.h>
#include "../Tools/GUI/HtmlViewer/HtmlViewerWindow.h"
#ifdef _DEBUG
#pragma comment(lib,"../Debug/HtmlViewer.lib")
#else
#pragma comment(lib,"../Release/HtmlViewer.lib")
#endif // _DEBUG

#include <ExDispid.h>
#include "WebBrwoser2EventListener.h"

// CElementEvents::Invoke(DISPID dispidMember,...) 处回调
void __stdcall ElementEventsCallBack(DISPID dispidMember,WCHAR* ElementId,LPVOID UserParam)
{
	 switch(dispidMember)
	 {
	 case DISPID_HTMLELEMENTEVENTS2_ONCLICK:
		 {
			//MessageBox(NULL,_T("click event"),_T("Tip"),MB_OK);
			 int nLen = wcslen(ElementId);
			 if (nLen>0)
			 {
				 OutputDebugStringW(ElementId);
				 OutputDebugStringW(L"\n");
			 }
		 }
		 break;
	//case DISPID_HTMLELEMENTEVENTS2_ONKEYDOWN: 
	//	 {
	//		 ::MessageBox(NULL, _T("按键消息"),_T("ie"),MB_ICONSTOP);
	//		 break;
	//	 }
	 default:
			break;
	 }
}

void __stdcall ElementEventsCallBackEx(DISPID dispidMember,IHTMLEventObj* pEvtObj,LPVOID UserParam)
{
	switch(dispidMember)
	{
	case DISPID_HTMLELEMENTEVENTS_ONCLICK: // = DISPID_HTMLELEMENTEVENTS2_ONCLICK
		{
			// MessageBox(NULL,_T("click event"),_T("Tip"),MB_OK);
		}
		break;
	case  DISPID_HTMLELEMENTEVENTS_ONKEYUP:
		{
			int i = 0;
		}
		break;
	default:
		break;
	}
}

int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	CHtmlViewerWindow* pHtmlViewerWindow;
	pHtmlViewerWindow= new CHtmlViewerWindow(800,600);

	HWND hWnd = GetDesktopWindow();
	pHtmlViewerWindow->Show(hInstance,hWnd,_T("My Title"));


	pHtmlViewerWindow->Navigate(_T("http://www.baidu.com"));
	pHtmlViewerWindow->WaitForPageCompleted(NULL);
	pHtmlViewerWindow->SetElementsEventsCallBack(ElementEventsCallBack,NULL);
	pHtmlViewerWindow->SetElementsEventsCallBackEx(ElementEventsCallBackEx,NULL);
	

	//从 pWeb 捕获定义的几个事件了
	IDispatch* pDispatch = pHtmlViewerWindow->GetHTMLDocument();
	IWebBrowser2* pWeb = pHtmlViewerWindow->GetWebBrowser();
	IConnectionPointContainer* pCPC = NULL;
	IConnectionPoint* pCP = NULL;
	DWORD dwCookie = 0;
	pWeb->QueryInterface(IID_IConnectionPointContainer,(void**)&pCPC);
	pCPC->FindConnectionPoint( DIID_DWebBrowserEvents2,&pCP);
	CWebBrwoser2EventListener* pEventListener=new CWebBrwoser2EventListener;
	pCP->Advise( (IUnknown*)(void*)pEventListener,&dwCookie);


	// 开启右键菜单和复制
	pHtmlViewerWindow->EnableContextMenu(TRUE);
	pHtmlViewerWindow->EnableSelection(TRUE);
	


	pHtmlViewerWindow->WaitWindowClose();

	//使用完成后要删除
	pCP->Unadvise(dwCookie); 
	delete pEventListener;

	delete pHtmlViewerWindow;
	return 0;
}
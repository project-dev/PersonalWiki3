// RSSPlugin.cpp : DLL 用の初期化処理の定義を行います。
//

#include "stdafx.h"
#include "RSSPlugin.h"
#include "RssWnd.h"
#include "SetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	メモ!
//
//		この DLL が MFC DLL に対して動的にリンクされる場合、
//		MFC 内で呼び出されるこの DLL からエクスポートされた
//		どの関数も関数の最初に追加される AFX_MANAGE_STATE 
//		マクロを含んでいなければなりません。
//
//		例:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 通常関数の本体はこの位置にあります
//		}
//
//		このマクロが各関数に含まれていること、MFC 内の
//		どの呼び出しより優先することは非常に重要です。
//		これは関数内の最初のステートメントでなければな
//		らないことを意味します、コンストラクタが MFC 
//		DLL 内への呼び出しを行う可能性があるので、オブ
//		ジェクト変数の宣言よりも前でなければなりません。
//
//		詳細については MFC テクニカル ノート 33 および
//		58 を参照してください。
//

/////////////////////////////////////////////////////////////////////////////
// CRSSPluginApp

BEGIN_MESSAGE_MAP(CRSSPluginApp, CWinApp)
	//{{AFX_MSG_MAP(CRSSPluginApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRSSPluginApp の構築

CRSSPluginApp::CRSSPluginApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance の中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CRSSPluginApp オブジェクト

CRSSPluginApp theApp;
CRssWnd g_rssWnd;
static const UINT g_uTabID = ::RegisterWindowMessage("PWIKI_RSSPLUGIN_TAB_WND");

/**
 * @brif 
 */
BOOL WINAPI GetPluginInfo(PPWIKIPLUGIN pInfo){
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	if(!pInfo){
		return FALSE;
	}
	memset(pInfo, 0, sizeof(PWIKIPLUGIN));
	strcpy(pInfo->szName, "RSS Plugin");
	strcpy(pInfo->szInfo, "RSSを表示するプラグイン");
	pInfo->arrType[eTypeTabExtend] = TRUE;
	pInfo->nPlgVersion[0] = 1;
	pInfo->nPlgVersion[1] = 0;
	pInfo->nPlgVersion[2] = 0;
	RSS_EVENT = ::CreateEvent(NULL, FALSE, FALSE, "PersonalWiki_RSSPlugin_Event");
	return TRUE;
}

/**
 * @brif 
 */
BOOL WINAPI ShowSetupDlg(){
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	CSetDlg dlg;
	if(dlg.DoModal() == IDOK){
		//設定変更を反映させる
		g_rssWnd.UpdateConfig();
	}
	return TRUE;
}

/**
 * @brif 
 */
BOOL WINAPI GetUse(){
	char szPath[MAX_PATH + 1];
	char szDrv[MAX_PATH];
	char szDir[MAX_PATH];
	memset(szPath, 0, MAX_PATH + 1);
	memset(szDrv, 0, MAX_PATH);
	memset(szDir, 0, MAX_PATH);
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	_splitpath(szPath, szDrv, szDir, NULL, NULL);
	CString strIni;
	strIni.Format("%s%splugins\\RSSPlugin.ini", szDrv, szDir);
	return ::GetPrivateProfileInt("RSSPlugin", "IsUse", 0, strIni);
}

/**
 * @brif 
 */
void WINAPI SetUse(BOOL bUse){
	char szPath[MAX_PATH + 1];
	char szDrv[MAX_PATH];
	char szDir[MAX_PATH];
	memset(szPath, 0, MAX_PATH + 1);
	memset(szDrv, 0, MAX_PATH);
	memset(szDir, 0, MAX_PATH);
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	_splitpath(szPath, szDrv, szDir, NULL, NULL);
	CString strIni;
	strIni.Format("%s%splugins\\RSSPlugin.ini", szDrv, szDir);
	::WritePrivateProfileString("RSSPlugin", "IsUse", bUse ? "1" : "0", strIni);
}

/**
 * @brif 
 */
BOOL WINAPI ExitPlugin(){
	
	if(::WaitForSingleObject(RSS_EVENT, 0) == WAIT_OBJECT_0){
		return FALSE;
	}
	
	if(::IsWindow(g_rssWnd.m_hWnd)){
		g_rssWnd.SendMessage(WM_CLOSE);
	}

	::CloseHandle(RSS_EVENT);
	return TRUE;
}

/**
 * @brif 
 */
HWND WINAPI GetTabWnd(HWND hParent){
	if(::IsWindow(g_rssWnd.m_hWnd)){
		return g_rssWnd.m_hWnd;
	}
	CRect rect(0, 0, 1, 1);
	CWnd *pWnd = CWnd::FromHandle(hParent);
	g_rssWnd.Create(WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, rect, pWnd, g_uTabID);
	return g_rssWnd.m_hWnd;
}

BOOL CRSSPluginApp::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
	return CWinApp::PreTranslateMessage(pMsg);
}

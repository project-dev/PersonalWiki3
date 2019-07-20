// BinderPlugin.cpp : DLL 用の初期化処理の定義を行います。
//

#include "stdafx.h"
#include "BinderPlugin.h"
#include "BinderWnd.h"
#include "LogFile.h"

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
// CBinderPluginApp

BEGIN_MESSAGE_MAP(CBinderPluginApp, CWinApp)
	//{{AFX_MSG_MAP(CBinderPluginApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBinderPluginApp の構築

CBinderPluginApp::CBinderPluginApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance の中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CBinderPluginApp オブジェクト

CBinderPluginApp theApp;
CBinderWnd g_binderWnd;
static const UINT g_uTabID = ::RegisterWindowMessage("PWIKI_BINDERPLUGIN_TAB_WND");

/**
 * @brif 
 */
BOOL WINAPI GetPluginInfo(PPWIKIPLUGIN pInfo){
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	if(!pInfo){
		return FALSE;
	}
	memset(pInfo, 0, sizeof(PWIKIPLUGIN));
	strcpy(pInfo->szName, "Binder Plugin");
	strcpy(pInfo->szInfo, "WEBサイトの記事をバインドします");
	pInfo->arrType[eTypeTabExtend]  = TRUE;
	pInfo->arrType[eTypeWikiFormat] = TRUE;
	pInfo->nPlgVersion[0] = 1;
	pInfo->nPlgVersion[1] = 0;
	pInfo->nPlgVersion[2] = 0;
	return TRUE;
}

/**
 * @brif 
 */
BOOL WINAPI ShowSetupDlg(){
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
/*
	CSetDlg dlg;
	if(dlg.DoModal() == IDOK){
		//設定変更を反映させる
		g_rssWnd.UpdateConfig();
	}
*/
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
	strIni.Format("%s%splugins\\BinderPlugin.ini", szDrv, szDir);
	return ::GetPrivateProfileInt("BinderPlugin", "IsUse", 0, strIni);
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
	strIni.Format("%s%splugins\\BinderPlugin.ini", szDrv, szDir);
	::WritePrivateProfileString("BinderPlugin", "IsUse", bUse ? "1" : "0", strIni);
}

/**
 * @brif 
 */
BOOL WINAPI ExitPlugin(){
	if(::IsWindow(g_binderWnd.m_hWnd)){
		g_binderWnd.SendMessage(WM_CLOSE);
	}
	return TRUE;
}

/**
 * @brif 
 */
HWND WINAPI GetTabWnd(HWND hParent){
	if(::IsWindow(g_binderWnd.m_hWnd)){
		return g_binderWnd.m_hWnd;
	}
	CRect rect(0, 0, 1, 1);
	CWnd *pWnd = CWnd::FromHandle(hParent);
	g_binderWnd.DestroyWindow();
	g_binderWnd.Create(WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, rect, pWnd, g_uTabID);
	return g_binderWnd.m_hWnd;
}

void WINAPI SetLogFlag(BOOL bLogState, BOOL bAppLogState, BOOL bExceptLogState, BOOL bFatalLogState){
	CLogFile::SetLogState(bLogState);
	CLogFile::SetAppLogState(bAppLogState);	
	CLogFile::SetExceptLogState(bExceptLogState);
	CLogFile::SetFatalLogState(bFatalLogState);
}
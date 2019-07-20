// MainFrm.cpp : CMainFrame クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "PersonalWiki.h"

#include "MainFrm.h"

#include "CalView.h"
#include "ToDoView.h"
#include "InfoTabView.h"
#include "DlgFixData.h"
#include "DlgAppSet.h"
#include "WikiWnd.h"
#include "LogFile.h"
#include <Setupapi.h>

#include <dbt.h>
#include <WINUSER.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
USB_STATE CMainFrame::m_arrUsbState[27];

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_COMMAND(IDM_FIXED_DATA, OnFixedData)
	ON_COMMAND(IDM_PWIKI_SET, OnPwikiSet)
	ON_COMMAND(IDM_CLOSE, OnAppClose)
	ON_COMMAND(IDM_DUMMY, OnDummy)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_COMMAND(IDM_RULE, OnRule)
	ON_COMMAND(IDM_HELP, OnHelp)
	ON_WM_ACTIVATE()
	ON_WM_QUERYENDSESSION()
	ON_COMMAND(ID_APP_END, OnAppEnd)
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
	ON_WM_DEVICECHANGE()
	ON_REGISTERED_MESSAGE(WM_TASKBERCREATED, OnTaskbarCreated)
	ON_MESSAGE(WM_TRYCLICK, OnTrayClick)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ステータス ライン インジケータ
	ID_INDICATOR_KANA,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの構築/消滅

CMainFrame::CMainFrame()
{
	// TODO: この位置にメンバの初期化処理コードを追加してください。
	for(int i = 0; i < 27; i++){
		memset(&m_arrUsbState[i], 0, sizeof(USB_STATE));
		m_arrUsbState[i].szDrv = (char)((int)'A' + i);
		m_arrUsbState[i].bAlive = FALSE;
	}
	m_bEndCall = FALSE;
	m_bEndSession = FALSE;
}	

CMainFrame::~CMainFrame(){
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct){
	CLogFile::SaveAppLog("CMainFrame::OnCreate");
	char szPath[MAX_PATH + 1];
	memset(szPath, 0, MAX_PATH + 1);
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	CString strIniPath = szPath;
	strIniPath.Replace(".exe", ".ini");
	m_objIniFile.IniFileAccess(strIniPath, FALSE);

	MAININFO objInfo;
	m_objIniFile.GetMainInfoIniData(objInfo);

	MoveWindow(objInfo.nX, objInfo.nY, objInfo.nWidth, objInfo.nHeight, FALSE);
//	lpCreateStruct->x = objInfo.nX;
//	lpCreateStruct->y = objInfo.nY;
//	lpCreateStruct->cx = objInfo.nWidth;
//	lpCreateStruct->cy = objInfo.nHeight;

	DEBUGINFO objIni;
	memset(&objIni, 0, sizeof(DEBUGINFO));
	m_objIniFile.GetDebugInfoIniData(objIni);

	CString strMimePath = GetBasePath();
	strMimePath += "MIME.dat";
	m_objMimeTypes.LoadMIME(strMimePath);

	//プラグインロード
	CString strPlugPath = GetBasePath();
	strPlugPath += "plugins\\";
	m_objPlugins.Create(strPlugPath);
	m_objPlugins.EnumPlugins(objIni.bLogOut, objIni.bAppLogOut, objIni.bExceptLogOut, objIni.bFatalLogOut);


	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		/*| CBRS_GRIPPER*/ | CBRS_TOOLTIPS /*| CBRS_FLYBY*/ | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // 作成に失敗
	}
	EnableToolTips(TRUE);
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // 作成に失敗
	}

	TBIMGINFO objTbInfo;
	memset(&objTbInfo, 0, sizeof(TBIMGINFO));
	objTbInfo.crMask = RGB(0, 128, 128);
	objTbInfo.nBtnHeight = 16;
	objTbInfo.nBtnWidth = 16;
	objTbInfo.nButtons = 2;
	objTbInfo.nColorBit = 8;
	objTbInfo.pToolBar = &m_wndToolBar;
	objTbInfo.uID = IDB_MAIN_TB_IMG;
	SetToolbarImg(&objTbInfo);

/*
	// TODO: ツール バーをドッキング可能にしない場合は以下の３行を削除
	//       してください。
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
*/
	m_objNowDate = COleDateTime::GetCurrentTime();
/*
	m_objDlgInfo.SetMainFrame(this);
	m_objDlgInfo.Create(IDD_DLGINFO, NULL);
//	m_objDlgInfo.ShowWindow(SW_SHOWNORMAL);
*/
	SetTrayMode();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs){
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: この位置で CREATESTRUCT cs を修正して、Window クラスやスタイルを
	//       修正してください。
	cs.style &= ~WS_VISIBLE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの診断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame メッセージ ハンドラ


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) {
	CLogFile::SaveAppLog("CMainFrame::OnCreateClient Start");
	// 分割ウィンドウを作成します
	
	MAININFO objInfo;
	m_objIniFile.GetMainInfoIniData(objInfo);
	
	CRect rect;
	GetClientRect(rect);

	CSize szSplLeft(objInfo.nSplitLWidth, rect.Height());
	CSize szSplTop(rect.Width() - objInfo.nSplitLWidth, objInfo.nSplitTHeight);
	CSize szSplBtm(rect.Width() - objInfo.nSplitLWidth, rect.Height() - objInfo.nSplitTHeight);

	if(!m_wndSplitter1.CreateStatic(this, 1, 2)){
		return FALSE;
	}
	if(!m_wndSplitter2.CreateStatic(&m_wndSplitter1, 2, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter1.IdFromRowCol( 0, 1 ))){
		return FALSE;
	}
	if (!m_wndSplitter1.CreateView(0, 0,RUNTIME_CLASS(CCalView), szSplLeft, pContext)){
		m_wndSplitter1.DestroyWindow();
		return FALSE;
	}
	if (!m_wndSplitter2.CreateView(1, 0,RUNTIME_CLASS(CToDoView), szSplBtm, pContext)){
		m_wndSplitter2.DestroyWindow();
		return FALSE;
	}
	if (!m_wndSplitter2.CreateView(0, 0,RUNTIME_CLASS(CInfoTabView), szSplTop, pContext)){
		m_wndSplitter2.DestroyWindow();
		return FALSE;
	}

#if defined(USE_CREATE_VIEW)
	CLogFile::SaveAppLog("USE_CREATE_VIEW");
	CCreateContext ccc;
	ccc.m_pCurrentDoc		= pContext->m_pCurrentDoc;
	ccc.m_pCurrentFrame		= this;
	ccc.m_pLastView			= pContext->m_pLastView;
	ccc.m_pNewDocTemplate	= pContext->m_pNewDocTemplate;

	//Htmlビューの生成
	ccc.m_pNewViewClass	= RUNTIME_CLASS(CInfoView);
	if( !CreateView(&ccc) ){
		CLogFile::SaveAppLog("HTMLViewの生成に失敗");
		return FALSE;
	}
#endif

	CLogFile::SaveAppLog("CMainFrame::OnCreateClient End");
	return TRUE;
//	return CFrameWnd::OnCreateClient(lpcs, pContext);
}
CToDoView* CMainFrame::GetToDoView(){
	if(!::IsWindow(m_wndSplitter2.m_hWnd)){
		return NULL;
	}
	if(m_wndSplitter2.GetRowCount() <= 0){
		return NULL;
	}
	CWnd *pWnd = m_wndSplitter2.GetPane(1, 0);
	if(pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CToDoView))){
		return (CToDoView*)pWnd;
	}else{
		return NULL;
	}
}
CCalView* CMainFrame::GetCalView(){
	if(!::IsWindow(m_wndSplitter1.m_hWnd)){
		return NULL;
	}
	if(m_wndSplitter1.GetColumnCount() <= 0){
		return NULL;
		
	}
	if(m_wndSplitter1.GetRowCount() <= 0){
		return NULL;
	}

	CWnd *pWnd = m_wndSplitter1.GetPane(0, 0);
	if(pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CCalView))){
		return (CCalView*)pWnd;
	}else{
		return NULL;
	}
}

CInfoTabView* CMainFrame::GetInfoTabView(){
	if(!::IsWindow(m_wndSplitter2.m_hWnd)){
		return NULL;
	}
	if(m_wndSplitter2.GetRowCount() <= 0){
		return NULL;
	}
	CWnd *pWnd = m_wndSplitter2.GetPane(0, 0);
	if(pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CInfoTabView))){
		return (CInfoTabView*)pWnd;
	}else{
		return NULL;
	}
}

void CMainFrame::OnDestroy(){

	SetWndRectToIniFile();

	char szPath[MAX_PATH + 1];
	memset(szPath, 0, MAX_PATH + 1);
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	CString strIniPath = szPath;
	strIniPath.Replace(".exe", ".ini");

	m_objIniFile.IniFileAccess(strIniPath, TRUE);
	
	m_objPlugins.ReleasePlugins();
	
	CFrameWnd::OnDestroy();
}

void CMainFrame::OnClose(){
	if(m_bEndCall || m_bEndSession){
		//終了呼び出し、またはWindowsの終了セッション中
		SetWndRectToIniFile();
		m_objDlgInfo.SendMessage(WM_CLOSE);
		SetTrayMode(FALSE);
		CFrameWnd::OnClose();
	}else{
		//それ以外は最小化
		ShowWindow(SW_HIDE);
	}
}

void CMainFrame::SetToDayIinfo(LPCTSTR pszInfo){
	m_objDlgInfo.SetInfo(pszInfo);
}

void CMainFrame::OnFixedData(){
	CDlgFixData dlg;
	if(dlg.DoModal() != IDOK){
		return;
	}
	//表示更新
	CCalView *pView = GetCalView();
	pView->UpdateCalender();
}

void CMainFrame::OnPwikiSet(){
	CLogFile::SaveAppLog("PersonalWikiの設定");
	CDlgAppSet dlg;
	if(dlg.DoModal() != IDOK){
		CLogFile::SaveAppLog("PersonalWikiの設定キャンセル");
		return;
	}
	char szPath[MAX_PATH + 1];
	memset(szPath, 0, MAX_PATH + 1);
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	CString strIniPath = szPath;
	strIniPath.Replace(".exe", ".ini");
	m_objIniFile.IniFileAccess(strIniPath, TRUE);

	CLogFile::SaveAppLog("PersonalWikiの設定OK");
	//表示更新
	CCalView *pView = GetCalView();
	pView->UpdateCalender();
	pView->UpdateShowPluginTab();
}

BOOL CMainFrame::SetTrayMode(BOOL bOnTray){
	BOOL bRet;
	CPWikiApp *pApp = (CPWikiApp*)AfxGetApp();
	if(bOnTray){
		//タスクトレイに常駐する = TRUE
		//多重起動禁止           = TRUE
		//上記の条件を満たす場合のみ表示す
		memset(&m_objNotifyIcon, 0, sizeof(NOTIFYICONDATA));
		m_objNotifyIcon.cbSize	= sizeof(NOTIFYICONDATA);
		m_objNotifyIcon.uID		= IDC_PWIKI_BALLOON;
		m_objNotifyIcon.hWnd	= m_hWnd;
		m_objNotifyIcon.uFlags	= NIF_MESSAGE | NIF_ICON | NIF_TIP;
		m_objNotifyIcon.hIcon	= AfxGetApp()->LoadIcon( IDR_MAINFRAME);;
		m_objNotifyIcon.uCallbackMessage = WM_TRYCLICK;
		lstrcpy( m_objNotifyIcon.szTip, AfxGetAppName());
		bRet = ::Shell_NotifyIcon(NIM_ADD, &m_objNotifyIcon);
	}else{
		bRet = ::Shell_NotifyIcon(NIM_DELETE, &m_objNotifyIcon);

		//タスクトレイのウィンドウハンドルを取得し、確実に再描画を発生させる。
		HWND hwndTray = ::FindWindow(_T("Shell_TrayWnd"), NULL);
		if (hwndTray != NULL) {
			HWND hWndTask = FindWindowEx(hwndTray, NULL, "TrayNotifyWnd", NULL) ;
			if(hWndTask){
				::InvalidateRect(hWndTask, NULL, TRUE);
			}
		}
	}
	return bRet;
}

LRESULT CMainFrame::OnTrayClick(WPARAM wParam, LPARAM lParam){
	CMenu objMenu;
	objMenu.LoadMenu(IDR_DLGINFOMENU);
	CMenu *pPopMenu = objMenu.GetSubMenu(0);
	POINT pos;
	::GetCursorPos(&pos);
    switch( lParam){
    case WM_LBUTTONUP:
		{
			pPopMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, pos.x, pos.y, this);
		}
        break;
    case WM_RBUTTONUP:
		{
			pPopMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, pos.x, pos.y, this);
		}
        break;
    }

	HWND hTryWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
	if(hTryWnd){
		//タスクトレイの再描画
		::InvalidateRect(hTryWnd, NULL, TRUE);
	}
	return 0L;
}
LRESULT CMainFrame::OnTaskbarCreated(WPARAM, LPARAM){
	SetTrayMode();
	return 0;
}

void CMainFrame::OnAppClose() {
	PostMessage(WM_CLOSE);
}

void CMainFrame::OnDummy() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo){
	CCalView *pCalView = GetCalView();
    if(pCalView){
		CWikiWnd *pWikiWnd = pCalView->GetWikiWnd();
		if(pWikiWnd && ::IsWindow(pWikiWnd->m_hWnd)){
			//ツールバーを有効にする為に、コマンドIDをCWikiWndにも送る
			if(pWikiWnd->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo)){
				return TRUE ;
			}
		}
    }	
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus) {
	CFrameWnd::OnShowWindow(bShow, nStatus);
	//m_objDlgInfo.ShowWindow(SW_SHOWNORMAL);
	CRect rect;
	GetWindowRect(rect);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy){
	CFrameWnd::OnSize(nType, cx, cy);
	if(nType == SIZE_MINIMIZED){
		ShowWindow(SW_HIDE);
	}else{
		SetWndRectToIniFile();
	}
}

void CMainFrame::OnRule(){
	CInfoTabView *pInfo = GetInfoTabView();
	if(!pInfo){
		return;
	}
	CString strWikiPage = "ヘルプ/ルール";
	pInfo->UpdateInfo(strWikiPage);
}

void CMainFrame::OnHelp(){
	CInfoTabView *pInfo = GetInfoTabView();
	if(!pInfo){
		return;
	}
	CString strWikiPage = "ヘルプ";
	pInfo->UpdateInfo(strWikiPage);
}


BOOL CMainFrame::OnDeviceChange( UINT nEventType, DWORD dwData ){
#if defined(USE_USB_DOC)
	LINKINFO objIni;
	m_objIniFile.GetLinkInfoIniData(objIni);
	CCalView *pView = GetCalView();
	
	if(objIni.bUseUSBLink){
		switch(nEventType){
		case DBT_DEVICEARRIVAL:
			//追加デバイス使用可能
			CLogFile::SaveAppLog("追加デバイス使用可能");
			break;
		case DBT_DEVICEQUERYREMOVE:
			//デバイス削除要求
			CLogFile::SaveAppLog("デバイス削除要求");
			break;
		case DBT_DEVICEQUERYREMOVEFAILED:
			//デバイス削除要求取り消し
			CLogFile::SaveAppLog("デバイス削除要求取り消し");
			break;
		case DBT_DEVICEREMOVEPENDING:
			//デバイス削除中
			CLogFile::SaveAppLog("デバイス削除中");
			break;
		case DBT_DEVICEREMOVECOMPLETE:
			//デバイス削除完了
			CLogFile::SaveAppLog("デバイス削除完了");
			break;
		case DBT_DEVICETYPESPECIFIC:
			//デバイス固有イベント
			CLogFile::SaveAppLog("デバイス固有イベント");
			break;
		case DBT_CONFIGCHANGED:
			//設定変更
			CLogFile::SaveAppLog("設定変更");
			break;
		case DBT_DEVNODES_CHANGED:
			//デバイスノード変更
			CLogFile::SaveAppLog("デバイスノード変更");
			break;
		default:
			CLogFile::SaveAppLog("不明");
			break;
		}
		
		PDEV_BROADCAST_HDR pDev = NULL;
	//	DEV_BROADCAST_USERDEFINED dbu;

		PDEV_BROADCAST_DEVICEINTERFACE pDevInf = NULL;
		PDEV_BROADCAST_HANDLE pDevHnd = NULL;
		PDEV_BROADCAST_OEM pDevOEM = NULL;
		PDEV_BROADCAST_PORT pDevPort = NULL;
		PDEV_BROADCAST_VOLUME pDevVol = NULL;

		switch(nEventType){
		case DBT_DEVICEARRIVAL:
		case DBT_DEVICEQUERYREMOVE:
		case DBT_DEVICEQUERYREMOVEFAILED:
		case DBT_DEVICEREMOVEPENDING:
		case DBT_DEVICEREMOVECOMPLETE:
			pDev = (PDEV_BROADCAST_HDR)dwData;
			if(pDev->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE){
				pDevInf = (PDEV_BROADCAST_DEVICEINTERFACE)pDev;
			}else if(pDev->dbch_devicetype == DBT_DEVTYP_HANDLE){
				pDevHnd = (PDEV_BROADCAST_HANDLE)pDev;
			}else if(pDev->dbch_devicetype == DBT_DEVTYP_OEM){
				pDevOEM = (PDEV_BROADCAST_OEM)pDev;
			}else if(pDev->dbch_devicetype == DBT_DEVTYP_PORT){
				pDevPort = (PDEV_BROADCAST_PORT)pDev;
			}else if(pDev->dbch_devicetype == DBT_DEVTYP_VOLUME){
				pDevVol = (PDEV_BROADCAST_VOLUME)pDev;
			}
			break;
	//	case DBT_DEVICETYPESPECIFIC:	//デバイス固有イベント
	//	case DBT_CONFIGCHANGED:			//設定変更
	//	case DBT_DEVNODES_CHANGED:		//デバイスノード変更
		default:
			break;
		}

		GUID		guid;
		HANDLE		handle = NULL;
		HDEVNOTIFY	notify = NULL;
		LONG		nmOffset = 0;
		DWORD		dwMask = 0;
		WORD		wFlags = 0;
		DWORD		dwIdentifier;
		DWORD		dwSuppfunc;
		char*		pszName = NULL;
		PBYTE		pByte = NULL;
		CStringArray arrDrv;
		if(pDevInf){
			guid			= pDevInf->dbcc_classguid;
			int nSize		= pDevInf->dbcc_size - sizeof(DEV_BROADCAST_DEVICEINTERFACE);
			pszName			= new char[nSize + 1];
			memset(pszName, 0, nSize + 1);
			strncpy(pszName, &pDevInf->dbcc_name[0], nSize);
		}else if(pDevHnd){
			handle			= pDevHnd->dbch_handle;
			notify			= (HDEVNOTIFY)pDevHnd->dbch_hdevnotify;
			guid			= pDevHnd->dbch_eventguid;
			nmOffset		= pDevHnd->dbch_nameoffset;
			pByte			= new BYTE[nmOffset + 1];
			memset(pByte, 0, nmOffset + 1);
			memcpy(pByte, &pDevHnd->dbch_data[0], nmOffset);
		}else if(pDevOEM){
			dwIdentifier	= pDevOEM->dbco_identifier; 
			dwSuppfunc		= pDevOEM->dbco_suppfunc;
		}else if(pDevPort){
			int nSize		= pDevPort->dbcp_size - sizeof(DEV_BROADCAST_PORT);
			pszName			= new char[nSize + 1];
			memset(pszName, 0, nSize + 1);
			strncpy(pszName, &pDevPort->dbcp_name[0], nSize);
		}else if(pDevVol){
			dwMask			= pDevVol->dbcv_unitmask;
			for(int nDrv = 'A'; nDrv <= 'Z'; nDrv++){
				if(dwMask & 0x0001 << (nDrv - 'A') ? 1 : 0){
					//有効ドライブ
					CString strDrv;
					strDrv.Format("%c:", (char)nDrv);
					arrDrv.Add(strDrv);
					TRACE("%s\n", strDrv);
					CLogFile::SaveAppLog(strDrv);
				}
			}
			wFlags			= pDevVol->dbcv_flags;
		}
		
		WIN32_FIND_DATA wfd;
		HANDLE hRet = NULL;
		switch(nEventType){
		case DBT_DEVICEARRIVAL:
			//追加デバイス使用可能
			{
				BOOL bSend = FALSE;
				int nSize = arrDrv.GetSize();
				for(int i = 0; i < nSize; i++){
					for(int j = 0; j < 4; j++){
						memset(&wfd, 0, sizeof(WIN32_FIND_DATA));
						
						CString strDir = objIni.szLinkDir[j];
						strDir.TrimLeft();
						strDir.TrimRight();
						if(strDir.IsEmpty()){
							continue;
						}
						CString strFind;
						strFind.Format("%s\\%s", arrDrv.GetAt(i), strDir);
						
						hRet = ::FindFirstFile(strFind, &wfd);
						if(hRet != INVALID_HANDLE_VALUE){
							CString strDrv = arrDrv.GetAt(i);
							int nIndex = strDrv.GetAt(0) - 'A';
							m_arrUsbState[nIndex].bAlive = TRUE;
							strncpy(&m_arrUsbState[nIndex].szPath[j][0], strFind, MAX_PATH);
							bSend = TRUE;
						}
						::FindClose(hRet);
					}
				}
				if(bSend && pView){
					//WikiWndに追加通知を行う
					pView->UpdateWikiTree(TRUE);
				}
			}
			break;
		case DBT_DEVICEQUERYREMOVE:
			//デバイス削除要求
			break;
		case DBT_DEVICEQUERYREMOVEFAILED:
			//デバイス削除要求取り消し
			break;
		case DBT_DEVICEREMOVEPENDING:
			//デバイス削除中
			break;
		case DBT_DEVICEREMOVECOMPLETE:
			//デバイス削除完了
			{
				int nSize = arrDrv.GetSize();
				for(int i = 0; i < nSize; i++){
					//WikiWndに削除通知を行う
					CString strDrv = arrDrv.GetAt(i);
					int nIndex = strDrv.GetAt(0) - 'A';
					m_arrUsbState[nIndex].bAlive = FALSE;
					if(pView){
						pView->UpdateWikiTree(TRUE);
					}
				}
			}
			break;
		case DBT_DEVICETYPESPECIFIC:
			//デバイス固有イベント
			break;
		case DBT_CONFIGCHANGED:
			//設定変更
			break;
		case DBT_DEVNODES_CHANGED:
			//デバイスノード変更
			break;
		default:
			break;
		}
	}
#endif
	return CFrameWnd::OnDeviceChange(nEventType, dwData);
}

void CMainFrame::GetUSBDevDrv(CStringArray &arrDrv)
{

}

BOOL CMainFrame::EnumDevice(){
	LINKINFO objIni;
	m_objIniFile.GetLinkInfoIniData(objIni);
	CCalView *pView = GetCalView();
	if(!pView || !::IsWindow(pView->m_hWnd)){
		return TRUE;
	}
	if(!objIni.bUseUSBLink){
		return TRUE;
	}
	BOOL bSend = FALSE;
	char szRetPath[MAX_PATH + 1];
	for(char szDrv = 'A'; szDrv <= 'Z'; szDrv++){
		memset(szRetPath, 0, MAX_PATH + 1);
		CString strDrv;
		strDrv.Format("%c:", szDrv);
		CString strDrvInfo;
		if(::QueryDosDevice(strDrv, szRetPath, MAX_PATH)){
			//成功
			strDrvInfo.Format("%s %s", strDrv, szRetPath);
			UINT uFlag = ::GetDriveType(strDrv);
			switch(uFlag){
			case DRIVE_UNKNOWN:
				strDrvInfo += " DRIVE_UNKNOWN (not target)";
				break;
			case DRIVE_NO_ROOT_DIR:
				strDrvInfo += " DRIVE_NO_ROOT_DIR (not target)";
				break;
			case DRIVE_REMOVABLE:
				{
					for(int j = 0; j < 4; j++){
						WIN32_FIND_DATA wfd;
						memset(&wfd, 0, sizeof(WIN32_FIND_DATA));
						
						CString strDir = objIni.szLinkDir[j];
						strDir.TrimLeft();
						strDir.TrimRight();
						if(strDir.IsEmpty()){
							continue;
						}
						CString strFind;
						strFind.Format("%s\\%s", strDrv, strDir);
						
						HANDLE hRet = ::FindFirstFile(strFind, &wfd);
						if(hRet != INVALID_HANDLE_VALUE){
							int nIndex = (int)(szDrv - 'A');
							m_arrUsbState[nIndex].bAlive = TRUE;
							strncpy(&m_arrUsbState[nIndex].szPath[j][0], strFind, MAX_PATH);
							bSend = TRUE;
						}
						if(hRet != NULL){
							::FindClose(hRet);
						}
					}
				}
				break;
			case DRIVE_FIXED:

				strDrvInfo += " DRIVE_FIXED (not target)";
				break;
			case DRIVE_REMOTE:
				strDrvInfo += " DRIVE_REMOTE (not target)";
				break;
			case DRIVE_CDROM:
				strDrvInfo += " DRIVE_CDROM (not target)";
				break;
			case DRIVE_RAMDISK:
				strDrvInfo += " DRIVE_RAMDISK (not target)";
				break;
			}
		}
	}
	if(pView){
		pView->UpdateWikiTree(TRUE);
	}
	return TRUE;
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) {
	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	CreateDlgInfo();
}

void CMainFrame::CreateDlgInfo(){
	if(!::IsWindow(m_objDlgInfo.m_hWnd)){
		m_objDlgInfo.SetMainFrame(this);
		m_objDlgInfo.Create(IDD_DLGINFO, NULL);
		m_objDlgInfo.ShowWindow(SW_SHOWNORMAL);
	}

}

BOOL CMainFrame::OnQueryEndSession() {
	if (!CFrameWnd::OnQueryEndSession()){
		return FALSE;
	}
	
	m_bEndSession = TRUE;
	return TRUE;
}

void CMainFrame::ApplExit(){
	m_bEndCall = TRUE;
	SendMessage(WM_CLOSE);
}

BOOL CMainFrame::IsEndSession(){
	return m_bEndSession;
}

void CMainFrame::OnAppEnd(){
	ApplExit();
}

void CMainFrame::SetWndRectToIniFile(){
	CCalView* pCalView = GetCalView();
	CInfoTabView* pTabView = GetInfoTabView();
	TRACE("Call SetWndRectToIniFile\n");

	if(!::IsWindow(m_hWnd) || !::IsWindowVisible(m_hWnd)){
		return;
	}
	if(!pCalView || !::IsWindow(pCalView->m_hWnd)){
		return;
	}
	if(!pTabView || !::IsWindow(pTabView->m_hWnd)){
		return;
	}
	MAININFO objInfo;
	m_objIniFile.GetMainInfoIniData(objInfo);

	CRect rect;
	GetWindowRect(rect);

	objInfo.nX = rect.left;
	objInfo.nY = rect.top;
	objInfo.nWidth = rect.Width();
	objInfo.nHeight = rect.Height();

	pCalView->GetWindowRect(rect);
	objInfo.nSplitLWidth = rect.Width();

	pTabView->GetWindowRect(rect);
	objInfo.nSplitTHeight = rect.Height();

	m_objIniFile.SetMainInfoIniData(&objInfo);
	TRACE("Save SetWndRectToIniFile\n");

}

void CMainFrame::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) {
	CFrameWnd::OnWindowPosChanged(lpwndpos);
	CCalView* pCalView = GetCalView();
	CInfoTabView* pTabView = GetInfoTabView();
	CToDoView* pToDo = GetToDoView();
#ifdef _DEBUG
	if(pCalView && pCalView->m_hWnd == lpwndpos->hwnd){
		TRACE("CCalView\n");
	}
	if(pTabView && pTabView->m_hWnd == lpwndpos->hwnd){
		TRACE("CInfoTabView\n");
	}
	if(pToDo && pToDo->m_hWnd == lpwndpos->hwnd){
		TRACE("CToDoView\n");
	}
	switch(lpwndpos->flags){
	case SWP_DRAWFRAME:
		TRACE("SWP_DRAWFRAME\r\n");
		break;
	case SWP_HIDEWINDOW:
		TRACE("SWP_HIDEWINDOW\r\n");
		break;
	case SWP_NOACTIVATE:
		TRACE("SWP_NOACTIVATE\r\n");
		break;
	case SWP_NOCOPYBITS:
		TRACE("SWP_NOCOPYBITS\r\n");
		break;
	case SWP_NOMOVE:
		TRACE("SWP_NOMOVE\r\n");
		break;
	case SWP_NOOWNERZORDER:
		TRACE("SWP_NOOWNERZORDER\r\n");
		break;
	case SWP_NOSIZE:
		TRACE("SWP_NOSIZE\r\n");
		break;
	case SWP_NOREDRAW:
		TRACE("SWP_NOREDRAW\r\n");
		break;
	case SWP_NOSENDCHANGING:
		TRACE("SWP_NOSENDCHANGING\r\n");
		break;
	case SWP_NOZORDER:
		TRACE("SWP_NOZORDER\r\n");
		break;
	case SWP_SHOWWINDOW:
		TRACE("SWP_SHOWWINDOW\r\n");
		break;
	default:
		TRACE("DEFAULT(%d)\r\n", lpwndpos->flags);
		if(lpwndpos->hwnd == m_hWnd){
			if(::IsWindow(m_hWnd)){
				TRACE("CMainFrame(Alive)\n");
			}else{
				TRACE("CMainFrame(Lost)\n");
			}
		}
		if(lpwndpos->flags & SWP_DRAWFRAME){
			TRACE("DEFAULT(SWP_DRAWFRAME)\r\n");
		}
		if(lpwndpos->flags & SWP_HIDEWINDOW){
			TRACE("DEFAULT(SWP_HIDEWINDOW)\r\n");
		}
		if(lpwndpos->flags & SWP_NOACTIVATE){
			TRACE("DEFAULT(SWP_NOACTIVATE)\r\n");
		}
		if(lpwndpos->flags & SWP_NOCOPYBITS){
			TRACE("DEFAULT(SWP_NOCOPYBITS)\r\n");
		}
		if(lpwndpos->flags & SWP_NOMOVE){
			TRACE("DEFAULT(SWP_NOMOVE)\r\n");
		}
		if(lpwndpos->flags & SWP_NOOWNERZORDER){
			TRACE("DEFAULT(SWP_NOOWNERZORDER)\r\n");
		}
		if(lpwndpos->flags & SWP_NOSIZE){
			TRACE("DEFAULT(SWP_NOSIZE)\r\n");
		}
		if(lpwndpos->flags & SWP_NOREDRAW){
			TRACE("DEFAULT(SWP_NOREDRAW)\r\n");
		}
		if(lpwndpos->flags & SWP_NOSENDCHANGING){
			TRACE("DEFAULT(SWP_NOSENDCHANGING)\r\n");
		}
		if(lpwndpos->flags & SWP_NOZORDER){
			TRACE("DEFAULT(SWP_NOZORDER)\r\n");
		}
		if(lpwndpos->flags & SWP_SHOWWINDOW){
			TRACE("DEFAULT(SWP_SHOWWINDOW)\r\n");
		}
		break;
	}
#endif	
	if(lpwndpos->hwnd == m_hWnd && ::IsWindow(m_hWnd) && ::IsWindowVisible(m_hWnd) && !(lpwndpos->flags & SWP_SHOWWINDOW)){
		SetWndRectToIniFile();
	}
}

// RssWnd.cpp: CRssWnd クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RSSPlugin.h"
#include "RssWnd.h"
#include "devlib.h"
#include "RssCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////
CRssWnd::CRssWnd(){
	m_pHtmlView = NULL;
}

CRssWnd::~CRssWnd(){

}

BEGIN_MESSAGE_MAP(CRssWnd, CWnd)
	//{{AFX_MSG_MAP(CRssWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDM_READRSS, OnReadrss)
	ON_UPDATE_COMMAND_UI(IDM_READRSS, OnUpdateReadrss)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CRssWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID){
	return CWnd::Create(NULL, NULL, dwStyle, rect, pParentWnd, nID);
}

int CRssWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect(0,0,0,0);
	CRuntimeClass *pRuntime = RUNTIME_CLASS(CFixHtmlView);

	m_objSepBtn.Create("", WS_CHILD | WS_VISIBLE, rect, this, g_uSepID);
	m_objRssList.Create(WS_CHILD | WS_BORDER | LVS_REPORT | WS_VISIBLE, rect, this, g_uRssID);
	m_objRssList.m_pRssWnd = this;
	
	m_pHtmlView = (CFixHtmlView*)pRuntime->CreateObject();
	m_pHtmlView->Create(NULL, NULL, WS_CHILD | WS_BORDER | WS_VISIBLE, rect, this, g_uHtmID);

	m_objRssList.InsertColumn(0, "ページ名");
	m_objRssList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_objSepBtn.SetSepalatorUD(&m_objRssList, m_pHtmlView);
	SetCtrlPos();


	LoadRSSData();
	LoadIniData();

	SetColumnWidthLC(&m_objRssList);
	UpdateRSSHtml();
	m_uTimerID = SetTimer(g_uTmID, 1000 * 60 * m_nChkSpanIni, NULL);

	m_pHtmlView->Navigate("about:ここにはRSSの内容が表示されます。<BR>内容を表示するには上部のリストから表示したいページをクリックしてください。<BR>");
	return 0;
}

void CRssWnd::OnDestroy(){
	m_pHtmlView = NULL;
	ReleaseData();
	CWnd::OnDestroy();
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	
}

void CRssWnd::OnSize(UINT nType, int cx, int cy) {
	CWnd::OnSize(nType, cx, cy);
	SetCtrlPos();
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	
}

void CRssWnd::OnShowWindow(BOOL bShow, UINT nStatus) {
	CWnd::OnShowWindow(bShow, nStatus);
	SetCtrlPos();
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	
}

BOOL CRssWnd::SetCtrlPos(){
	CRect rect;
	CRect chkRect;
	GetClientRect(rect);
	m_objRssList.GetClientRect(chkRect);
	if(!chkRect.Width() || !chkRect.Height()){
		int nHeightBase = rect.Height() / 3;
		int nListH = nHeightBase;
		int nSepH = 4;
		int nHtmlH = rect.Height() - nHeightBase - nSepH;
		m_objSepBtn.SetWindowPos(&wndTop,	0, nHeightBase,			rect.Width(), nSepH,	SWP_SHOWWINDOW);
		m_objRssList.SetWindowPos(&wndTop,	0, 0,					rect.Width(), nListH,	SWP_SHOWWINDOW);
		m_pHtmlView->SetWindowPos(&wndTop,	0, nHeightBase + nSepH, rect.Width(), nHtmlH,	SWP_SHOWWINDOW);
	}else{
		CRect rectList;
		CRect rectSep;
		CRect rectHtml;
		CRect rect2;
		m_objRssList.GetClientRect(rectList);
		m_objSepBtn.GetClientRect(rectSep);
		m_pHtmlView->GetClientRect(rectHtml);

		int nRssH	= rectList.Height();
		int nBtnH	= rectSep.Height();
		int nHtmlH	= rectHtml.Height();

		SetRedraw(FALSE);
		m_objRssList.SetRedraw(FALSE);
		m_objSepBtn.SetRedraw(FALSE);
		m_pHtmlView->SetRedraw(FALSE);

		m_objRssList.SetWindowPos(&wndTop,
								  rect.left,		rect.top,
								  rect.Width(),		nRssH,
								  SWP_SHOWWINDOW);
		m_objSepBtn.SetWindowPos( &wndTop,
								  rect.left,		rect.top + nRssH,
								  rect.Width(),		nBtnH,
								  SWP_SHOWWINDOW);
		m_pHtmlView->SetWindowPos(&wndTop,	
								  rect.left,		rect.top + nRssH + nBtnH,	
								  rect.Width(),		rect.Height() - nRssH - nBtnH,	SWP_SHOWWINDOW);

		UpdateWindow();
		m_objRssList.SetRedraw(TRUE);
		m_objSepBtn.SetRedraw(TRUE);
		m_pHtmlView->SetRedraw(TRUE);
		SetRedraw(TRUE);

		m_objRssList.InvalidateRect(NULL);
		m_objSepBtn.InvalidateRect(NULL);
		m_pHtmlView->InvalidateRect(NULL);
		InvalidateRect(NULL);
	}
	return FALSE;
}

void CRssWnd::OnTimer(UINT nIDEvent){
	if(m_uTimerID == nIDEvent){
		LoadIniData();
		if(m_bUseCheckIni){
			KillTimer(nIDEvent);
			UpdateRSSHtml();
		}
		SetTimer(nIDEvent, 1000 * 60 * m_nChkSpanIni, NULL);
	}
	CWnd::OnTimer(nIDEvent);
}

BOOL CRssWnd::PreTranslateMessage(MSG* pMsg){
	return CWnd::PreTranslateMessage(pMsg);
}

void CRssWnd::OnLButtonDown(UINT nFlags, CPoint point){
	CWnd::OnLButtonDown(nFlags, point);
}

void CRssWnd::OnMouseMove(UINT nFlags, CPoint point){
	CWnd::OnMouseMove(nFlags, point);
}

LRESULT CRssWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam){
	return CWnd::WindowProc(message, wParam, lParam);
}

LRESULT CRssWnd::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam){
	return CWnd::DefWindowProc(message, wParam, lParam);
}

BOOL CRssWnd::OnLoadOneData(const PRSSINFO pInfo){
	PRSSINFO pRss = new RSSINFO;
	memset(pRss, 0, sizeof(RSSINFO));
	memcpy(pRss, pInfo, sizeof(RSSINFO));
	if(pRss->bUse){
		int nCnt = m_objRssList.GetItemCount();
		int nIndex = m_objRssList.InsertItem(nCnt, pRss->szName, 0);
		m_objRssList.SetItemData(nIndex, (LPARAM)pRss);
	}
	return TRUE;
}
BOOL CRssWnd::OnSaveOneData(int nCnt, RSSINFO &objInfo){
	return TRUE;
}

void CRssWnd::ReleaseData(){
	int nCnt = m_objRssList.GetItemCount();
	for(int i = 0; i < nCnt; i++){
		PRSSINFO pInfo = (PRSSINFO)m_objRssList.GetItemData(i);
		delete pInfo;
	}
	m_objRssList.DeleteAllItems();
}

void CRssWnd::UpdateRSSHtml(){
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
	int nUse = ::GetPrivateProfileInt( "RSSPlugin", "IsUse", 0, strIni);
	if(nUse == 0){
		return;
	}

	//更新処理
	CString strHtml;
	CString strHTMLBody = "";
	int nCnt = m_objRssList.GetItemCount();
	m_arrHtml.RemoveAll();
	for(int i = 0; i < nCnt; i++){
		PRSSINFO pInfo = (PRSSINFO)m_objRssList.GetItemData(i);
		//pInfo->szURL
		CRssCtrl objRss;
		if(objRss.Create(pInfo->szURL, pInfo->szUserID, pInfo->szPassWord)){
			CString strRss;
			CString strOut;
			objRss.GetRSS(strRss);
			objRss.ConvertHTML(strRss, strOut);
			strHTMLBody = strOut;
		}else{
			strHTMLBody = "記事取得失敗";
		}
		strHtml.Format(//"<HTML>\r\n"
					   "<HEAD>\r\n"
					   "	<META http-equiv=\"Content-Style-Type\" content=\"text/css\">\r\n"
					   "	<META http-equiv=\"Content-Type\" content=\"text/html; charset=Shift_JIS\">\r\n"
					   "	<STYLE type=\"text/css\">\r\n"
					   "	<!--\r\n"
					   "	body{\r\n"
					   "		font-size:8pt;\r\n"
					   "		margin:0 0 0 0;\r\n"
					   "	}\r\n"
					   "	table{\r\n"
					   "		background:#00AAAA;\r\n"
					   "		border-width:0px;\r\n"
					   "		border-height:0px;\r\n"
					   "		border-color:#00AAAA;\r\n"
					   "		border-style:SOLID;\r\n"
					   "	}\r\n"
					   "	td{\r\n"
					   "		font-size:8pt;\r\n"
					   "		border-width:0px;\r\n"
					   "		border-height:0px;\r\n"
					   "	}\r\n"
					   "	td.rss_head{\r\n"
					   "		background:#00AAAA;\r\n"
					   "		color:#ffffff;\r\n"
					   "	}\r\n"
					   "	td.rss_normal{\r\n"
					   "		background:#ffffff;\r\n"
					   "		color:#000000;\r\n"
					   "	}\r\n"
					   "	a.rss_normal{\r\n"
					   "		color:#ffffff;\r\n"
					   "	}\r\n"
					   "	//-->\r\n"
					   "	</STYLE>\r\n"
					   "</HEAD>\r\n"
					   "<BODY oncontextmenu=\"return false;\">\r\n"
					   "<TABLE>\r\n"
					   "%s\r\n"
					   "</TABLE>\r\n"
					   "</BODY>\r\n"
					   /*"</HTML>\r\n"*/, strHTMLBody);
		m_arrHtml.Add(strHtml);
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);
	}
}

void CRssWnd::OnUpdateRSS(int iItem){
	if(iItem < 0){
		return;
	}
	if(!m_arrHtml.GetSize()){
		return;
	}
	if(m_arrHtml.GetSize() <= iItem){
		return;
	}

	CString strHtmlPath;
	strHtmlPath.Format("%sRSS.html", m_strRssBase);
	CString strHtml = m_arrHtml.GetAt(iItem);
	CFile file;
	file.Open(strHtmlPath, CFile::modeCreate | CFile::modeWrite);
	file.Write(strHtml, strHtml.GetLength());
	file.Flush();
	file.Close();
	m_pHtmlView->Navigate2(strHtmlPath);

}

void CRssWnd::UpdateConfig(){
	ReleaseData();
	LoadRSSData();
	LoadIniData();
	UpdateRSSHtml();
	SetColumnWidthLC(&m_objRssList);
	KillTimer(m_uTimerID);
	SetTimer(m_uTimerID, 1000 * 60 * m_nChkSpanIni, NULL);
}

void CRssWnd::OnContextMenu(CWnd* pWnd, CPoint point){
	
}

void CRssWnd::OnReadrss() {
	int iItem = m_objRssList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if(iItem == -1){
		return;
	}
	CString strHtmlPath;
	strHtmlPath.Format("%sRSS.html", m_strRssBase);
	CString strHtml = m_arrHtml.GetAt(iItem);
	CFile file;
	file.Open(strHtmlPath, CFile::modeCreate | CFile::modeWrite);
	file.Write(strHtml, strHtml.GetLength());
	file.Flush();
	file.Close();
	m_pHtmlView->Navigate2(strHtmlPath);

}

void CRssWnd::OnUpdateReadrss(CCmdUI* pCmdUI){
}

BOOL CRssWnd::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) {
	return CWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CRssWnd::OnCommand(WPARAM wParam, LPARAM lParam){
	return CWnd::OnCommand(wParam, lParam);
}

// CalView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "CalView.h"
#include "InfoView.h"
#include "DlgDateInp.h"
#include "PWikiDoc.h"
#include "EventDate.h"
#include "LogFile.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalView

IMPLEMENT_DYNCREATE(CCalView, CView)

CCalView::CCalView(){
}

CCalView::~CCalView(){
}


BEGIN_MESSAGE_MAP(CCalView, CView)
	//{{AFX_MSG_MAP(CCalView)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
#if !defined(USE_DEVLIB_TAB)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnTabChange)
#endif
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalView 描画

void CCalView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: この位置に描画用のコードを追加してください
}

/////////////////////////////////////////////////////////////////////////////
// CCalView 診断

#ifdef _DEBUG
void CCalView::AssertValid() const{
	CView::AssertValid();
}

void CCalView::Dump(CDumpContext& dc) const{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCalView メッセージ ハンドラ

/**
 * @brif 最初のUpdate
 */
void CCalView::OnInitialUpdate(){
	CView::OnInitialUpdate();

	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CCalView::OnInitialUpdate : pFrm is null");
	}
	APPINFO objIni;
	pFrm->m_objIniFile.GetAppInfoIniData(objIni);
/*
	CFont *pFont = GetFont();
	LOGFONT lFont;
	memset(&lFont, 0, sizeof(LOGFONT));
	if(pFont){
		pFont->GetLogFont(&lFont);
	}else{
		strcpy(lFont.lfFaceName, "MS UI Gothic");
		lFont.lfCharSet = DEFAULT_CHARSET;
	}
	lFont.lfHeight = -10;
	m_objFont.CreateFontIndirect(&lFont);
*/
	MakeFont(m_objFont, GetDC(), "MS UI Gothic", -10);
	CRect crRect;
	GetClientRect(crRect);

#if defined(USE_DEVLIB_TAB)
	CRect tabRect = crRect;
	tabRect.bottom = 24;
	m_objTab.Create(WS_CHILD, tabRect, this, IDC_TAB);

	CRect rect2;
	m_objTab.GetClientRect(rect2);
	m_objTabRect = rect2;
	m_objTab.AdjustRect(FALSE, rect2);
	m_objTabRect.bottom = rect2.top;
	m_objTab.SetFont(&m_objFont);

	CRect calRect = crRect;
	calRect.top = rect2.top;
	m_objCalWnd.Create(WS_CHILD /*| WS_BORDER*/, calRect, this, IDS_CALWND);
	m_objCalWnd.ModifyStyleEx(0, WS_EX_CLIENTEDGE, 0);

	m_objWikiWnd.Create(WS_CHILD /*| WS_BORDER*/, calRect, this, IDS_WIKIWND);
	//m_objWikiWnd.ModifyStyleEx(0, WS_EX_CLIENTEDGE, 0);

	m_objFindWnd.Create(WS_CHILD | WS_BORDER, calRect, this, IDS_FINDWND);
	//m_objFindWnd.ModifyStyleEx(0, WS_EX_CLIENTEDGE, 0);
	
	m_objTab.AddNewPage(0, "カレンダー", m_objCalWnd.m_hWnd);
	m_objTab.AddNewPage(1, "メモ", m_objWikiWnd.m_hWnd);
	m_objTab.AddNewPage(2, "検索", m_objFindWnd.m_hWnd);

	//プラグインウィンドウ
	UpdateShowPluginTab();
	EnableToolTips(TRUE);

	SetCtrlPos();

	m_objTab.SetCurSel(objIni.nStartActTab);
	m_objTab.SetActivePage(objIni.nStartActTab);
#else
	CRect tabRect = crRect;
	tabRect.bottom = 24;
	m_objTab.Create(WS_CHILD, tabRect, this, IDC_TAB);
	m_objTab.InsertItem(0, "カレンダー", 0);
	m_objTab.InsertItem(1, "メモ", 0);
	m_objTab.InsertItem(2, "検索", 0);
	m_objTab.SetFont(&m_objFont);

	m_objTab.SetCurSel(objIni.nStartActTab);

	CRect rect2;
	m_objTab.GetClientRect(rect2);
	m_objTabRect = rect2;
	m_objTab.AdjustRect(FALSE, rect2);
	m_objTabRect.bottom = rect2.top;

	CRect calRect = crRect;
	calRect.top = rect2.top;
	m_objCalWnd.Create(WS_CHILD, calRect, this, IDS_CALWND);

	m_objWikiWnd.Create(WS_CHILD, calRect, this, IDS_WIKIWND);

	m_objFindWnd.Create(WS_CHILD, calRect, this, IDS_FINDWND);

	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask = TCIF_PARAM;
	tcItem.lParam = (LPARAM)m_objCalWnd.m_hWnd;
	m_objTab.SetItem(0, &tcItem);

	tcItem.lParam = (LPARAM)m_objWikiWnd.m_hWnd;
	m_objTab.SetItem(1, &tcItem);

	tcItem.lParam = (LPARAM)m_objFindWnd.m_hWnd;
	m_objTab.SetItem(2, &tcItem);

	//プラグインウィンドウ
	UpdateShowPluginTab();
	EnableToolTips(FALSE);

	SetCtrlPos();
#endif

}

/**
 * @brif WM_SIZEのハンドラ関数
 */
void CCalView::OnSize(UINT nType, int cx, int cy){
	CView::OnSize(nType, cx, cy);
	CLogFile::SaveAppLog("CCalView::OnSize");
	SetCtrlPos();
}

/**
 * @brif WM_DESTROYのハンドラ関数
 */
void CCalView::OnDestroy() {
	CView::OnDestroy();
}

/**
 * @brif WM_CREATEのハンドラ関数
 */
int CCalView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	CLogFile::SaveAppLog("CCalView 生成");	
	
	// TODO: この位置に固有の作成用コードを追加してください
	
	return 0;
}

#if !defined(USE_DEVLIB_TAB)
/**
 * @brif TCN_SELCHANGEのハンドラ関数
 */
void CCalView::OnTabChange(LPNMHDR pNmhdr, HRESULT *pResult){
	*pResult = 0;
	SetCtrlPos();
}
#endif

/**
 * @brif コントロールの座標、サイズを調整する
 */
void CCalView::SetCtrlPos(){
	if(::IsWindow(m_objTab.m_hWnd)){
#if defined(USE_DEVLIB_TAB)
		CRect crRect;
		GetClientRect(crRect);
		m_objTab.SetWindowPos(&wndTop, crRect.left, crRect.top, crRect.Width(), crRect.Height(), SWP_SHOWWINDOW);
#else
		CRect crRect;
		GetClientRect(crRect);
		CRect tabRect(0, 0, crRect.right, m_objTabRect.Height());
		m_objTab.SetWindowPos(&wndTop, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		int nSel = m_objTab.GetCurSel();
		int nCnt = m_objTab.GetItemCount();
		HWND hWnd;
		TCITEM tcItem;
		CRect calRect(0, m_objTabRect.Height(), crRect.right, crRect.bottom);
		for(int i = 0; i < nCnt; i++){
			m_objTab.GetItem(i, &tcItem);
			hWnd = (HWND)tcItem.lParam;
			if(i == nSel){
				::SetWindowPos(hWnd, HWND_TOP, calRect.left, calRect.top, calRect.Width(), calRect.Height(), SWP_SHOWWINDOW);
				::SetFocus(hWnd);
			}else{
				::ShowWindow(hWnd, SW_HIDE);
			}
		}
#endif
	}
}

/**
 * @brif カレンダーの表示を更新する
 */
void CCalView::UpdateCalender(){
	m_objCalWnd.UpdateCalender();
}

/**
 *
 */
void CCalView::UpdateWikiTree(BOOL bUSBTree /*= FALSE*/){
	if(bUSBTree){
		m_objWikiWnd.FindWikiDocUSB();
	}else{
		m_objWikiWnd.FindWikiDoc();
	}
}

/**
 *
 */
CWikiWnd* CCalView::GetWikiWnd(){
	return &m_objWikiWnd;
}

void CCalView::ActiveWikiPage(LPCTSTR pszWikiPath){
	m_objWikiWnd.ActiveTreeItem(pszWikiPath);
}

void CCalView::UpdateShowPluginTab(){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CCalView::UpdateShowPluginTab : pFrm is null");
	}
	int nSize = pFrm->m_objPlugins.GetSize();
	TCITEM tcItem;
	BOOL bMatch = FALSE;
	for(int i = 0; i < nSize; i++){
		CPWikiPlugin *pPlug = pFrm->m_objPlugins.GetPlugin(i);
		if(!pPlug){
			continue;
		}
		if(!pPlug->m_objInfo.arrType[eTypeTabExtend]){
			//タブ拡張ではない
			continue;
		}
		HWND hWnd = pPlug->GetTabWnd(m_hWnd);
		int nCnt = m_objTab.GetItemCount();
		int nCurSel = m_objTab.GetCurSel();
		for(int j = nCnt - 1; j >= 3; j--){
			memset(&tcItem, 0, sizeof(TCITEM));
			tcItem.mask = TCIF_PARAM;
			m_objTab.GetItem(j, &tcItem);
			if(hWnd == (HWND)tcItem.lParam){
				if(!pPlug->GetUse()){
					//タブを削除する
					if(nCurSel == j){
						m_objTab.SetCurSel(0);
						m_objTab.SetActivePage(0);
					}else if(nCurSel > j){
						m_objTab.SetCurSel(nCurSel - 1);
						m_objTab.SetActivePage(nCurSel - 1);
					}
					m_objTab.DeleteItem(j);
					::ShowWindow(hWnd, SW_HIDE);
					//::SendMessage(hWnd, WM_CLOSE, 0, 0);
				}
				bMatch = TRUE;
				break;
			}
		}
		if((!bMatch) && (pPlug->GetUse())){
#if defined(USE_DEVLIB_TAB)
			m_objTab.AddNewPage(m_objTab.GetItemCount(), pPlug->m_objInfo.szName, hWnd);
#else
			int nInsIndex = m_objTab.InsertItem(m_objTab.GetItemCount(), pPlug->m_objInfo.szName, 0);
			memset(&tcItem, 0, sizeof(TCITEM));
			tcItem.mask = TCIF_PARAM;
			tcItem.lParam = (LPARAM)hWnd;
			m_objTab.SetItem(nInsIndex, &tcItem);
#endif
		}
	}
}

BOOL CCalView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
	return CView::PreTranslateMessage(pMsg);
}

void CCalView::UpdateSetting(){
	m_objFont.DeleteObject();

	FONTINFO objFontInfo;
	CMainFrame *pFrm = GetMainFrame(this);
	pFrm->m_objIniFile.GetFontInfoIniData(objFontInfo);
	MakeFont(m_objFont, GetDC(), objFontInfo.szEtcFontName, objFontInfo.lEtcHeight);

	m_objTab.SetFont(&m_objFont);
	
	m_objCalWnd.UpdateSetting();
	m_objWikiWnd.UpdateSetting();
}

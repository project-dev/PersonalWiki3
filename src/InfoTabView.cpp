// InfoTabView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "personalwiki.h"
#include "InfoTabView.h"
#include "LogFile.h"
#include "MainFrm.h"

#include "InfoView.h"
#include "WikiEditWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoTabView

IMPLEMENT_DYNCREATE(CInfoTabView, CView)

CInfoTabView::CInfoTabView(){
	m_pEditWnd = NULL;
	m_pHtmlView = NULL;
}

CInfoTabView::~CInfoTabView(){

}


BEGIN_MESSAGE_MAP(CInfoTabView, CView)
	//{{AFX_MSG_MAP(CInfoTabView)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_WIKI_BOLD, OnWikiBold)
	ON_UPDATE_COMMAND_UI(ID_WIKI_BOLD, OnUpdateWikiBold)
	ON_COMMAND(ID_WIKI_HEAD, OnWikiHead)
	ON_UPDATE_COMMAND_UI(ID_WIKI_HEAD, OnUpdateWikiHead)
	ON_COMMAND(ID_WIKI_HLINE, OnWikiHline)
	ON_UPDATE_COMMAND_UI(ID_WIKI_HLINE, OnUpdateWikiHline)
	ON_COMMAND(ID_WIKI_ITALIC, OnWikiItalic)
	ON_UPDATE_COMMAND_UI(ID_WIKI_ITALIC, OnUpdateWikiItalic)
	ON_COMMAND(ID_WIKI_LINK, OnWikiLink)
	ON_UPDATE_COMMAND_UI(ID_WIKI_LINK, OnUpdateWikiLink)
	ON_COMMAND(ID_WIKI_LIST, OnWikiList)
	ON_UPDATE_COMMAND_UI(ID_WIKI_LIST, OnUpdateWikiList)
	ON_COMMAND(ID_WIKI_NUMLIST, OnWikiNumlist)
	ON_UPDATE_COMMAND_UI(ID_WIKI_NUMLIST, OnUpdateWikiNumlist)
	ON_COMMAND(ID_WIKI_RET, OnWikiRet)
	ON_UPDATE_COMMAND_UI(ID_WIKI_RET, OnUpdateWikiRet)
	ON_COMMAND(ID_WIKI_STRIKE, OnWikiStrike)
	ON_UPDATE_COMMAND_UI(ID_WIKI_STRIKE, OnUpdateWikiStrike)
	ON_COMMAND(ID_WIKI_UNDERLINE, OnWikiUnderline)
	ON_UPDATE_COMMAND_UI(ID_WIKI_UNDERLINE, OnUpdateWikiUnderline)
	//}}AFX_MSG_MAP
	//ON_NOTIFY(TCN_SELCHANGE, IDC_WIKITAB, OnTabChange)
	ON_MESSAGE(WM_HWNDTABCHANGE, OnHwndTabChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoTabView 描画

void CInfoTabView::OnDraw(CDC* pDC){
	CDocument* pDoc = GetDocument();
	// TODO: この位置に描画用のコードを追加してください
}

/////////////////////////////////////////////////////////////////////////////
// CInfoTabView 診断

#ifdef _DEBUG
void CInfoTabView::AssertValid() const
{
	CView::AssertValid();
}

void CInfoTabView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInfoTabView メッセージ ハンドラ
int CInfoTabView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	CLogFile::SaveAppLog("CInfoTabView::OnCreate Start");		
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: この位置に固有の作成用コードを追加してください
	CLogFile::SaveAppLog("CInfoTabView::OnCreate End");		
	return 0;
}

void CInfoTabView::OnInitialUpdate() {
	CLogFile::SaveAppLog("CInfoTabView::OnInitialUpdate Start");		
	CView::OnInitialUpdate();
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
	
	if(!CreateChildWnd()){
		return;
	}

	CRect crRect;
	GetClientRect(crRect);

	CRect tabRect = crRect;
	tabRect.bottom = 24;
	m_objTab.Create(WS_VISIBLE | WS_CHILD, crRect, this, IDC_WIKITAB);
	m_objTab.SetFont(&m_objFont);
	m_objTab.AddNewPage(0, "Wiki", m_pInfo);
	m_objTab.AddNewPage(1, "編集", m_pEditWnd);
	m_objTab.SetActivePage(0);
/*
	CRect rect2;
	m_objTab.GetClientRect(rect2);
	m_objTabRect = rect2;
	m_objTab.AdjustRect(FALSE, rect2);
	m_objTabRect.bottom = rect2.top;
*/
	m_pDoc = (CPWikiDoc*)GetDocument();
	m_pFrm = GetMainFrame(this);
	if(!m_pFrm){
		CLogFile::SaveFatalLog("CInfoTabView::OnCreate : pFrm is null");
	}
	CLogFile::SaveAppLog("CInfoTabView::OnInitialUpdate End");		
}

BOOL CInfoTabView::CreateChildWnd(){
	CRect crRect;
	GetClientRect(crRect);

	DWORD dwDefStyle = WS_CHILD | WS_BORDER /*| WS_VISIBLE*/;
	if(!m_pHtmlView){
		CRuntimeClass* rc = RUNTIME_CLASS(CInfoView);
		m_pHtmlView = (CInfoView*)rc->CreateObject();
		if(!m_pHtmlView){
			return FALSE;
		}
		if(!m_pHtmlView->Create(NULL, "CInfoView", dwDefStyle, crRect, this, IDC_HTMLVIEW)){
			CLogFile::SaveAppLog("m_pHtmlView->Createに失敗");
			return FALSE;
		}
	}
	if(!m_pEditWnd){
		m_pEditWnd = new CWikiEditWnd();
		if(!m_pEditWnd->Create(NULL, "CWikiEditWnd", dwDefStyle, crRect, this, IDC_WIKIEDITWND)){
			return FALSE;
		}
	}
	return TRUE;
}

void CInfoTabView::SetCtrlPos(){
	if(::IsWindow(m_objTab.m_hWnd)){
/*
		CRect crRect;
		GetClientRect(crRect);
		CRect tabRect(0, 0, crRect.right, m_objTabRect.Height());
		m_objTab.SetWindowPos(&wndTop, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_objTab.SetPagePosition();
*/

		CRect rect;
		GetClientRect(rect);
		m_objTab.SetWindowPos(&wndTop, 0, 0, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
	}
}
/**
 * @brif TCN_SELCHANGEのハンドラ関数
 */
void CInfoTabView::OnTabChange(LPNMHDR pNmhdr, HRESULT *pResult){
	*pResult = 0;
	
	
	//SetCtrlPos();
}

long CInfoTabView::OnHwndTabChange(WPARAM wParam, LPARAM lParam){
	int nPos = m_objTab.GetCurSel();
	if((nPos == 0) && (m_pEditWnd)){
		m_pEditWnd->SaveText();
	}
	return 0;
}


void CInfoTabView::GetHtmlHead(CString &strHtml, LPCTSTR pszTitle){
}

void CInfoTabView::UpdateInfo(COleDateTime *pDate){
	m_pEditWnd->SaveText();
	CAbstractWikiWnd::UpdateInfoSc(pDate);
}

void CInfoTabView::UpdateInfo(CString &strWikiPath){
	m_pEditWnd->SaveText();
	m_strDataBasePath = "";
	m_strWikiPath = strWikiPath;

	CAbstractWikiWnd::UpdateInfo(strWikiPath);
}

void CInfoTabView::UpdateInfoUSB(CString &strBasePath, LPCTSTR pszBasePath){
	m_pEditWnd->SaveText();
	m_strDataBasePath = pszBasePath;
	m_strWikiPath = strBasePath;

	CAbstractWikiWnd::UpdateInfoUSB(strBasePath, pszBasePath);
}


void CInfoTabView::OnDestroy(){
	m_pHtmlView = NULL;
	if(m_pEditWnd){
		delete m_pEditWnd;
		m_pEditWnd = NULL;
	}	
	CView::OnDestroy();
}


void CInfoTabView::OnSize(UINT nType, int cx, int cy){
	CView::OnSize(nType, cx, cy);
	SetCtrlPos();
}

void CInfoTabView::OnUpdateEditCopy(CCmdUI* pCmdUI){
	m_pEditWnd->OnUpdateEditCopy(pCmdUI);
}

void CInfoTabView::OnUpdateEditCut(CCmdUI* pCmdUI){
	m_pEditWnd->OnUpdateEditCut(pCmdUI);
}

void CInfoTabView::OnUpdateEditPaste(CCmdUI* pCmdUI){
	m_pEditWnd->OnUpdateEditPaste(pCmdUI);
}

void CInfoTabView::OnUpdateEditUndo(CCmdUI* pCmdUI){
	m_pEditWnd->OnUpdateEditUndo(pCmdUI);
}

void CInfoTabView::OnUpdateWikiBold(CCmdUI* pCmdUI){
	m_pEditWnd->OnUpdateWikiBold(pCmdUI);
}

void CInfoTabView::OnUpdateWikiHead(CCmdUI* pCmdUI){
	m_pEditWnd->OnUpdateWikiHead(pCmdUI);
}

void CInfoTabView::OnUpdateWikiHline(CCmdUI* pCmdUI){
	m_pEditWnd->OnUpdateWikiHead(pCmdUI);
}

void CInfoTabView::OnUpdateWikiItalic(CCmdUI* pCmdUI){
	m_pEditWnd->OnUpdateWikiItalic(pCmdUI);
}

void CInfoTabView::OnUpdateWikiLink(CCmdUI* pCmdUI){
	m_pEditWnd->OnUpdateWikiLink(pCmdUI);
}

void CInfoTabView::OnUpdateWikiList(CCmdUI* pCmdUI){
	m_pEditWnd->OnUpdateWikiList(pCmdUI);
}

void CInfoTabView::OnUpdateWikiNumlist(CCmdUI* pCmdUI){
	m_pEditWnd->OnUpdateWikiNumlist(pCmdUI);
}

void CInfoTabView::OnUpdateWikiRet(CCmdUI* pCmdUI){
	m_pEditWnd->OnUpdateWikiRet(pCmdUI);
}

void CInfoTabView::OnUpdateWikiStrike(CCmdUI* pCmdUI){
	m_pEditWnd->OnUpdateWikiStrike(pCmdUI);
}

void CInfoTabView::OnUpdateWikiUnderline(CCmdUI* pCmdUI){
	m_pEditWnd->OnUpdateWikiUnderline(pCmdUI);
}

void CInfoTabView::OnEditCopy(){
	m_pEditWnd->SendMessage(WM_COMMAND, ID_EDIT_COPY, 0);
}

void CInfoTabView::OnEditCut(){
	m_pEditWnd->SendMessage(WM_COMMAND, ID_EDIT_CUT, 0);
}

void CInfoTabView::OnEditPaste(){
	m_pEditWnd->SendMessage(WM_COMMAND, ID_EDIT_PASTE, 0);
}

void CInfoTabView::OnEditUndo(){
	m_pEditWnd->SendMessage(WM_COMMAND, ID_EDIT_UNDO, 0);
}

void CInfoTabView::OnWikiBold(){
	m_pEditWnd->SendMessage(WM_COMMAND, ID_WIKI_BOLD, 0);
}

void CInfoTabView::OnWikiHead(){
	m_pEditWnd->SendMessage(WM_COMMAND, ID_WIKI_HEAD, 0);
}

void CInfoTabView::OnWikiHline(){
	m_pEditWnd->SendMessage(WM_COMMAND, ID_WIKI_HLINE, 0);
}

void CInfoTabView::OnWikiItalic(){
	m_pEditWnd->SendMessage(WM_COMMAND, ID_WIKI_ITALIC, 0);
}

void CInfoTabView::OnWikiLink(){
	m_pEditWnd->SendMessage(WM_COMMAND, ID_WIKI_LINK, 0);
}

void CInfoTabView::OnWikiList(){
	m_pEditWnd->SendMessage(WM_COMMAND, ID_WIKI_LIST, 0);
}

void CInfoTabView::OnWikiNumlist(){
	m_pEditWnd->SendMessage(WM_COMMAND, ID_WIKI_NUMLIST, 0);
}

void CInfoTabView::OnWikiRet(){
	m_pEditWnd->SendMessage(WM_COMMAND, ID_WIKI_RET, 0);
}

void CInfoTabView::OnWikiStrike(){
	m_pEditWnd->SendMessage(WM_COMMAND, ID_WIKI_STRIKE, 0);
}

void CInfoTabView::OnWikiUnderline(){
	m_pEditWnd->SendMessage(WM_COMMAND, ID_WIKI_UNDERLINE, 0);
}

void CInfoTabView::UpdateSetting(){
	FONTINFO objFontInfo;
	CMainFrame *pFrm = GetMainFrame(this);
	pFrm->m_objIniFile.GetFontInfoIniData(objFontInfo);
	MakeFont(m_objFont, GetDC(), objFontInfo.szEtcFontName, objFontInfo.lEtcHeight);
	m_objTab.SetFont(&m_objFont);
	SetCtrlPos();
	
	if(m_pEditWnd){
		m_pEditWnd->UpdateSetting();
	}
}

// WikiEditWnd.cpp: CWikiEditWnd クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "personalwiki.h"
#include "WikiEditWnd.h"
#include "LogFile.h"
#include "EventDate.h"
#include "PWikiDoc.h"
#include "MainFrm.h"
#include "CalView.h"
#include "InfoTabView.h"
#include "FileCtrl.h"
#include <atlbase.h>
#include "Cryptography.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CWikiEditWnd::CWikiEditWnd(){
	m_strOldText = "";
//	m_lpRichEditOle = NULL;
}

CWikiEditWnd::~CWikiEditWnd(){

}

BEGIN_MESSAGE_MAP(CWikiEditWnd, CWnd)
	//{{AFX_MSG_MAP(CWikiEditWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_WIKI_BOLD, OnWikiBold)
	ON_COMMAND(ID_WIKI_HEAD, OnWikiHead)
	ON_COMMAND(ID_WIKI_HLINE, OnWikiHline)
	ON_COMMAND(ID_WIKI_ITALIC, OnWikiItalic)
	ON_COMMAND(ID_WIKI_LINK, OnWikiLink)
	ON_COMMAND(ID_WIKI_LIST, OnWikiList)
	ON_COMMAND(ID_WIKI_NUMLIST, OnWikiNumlist)
	ON_COMMAND(ID_WIKI_RET, OnWikiRet)
	ON_COMMAND(ID_WIKI_STRIKE, OnWikiStrike)
	ON_COMMAND(ID_WIKI_UNDERLINE, OnWikiUnderline)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_WIKI_BOLD, OnUpdateWikiBold)
	ON_UPDATE_COMMAND_UI(ID_WIKI_HEAD, OnUpdateWikiHead)
	ON_UPDATE_COMMAND_UI(ID_WIKI_HLINE, OnUpdateWikiHline)
	ON_UPDATE_COMMAND_UI(ID_WIKI_ITALIC, OnUpdateWikiItalic)
	ON_UPDATE_COMMAND_UI(ID_WIKI_LINK, OnUpdateWikiLink)
	ON_UPDATE_COMMAND_UI(ID_WIKI_LIST, OnUpdateWikiList)
	ON_UPDATE_COMMAND_UI(ID_WIKI_NUMLIST, OnUpdateWikiNumlist)
	ON_UPDATE_COMMAND_UI(ID_WIKI_RET, OnUpdateWikiRet)
	ON_UPDATE_COMMAND_UI(ID_WIKI_STRIKE, OnUpdateWikiStrike)
	ON_UPDATE_COMMAND_UI(ID_WIKI_UNDERLINE, OnUpdateWikiUnderline)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
    ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotifyEx)
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipNotifyEx)
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipNotifyEx)
END_MESSAGE_MAP()

void CWikiEditWnd::OnSize(UINT nType, int cx, int cy) {
	CWnd::OnSize(nType, cx, cy);
	SetCtrlPos();
}

int CWikiEditWnd::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
    m_hAccelTable = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));

	DWORD dwStyle = WS_CHILD | WS_VISIBLE | /*WS_BORDER |*/ CBRS_TOOLTIPS | CBRS_SIZE_FIXED | CBRS_FLYBY /*| CBRS_BORDER_BOTTOM*/;
	if(!m_objToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle, CRect(0, 0, 0, 0), IDR_DLGWIKIINP)
	|| !m_objToolBar.LoadToolBar(IDR_DLGWIKIINP)){
		CLogFile::SaveAppLog("ツールバーの生成に失敗");
	}else{
		TBIMGINFO objTbInfo;
		memset(&objTbInfo, 0, sizeof(TBIMGINFO));
		objTbInfo.crMask = RGB(0, 128, 128);
		objTbInfo.nBtnHeight = 16;
		objTbInfo.nBtnWidth = 16;
		objTbInfo.nButtons = 6;
		objTbInfo.nColorBit = 8;
		objTbInfo.pToolBar = &m_objToolBar;
		objTbInfo.uID = IDB_DLGWIKIINP256;
		SetToolbarImg(&objTbInfo);

		CSize szToolBar = m_objToolBar.CalcFixedLayout(FALSE,TRUE);
		m_objToolBar.MoveWindow(4, 0, szToolBar.cx, szToolBar.cy);
		m_objTbRect.SetRect(4, 0, szToolBar.cx, szToolBar.cy);

		CRect rect;
		GetClientRect(rect);
		m_objToolTip.Create(this);
		m_objToolTip.SetDelayTime(TTDT_AUTOPOP, 9999);
		m_objToolTip.SetDelayTime(TTDT_INITIAL, 100);
		m_objToolTip.Activate(TRUE);
		m_objToolBar.GetToolBarCtrl().SetToolTips(&m_objToolTip);

		UINT uIDs[] = { ID_WIKI_BOLD, ID_WIKI_ITALIC, ID_WIKI_UNDERLINE, ID_WIKI_STRIKE, 
						ID_WIKI_LIST, ID_WIKI_NUMLIST, ID_WIKI_HEAD, ID_WIKI_LINK, ID_WIKI_RET,
						ID_WIKI_HLINE};
		int nSize = sizeof(uIDs) / sizeof(UINT);

		for(int i = 0; i < nSize; i++){
			m_objToolBar.GetToolBarCtrl().GetItemRect(i, rect);
			m_objToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rect, uIDs[i]);
		}
	}

	CRect rect;
	GetClientRect(rect);
	DWORD dwDefStyle = WS_CHILD | WS_BORDER | WS_VISIBLE;
	DWORD dwEdStyle = ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_NOHIDESEL;
	m_objEdit.Create(dwDefStyle | dwEdStyle | WS_HSCROLL | WS_VSCROLL, rect, this, 0);
	m_objEdit.ModifyStyleEx(WS_EX_CLIENTEDGE, 0);

//	m_lpRichEditOle = m_objEdit.GetIRichEditOle();
//	CDC *pEditDC = m_objEdit.GetDC();
//	long twips = 1440 /  pEditDC->GetDeviceCaps(LOGPIXELSX);
//	CHARFORMAT cf;
//	memset(&cf,0 ,sizeof(CHARFORMAT));
//	cf.cbSize = sizeof(CHARFORMAT);
//	cf.yHeight = twips * 10;
//	cf.dwMask = CFM_SIZE | CFM_FACE;
//	strcpy(cf.szFaceName, "ＭＳ ゴシック");
//	m_objEdit.SetDefaultCharFormat(cf);
//	m_objEdit.SetOLECallback(&m_xRichEditOleCallback);
//	SetEditorOpt();

	m_pEdit = this;
	
	m_objAttList.Create(WS_CHILD | WS_BORDER | LVS_REPORT, rect, this, 0);

	m_objAttList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_objAttList.InsertColumn(0, "ファイル名");
	m_objAttList.InsertColumn(1, "サイズ");

	DragAcceptFiles(TRUE);
	ModifyStyleEx(0, WS_EX_ACCEPTFILES);

	//添付ファイルを検索する
	//FindAttachFile();
	SetText(NULL, NULL, OP_WIKI);

	UpdateSetting();

	m_objEdit.EnableWindow(FALSE);
	m_objAttList.EnableWindow(FALSE);

	CLogFile::SaveAppLog("CWikiEditWnd 生成");	
	return 0;
}

void CWikiEditWnd::SetEditorOpt(){
/*
	DWORD dwOpt = ECO_AUTOVSCROLL | ECO_AUTOHSCROLL | ECO_WANTRETURN;
	DWORD dwDelOpt = 0;

//	if(pApp->m_bHideSel){
		dwOpt	|= ECO_NOHIDESEL | ECO_SAVESEL;
//	}else{
//		dwDelOpt|= ECO_NOHIDESEL | ECO_SAVESEL;
//	}
//	if(pApp->m_bSelWord){
		dwOpt	|= ECO_AUTOWORDSELECTION;
//	}else{
//		dwDelOpt|= ECO_AUTOWORDSELECTION;
//	}
	m_objEdit.SetOptions(ECOOP_SET, dwOpt);
	m_objEdit.SetOptions(ECOOP_XOR, dwDelOpt);
*/
}

BOOL CWikiEditWnd::OnToolTipNotifyEx(UINT id, NMHDR *pTTTStruct, LRESULT *pResult) {
	return OnToolTioNotifyFunc(pTTTStruct, pResult);
}
void CWikiEditWnd::OnToolTipNotify(NMHDR *pTTTStruct, LRESULT *pResult) {
	OnToolTioNotifyFunc(pTTTStruct, pResult);
}
void CWikiEditWnd::GetToolTipText(NMHDR *pTTTStruct, CString &strTipText){
	TOOLTIPTEXT *pInfo = (TOOLTIPTEXT*)pTTTStruct;

		UINT uIDs[] = { ID_WIKI_BOLD, ID_WIKI_ITALIC, ID_WIKI_UNDERLINE, ID_WIKI_STRIKE, 
						ID_WIKI_LIST, ID_WIKI_NUMLIST, ID_WIKI_HEAD, ID_WIKI_LINK, ID_WIKI_RET,
						ID_WIKI_HLINE};
	switch(pTTTStruct->idFrom){
	case ID_WIKI_BOLD:
		strTipText = "ボールド";
		break;
	case ID_WIKI_ITALIC:
		strTipText = "イタリック";
		break;
	case ID_WIKI_UNDERLINE:
		strTipText = "下線";
		break;
	case ID_WIKI_STRIKE:
		strTipText = "打ち消し線";
		break;
	case ID_WIKI_LIST:
		strTipText = "箇条書き";
		break;
	case ID_WIKI_NUMLIST:
		strTipText = "番号付き箇条書き";
		break;
	case ID_WIKI_HEAD:
		strTipText = "タイトル";
		break;
	case ID_WIKI_LINK:
		strTipText = "リンク";
		break;
	case ID_WIKI_RET:
		strTipText = "改行";
		break;
	case ID_WIKI_HLINE:
		strTipText = "水平線";
		break;
	}
}
int CWikiEditWnd::OnToolHitTest(CPoint point, TOOLINFO* pTI ) const{
//	CRect rect;
//	GetWindowRect(rect);
//	pTI->hwnd		= m_hWnd;
//	pTI->uId		= CDlgInfo::IDD;
//	pTI->lpszText	= LPSTR_TEXTCALLBACK;
//	pTI->rect		= rect;
//	pTI->uFlags		= TTF_NOTBUTTON | TTF_CENTERTIP | TTF_ALWAYSTIP /*| TTF_TRACK*/;
//	pTI->hinst		= AfxGetInstanceHandle();
	return pTI->uId;
}

void CWikiEditWnd::SetCtrlPos(){
	CRect rect;
	GetClientRect(rect);

	CRect edRect = rect;
	edRect.top += 24;
	edRect.bottom -= 120;

	m_objEdit.SetWindowPos(&wndTop, edRect.left, edRect.top, edRect.Width(), edRect.Height(), SWP_SHOWWINDOW);
	
	CRect ltRect;
	ltRect = rect;
	ltRect.top = edRect.bottom;
	m_objAttList.SetWindowPos(&wndTop, ltRect.left, ltRect.top, ltRect.Width(), ltRect.Height(), SWP_SHOWWINDOW);
}

void CWikiEditWnd::SetText(LPCTSTR lpWiki, LPCTSTR pszPathName, OPENMODE opMode){
	m_strOldText = lpWiki;
	m_objEdit.SetWindowText(lpWiki);
	m_strPathName = pszPathName;
	m_opMode = opMode;

	if(m_strPathName.IsEmpty()){
		m_objEdit.EnableWindow(FALSE);
		m_objAttList.EnableWindow(FALSE);
		return;			
	}
	m_objEdit.EnableWindow(TRUE);
	m_objAttList.EnableWindow(TRUE);
	FindAttachFile();
}


void CWikiEditWnd::SaveText(){
	if(m_pDoc == NULL){
		CLogFile::SaveAppLog("CWikiEditWnd::SaveText:m_pDocがnull");
		return;
	}
	if(m_pFrm == NULL){
		CLogFile::SaveAppLog("CWikiEditWnd::SaveText:m_pFrmがnull");
	}
	if(m_strPathName.IsEmpty()){
		CLogFile::SaveAppLog("CWikiEditWnd::SaveText:パス名が空なので保存せず");
		return;
	}
	CString strWikiText = "";
	m_objEdit.GetWindowText(strWikiText);
	if(!strWikiText.Compare(m_strOldText)){
		CLogFile::SaveAppLog("CWikiEditWnd::SaveText:内容が読み込み時と同じなので保存せず");
		return;
	}
	m_strOldText = strWikiText;
	switch(m_opMode){
	case OP_WIKI:
	case OP_USB:
		{
		//そのまま保存
			try{
				CString strPropFile = m_strPathName;
				strPropFile.Replace(".pwd", "\\.property");
				BOOL bCryp = (BOOL)GetInifileInt("Status", "Cryptography", 0, strPropFile);
				if(bCryp){
					//暗号化する
					CCryptography cryp;
					int nLen = strWikiText.GetLength();
					byte *pBuff = NULL;
					char *pszFrom = strWikiText.GetBuffer(strWikiText.GetLength());
					cryp.EncodeData((byte*)pszFrom, nLen, "PersonalWiki", pBuff);
					strWikiText.ReleaseBuffer();
					strWikiText = pBuff;
				}

				if(!m_strPathName.IsEmpty()){
					CFile file;
					file.Open(m_strPathName, CFile::modeCreate | CFile::modeNoInherit | CFile::modeReadWrite);
					file.Write(strWikiText.GetBuffer(0), strWikiText.GetLength());
					file.Flush();
					file.Close();
					switch(m_opMode){
					case OP_WIKI:
						m_pFrm->GetInfoTabView()->UpdateInfo(m_strWikiPath);
						break;
					case OP_USB:
						m_pFrm->GetInfoTabView()->UpdateInfoUSB(m_strWikiPath, m_strDataBasePath);
						break;
					}
				}
			}catch(CFileException &fe){
				CLogFile::SaveExceptionLog(&fe, "CWikiEditWnd::SaveText");
			}
		}
		break;
	case OP_DATE:
		{
			if(!m_strPathName.IsEmpty()){
				//スケジュールデータを取得して設定する
				COleDateTime oldDateTime;
				oldDateTime.ParseDateTime(m_strPathName);
				int year = oldDateTime.GetYear();
				int month = oldDateTime.GetMonth();
				int day = oldDateTime.GetDay();
				CEventDate *pData = m_pDoc->FindDate(year, month, day);
				if(pData){
					pData->SetDetail(strWikiText);
				}else{
					CEventDate objDate;
					objDate.Create("", strWikiText, &oldDateTime);
					m_pDoc->m_objScDateData.AddDate(&objDate);
				}
				m_pFrm->GetCalView()->UpdateCalender();
				m_pFrm->GetInfoTabView()->UpdateInfo(&oldDateTime);
			}
		}
		break;
	}
}

void CWikiEditWnd::OnDropFiles(HDROP hDropInfo){
	char pBuf[1025];
	memset(pBuf, 0, 1025);
	UINT fileCount = ::DragQueryFile(  hDropInfo, 
					0xFFFFFFFF,    
					pBuf, 
					1024);

	CString strBasePath = GetBasePath();
	for(unsigned int i=0; i < fileCount; i++){
		memset(pBuf, 0, 1025);
		::DragQueryFile(  hDropInfo, i, pBuf, 1024);

		//pBuf ... ドラッグしたファイル名が入ります
		//このファイルを開くコードを追加します
		CString strAttachFile;
		char szFile[MAX_PATH];
		char szExt[MAX_PATH];
		memset(szFile, 0, MAX_PATH);
		memset(szExt, 0, MAX_PATH);
		_splitpath(pBuf, NULL, NULL, szFile, szExt);
		CString strFileName;
		strFileName.Format("%s%s", szFile, szExt);
		CString strDir;
		strDir.Format("%sAttach\\%s\\", strBasePath, m_strWikiPath);
		strDir.Replace("/", "\\");
		strDir.Replace("\\\\", "\\");

		strAttachFile.Format("%s%s", strDir, strFileName);
		CFileCtrl::CreateDirectory(strDir);
		if(::CopyFile(pBuf, strAttachFile, FALSE)){
			int nCnt = m_objAttList.GetItemCount();
			m_objAttList.InsertItem(nCnt, strFileName);
		}
	}
	::DragFinish(hDropInfo);
//	CDialog::OnDropFiles(hDropInfo);
}

void CWikiEditWnd::OnWikiBold() {
	m_objEdit.ReplaceSel("''Bold''\r\n", TRUE);
}
void CWikiEditWnd::OnWikiItalic() {
	m_objEdit.ReplaceSel("'''Italic'''\r\n", TRUE);
}
void CWikiEditWnd::OnWikiStrike() {
	m_objEdit.ReplaceSel("%%Strike%%\r\n", TRUE);
}
void CWikiEditWnd::OnWikiUnderline() {
	m_objEdit.ReplaceSel("%%%UnderLine%%%\r\n", TRUE);
}
void CWikiEditWnd::OnWikiHead() {
	m_objEdit.ReplaceSel("*Title\r\n", TRUE);
}
void CWikiEditWnd::OnWikiHline() {
	m_objEdit.ReplaceSel("----\r\n", TRUE);
}
void CWikiEditWnd::OnWikiLink() {
	m_objEdit.ReplaceSel("[[Link]]\r\n", TRUE);
}
void CWikiEditWnd::OnWikiList() {
	m_objEdit.ReplaceSel("-List\r\n", TRUE);
}
void CWikiEditWnd::OnWikiNumlist() {
	m_objEdit.ReplaceSel("+List\r\n", TRUE);
}
void CWikiEditWnd::OnWikiRet() {
	m_objEdit.ReplaceSel("~\r\n", TRUE);
}

void CWikiEditWnd::OnUpdateWikiBold(CCmdUI* pCmdUI) {
	CWnd* pWnd = GetFocus();
	pCmdUI->Enable(pWnd ? m_objEdit.m_hWnd == pWnd->m_hWnd : FALSE);
}
void CWikiEditWnd::OnUpdateWikiHead(CCmdUI* pCmdUI) {
	CWnd* pWnd = GetFocus();
	pCmdUI->Enable(pWnd ? m_objEdit.m_hWnd == pWnd->m_hWnd : FALSE);
}
void CWikiEditWnd::OnUpdateWikiHline(CCmdUI* pCmdUI) {
	CWnd* pWnd = GetFocus();
	pCmdUI->Enable(pWnd ? m_objEdit.m_hWnd == pWnd->m_hWnd : FALSE);
}
void CWikiEditWnd::OnUpdateWikiItalic(CCmdUI* pCmdUI) {
	CWnd* pWnd = GetFocus();
	pCmdUI->Enable(pWnd ? m_objEdit.m_hWnd == pWnd->m_hWnd : FALSE);
}
void CWikiEditWnd::OnUpdateWikiLink(CCmdUI* pCmdUI) {
	CWnd* pWnd = GetFocus();
	pCmdUI->Enable(pWnd ? m_objEdit.m_hWnd == pWnd->m_hWnd : FALSE);
}
void CWikiEditWnd::OnUpdateWikiList(CCmdUI* pCmdUI) {
	CWnd* pWnd = GetFocus();
	pCmdUI->Enable(pWnd ? m_objEdit.m_hWnd == pWnd->m_hWnd : FALSE);
}
void CWikiEditWnd::OnUpdateWikiNumlist(CCmdUI* pCmdUI) {
	CWnd* pWnd = GetFocus();
	pCmdUI->Enable(pWnd ? m_objEdit.m_hWnd == pWnd->m_hWnd : FALSE);
}
void CWikiEditWnd::OnUpdateWikiRet(CCmdUI* pCmdUI) {
	CWnd* pWnd = GetFocus();
	pCmdUI->Enable(pWnd ? m_objEdit.m_hWnd == pWnd->m_hWnd : FALSE);
}
void CWikiEditWnd::OnUpdateWikiStrike(CCmdUI* pCmdUI) {
	CWnd* pWnd = GetFocus();
	pCmdUI->Enable(pWnd ? m_objEdit.m_hWnd == pWnd->m_hWnd : FALSE);
}
void CWikiEditWnd::OnUpdateWikiUnderline(CCmdUI* pCmdUI) {
	CWnd* pWnd = GetFocus();
	pCmdUI->Enable(pWnd ? m_objEdit.m_hWnd == pWnd->m_hWnd : FALSE);
}

BOOL CWikiEditWnd::PreTranslateMessage(MSG* pMsg) {
//	if(DlgKeyCancel(m_hWnd, pMsg)){
//		return TRUE;
//	}
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	switch(pMsg->message){
//	case WM_LBUTTONDOWN: 
//	case WM_LBUTTONUP: 
	case WM_MOUSEMOVE: 
		m_objToolTip.RelayEvent(pMsg);
		break;
	}
/*
	BOOL bResult = CWnd::PreTranslateMessage ( pMsg );
	if ( !bResult )
	{
		bResult = ( m_hAccel != NULL && TranslateAccelerator ( m_hWnd, m_hAccel, pMsg ) );
	}
	return bResult;
*/
    if(m_hAccelTable != NULL){
        if(::TranslateAccelerator(m_hWnd, m_hAccelTable, pMsg))
            return TRUE;
    }


	return CWnd::PreTranslateMessage ( pMsg );
}

void CWikiEditWnd::FindAttachFile(){
	if(!IsWindowSafe(&m_objAttList)){
		return;
	}
	CString strBase =  GetBasePath();
	CStringArray arrAttach;
	CAnalisysWiki::GetAttachFiles(m_strWikiPath, strBase, arrAttach);
	char szName[MAX_PATH];
	char szExt[MAX_PATH];
	m_objAttList.DeleteAllItems();
	for(int i = 0; i < arrAttach.GetSize(); i++){
		CString strAttach = arrAttach.GetAt(i);
		memset(szName, 0, MAX_PATH);
		memset(szExt, 0, MAX_PATH);
		_splitpath(strAttach, NULL, NULL, szName, szExt);
		CString strFileName;
		strFileName.Format("%s%s", szName, szExt);
		m_objAttList.InsertItem(i, strFileName, 0);
	}
	SetColumnWidthLC(&m_objAttList);
}

void CWikiEditWnd::OnUpdateEditCopy(CCmdUI* pCmdUI) {
}

void CWikiEditWnd::OnUpdateEditCut(CCmdUI* pCmdUI){
}

void CWikiEditWnd::OnUpdateEditPaste(CCmdUI* pCmdUI){
}

void CWikiEditWnd::OnUpdateEditUndo(CCmdUI* pCmdUI){
}

void CWikiEditWnd::OnEditCopy(){
	m_objEdit.Copy();
}

void CWikiEditWnd::OnEditCut(){
	m_objEdit.Cut();
}

void CWikiEditWnd::OnEditPaste(){
	m_objEdit.Paste();
}

void CWikiEditWnd::OnEditUndo(){
	m_objEdit.Undo();
}

/*
/////////////////////////////////////////////////////////////////////////////
// CWikiEditWnd::XRichEditOleCallback

BEGIN_INTERFACE_MAP(CWikiEditWnd, CWnd)
	// we use IID_IUnknown because richedit doesn't define an IID
	INTERFACE_PART(CWikiEditWnd, IID_IUnknown, RichEditOleCallback)
END_INTERFACE_MAP()
STDMETHODIMP_(ULONG) CWikiEditWnd::XRichEditOleCallback::AddRef(){
	METHOD_PROLOGUE_EX_(CWikiEditWnd, RichEditOleCallback)
	return (ULONG)pThis->InternalAddRef();
}

STDMETHODIMP_(ULONG) CWikiEditWnd::XRichEditOleCallback::Release(){
	METHOD_PROLOGUE_EX_(CWikiEditWnd, RichEditOleCallback)
	return (ULONG)pThis->InternalRelease();
}

STDMETHODIMP CWikiEditWnd::XRichEditOleCallback::QueryInterface(REFIID iid, LPVOID* ppvObj){
	METHOD_PROLOGUE_EX_(CWikiEditWnd, RichEditOleCallback)
	return (HRESULT)pThis->InternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CWikiEditWnd::XRichEditOleCallback::GetNewStorage(LPSTORAGE* ppstg){
	METHOD_PROLOGUE_EX_(CWikiEditWnd, RichEditOleCallback)
	// Create a flat storage and steal it from the client item
	// the client item is only used for creating the storage
	COleClientItem item;
	item.GetItemStorageFlat();
	*ppstg = item.m_lpStorage;
	HRESULT hRes = E_OUTOFMEMORY;
	if (item.m_lpStorage != NULL)
	{
		item.m_lpStorage = NULL;
		hRes = S_OK;
	}
//	pThis->GetDocument()->InvalidateObjectCache();
	return hRes;
}

STDMETHODIMP CWikiEditWnd::XRichEditOleCallback::GetInPlaceContext(
	LPOLEINPLACEFRAME* lplpFrame, LPOLEINPLACEUIWINDOW* lplpDoc,
	LPOLEINPLACEFRAMEINFO lpFrameInfo){
	METHOD_PROLOGUE_EX(CWikiEditWnd, RichEditOleCallback)
//	return pThis->GetWindowContext(lplpFrame, lplpDoc, lpFrameInfo);
	return E_NOTIMPL;
}

STDMETHODIMP CWikiEditWnd::XRichEditOleCallback::ShowContainerUI(BOOL fShow){
	METHOD_PROLOGUE_EX(CWikiEditWnd, RichEditOleCallback)
//	return pThis->ShowContainerUI(fShow);
	return E_NOTIMPL;
}

STDMETHODIMP CWikiEditWnd::XRichEditOleCallback::QueryInsertObject(
	LPCLSID lpclsid, LPSTORAGE pstg, LONG cp){
	METHOD_PROLOGUE_EX(CWikiEditWnd, RichEditOleCallback)

//	pThis->GetDocument()->InvalidateObjectCache();
//	return S_OK;

	return E_NOTIMPL;
}

STDMETHODIMP CWikiEditWnd::XRichEditOleCallback::DeleteObject(LPOLEOBJECT lpoleobj){
	METHOD_PROLOGUE_EX_(CWikiEditWnd, RichEditOleCallback)
//	pThis->GetDocument()->InvalidateObjectCache();
	return S_OK;
}

STDMETHODIMP CWikiEditWnd::XRichEditOleCallback::QueryAcceptData(
	LPDATAOBJECT lpdataobj, CLIPFORMAT* lpcfFormat, DWORD reco,
	BOOL fReally, HGLOBAL hMetaPict){
	METHOD_PROLOGUE_EX(CWikiEditWnd, RichEditOleCallback)
//	return pThis->QueryAcceptData(lpdataobj, lpcfFormat, reco,
//		fReally, hMetaPict);
    ATLASSERT(lpcfFormat != NULL);
    if (!fReally) // not actually pasting
        return S_OK;
    if (*lpcfFormat == CF_TEXT)
        return S_OK;
    CComPtr<IDataObject> data(lpdataobj);
    FORMATETC fe;
    fe.cfFormat = CF_TEXT;
    fe.ptd = NULL;
    fe.dwAspect = DVASPECT_CONTENT;
    fe.lindex = -1;
    fe.tymed = TYMED_HGLOBAL;
    if (S_OK == data->QueryGetData(&fe)) {
        *lpcfFormat = CF_TEXT;
        return S_OK;
    } else {
        return S_FALSE;
    }
}

STDMETHODIMP CWikiEditWnd::XRichEditOleCallback::ContextSensitiveHelp(BOOL fEnterMode){
	return E_NOTIMPL;
}

STDMETHODIMP CWikiEditWnd::XRichEditOleCallback::GetClipboardData(
	CHARRANGE* lpchrg, DWORD reco, LPDATAOBJECT* lplpdataobj){
	METHOD_PROLOGUE_EX(CWikiEditWnd, RichEditOleCallback)

	LPDATAOBJECT lpOrigDataObject = NULL;

	// get richedit's data object
	if (FAILED(pThis->m_lpRichEditOle->GetClipboardData(lpchrg, reco,
		&lpOrigDataObject)))
	{
		return E_NOTIMPL;
	}

	// allow changes
//	HRESULT hRes = pThis->GetClipboardData(lpchrg, reco, lpOrigDataObject,
//		lplpdataobj);
	HRESULT hRes = E_NOTIMPL;

	// if changed then free original object
	if (SUCCEEDED(hRes))
	{
		if (lpOrigDataObject!=NULL)
			lpOrigDataObject->Release();
		return hRes;
	}
	else
	{
		// use richedit's data object
		*lplpdataobj = lpOrigDataObject;
		return S_OK;
	}

	return S_OK;
}

STDMETHODIMP CWikiEditWnd::XRichEditOleCallback::GetDragDropEffect(
	BOOL fDrag, DWORD grfKeyState, LPDWORD pdwEffect){
	if (!fDrag) // allowable dest effects
	{
		DWORD dwEffect;
		// check for force link
		if ((grfKeyState & (MK_CONTROL|MK_SHIFT)) == (MK_CONTROL|MK_SHIFT))
			dwEffect = DROPEFFECT_LINK;
		// check for force copy
		else if ((grfKeyState & MK_CONTROL) == MK_CONTROL)
			dwEffect = DROPEFFECT_COPY;
		// check for force move
		else if ((grfKeyState & MK_ALT) == MK_ALT)
			dwEffect = DROPEFFECT_MOVE;
		// default -- recommended action is move
		else
			dwEffect = DROPEFFECT_MOVE;
		if (dwEffect & *pdwEffect) // make sure allowed type
			*pdwEffect = dwEffect;
	}
	return S_OK;
}

STDMETHODIMP CWikiEditWnd::XRichEditOleCallback::GetContextMenu(
	WORD seltype, LPOLEOBJECT lpoleobj, CHARRANGE* lpchrg,
	HMENU* lphmenu){
	METHOD_PROLOGUE_EX(CWikiEditWnd, RichEditOleCallback)

//	HMENU hMenu = pThis->GetContextMenu(seltype, lpoleobj, lpchrg);
//	if (hMenu == NULL)
//		return E_NOTIMPL;
//	*lphmenu = hMenu;

	return E_NOTIMPL;
}
*/
void CWikiEditWnd::OnDestroy(){
//	if (m_lpRichEditOle != NULL){
//		m_lpRichEditOle->Release();
//		m_lpRichEditOle = NULL;
//	}
	CWnd::OnDestroy();
}

void CWikiEditWnd::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	m_objEdit.SetFocus();
	
}

void CWikiEditWnd::UpdateSetting(){
	FONTINFO objFontInfo;
	CMainFrame *pFrm = GetMainFrame(this);
	pFrm->m_objIniFile.GetFontInfoIniData(objFontInfo);
	
	m_objFont.DeleteObject();
	MakeFont(m_objFont, GetDC(), objFontInfo.szEditFontName, objFontInfo.lEditHeight);
	m_objEdit.SetFont(&m_objFont);
}
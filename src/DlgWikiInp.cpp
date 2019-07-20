// DlgWikiInp.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "personalwiki.h"
#include "DlgWikiInp.h"
#include "AnalisysWiki.h"
#include "MainFrm.h"
#include "InfoView.h"
#include "LogFile.h"
#include "FileCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define USE_TOOLBAR

/////////////////////////////////////////////////////////////////////////////
// CDlgWikiInp ダイアログ


CDlgWikiInp::CDlgWikiInp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWikiInp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWikiInp)
	m_strText = _T("");
	//}}AFX_DATA_INIT
	m_strWikiPath = "";
	m_pPreview = NULL;
}


void CDlgWikiInp::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWikiInp)
	DDX_Control(pDX, IDC_HTMLDUMMY, m_objDummy);
	DDX_Control(pDX, IDC_ED_WIKITEXT, m_objEdit);
	DDX_Control(pDX, IDC_ATTACHLIST, m_objAttList);
	DDX_Text(pDX, IDC_ED_WIKITEXT, m_strText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWikiInp, CDialog)
	//{{AFX_MSG_MAP(CDlgWikiInp)
	ON_BN_CLICKED(IDC_BTN_PREVIEW, OnBtnPreview)
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
	ON_WM_DROPFILES()
    ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotifyEx)
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipNotifyEx)
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipNotifyEx)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWikiInp メッセージ ハンドラ
BOOL CDlgWikiInp::OnToolTipNotifyEx(UINT id, NMHDR *pTTTStruct, LRESULT *pResult) {
	return OnToolTioNotifyFunc(pTTTStruct, pResult);
}
void CDlgWikiInp::OnToolTipNotify(NMHDR *pTTTStruct, LRESULT *pResult) {
	OnToolTioNotifyFunc(pTTTStruct, pResult);
}
void CDlgWikiInp::GetToolTipText(NMHDR *pTTTStruct, CString &strTipText){
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
int CDlgWikiInp::OnToolHitTest(CPoint point, TOOLINFO* pTI ) const{
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

BOOL CDlgWikiInp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: この位置に初期化の補足処理を追加してください
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
	m_strText = m_strSetText;
	UpdateData(FALSE);
	m_objAttList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_objAttList.InsertColumn(0, "ファイル名");
	m_objAttList.InsertColumn(1, "サイズ");

	DragAcceptFiles(TRUE);
	ModifyStyleEx(0, WS_EX_ACCEPTFILES);

	m_pPreview = (CPreviewHtmlView*)RUNTIME_CLASS(CPreviewHtmlView)->CreateObject();
	CRect rectPrev;
	m_objDummy.GetClientRect(rectPrev);
	m_objDummy.MapWindowPoints(this, rectPrev);
	m_pPreview->Create(NULL, NULL, WS_CHILD | WS_BORDER | WS_VISIBLE, rectPrev, this, IDS_PREVIEW);
	//添付ファイルを検索する
	CString strBase =  GetBasePath();
	CStringArray arrAttach;
	CAnalisysWiki::GetAttachFiles(m_strWikiPath, strBase, arrAttach);
	char szName[MAX_PATH];
	char szExt[MAX_PATH];
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

	OnBtnPreview();

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDlgWikiInp::OnBtnPreview(){
	UpdateData();
	CAnalisysWiki analize;
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgWikiInp::OnBtnPreview : pFrm is null");
	}
	WIKIINFO objIni;
	pFrm->m_objIniFile.GetWikiInfoIniData(objIni);
	
	ANAINFO objAna;
	memset(&objAna, 0, sizeof(ANAINFO));
	objAna.bUseRetFormat = objIni.bUseRet;
	objAna.bUseTBLink = objIni.bUseTopBtmLnk;
	objAna.bShowAttach = objIni.bUseShowAttach;
	objAna.bUseShowConvTime = objIni.bUseShowConvTime;
	strcpy(objAna.pszBasePath, GetBasePath());
	analize.SetAnaSetting(&objAna);
	CString strHtml;
	CString strBody;
	analize.SetMimeType(&pFrm->m_objMimeTypes);
	analize.Analisys(m_strText, strBody, "", FALSE);
	analize.CreateHTML(strHtml, objIni.szCss, "", strBody); 
	
	CFile file;
	try{
		CString strTmpPath;
		strTmpPath.Format("%sprev.html", GetBasePath());
		file.Open(strTmpPath, CFile::modeCreate | CFile::modeNoInherit | CFile::modeReadWrite);
		file.Write(strHtml, strHtml.GetLength());
		file.Flush();
		file.Close();
		m_pPreview->Navigate2(strTmpPath);
	}catch(CFileException &fe){
		CLogFile::SaveExceptionLog(&fe, "CDlgWikiInp::OnBtnPreview");
	}
}

void CDlgWikiInp::OnOK(){
	UpdateData(TRUE);	
	m_strSetText = m_strText;
	CDialog::OnOK();
}

void CDlgWikiInp::OnDropFiles(HDROP hDropInfo){
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

BOOL CDlgWikiInp::PreTranslateMessage(MSG* pMsg) 
{
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	switch(pMsg->message){
//	case WM_LBUTTONDOWN: 
//	case WM_LBUTTONUP: 
	case WM_MOUSEMOVE: 
		m_objToolTip.RelayEvent(pMsg);
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgWikiInp::OnWikiBold() {
	m_objEdit.ReplaceSel("''Bold''\r\n", TRUE);
}
void CDlgWikiInp::OnWikiItalic() {
	m_objEdit.ReplaceSel("'''Italic'''\r\n", TRUE);
}
void CDlgWikiInp::OnWikiStrike() {
	m_objEdit.ReplaceSel("%%Strike%%\r\n", TRUE);
}
void CDlgWikiInp::OnWikiUnderline() {
	m_objEdit.ReplaceSel("%%%UnderLine%%%\r\n", TRUE);
}
void CDlgWikiInp::OnWikiHead() {
	m_objEdit.ReplaceSel("*Title\r\n", TRUE);
}
void CDlgWikiInp::OnWikiHline() {
	m_objEdit.ReplaceSel("----\r\n", TRUE);
}
void CDlgWikiInp::OnWikiLink() {
	m_objEdit.ReplaceSel("[[Link]]\r\n", TRUE);
}
void CDlgWikiInp::OnWikiList() {
	m_objEdit.ReplaceSel("-List\r\n", TRUE);
}
void CDlgWikiInp::OnWikiNumlist() {
	m_objEdit.ReplaceSel("+List\r\n", TRUE);
}
void CDlgWikiInp::OnWikiRet() {
	m_objEdit.ReplaceSel("~\r\n", TRUE);
}

void CDlgWikiInp::OnUpdateWikiBold(CCmdUI* pCmdUI) {
	pCmdUI->Enable(m_objEdit.m_hWnd == GetFocus()->m_hWnd);
}
void CDlgWikiInp::OnUpdateWikiHead(CCmdUI* pCmdUI) {
	pCmdUI->Enable(m_objEdit.m_hWnd == GetFocus()->m_hWnd);
}
void CDlgWikiInp::OnUpdateWikiHline(CCmdUI* pCmdUI) {
	pCmdUI->Enable(m_objEdit.m_hWnd == GetFocus()->m_hWnd);
}
void CDlgWikiInp::OnUpdateWikiItalic(CCmdUI* pCmdUI) {
	pCmdUI->Enable(m_objEdit.m_hWnd == GetFocus()->m_hWnd);
}
void CDlgWikiInp::OnUpdateWikiLink(CCmdUI* pCmdUI) {
	pCmdUI->Enable(m_objEdit.m_hWnd == GetFocus()->m_hWnd);
}
void CDlgWikiInp::OnUpdateWikiList(CCmdUI* pCmdUI) {
	pCmdUI->Enable(m_objEdit.m_hWnd == GetFocus()->m_hWnd);
}
void CDlgWikiInp::OnUpdateWikiNumlist(CCmdUI* pCmdUI) {
	pCmdUI->Enable(m_objEdit.m_hWnd == GetFocus()->m_hWnd);
}
void CDlgWikiInp::OnUpdateWikiRet(CCmdUI* pCmdUI) {
	pCmdUI->Enable(m_objEdit.m_hWnd == GetFocus()->m_hWnd);
}
void CDlgWikiInp::OnUpdateWikiStrike(CCmdUI* pCmdUI) {
	pCmdUI->Enable(m_objEdit.m_hWnd == GetFocus()->m_hWnd);
}
void CDlgWikiInp::OnUpdateWikiUnderline(CCmdUI* pCmdUI) {
	pCmdUI->Enable(m_objEdit.m_hWnd == GetFocus()->m_hWnd);
}

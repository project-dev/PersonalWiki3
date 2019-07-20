// DlgInfo.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "DlgInfo.h"
#include "MainFrm.h"
#include "AnalisysWiki.h"

#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfo ダイアログ


CDlgInfo::CDlgInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfo)
	m_strTime = _T("");
	//}}AFX_DATA_INIT
	m_pMainFrm = NULL;
	m_pBackDC = NULL;
	m_pBackBmp = NULL;
	m_pOldBmp = NULL;
	m_strInfo = "";
	m_uTimerID = 0;
	m_objDefRect.SetRect(0, 0, 0, 0);
}
CDlgInfo::~CDlgInfo(){
	if(m_pBackDC){
		delete m_pBackDC;
		m_pBackDC = NULL;
	}
	if(m_pBackBmp){
		delete m_pBackBmp;
		m_pBackBmp = NULL;
	}
}

void CDlgInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfo)
	DDX_Control(pDX, IDC_TIME, m_objTime);
	DDX_Text(pDX, IDC_TIME, m_strTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgInfo)
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_NCMOUSEMOVE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_MOVE()
	ON_COMMAND(IDM_CLOSE, OnClose)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDM_FIXED_DATA, OnFixedData)
	ON_COMMAND(IDM_PWIKI_SET, OnPwikiSet)
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
//	ON_NOTIFY_EX(TTN_NEEDTEXTW, 0, OnToolTipNotifyEx)
//	ON_NOTIFY_EX(TTN_NEEDTEXTA, 0, OnToolTipNotifyEx)
//	ON_NOTIFY(TTN_NEEDTEXTW, 0, OnToolTipNotify)
//	ON_NOTIFY(TTN_NEEDTEXTA, 0, OnToolTipNotify)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotifyEx)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipNotifyEx)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipNotifyEx)

END_MESSAGE_MAP()

BOOL CDlgInfo::OnToolTipNotifyEx(UINT id, NMHDR *pTTTStruct, LRESULT *pResult) {
	return OnToolTioNotifyFunc(pTTTStruct, pResult);
}

void CDlgInfo::OnToolTipNotify(NMHDR *pTTTStruct, LRESULT *pResult) {
	OnToolTioNotifyFunc(pTTTStruct, pResult);
}

void CDlgInfo::GetToolTipText(NMHDR *pTTTStruct, CString &strTipText){
	CreateScrollText(strTipText);
	strTipText.TrimLeft();
	strTipText.TrimRight();
	strTipText.Replace("\r\n", " ");
	strTipText.Replace("  ", " ");
	strTipText.Replace(" ", "\r\n - ");
	//最大幅を求める
	CString strTmp = strTipText;
	int nMaxLen = 80;
	CSize sz;
	CDC *pDC = GetDC();
	while(!strTmp.IsEmpty()){
		int nPos = strTmp.Find("\r\n", 0);
		if(nPos == -1){
			sz = pDC->GetTextExtent(nMaxLen);
			if(nMaxLen < sz.cx){
				nMaxLen = sz.cx;
			}
			strTmp = "";
		}else{
			CString strChkLen = strTmp.Left(nPos);
			sz = pDC->GetTextExtent(strChkLen);
			if(nMaxLen < sz.cx){
				nMaxLen = sz.cx;
			}
			strTmp = strTmp.Mid(nPos + 1);
		}
	}
	m_objToolTip.SetMaxTipWidth(nMaxLen);
	ReleaseDC(pDC);
}

int CDlgInfo::OnToolHitTest(CPoint point, TOOLINFO* pTI ) const{
	CRect rect;
	GetClientRect(rect);
	pTI->hwnd		= m_hWnd;
	pTI->uId		= 0;
	pTI->lpszText	= LPSTR_TEXTCALLBACK;
	pTI->rect		= rect;
	pTI->uFlags		= TTF_NOTBUTTON | TTF_CENTERTIP ;
	pTI->hinst		= AfxGetInstanceHandle();
	return CDlgInfo::IDD;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgInfo メッセージ ハンドラ
int CDlgInfo::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CLogFile::SaveAppLog("情報バー生成 Start");
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(rect);
	GetWindowRect(m_objDefRect);

	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgInfo::OnCreate : pFrm is null");
	}
	DLGINFO objInfo;
	pFrm->m_objIniFile.GetDlgInfoIniData(objInfo);
	ModifyStyleEx(0, WS_EX_TOPMOST);

	CDC *pDC = GetDC();
	int nHorz = pDC->GetDeviceCaps(HORZRES);
	int nVert = pDC->GetDeviceCaps(VERTRES);

	if((objInfo.nX + rect.Width())> nHorz){
		objInfo.nX = nHorz - rect.Width();
	}
	if((objInfo.nY + rect.Height())> nVert){
		objInfo.nY = nVert - rect.Height();
	}
	ReleaseDC(pDC);

	SetWindowPos(&wndTopMost, objInfo.nX, objInfo.nY, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
	m_hIcon = LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_PERSONTYPE));
	SetIcon(m_hIcon, FALSE);
	SetIcon(m_hIcon, TRUE);

	GetClientRect(rect);
	m_objToolTip.Create(this);
	m_objToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rect, IDD_DLGINFO);
	m_objToolTip.SetDelayTime(TTDT_AUTOPOP, 9999);
	m_objToolTip.SetDelayTime(TTDT_INITIAL, 100);
	m_objChkDate = COleDateTime::GetCurrentTime();
	
	m_objDlgToDay.Create(IDD_DLG_TODAY, this);
	ShowToDay(TRUE);
	CLogFile::SaveAppLog("情報バー生成 End");
	return 0;
}

BOOL CDlgInfo::OnInitDialog() {
	CLogFile::SaveAppLog("CDlgInfo::OnInitDialog");

	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	CRect rect;
	GetClientRect(rect);
	m_nScrPos = rect.Width();

	CFont *pFont = GetFont();
	LOGFONT lFont;
	pFont->GetLogFont(&lFont);
	lFont.lfHeight = -12;
	m_objFont.CreateFontIndirect(&lFont);

	CreateBackBuff();
	SetTimer(1, 100, NULL);

	SetWindowText("PersnalWiki");
	UpdateDisp();

	CLogFile::SaveAppLog("CDlgInfo::OnInitDialog End");
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

BOOL CDlgInfo::PreTranslateMessage(MSG* pMsg){
	if(::IsWindow(m_objToolTip.m_hWnd)){
		switch(pMsg->message){
		case WM_MOUSEMOVE:
			if(GetActiveWindow() == this){
				m_objToolTip.RelayEvent(pMsg);
			}
			break;
		}
	}
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgInfo::OnTimer(UINT nIDEvent) {
	CDialog::OnTimer(nIDEvent);
	UpdateDisp();
	ShowToDay();
}

void CDlgInfo::OnLButtonDblClk(UINT nFlags, CPoint point){
	if(m_pMainFrm){
		if(m_pMainFrm->IsWindowVisible()){
			m_pMainFrm->ShowWindow(SW_HIDE);
		}else{
			m_pMainFrm->ShowWindow(SW_RESTORE);
			m_pMainFrm->ShowWindow(SW_SHOW);
			//m_pMainFrm->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
//			m_pMainFrm->SetActiveWindow();
//			m_pMainFrm->SetFocus();
			m_pMainFrm->SetForegroundWindow();
		}
	}

	CDialog::OnLButtonDblClk(nFlags, point);
}

int CDlgInfo::CalcTextCount(){
	CRect rect;
	CDC *pDC = GetDC();
	GetClientRect(rect);
	CString arrChkTxt[] = {
		"A","C","E","G","I",
	};
	int nSize = sizeof(arrChkTxt) / sizeof(CString);
	int nWidth = 0;
	int nHeight = 0;
	for(int i = 0; i < nSize; i++){
		CSize size = pDC->GetTextExtent(arrChkTxt[i]);
		nWidth += size.cx;
	}
	nWidth = nWidth / nSize;
	ReleaseDC(pDC);
	return rect.Width() / nWidth;
}

void CDlgInfo::OnPaint(){
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	if(m_pBackDC){
		CRect rect;
		GetTextOutRect(rect);
		dc.BitBlt(rect.left, 0, rect.Width(), rect.Height(), m_pBackDC, 0, 0, SRCCOPY);
	}
}

void CDlgInfo::SetMainFrame(CMainFrame *pFrm){
	m_pMainFrm = pFrm;
}

BOOL CDlgInfo::UpdateViewSetting(){
	return TRUE;
}

void CDlgInfo::OnNcMouseMove(UINT nHitTest, CPoint point){
	CDialog::OnNcMouseMove(nHitTest, point);
}

void CDlgInfo::OnMouseMove(UINT nFlags, CPoint point) {
	POINT curPos;
	GetCursorPos(&curPos);
	CRect rect;
	GetClientRect(rect);
	if(nFlags == MK_LBUTTON){
		//ウィンドウも移動
		int nShiftX = m_objOldCurPos.x - curPos.x;
		int nShiftY = m_objOldCurPos.y - curPos.y;
		CRect rect;
		GetWindowRect(rect);
		int nMoveX = rect.left - nShiftX;
		int nMoveY = rect.top - nShiftY;

		CDC *pDC = GetDC();
		int nWidth = pDC->GetDeviceCaps(HORZRES);
		int nHeight = pDC->GetDeviceCaps(VERTRES);

		CRect taskRect;
		CRect moveRect(0, 0, nWidth, nHeight);

		HWND hwndTray = ::FindWindow(_T("Shell_TrayWnd"), NULL);
		if (hwndTray != NULL) {
			::GetWindowRect(hwndTray, taskRect);
			if(taskRect.left < 0){
				taskRect.left = 0;
			}
			if(taskRect.top < 0){
				taskRect.top = 0;
			}
			if(taskRect.right > nWidth){
				taskRect.right = nWidth;
			}
			if(taskRect.bottom > nHeight){
				taskRect.bottom = nHeight;
			}

			if((taskRect.left == 0) && (taskRect.right == nWidth)){
				if(taskRect.top == 0){
					moveRect.top += taskRect.Height();
				}else{
					moveRect.bottom -= taskRect.Height();
				}
			}
			if((taskRect.top == 0) && (taskRect.bottom == nHeight)){
				if(taskRect.left == 0){
					moveRect.left += taskRect.Width();
				}else{
					moveRect.right -= taskRect.Width();
				}
			}
		}
	
		ReleaseDC(pDC);
		if(nMoveX < moveRect.left){
			nMoveX = moveRect.left;
		}
		if(nMoveY < moveRect.top){
			nMoveY = moveRect.top;
		}
		if((nMoveX + rect.Width()) > moveRect.right){
			nMoveX = moveRect.right - rect.Width();
		}
		if((nMoveY + rect.Height()) > moveRect.bottom){
			nMoveY = moveRect.bottom - rect.Height();
		}

		MoveWindow(nMoveX, nMoveY, rect.Width(), rect.Height());	
	}
	m_objOldCurPos = curPos;
	CDialog::OnMouseMove(nFlags, point);
}

void CDlgInfo::OnLButtonDown(UINT nFlags, CPoint point){
	SetCapture();
	POINT curPos;
	GetCursorPos(&curPos);
	m_objOldCurPos = curPos;
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgInfo::OnLButtonUp(UINT nFlags, CPoint point){
	ReleaseCapture();
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgInfo::CreateScrollText(CString &strText){
	COleDateTime objCurrent = COleDateTime::GetCurrentTime();
	CString strDate = objCurrent.Format("%Y/%m/%d");
	int nCnt = CalcTextCount();
	
	//現在の出力文字
	int nOutCnt = m_nScrPos / nCnt;

	CAnalisysWiki objAna;
	CString strInfo;
	ANAINFO objAnaInfo;
	memset(&objAnaInfo, 0, sizeof(ANAINFO));
	objAnaInfo.bUseRetFormat = FALSE;
	objAnaInfo.bUseTBLink = FALSE;
	objAnaInfo.bShowAttach = FALSE;
	objAnaInfo.bUseShowConvTime = FALSE;
	strcpy(objAnaInfo.pszBasePath, "");
	objAna.SetAnaSetting(&objAnaInfo);
//	objAna.SetMimeType(&pFrm->m_objMimeTypes);
	objAna.Analisys(m_strInfo, strInfo, NULL, TRUE);

	CString strOutText = strDate;
	strOutText += " ";
	strOutText += strInfo;
	strOutText.Replace("\n", " ");
	strText = strOutText;

}

BOOL CDlgInfo::CreateBackBuff(){
	if(m_pBackDC){
		delete m_pBackDC;
		m_pBackDC = NULL;
	}
	if(m_pBackBmp){
		m_pBackBmp->DeleteObject();
		delete m_pBackBmp;
		m_pBackBmp = NULL;
	}
	if(!m_pBackDC){
		m_pBackDC = new CDC();
	}
	if(!m_pBackBmp){
		m_pBackBmp = new CBitmap();
	}
	if(!m_pBackDC || !m_pBackBmp){
		if(m_pBackDC){
			delete m_pBackDC;
			m_pBackDC = NULL;
		}
		if(m_pBackBmp){
			delete m_pBackBmp;
			m_pBackBmp = NULL;
		}
		return FALSE;
	}
	CDC *pDC = GetDC();
	if(!m_pBackDC->CreateCompatibleDC(pDC)){
		delete m_pBackDC;
		m_pBackDC = NULL;
		delete m_pBackBmp;
		m_pBackBmp = NULL;
		return FALSE;
	}
	CRect rect;
	GetTextOutRect(rect);
	if(!m_pBackBmp->CreateCompatibleBitmap(pDC, rect.Width(), rect.Height())){
		delete m_pBackDC;
		m_pBackDC = NULL;
		delete m_pBackBmp;
		m_pBackBmp = NULL;
		return FALSE;
	}
	m_pOldFont = (CFont*)m_pBackDC->SelectObject(m_objFont);
	m_pOldBmp = m_pBackDC->SelectObject(m_pBackBmp);
	ReleaseDC(pDC);
	return TRUE;
}

void CDlgInfo::GetTextOutRect(CRect &rect){
	CRect tmRect;
	GetClientRect(rect);
//	GetWindowRect(rect);
	if(::IsWindow(m_objTime.m_hWnd)){
		m_objTime.GetClientRect(tmRect);
//		m_objTime.GetWindowRect(tmRect);
		rect.right -= (tmRect.Width() + 1);
	}
}


void CDlgInfo::OnDestroy(){
	if(m_uTimerID != -1){
		KillTimer(m_uTimerID);
		m_uTimerID = -1;
	}
	if(m_pBackDC){
		delete m_pBackDC;
		m_pBackDC = NULL;
	}
	if(m_pBackBmp){
		delete m_pBackBmp;
		m_pBackBmp = NULL;
	}
	CDialog::OnDestroy();
}

void CDlgInfo::SetInfo(LPCTSTR pszInfo){
	m_strInfo = pszInfo;
}

void CDlgInfo::OnMove(int x, int y) {
	CDialog::OnMove(x, y);

	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgInfo::OnMove : pFrm is null");
	}
	if(pFrm){
		DLGINFO objInfo;
		pFrm->m_objIniFile.GetDlgInfoIniData(objInfo);
		CRect rect;
		GetWindowRect(rect);
		objInfo.nX = rect.left;
		objInfo.nY = rect.top;
		pFrm->m_objIniFile.SetDlgInfoIniData(&objInfo);
	}	
}

void CDlgInfo::OnClose(){

	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgInfo::OnClose : pFrm is null");
	}
	
	if(!pFrm->IsEndSession()){
		int nRet = ::MessageBox(NULL, "PersonalWikiを終了しますか？", "確認", MB_OKCANCEL);
		if(nRet != IDOK){
			return;
		}
	}

	if(m_uTimerID != -1)	{
		KillTimer(m_uTimerID);
		m_uTimerID = -1;
	}
	if(pFrm){
		CRect rect;
		GetWindowRect(rect);
		DLGINFO objInfo;
		pFrm->m_objIniFile.GetDlgInfoIniData(objInfo);
		objInfo.nX = rect.left;
		objInfo.nY = rect.top;
		pFrm->m_objIniFile.SetDlgInfoIniData(&objInfo);
	}

	pFrm->ApplExit();
	//PostMessage(WM_CLOSE);
	//if(pFrm){
	//	pFrm->PostMessage(WM_CLOSE);
	//}
}


void CDlgInfo::OnContextMenu(CWnd* pWnd, CPoint point) {
	CMenu objMenu;
	objMenu.LoadMenu(IDR_DLGINFOMENU);
	CMenu *pMenu = objMenu.GetSubMenu(0);
	POINT pos;
	GetCursorPos(&pos);
 	pMenu->TrackPopupMenu(TPM_LEFTALIGN, pos.x, pos.y, this);
}

void CDlgInfo::UpdateDisp(){
	SetRedraw(FALSE);

	BOOL bIsShowSec = FALSE;
	CMainFrame *pFrm = GetMainFrame(this);
	if(pFrm){
		DLGINFO objDlgIni;
		pFrm->m_objIniFile.GetDlgInfoIniData(objDlgIni);
		bIsShowSec = objDlgIni.bIsShowSec;
	}
	
	int nCnt = CalcTextCount();
	CDC *pDC = GetDC();
	if(pDC){
		CString strOutText;
		CreateScrollText(strOutText);
		CSize sz = pDC->GetTextExtent(strOutText);
		strOutText.TrimLeft();
		strOutText.TrimRight();
		CRect wndRect;
		GetWindowRect(wndRect);
		CRect rect;
		GetTextOutRect(rect);
		if(rect.Width() > sz.cx){
			//スクロール不要
			m_nScrPos = (rect.Width() - sz.cx) / 2;
		}else{
			m_nScrPos -= 4;
			if(m_nScrPos <= (sz.cx * -1)){
				m_nScrPos = rect.Width();
			}
		}
		if(m_pBackDC){
			CRect fillRect(0, 0, rect.Width(), rect.Height());
			CBrush brush;
			brush.CreateSolidBrush(RGB(0x00, 0x00, 0x88));
			m_pBackDC->SetBkMode(TRANSPARENT);
			m_pBackDC->SetTextColor(RGB(0xFF, 0xFF, 0xFF));
			m_pBackDC->FillRect(fillRect, &brush);

			int nYSpan = (rect.Height() - wndRect.Height()) / 2;
			nYSpan *= -1;
			m_pBackDC->TextOut(m_nScrPos, nYSpan, strOutText);
		}
		InvalidateRect(NULL);
		ReleaseDC(pDC);

		if(bIsShowSec){
			m_strTime = COleDateTime::GetCurrentTime().Format(" %H:%M:%S");
		}else{
			m_strTime = COleDateTime::GetCurrentTime().Format(" %H:%M   ");
		}
		UpdateData(FALSE);
	}
	SetRedraw(TRUE);
	InvalidateRect(NULL, FALSE);

}

void CDlgInfo::OnFixedData() {
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgInfo::OnFixedData : pFrm is null");
	}
	pFrm->SendMessage(WM_COMMAND, IDM_FIXED_DATA, (LPARAM)pFrm->m_hWnd);
}

void CDlgInfo::OnPwikiSet(){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgInfo::OnPwikiSet : pFrm is null");
	}
	pFrm->SendMessage(WM_COMMAND, IDM_PWIKI_SET, (LPARAM)pFrm->m_hWnd);
}

LRESULT CDlgInfo::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) {
	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CDlgInfo::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) {
	return CDialog::OnNotify(wParam, lParam, pResult);
}


void CDlgInfo::ShowToDay(BOOL bForce){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgInfo::ShowToDay : pFrm is null");
	}
	APPINFO objInfo;
	pFrm->m_objIniFile.GetAppInfoIniData(objInfo);

	if(!objInfo.bUseToDay){
		return;
	}
	
	COleDateTime objCur = COleDateTime::GetCurrentTime();
	COleDateTimeSpan span = objCur - m_objChkDate;
	int nSpan = span.GetDays();
	if(bForce || (nSpan > 0)){
		if(::IsWindow(m_objDlgToDay.m_hWnd) && !::IsWindowVisible(m_objDlgToDay.m_hWnd)){
			m_objDlgToDay.UpdateToDay();
			m_objDlgToDay.ShowWindow(SW_SHOW);

			CDC *pDC = GetDC();
			int nHorz = pDC->GetDeviceCaps(HORZRES);
			int nVert = pDC->GetDeviceCaps(VERTRES);

			CRect clRect;
			m_objDlgToDay.GetWindowRect(clRect);

			int nSx = (nHorz / 2) - (clRect.Width() / 2);
			int nSy = (nVert / 2) - (clRect.Height() / 2);

			m_objDlgToDay.SetWindowPos(&wndTop, 
									   nSx, nSy, 
									   clRect.Width(), clRect.Height(), 
									   SWP_SHOWWINDOW | SWP_NOSIZE);
		}
		m_objChkDate = objCur;
	}
}

void CDlgInfo::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI){
	if(::IsWindow(m_hWnd) && ::IsWindowVisible(m_hWnd)){
		//最大サイズ
//		lpMMI->ptMaxSize.x = m_objDefRect.Width();
		lpMMI->ptMaxSize.y = m_objDefRect.Height();

		//最小トラッキングサイズ
		lpMMI->ptMinTrackSize.y = m_objDefRect.Height();

		//最大トラッキングサイズ
		lpMMI->ptMaxTrackSize.y = m_objDefRect.Height();
	}

	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CDlgInfo::OnSize(UINT nType, int cx, int cy){
	CDialog::OnSize(nType, cx, cy);
	if(::IsWindow(m_hWnd)){
		SetCtrl();
		CreateBackBuff();
	}
}

void CDlgInfo::SetCtrl(){
	if(::IsWindow(m_objTime.m_hWnd) && ::IsWindowVisible(m_objTime.m_hWnd)){
		CRect rect;
		m_objTime.GetClientRect(rect);

		CRect clRect;
		GetClientRect(clRect);

		CRect tmRect(clRect.left - rect.Width(), clRect.top,
					 clRect.right,               clRect.bottom);
		m_objTime.SetWindowPos(&wndTop, 
							   tmRect.left,    tmRect.top, 
							   tmRect.Width(), tmRect.Height(), 
							   SWP_SHOWWINDOW);
	}
}

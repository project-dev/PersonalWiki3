// FindWnd.cpp: CFindWnd クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PersonalWiki.h"
#include "FindWnd.h"
#include "LogFile.h"
#include "PWikiDoc.h"
#include "MainFrm.h"
#include "FindFile.h"
#include "EventDate.h"
#include "AnalisysWiki.h"
#include "LogFile.h"
#include "InfoTabView.h"
#include "devlib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString CFindWnd::m_strFindText = "";
HANDLE CFindWnd::m_hThreadEnd = NULL;
CStringArray CFindWnd::m_arrHitFileName;
CStringArray CFindWnd::m_arrHitString;

const static UINT WM_FINDUPDATE = ::RegisterWindowMessage("PWIKI_FIND_UPDATE_MESSAGE");
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CFindWnd, CWnd)
	//{{AFX_MSG_MAP(CFindWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(WM_FINDUPDATE, OnFindUpdate)
	ON_NOTIFY(LVN_COLUMNCLICK, IDS_FIND_LIST, OnColumnClick)
END_MESSAGE_MAP()

CFindWnd::CFindWnd(){
	m_hThread = NULL;
	m_pThread = NULL;
	m_hThreadEnd = ::CreateEvent(NULL, TRUE, FALSE, "PWIKI_FIND_THREAD_END_EVENT");
	::ResetEvent(m_hThreadEnd);
}

CFindWnd::~CFindWnd(){
	if(m_hThreadEnd){
		::SetEvent(m_hThreadEnd);
		while(::WaitForSingleObject(m_hThread, 0) == WAIT_OBJECT_0){
			//スレッド終了を待つ
		}
		::CloseHandle(m_hThreadEnd);
		m_hThread = NULL;
		m_pThread = NULL;
	}
}

BOOL CFindWnd::Create(DWORD dwStyle, const RECT &rect, CWnd *pParent, UINT uID){
	return CWnd::Create(NULL, NULL, dwStyle, rect, pParent, uID);
}

int CFindWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CLogFile::SaveAppLog("CFindWnd 生成");	
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

	CRect rect;
	GetClientRect(rect);
	m_objBtnFind.Create("検索", WS_CHILD | WS_VISIBLE, rect, this, IDS_BTN_FIND);
	m_objBtnFind.SetFont(&m_objFont);
	m_objCmbText.Create(WS_BORDER | WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, rect, this, IDS_CMB_FIND);
	m_objCmbText.SetFont(&m_objFont);
//	m_objCmbText.SetItemHeight(-1, 24);
	m_objList.Create(WS_BORDER | WS_CHILD | WS_VISIBLE | LVS_REPORT, rect, this, IDS_FIND_LIST);
	m_objList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_objList.InsertColumn(0, "ページ");
	m_objList.InsertColumn(1, "文字列");
	SetCtrlPos();
	SetColumnWidthLC(&m_objList);
	LoadFindText();
	return 0;
}

void CFindWnd::SetCtrlPos(){
	CRect rect;
	GetClientRect(rect);
	CRect edRect(0, 0, rect.Width() - 32, 16);
	CRect btnRect(rect.Width() - 32, 0, rect.right, 16);
	CRect lsRect(0, 16, rect.right, rect.bottom);
	m_objCmbText.SetWindowPos(&wndTop, edRect.left, edRect.top, edRect.Width(), edRect.Height(), SWP_SHOWWINDOW);
	m_objBtnFind.SetWindowPos(&wndTop, btnRect.left, btnRect.top, btnRect.Width(), btnRect.Height(), SWP_SHOWWINDOW);
	m_objList.SetWindowPos(&wndTop, lsRect.left, lsRect.top, lsRect.Width(), lsRect.Height(), SWP_SHOWWINDOW);
}

CPWikiDoc* CFindWnd::GetDocument(){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CFindWnd::GetDocument : pFrm is null");
	}
	if(!pFrm){
		return NULL;
	}
	CPWikiDoc *pDoc = NULL;
	pDoc = (CPWikiDoc*)GetDoc();
	return pDoc;
}

void CFindWnd::OnPaint(){
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
}

void CFindWnd::OnSize(UINT nType, int cx, int cy){
	CWnd::OnSize(nType, cx, cy);
	SetCtrlPos();
}

BOOL CFindWnd::OnEraseBkgnd(CDC* pDC){
	return CWnd::OnEraseBkgnd(pDC);
}

void CFindWnd::OnDestroy(){
	::SetEvent(m_hThreadEnd);
	if(m_hThread != NULL){
		while(::WaitForSingleObject(m_hThread, 0) == WAIT_OBJECT_0){
			//スレッド終了を待つ
		}
		::CloseHandle(m_hThreadEnd);
	}
	m_hThreadEnd = NULL;
	m_hThread = NULL;
	m_pThread = NULL;
	CWnd::OnDestroy();
}

void CFindWnd::OnShowWindow(BOOL bShow, UINT nStatus){
	CWnd::OnShowWindow(bShow, nStatus);
}

BOOL CFindWnd::PreTranslateMessage(MSG* pMsg) {
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CFindWnd::PreTranslateMessage : pFrm is null");
	}
	CInfoTabView *pInfoView = pFrm->GetInfoTabView();
	if(pMsg->hwnd == m_objBtnFind.m_hWnd){
		CString strFindText;
		switch(pMsg->message){
//		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
			//検索開始
			if(m_objBtnFind.IsWindowEnabled()){

				m_objCmbText.GetWindowText(m_strFindText);
				if(m_objCmbText.FindStringExact(-1, m_strFindText) == CB_ERR){
					//検索文字列を保存する
					m_objCmbText.InsertString(0, m_strFindText);
					SaveFindText();
				}

				m_objBtnFind.EnableWindow(FALSE);
				m_objList.DeleteAllItems();
				m_arrHitFileName.RemoveAll();
				m_arrHitString.RemoveAll();
				m_pThread = AfxBeginThread(FindThread, this);
				m_hThread = m_pThread->m_hThread;
			}
//			return TRUE;
		}
	}else if(pMsg->hwnd == m_objList.m_hWnd){
		switch(pMsg->message){
		case WM_LBUTTONDBLCLK:
			int nIndex = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
			if(nIndex != -1){
				CString strPath = m_objList.GetItemText(nIndex, 0);
				CString strDtTest;
				strDtTest.Format("%s 00:00:00", strPath);
				COleDateTime objDate;
				if(objDate.ParseDateTime(strDtTest, VAR_DATEVALUEONLY)){
//					if(objDate.GetStatus() != COleDateTime::valid){
						pInfoView->UpdateInfo(&objDate);
//					}else{
//						pInfoView->UpdateInfo(strPath);
//					}
				}else{
					pInfoView->UpdateInfo(strPath);
				}
			}
			return TRUE;
		}
		
	}

	return CWnd::PreTranslateMessage(pMsg);
}
UINT CFindWnd::FindThread( LPVOID pParam ){
	CFindWnd *pWnd = (CFindWnd*)pParam;
	CString strBasePath = GetBasePath();
	CString strWikiPath = strBasePath + "Wiki";
	CString strScPath = strBasePath + "Date";
//	CString strToDoPath = strBasePath + "ToDo";
	CString strFindFile;

	CString strLog;

	int nFindStep = 0;
	int nCnt;

	CFindFile objFile;
	objFile.SetCallBack(FindProc, PreFindNextProc);
	
	if(::WaitForSingleObject(m_hThreadEnd, 0) == WAIT_OBJECT_0){
		return 0;
	}
	strLog.Format("%sを検索\n", strWikiPath);
	CLogFile::SaveAppLog(strLog);
	objFile.FindFile(strWikiPath, "*.pwd", TRUE, TRUE);
	nCnt = m_arrHitFileName.GetSize();
	pWnd->SendMessage(WM_FINDUPDATE, 0, nCnt);

	if(::WaitForSingleObject(m_hThreadEnd, 0) == WAIT_OBJECT_0){
		return 0;
	}
	strLog.Format("%sを検索\n", strScPath);
	CLogFile::SaveAppLog(strLog);
	objFile.FindFile(strScPath,   "*.dat", TRUE, TRUE);
	pWnd->SendMessage(WM_FINDUPDATE, nCnt, m_arrHitFileName.GetSize());
	nCnt = m_arrHitFileName.GetSize();
/*
	if(::WaitForSingleObject(m_hThreadEnd, 0) == WAIT_OBJECT_0){
		return 0;
	}
	strLog.Format("%sを検索\n", strToDoPath);
	CLogFile::SaveAppLog(strLog);
	objFile.FindFile(strToDoPath, "*.todo", TRUE, TRUE);
	pWnd->SendMessage(WM_FINDUPDATE, nCnt, m_arrHitFileName.GetSize());
	nCnt = m_arrHitFileName.GetSize();
*/
	pWnd->SendMessage(WM_FINDUPDATE, -1, -1);
	return 0;
}
BOOL CFindWnd::PreFindNextProc(){
	if(::WaitForSingleObject(m_hThreadEnd, 0) == WAIT_OBJECT_0){
		return FALSE;
	}
	return TRUE;
}
BOOL CFindWnd::FindProc(LPCTSTR pszDir, WIN32_FIND_DATA &wfd){
	CString strBasePath = GetBasePath();
	CString strWikiPath = strBasePath + "Wiki";
	CString strScPath = strBasePath + "Date";
	CString strToDoPath = strBasePath + "ToDo";
	CString strFile;
	strFile.Format("%s\\%s", pszDir, wfd.cFileName);
	strFile.Replace("\\\\", "\\");

	CFile file;
	CFileStatus status;
	CEventDate objDate;
	CString strData;
	CAnalisysWiki objAna;
//	CLogFile::SaveAppLog(strFile);
	try{
		strData = "";
		if(strFile.Find(strWikiPath) != -1){
			//Wiki
			if(file.Open(strFile, CFile::modeRead)){
				file.GetStatus(status);
				if(status.m_size){
					char *pszBuff = new char[status.m_size + 1];
					memset(pszBuff, 0, status.m_size + 1);
					file.Read(pszBuff, status.m_size);
					objAna.Analisys(pszBuff, strData, NULL , TRUE);
					strData = pszBuff;
					delete pszBuff;
					strFile.Replace(strWikiPath, "");
					strFile.Replace(".pwd", "");
					strFile.Replace("\\", "/");
				}
				file.Close();
			}
		}else if(strFile.Find(strScPath) != -1){
			//スケジュール
			CLogFile::SaveAppLog(strFile);
			objDate.LoadEvent(strFile, FALSE);
			objAna.Analisys(objDate.GetDetail(), strData, NULL , TRUE);
			strFile.Replace(strScPath, "");
			strFile.Replace(".dat", "");
			if(!strFile.Left(1).Compare("\\")){
				strFile = strFile.Right(strFile.GetLength() - 1);
			}
			CString strYear = strFile.Left(4);
			CString strMonth = strFile.Mid(4, 2);
			CString strDay = strFile.Right(2);
			strFile.Format("%s/%s/%s", strYear, strMonth, strDay);
/*
		}else if(strFile.Find(strToDoPath) != -1){
			//ToDo
			objDate.LoadEvent(strFile, TRUE);
			strData = objDate.GetName();
			CString strToDo = objDate.GetDetail();
			objAna.Analisys(objDate.GetDetail(), strToDo, NULL , TRUE);
			strData += strToDo;
			strFile.Replace(strToDoPath, "");
			strFile.Replace(".todo", "");
*/
		}
		int nPos = 0;
		while(TRUE){
			nPos = strData.Find(m_strFindText, nPos);
			if(nPos == -1){
				break;
			}else{
				int nEnd = strData.Find("\n", nPos);
				CString strString;
				if(nEnd == -1){
					strString = strData.Right(strData.GetLength() - nPos);
				}else{
					strString = strData.Mid(nPos, nEnd - nPos);
				}
				m_arrHitFileName.Add(strFile);
				m_arrHitString.Add(strString);
				nPos++;
			}
		}
	}catch(CFileException &fe){
		CString strLog;
		char szErr[1025];
		memset(szErr, 0, 1025);
		fe.GetErrorMessage(szErr, 1024);
		strLog.Format("検索エラー:%s (%s)", strFile, szErr);
		CLogFile::SaveAppLog(strLog);
	}catch(CMemoryException &me){
		CString strLog;
		char szErr[1025];
		memset(szErr, 0, 1025);
		me.GetErrorMessage(szErr, 1024);
		strLog.Format("検索エラー:%s (%s)", strFile, szErr);
		CLogFile::SaveAppLog(strLog);
	}
	return TRUE;
}
LRESULT CFindWnd::OnFindUpdate(WPARAM wParam, LPARAM lParam){
	if((wParam == -1) && (lParam)){
		m_objBtnFind.EnableWindow(TRUE);
		m_pThread = NULL;
		m_hThread = NULL;
	}else{
		for(int i = wParam; i < lParam; i++){
			CString strLine = m_arrHitFileName.GetAt(i);
			m_objList.InsertItem(i, strLine);
			strLine = m_arrHitString.GetAt(i);
			m_objList.SetItemText(i, 1, strLine);
		}
	}
	return 0;
}

BOOL CFindWnd::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo){
	if(nID == IDS_CMB_FIND){
		switch(nCode){
		case CBN_EDITUPDATE:
		case CBN_EDITCHANGE:
			break;
		}
	}
	return CWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CFindWnd::SaveFindText(){
	int nCnt = m_objCmbText.GetCount();
	CString strItem;
	CStdioFile objFile;
	CString strBasePath;
	CString strPath;
	try{
		strBasePath = GetBasePath();
		strPath.Format("%sFindText.dat", strBasePath);
		if(!objFile.Open(strPath, CFile::modeCreate | CFile::modeWrite)){
			throw(0);
		}
		for(int i = 0; i < nCnt; i++){
			m_objCmbText.GetLBText(i, strItem);
			strItem += "\n";
			objFile.WriteString(strItem);
		}
		objFile.Flush();
		objFile.Close();

	}catch(CFileException &fe){
		CLogFile::SaveExceptionLog(&fe, "検索文字列保存中にエラー発生");
	}catch(int nErr){
		if(nErr){
			CLogFile::SaveAppLog("検索文字列保存中にエラー発生");
		}else{
			CLogFile::SaveAppLog("検索文字列保存中にエラー発生");
		}
	}
}

void CFindWnd::LoadFindText(){
	int nCnt = m_objCmbText.GetCount();
	CString strItem;
	CStdioFile objFile;
	CString strBasePath;
	CString strPath;
	try{
		strBasePath = GetBasePath();
		strPath.Format("%sFindText.dat", strBasePath);
		if(::IsFileExsist(strPath)){
			if(!objFile.Open(strPath, CFile::modeRead)){
				throw(0);
			}
			while(objFile.ReadString(strItem)){
				m_objCmbText.AddString(strItem);
			}
			objFile.Close();
		}
	}catch(CFileException &fe){
		CLogFile::SaveExceptionLog(&fe, "検索文字列読み込み中にエラー発生");
	}catch(int nErr){
		if(nErr){
			CLogFile::SaveAppLog("検索文字列読み込み中にエラー発生");
		}else{
			CLogFile::SaveAppLog("検索文字列読み込み中にエラー発生");
		}
	}

}

void CFindWnd::OnColumnClick(LPNMHDR pNmhdr, LRESULT *pResult){
	
//	m_objList.SortItems();
}

// AppSetPage9.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "personalwiki.h"
#include "AppSetPage9.h"
#include "MainFrm.h"
#include "IniFile.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage9 ダイアログ


CAppSetPage9::CAppSetPage9(CWnd* pParent /*=NULL*/)
	: CDialog(CAppSetPage9::IDD, pParent)
{
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage9::CAppSetPage9 : pFrm is null");
	}
	DLGINFO objDlgIni;
	pFrm->m_objIniFile.GetDlgInfoIniData(objDlgIni);

	//{{AFX_DATA_INIT(CAppSetPage9)
	m_bShowSec = objDlgIni.bIsShowSec;
	m_bShowSc = objDlgIni.bShowSc;
	m_bShowTodo = objDlgIni.bShowToDo;
	m_bShowTime = objDlgIni.bShowTime;
	m_bShowFix = objDlgIni.bShowFix;
	//}}AFX_DATA_INIT
}


void CAppSetPage9::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CAppSetPage9)
	DDX_Check(pDX, IDC_CHK_VIEW_SEC, m_bShowSec);
	DDX_Check(pDX, IDC_CHK_SC, m_bShowSc);
	DDX_Check(pDX, IDC_CHK_TODO, m_bShowTodo);
	DDX_Check(pDX, IDC_SHOWTIME, m_bShowTime);
	DDX_Check(pDX, IDC_CHK_FIX, m_bShowFix);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppSetPage9, CDialog)
	//{{AFX_MSG_MAP(CAppSetPage9)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage9 メッセージ ハンドラ

void CAppSetPage9::UpdateInfo(){
	UpdateData(TRUE);
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage9::UpdateInfo : pFrm is null");
	}
	DLGINFO objDlgIni;
	pFrm->m_objIniFile.GetDlgInfoIniData(objDlgIni);
	objDlgIni.bShowSc = m_bShowSc;
	objDlgIni.bShowFix = m_bShowFix;
	objDlgIni.bShowToDo = m_bShowTodo;
	objDlgIni.bIsShowSec = m_bShowSec;
	objDlgIni.bShowTime = m_bShowTime;
	pFrm->m_objIniFile.SetDlgInfoIniData(&objDlgIni);
}

BOOL CAppSetPage9::PreTranslateMessage(MSG* pMsg) {
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

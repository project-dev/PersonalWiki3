// AppSetPage6.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "AppSetPage6.h"
#include "MainFrm.h"
#include "IniFile.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage6 ダイアログ


CAppSetPage6::CAppSetPage6(CWnd* pParent /*=NULL*/)
	: CDialog(CAppSetPage6::IDD, pParent){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage6::CAppSetPage6 : pFrm is null");
	}
	DEBUGINFO objIni;
	pFrm->m_objIniFile.GetDebugInfoIniData(objIni);
	//{{AFX_DATA_INIT(CAppSetPage6)
	m_bUseFatalLog = objIni.bFatalLogOut;
	m_bUseStateLog = objIni.bAppLogOut;
	m_bUseLog = objIni.bLogOut;
	m_bUseExceptLog = objIni.bExceptLogOut;
	//}}AFX_DATA_INIT
}


void CAppSetPage6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppSetPage6)
	DDX_Check(pDX, IDC_CHK_USE_FATAL_LOG, m_bUseFatalLog);
	DDX_Check(pDX, IDC_CHK_USE_STATE_LOG, m_bUseStateLog);
	DDX_Check(pDX, IDC_CHK_USELOG, m_bUseLog);
	DDX_Check(pDX, IDC_CHK_USE_EXCEPT_LOG, m_bUseExceptLog);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppSetPage6, CDialog)
	//{{AFX_MSG_MAP(CAppSetPage6)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage6 メッセージ ハンドラ

BOOL CAppSetPage6::UpdateInfo(){
	UpdateData(TRUE);
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage6::UpdateInfo : pFrm is null");
	}
	DEBUGINFO objIni;
	objIni.bLogOut = m_bUseLog;
	objIni.bFatalLogOut = m_bUseFatalLog;
	objIni.bAppLogOut = m_bUseStateLog;
	objIni.bExceptLogOut = m_bUseExceptLog;
	pFrm->m_objIniFile.SetDebugInfoIniData(&objIni);
	return TRUE;
}

BOOL CAppSetPage6::PreTranslateMessage(MSG* pMsg) {
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

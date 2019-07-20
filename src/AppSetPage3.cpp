// AppSetPage3.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "AppSetPage3.h"
#include "IniFile.h"
#include "MainFrm.h"
#include "FindFile.h"
#include "LogFile.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage3 ダイアログ


CAppSetPage3::CAppSetPage3(CWnd* pParent /*=NULL*/)
	: CDialog(CAppSetPage3::IDD, pParent){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage3::CAppSetPage3 : pFrm is null");
	}
	WIKIINFO objIni;
	pFrm->m_objIniFile.GetWikiInfoIniData(objIni);
	//{{AFX_DATA_INIT(CAppSetPage3)
	m_bUseRet = objIni.bUseRet;;
	m_bUseTBLink = objIni.bUseTopBtmLnk;
	m_bShowAttach = objIni.bUseShowAttach;
	m_bUseConvTime = objIni.bUseShowConvTime;
	//}}AFX_DATA_INIT
}


void CAppSetPage3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppSetPage3)
	DDX_Control(pDX, IDC_COMB_CSS, m_objCmbCss);
	DDX_Check(pDX, IDC_CHK_USE_RET, m_bUseRet);
	DDX_Check(pDX, IDC_CHK_TBLINK, m_bUseTBLink);
	DDX_Check(pDX, IDC_CHK_SHOWATTACH, m_bShowAttach);
	DDX_Check(pDX, IDC_CHK_CONV_TIME, m_bUseConvTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppSetPage3, CDialog)
	//{{AFX_MSG_MAP(CAppSetPage3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage3 メッセージ ハンドラ

BOOL CAppSetPage3::UpdateInfo(){
	UpdateData(TRUE);
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage3::UpdateInfo : pFrm is null");
	}
	WIKIINFO objIni;
	objIni.bUseRet = m_bUseRet;
	objIni.bUseShowAttach = m_bShowAttach;
	objIni.bUseTopBtmLnk = m_bUseTBLink;
	objIni.bUseShowConvTime = m_bUseConvTime;
	m_objCmbCss.GetWindowText(objIni.szCss, MAX_PATH);
	pFrm->m_objIniFile.SetWikiInfoIniData(&objIni);
	return TRUE;
}

BOOL CAppSetPage3::OnInitDialog() {
	CDialog::OnInitDialog();
	
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage3::OnInitDialog : pFrm is null");
	}
	WIKIINFO objIni;
	pFrm->m_objIniFile.GetWikiInfoIniData(objIni);
	FindCSS();
	int nIndex = m_objCmbCss.FindStringExact(0, objIni.szCss);
	if(nIndex == CB_ERR){
		nIndex = 0;
	}
	m_objCmbCss.SetCurSel(nIndex);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CAppSetPage3::FindCSS(){
	CString strDir = GetBasePath();
	strDir += "CSS";
	CFindFile objFind;
	objFind.FindFile(strDir, "*.css", TRUE, FALSE);
	int nSize = objFind.GetCount();
	CString strFile;
	m_objCmbCss.ResetContent();
	for(int i = 0; i < nSize; i++){
		objFind.GetFileName(i, strFile);
		m_objCmbCss.AddString(strFile);
	}
}

BOOL CAppSetPage3::PreTranslateMessage(MSG* pMsg){
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

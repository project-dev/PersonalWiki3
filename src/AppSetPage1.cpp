// AppSetPage1.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "AppSetPage1.h"
#include "MainFrm.h"
#include "PWikiDoc.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage1 ダイアログ


CAppSetPage1::CAppSetPage1(CWnd* pParent /*=NULL*/)
	: CDialog(CAppSetPage1::IDD, pParent){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage1 constractor : pFrm is null");
	}
	APPINFO objIni;
//	DLGINFO objDlgIni;
	memset(&objIni, 0, sizeof(APPINFO));
//	memset(&objDlgIni, 0, sizeof(DLGINFO));
	pFrm->m_objIniFile.GetAppInfoIniData(objIni);
//	pFrm->m_objIniFile.GetDlgInfoIniData(objDlgIni);
	//{{AFX_DATA_INIT(CAppSetPage1)
	m_bEndToDoDel = objIni.bEndToDoDel;
	m_nEndToDoDelSpan = objIni.nEndToDoDelSpan;
	m_bUsePassWord = objIni.bUsePassWord;
	m_strPassWord = objIni.szPassWord;
	m_strCategory = _T("");
	m_bUseToDay = objIni.bUseToDay;
	m_bRunMainWndShow = objIni.bRunMainWndShow;
	//}}AFX_DATA_INIT

}


void CAppSetPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppSetPage1)
	DDX_Control(pDX, IDC_CATEGORYLIST, m_objCtgList);
	DDX_Check(pDX, IDC_CHK_END_TODO_DEL, m_bEndToDoDel);
	DDX_Text(pDX, IDC_ED_END_TODO_DEL_SPAN, m_nEndToDoDelSpan);
	DDV_MinMaxInt(pDX, m_nEndToDoDelSpan, 0, 365);
	DDX_Check(pDX, IDC_CHK_PASSWORD, m_bUsePassWord);
	DDX_Text(pDX, IDC_ED_PASSWORD, m_strPassWord);
	DDV_MaxChars(pDX, m_strPassWord, 32);
	DDX_Text(pDX, IDC_ED_CATEGORY, m_strCategory);
	DDX_Check(pDX, IDC_CHK_USE_TODAY, m_bUseToDay);
	DDX_Check(pDX, IDC_CHK_RUN_MAINWND_SHOW, m_bRunMainWndShow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppSetPage1, CDialog)
	//{{AFX_MSG_MAP(CAppSetPage1)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_MOD, OnBtnMod)
	ON_LBN_SELCHANGE(IDC_CATEGORYLIST, OnSelchangeCategorylist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage1 メッセージ ハンドラ

BOOL CAppSetPage1::UpdateInfo(){
	UpdateData(TRUE);
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage1::UpdateInfo : pFrm is null");
	}
	UINT uID = GetCheckedRadioButton(IDC_RAD_SC, IDC_RAD_MEMO);
	
	APPINFO objIni;
//	DLGINFO objDlgIni;
//	pFrm->m_objIniFile.GetDlgInfoIniData(objDlgIni);

	objIni.bEndToDoDel		= m_bEndToDoDel;
	objIni.nEndToDoDelSpan	= m_nEndToDoDelSpan;
	objIni.bUsePassWord		= m_bUsePassWord;
	objIni.bUseToDay		= m_bUseToDay;
	objIni.bRunMainWndShow	= m_bRunMainWndShow;
	switch(uID){
	case IDC_RAD_MEMO:
		objIni.nStartActTab	= 1;
		break;
	case IDC_RAD_SC:
	default:
		objIni.nStartActTab	= 0;
		break;
	}
	strcpy(objIni.szPassWord, (LPCTSTR)m_strPassWord);
	pFrm->m_objIniFile.SetAppInfoIniData(&objIni);
/*
	objDlgIni.bShowSc = m_bShowSc;
	objDlgIni.bShowFix = m_bShowFix;
	objDlgIni.bShowToDo = m_bShowToDo;
	pFrm->m_objIniFile.SetDlgInfoIniData(&objDlgIni);
*/

	CPWikiDoc *pDoc = (CPWikiDoc*)GetDoc();
	int nSize = m_objCtgList.GetCount();
	CString strItem;
	pDoc->m_arrCategory.RemoveAll();
	for(int i = 0; i < nSize; i++){
		m_objCtgList.GetText(i, strItem);
		pDoc->m_arrCategory.Add(strItem);
	}

	return TRUE;
}

void CAppSetPage1::OnBtnAdd(){
	UpdateData(TRUE);
	m_objCtgList.AddString(m_strCategory);
}

void CAppSetPage1::OnBtnDel(){
	UpdateData(TRUE);
	int nSel = m_objCtgList.GetCurSel();
	m_objCtgList.DeleteString(nSel);
}

void CAppSetPage1::OnBtnMod(){
	UpdateData(TRUE);
	int nSel = m_objCtgList.GetCurSel();
	m_objCtgList.DeleteString(nSel);
	m_objCtgList.InsertString(nSel, m_strCategory);
}

void CAppSetPage1::OnSelchangeCategorylist() {
	UpdateData(TRUE);
	int nSel = m_objCtgList.GetCurSel();
	if(nSel == LB_ERR){
		return;
	}

	m_objCtgList.GetText(nSel, m_strCategory);
	UpdateData(FALSE);
}

BOOL CAppSetPage1::OnInitDialog() {
	CDialog::OnInitDialog();
	
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage1::OnInitDialog : pFrm is null");
	}

	CPWikiDoc *pDoc = (CPWikiDoc*)GetDoc();
	if(!pDoc){
		return FALSE;
	}
	int nSize = pDoc->m_arrCategory.GetSize();
	for(int i = 0; i < nSize; i++){
		m_objCtgList.AddString(pDoc->m_arrCategory.GetAt(i));
	}

	APPINFO objIni;
	pFrm->m_objIniFile.GetAppInfoIniData(objIni);
	UINT uID;
	switch(objIni.nStartActTab){
	case 1:
		uID = IDC_RAD_MEMO;
		break;
	case 0:
	default:
		uID = IDC_RAD_SC;
		break;
	}
	CheckRadioButton(IDC_RAD_SC, IDC_RAD_MEMO, uID);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

BOOL CAppSetPage1::PreTranslateMessage(MSG* pMsg) {
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

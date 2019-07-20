// DlgToDoInp.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "DlgToDoInp.h"
#include "MainFrm.h"
#include "PWikiDoc.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgToDoInp ダイアログ


CDlgToDoInp::CDlgToDoInp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgToDoInp::IDD, pParent){
	//{{AFX_DATA_INIT(CDlgToDoInp)
	m_objPlanEnd = COleDateTime::GetCurrentTime();
	m_objPlanStart = COleDateTime::GetCurrentTime();
	m_objProgressEnd = COleDateTime::GetCurrentTime();
	m_objProgressStart = COleDateTime::GetCurrentTime();
	m_strDetail = _T("");
	m_strName = _T("");
	m_dProcessPar = 0.0;
	m_nState = 0;
	//}}AFX_DATA_INIT
	m_strCategory = "";
}


void CDlgToDoInp::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgToDoInp)
	DDX_Control(pDX, IDC_CMB_STATE, m_objCmbState);
	DDX_Control(pDX, IDC_CMB_CATEGORY, m_objCmbCategory);
	DDX_Text(pDX, IDC_ED_DETAIL, m_strDetail);
	DDX_Text(pDX, IDC_ED_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 64);
	DDX_Text(pDX, IDC_ED_PROCESS, m_dProcessPar);
	DDV_MinMaxDouble(pDX, m_dProcessPar, 0., 100.);
	DDX_DateTimeCtrl(pDX, IDC_DT_PLAN_END, m_objPlanEnd);
	DDX_DateTimeCtrl(pDX, IDC_DT_PLAN_START, m_objPlanStart);
	DDX_DateTimeCtrl(pDX, IDC_DT_PROGRES_END, m_objProgressEnd);
	DDX_DateTimeCtrl(pDX, IDC_DT_PROGRES_START, m_objProgressStart);
	DDX_CBIndex(pDX, IDC_CMB_STATE, m_nState);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgToDoInp, CDialog)
	//{{AFX_MSG_MAP(CDlgToDoInp)
	ON_CBN_SELENDOK(IDC_CMB_STATE, OnSelendokCmbState)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgToDoInp メッセージ ハンドラ

BOOL CDlgToDoInp::OnInitDialog() {
	CDialog::OnInitDialog();
	UpdateData(FALSE);
	
	// TODO: この位置に初期化の補足処理を追加してください
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgToDoInp::OnInitDialog : pFrm is null");
	}
	CPWikiDoc *pDoc = (CPWikiDoc*)GetDoc();
	int nSize = pDoc->m_arrCategory.GetSize();
	for(int i = 0; i < nSize; i++){
		CString strCategory = pDoc->m_arrCategory.GetAt(i);
		m_objCmbCategory.AddString(strCategory);
	}
	int nIndex = m_objCmbCategory.FindStringExact(-1, m_strCategory);
	if(nIndex != -1){
		m_objCmbCategory.SetCurSel(nIndex);
	}else{
		m_objCmbCategory.SetWindowText(m_strCategory);
	}
//	m_objCmbState.SetCurSel(0);
	OnSelendokCmbState();

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDlgToDoInp::OnOK(){

	UpdateData(TRUE);

	m_objCmbCategory.GetWindowText(m_strCategory);
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgToDoInp::OnOK : pFrm is null");
	}
	CPWikiDoc *pDoc = (CPWikiDoc*)GetDoc();
	int nSize = pDoc->m_arrCategory.GetSize();
	BOOL bMatch = FALSE;
	for(int i = 0; i < nSize; i++){
		CString strText = pDoc->m_arrCategory.GetAt(i);
		if(!m_strCategory.CompareNoCase(strText)){
			bMatch = TRUE;
			break;
		}
	}
	if(!bMatch){
		pDoc->m_arrCategory.Add(m_strCategory);
	}

	CDialog::OnOK();
}

void CDlgToDoInp::OnSelendokCmbState() {
	int nSel = m_objCmbState.GetCurSel();
	BOOL bState = FALSE;
	CWnd *pStartWnd = GetDlgItem(IDC_DT_PROGRES_START);
	CWnd *pEndWnd = GetDlgItem(IDC_DT_PROGRES_END);
	if(!IsWindowSafe(pStartWnd) || !IsWindowSafe(pEndWnd)){
		return;
	}

	switch(nSel){
	case 4:	//完了
		pStartWnd->EnableWindow(TRUE);
		pEndWnd->EnableWindow(TRUE);
		break;
	case 1:	//対応中
	case 2:	//確認完
	case 3:	//待ち
	case 5:	//保留
		pStartWnd->EnableWindow(TRUE);
		pEndWnd->EnableWindow(FALSE);
		break;
	case 0:	//未着手
	default:
		pStartWnd->EnableWindow(FALSE);
		pEndWnd->EnableWindow(FALSE);
		break;
	}
}

BOOL CDlgToDoInp::PreTranslateMessage(MSG* pMsg){
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

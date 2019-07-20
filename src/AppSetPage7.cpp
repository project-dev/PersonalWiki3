// AppSetPage7.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "personalwiki.h"
#include "AppSetPage7.h"
#include "MimeType.h"
#include "MainFrm.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage7 ダイアログ


CAppSetPage7::CAppSetPage7(CWnd* pParent /*=NULL*/)
	: CDialog(CAppSetPage7::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAppSetPage7)
	m_strExt = _T("");
	m_strMIME = _T("");
	m_bUse = FALSE;
	//}}AFX_DATA_INIT
}


void CAppSetPage7::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppSetPage7)
	DDX_Control(pDX, IDC_LIST, m_objList);
	DDX_Text(pDX, IDC_ED_EXT, m_strExt);
	DDX_Text(pDX, IDC_ED_MIME, m_strMIME);
	DDX_Check(pDX, IDC_CHK_USE, m_bUse);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppSetPage7, CDialog)
	//{{AFX_MSG_MAP(CAppSetPage7)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_MOD, OnBtnMod)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage7 メッセージ ハンドラ

void CAppSetPage7::UpdateInfo(){


}

BOOL CAppSetPage7::OnInitDialog(){
	CDialog::OnInitDialog();
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage7::OnInitDialog : pFrm is null");
	}
	m_objList.InsertColumn(0, "拡張子");
	m_objList.InsertColumn(1, "MIME");
	m_objList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);

	int nSize = pFrm->m_objMimeTypes.GetDataSize();
	for(int nIndex = 0; nIndex < nSize; nIndex++){
		CString strExt = pFrm->m_objMimeTypes.GetExt(nIndex);
		CString strMime = pFrm->m_objMimeTypes.GetMimeType(nIndex);
		BOOL bUse = pFrm->m_objMimeTypes.GetUse(nIndex);
		int nType = pFrm->m_objMimeTypes.GetType(nIndex);
		m_objList.InsertItem(nIndex, strExt, 0);
		m_objList.SetItemText(nIndex, 1, strMime);
		m_objList.SetCheck(nIndex, bUse);
	}
	
	
	SetColumnWidthLC(&m_objList);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CAppSetPage7::OnBtnAdd(){
	UpdateData();
	int nCnt = m_objList.GetItemCount();
	m_objList.InsertItem(nCnt, m_strExt, 0);
	m_objList.SetItemText(nCnt, 1, m_strMIME);
	m_objList.SetCheck(nCnt, m_bUse);
}

void CAppSetPage7::OnBtnDel(){
	int nIndex = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED | LVNI_SELECTED);
	m_objList.DeleteItem(nIndex);
}

void CAppSetPage7::OnBtnMod(){
	UpdateData();
	int nIndex = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED | LVNI_SELECTED);
	if(nIndex == -1){
		return;
	}
	m_objList.SetItemText(nIndex, 0, m_strExt);
	m_objList.SetItemText(nIndex, 1, m_strMIME);
	m_objList.SetCheck(nIndex, m_bUse);
}

void CAppSetPage7::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult){
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
	int nIndex = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED | LVNI_SELECTED);
	if(nIndex == -1){
		m_bUse = FALSE;
		m_strExt = "";
		m_strMIME = "";
		UpdateData(FALSE);

	}else if(pNMListView->uOldState != pNMListView->uNewState){
		m_strExt = m_objList.GetItemText(nIndex, 0);
		m_strMIME = m_objList.GetItemText(nIndex, 1);
		m_bUse = m_objList.GetCheck(nIndex);
		UpdateData(FALSE);

	}
	UpdateData(FALSE);
}

BOOL CAppSetPage7::PreTranslateMessage(MSG* pMsg){
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

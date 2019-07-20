// SetDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "rssplugin.h"
#include "SetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetDlg ダイアログ


CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetDlg)
	m_strName = _T("");
	m_strURL = _T("");
	m_strID = _T("");
	m_strPass = _T("");
	m_bUseCheck = FALSE;
	m_nChkSpan = 60;
	//}}AFX_DATA_INIT
}


void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetDlg)
	DDX_Control(pDX, IDC_RSSLIST, m_objList);
	DDX_Text(pDX, IDC_ED_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 1024);
	DDX_Text(pDX, IDC_ED_URL, m_strURL);
	DDV_MaxChars(pDX, m_strURL, 1024);
	DDX_Text(pDX, IDC_ED_ID, m_strID);
	DDX_Text(pDX, IDC_ED_PASS, m_strPass);
	DDX_Check(pDX, IDC_CHK_CHECK, m_bUseCheck);
	DDX_Text(pDX, IDC_ED_SPAN, m_nChkSpan);
	DDV_MinMaxInt(pDX, m_nChkSpan, 1, 360);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
	//{{AFX_MSG_MAP(CSetDlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_RSSLIST, OnItemchangedRsslist)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_APPLY, OnBtnApply)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetDlg メッセージ ハンドラ
BOOL CSetDlg::OnLoadOneData(const PRSSINFO pInfo){
	PRSSINFO pRss = new RSSINFO;
	memset(pRss, 0, sizeof(RSSINFO));
	memcpy(pRss, pInfo, sizeof(RSSINFO));
	int nCnt = m_objList.GetItemCount();
	int nIndex = m_objList.InsertItem(nCnt, "", 0);
	m_objList.SetItemText(nIndex, 1, pRss->szName);
	m_objList.SetItemText(nIndex, 2, pRss->szURL);
	m_objList.SetCheck(nIndex, pRss->bUse);
	m_objList.SetItemData(nIndex, (LPARAM)pRss);
	return TRUE;
}
BOOL CSetDlg::OnSaveOneData(int nCnt, RSSINFO &objInfo){
	PRSSINFO pInfo = (PRSSINFO)m_objList.GetItemData(nCnt);
	pInfo->bUse = m_objList.GetCheck(nCnt);
	memcpy(&objInfo, pInfo, sizeof(RSSINFO));
	return TRUE;
}

BOOL CSetDlg::OnInitDialog(){
	CDialog::OnInitDialog();

	char szPath[MAX_PATH + 1];
	char szDrv[MAX_PATH];
	char szDir[MAX_PATH];
	memset(szPath, 0, MAX_PATH + 1);
	memset(szDrv, 0, MAX_PATH);
	memset(szDir, 0, MAX_PATH);
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	_splitpath(szPath, szDrv, szDir, NULL, NULL);
	m_strData.Format("%s%splugins\\RSSPlugin.ini", szDrv, szDir);

	m_objList.InsertColumn(0, "購読");
	m_objList.InsertColumn(1, "名前");
	m_objList.InsertColumn(2, "URL");
	m_objList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES);

	LoadRSSData();
	LoadIniData();

	m_bUseCheck = m_bUseCheckIni;
	m_nChkSpan  = m_nChkSpan;
	UpdateData(FALSE);
	SetColumnWidthLC(&m_objList);

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CSetDlg::OnItemchangedRsslist(NMHDR* pNMHDR, LRESULT* pResult){
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int iItem = pNMListView->iItem;
	if(iItem < 0){
		return;
	}
	if((pNMListView->uChanged & LVIF_STATE == 0) || (pNMListView->uNewState == pNMListView->uOldState)){
		return;
	}
	PRSSINFO pInfo = (PRSSINFO)m_objList.GetItemData(iItem);
	if(pInfo){
		m_strName = pInfo->szName;
		m_strURL = pInfo->szURL;
		m_strID = pInfo->szUserID;
		m_strPass = pInfo->szPassWord;
	}else{
		m_strName = "";
		m_strURL = "";
		m_strID = "";
		m_strPass = "";
	}
	UpdateData(FALSE);	
	*pResult = 0;
}

void CSetDlg::OnBtnAdd(){
	UpdateData();
	int nIndex = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if(nIndex == -1){
		nIndex = m_objList.GetItemCount();
	}
	PRSSINFO pInfo = new RSSINFO;
	memset(pInfo, 0, sizeof(RSSINFO));
	strncpy(pInfo->szURL, m_strURL, 1024);
	strncpy(pInfo->szName, m_strName, 1024);
	strncpy(pInfo->szUserID, m_strID, 64);
	strncpy(pInfo->szPassWord, m_strPass, 64);
	nIndex = m_objList.InsertItem(nIndex, "", 0);
	m_objList.SetItemText(nIndex, 1, m_strName);
	m_objList.SetItemText(nIndex, 2, m_strURL);
	m_objList.SetItemData(nIndex, (LPARAM)pInfo);
}

void CSetDlg::OnBtnApply(){
	UpdateData();
	int nIndex = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if(nIndex == -1){
		return;
	}
	PRSSINFO pInfo = (PRSSINFO)m_objList.GetItemData(nIndex);
	strncpy(pInfo->szURL, m_strURL, 1024);
	strncpy(pInfo->szName, m_strName, 1024);
	strncpy(pInfo->szUserID, m_strID, 64);
	strncpy(pInfo->szPassWord, m_strPass, 64);
	m_objList.SetItemText(nIndex, 1, m_strName);
	m_objList.SetItemText(nIndex, 2, m_strURL);
}

void CSetDlg::OnBtnDel(){
	int nIndex = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if(nIndex == -1){
		return;
	}
	PRSSINFO pInfo = (PRSSINFO)m_objList.GetItemData(nIndex);
	delete pInfo;
	m_objList.DeleteItem(nIndex);
}

void CSetDlg::OnOK(){
	UpdateData(TRUE);
	int nCnt = m_objList.GetItemCount();
	SaveRSSData(nCnt);

	m_bUseCheckIni = m_bUseCheck;
	m_nChkSpanIni = m_nChkSpan;
	SaveIniData();

	ReleaseData();
	CDialog::OnOK();
}

void CSetDlg::ReleaseData(){
	int nCnt = m_objList.GetItemCount();
	for(int i = 0; i < nCnt; i++){
		PRSSINFO pInfo = (PRSSINFO)m_objList.GetItemData(i);
		delete pInfo;
	}
	m_objList.DeleteAllItems();
}

void CSetDlg::OnCancel(){
	ReleaseData();
	CDialog::OnCancel();
}

void CSetDlg::SetColumnWidthLC(CListCtrl *pList){
	if(!pList || !::IsWindow(pList->m_hWnd)){
		return;
	}

	CHeaderCtrl *pHead = pList->GetHeaderCtrl();
	if(!pHead || !::IsWindow(pHead->m_hWnd)){
		return;
	}
	int nCnt = pHead->GetItemCount();
	for(int i = 0; i < nCnt; i++){
		if(!pList->SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER )){
			continue;
		}
		int nWidth = pList->GetColumnWidth(i);
		if(!pList->SetColumnWidth(i, LVSCW_AUTOSIZE )){
			continue;
		}
		if(nWidth > pList->GetColumnWidth(i)){
			pList->SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER );
		}
	}
}

BOOL CSetDlg::PreTranslateMessage(MSG* pMsg){
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

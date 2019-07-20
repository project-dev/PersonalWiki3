// DlgFixDataPage2.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "DlgFixDataPage2.h"
#include "PWikiDoc.h"
#include "MainFrm.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFixDataPage2 ダイアログ


CDlgFixDataPage2::CDlgFixDataPage2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFixDataPage2::IDD, pParent){
	//{{AFX_DATA_INIT(CDlgFixDataPage2)
	m_strData = _T("");
	//}}AFX_DATA_INIT
}


void CDlgFixDataPage2::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFixDataPage2)
	DDX_Control(pDX, IDC_LIST, m_objList);
	DDX_Text(pDX, IDC_ED_DATA, m_strData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFixDataPage2, CDialog)
	//{{AFX_MSG_MAP(CDlgFixDataPage2)
	ON_BN_CLICKED(IDC_BTN_MOD, OnBtnMod)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFixDataPage2 メッセージ ハンドラ

BOOL CDlgFixDataPage2::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	m_objList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_objList.InsertColumn(0, "日");
	m_objList.InsertColumn(1, "データ");
	CString strDate;
	for(int i = 0; i < 31; i++){
		strDate.Format("%d", i + 1);
		m_objList.InsertItem(i, strDate, 0);
		m_objList.SetItemData(1, 0);
	}
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgFixDataPage2::OnInitDialog : pFrm is null");
	}
	CPWikiDoc *pDoc = (CPWikiDoc*)GetDoc();
	int nSize = pDoc->m_objFixedData.GetSize();

	for(i = 0; i < nSize; i++){
		CEventDate *pData = pDoc->m_objFixedData.GetFixedData(i);
		if(pData->GetType() != SC_FIX_MONTH1){
			continue;
		}
		int nMonth;
		int nDay;
		pData->GetMonthDay(nMonth, nDay);
		int nCnt = m_objList.GetItemCount();
		CString strData;
		strData = pData->GetName();
		m_objList.SetItemText(nDay - 1, 1, strData);
		m_objList.SetItemData(nDay - 1, (LPARAM)pData);
	}
	SetColumnWidthLC(&m_objList);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDlgFixDataPage2::OnBtnMod(){
	UpdateData(TRUE);		
	int nSelItem = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if(nSelItem == -1){
		return;
	}
	m_objList.SetItemText(nSelItem, 1, m_strData);
}

void CDlgFixDataPage2::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult){
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nItem = pNMListView->iItem;
	if(nItem != -1){
		m_strData = m_objList.GetItemText(nItem, 1);
		UpdateData(FALSE);
	}
	
	*pResult = 0;
}
void CDlgFixDataPage2::OnDataSave(){
	int nCnt = m_objList.GetItemCount();
	CEventDate *pDate;
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgFixDataPage2::OnDataSave : pFrm is null");
	}
	CPWikiDoc *pDoc = (CPWikiDoc*)GetDoc();
	for(int i = 0; i < nCnt; i++){
		CString strName = m_objList.GetItemText(i, 1);
		pDate = (CEventDate*)m_objList.GetItemData(i);
		int nDay = atoi(m_objList.GetItemText(i, 0));
		if(pDate){
			CString strOldName = pDate->GetName();
			if(strOldName.Compare(strName)){
				pDate->SetName(strName);
			}
		}else if(!strName.IsEmpty()){
			CEventDate objData;
			objData.Create(strName, "", NULL, SC_FIX_MONTH1);
			objData.SetMonthDay(1, nDay);
			int nIndex = pDoc->m_objFixedData.AddFixedData(&objData);
			CEventDate *pDate = pDoc->m_objFixedData.GetFixedData(nIndex);
			pDate->SetModify(TRUE);
		}
	}
}

BOOL CDlgFixDataPage2::PreTranslateMessage(MSG* pMsg){
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

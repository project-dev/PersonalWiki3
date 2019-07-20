// DlgFixDataPage3.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "DlgFixDataPage3.h"
#include "PWikiDoc.h"
#include "MainFrm.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFixDataPage3 ダイアログ


CDlgFixDataPage3::CDlgFixDataPage3(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFixDataPage3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFixDataPage3)
	m_strData = _T("");
	//}}AFX_DATA_INIT
}


void CDlgFixDataPage3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFixDataPage3)
	DDX_Control(pDX, IDC_CMB_SPAN, m_objCmbSpan);
	DDX_Control(pDX, IDC_CMB_DAYS, m_objCmbDays);
	DDX_Control(pDX, IDC_LIST, m_objList);
	DDX_Text(pDX, IDC_ED_DATA, m_strData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFixDataPage3, CDialog)
	//{{AFX_MSG_MAP(CDlgFixDataPage3)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_MOD, OnBtnMod)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFixDataPage3 メッセージ ハンドラ
BOOL CDlgFixDataPage3::OnInitDialog(){
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	m_objList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_objList.InsertColumn(0, "内容");
	m_objList.InsertColumn(1, "条件１");
	m_objList.InsertColumn(2, "条件２");

	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgFixDataPage3::OnInitDialog : pFrm is null");
	}
	CPWikiDoc *pDoc = (CPWikiDoc*)GetDoc();
	int nSize = pDoc->m_objFixedData.GetSize();

	for(int i = 0; i < nSize; i++){
		CEventDate *pData = pDoc->m_objFixedData.GetFixedData(i);
		if(pData->GetType() != SC_FIX_MONTH2){
			continue;
		}
		int nCnt = m_objList.GetItemCount();
		CString strData;
		strData = pData->GetName();
		m_objList.InsertItem(nCnt, strData, 0);

		m_objCmbSpan.GetLBText(pData->GetSpan(), strData);
		m_objList.SetItemText(nCnt, 1, strData);

		m_objCmbDays.GetLBText(pData->GetWeekDay(), strData);
		m_objList.SetItemText(nCnt, 2, strData);

		m_objList.SetItemData(nCnt, (LPARAM)pData);
	}
	
	SetColumnWidthLC(&m_objList);

	m_objCmbSpan.SetCurSel(0);
	m_objCmbDays.SetCurSel(0);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDlgFixDataPage3::OnBtnAdd(){
	UpdateData(TRUE);
	int nIndex = m_objList.GetItemCount();
	CString strCondDays;
	m_objCmbDays.GetWindowText(strCondDays);
	CString strCondSpan;
	m_objCmbSpan.GetWindowText(strCondSpan);

	m_objList.InsertItem(nIndex, m_strData, 0);
	m_objList.SetItemText(nIndex, 1, strCondSpan);
	m_objList.SetItemText(nIndex, 2, strCondDays);
}

void CDlgFixDataPage3::OnBtnDel(){
	int nSelItem = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if(nSelItem == -1){
		return;
	}
	m_arrDelList.Add((CEventDate*)m_objList.GetItemData(nSelItem));
	m_objList.DeleteItem(nSelItem);
	if(nSelItem < 0){
		nSelItem = 0;
	}else if(nSelItem >= m_objList.GetItemCount()){
		nSelItem = m_objList.GetItemCount() - 1;
	}
	m_objList.SetItemState(nSelItem, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);

}

void CDlgFixDataPage3::OnBtnMod(){
	UpdateData(TRUE);
	int nIndex = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	CString strCondDays;
	m_objCmbDays.GetWindowText(strCondDays);
	CString strCondSpan;
	m_objCmbSpan.GetWindowText(strCondSpan);

	m_objList.SetItemText(nIndex, 0, m_strData);
	m_objList.SetItemText(nIndex, 1, strCondSpan);
	m_objList.SetItemText(nIndex, 2, strCondDays);
}


void CDlgFixDataPage3::OnDataSave(){
	int nCnt = m_objList.GetItemCount();
	CEventDate *pDate;
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgFixDataPage3::OnDataSave : pFrm is null");
	}
	CPWikiDoc *pDoc = (CPWikiDoc*)GetDoc();
	for(int i = 0; i < nCnt; i++){
		CString strName = m_objList.GetItemText(i, 0);
		CString strSpan = m_objList.GetItemText(i, 1);
		CString strDays = m_objList.GetItemText(i, 2);
		int nSpan = m_objCmbSpan.FindStringExact(-1, strSpan);
		int nDays = m_objCmbDays.FindStringExact(-1, strDays);
		pDate = (CEventDate*)m_objList.GetItemData(i);
		int nDay = atoi(m_objList.GetItemText(i, 0));
		if(pDate){
			CString strOldName = pDate->GetName();
			int nOldSpan = pDate->GetSpan();
			int nOldDays = pDate->GetWeekDay();
			if(strOldName.Compare(strName)){
				pDate->SetName(strName);
			}
			if(nOldSpan != nSpan){
				pDate->SetSpan(nSpan);
			}
			if(nOldDays != nDays){
				pDate->SetWeekDay(nDays);
			}
		}else if(!strName.IsEmpty()){
			CEventDate objData;
			objData.Create(strName, "", NULL, SC_FIX_MONTH2);
			objData.SetSpan(nSpan);
			objData.SetWeekDay(nDays);
			int nIndex = pDoc->m_objFixedData.AddFixedData(&objData);
			CEventDate *pDate = pDoc->m_objFixedData.GetFixedData(nIndex);
			pDate->SetModify(TRUE);
		}
	}
	//削除対象を削除する
	CEventDate* pDelDate;
	for(i = 0; i < m_arrDelList.GetSize(); i++){
		pDelDate = m_arrDelList.GetAt(i);
		int nSize = pDoc->m_objFixedData.GetSize();
		for(int j = 0; j < nSize; j++){
			pDate = pDoc->m_objFixedData.GetFixedData(j);
			if(*pDelDate == *pDate){
				pDelDate = NULL;
				pDoc->m_objFixedData.DelFixedData(j);
				break;
			}
		}
		if(pDelDate){
			delete pDelDate;
		}
	}
}

void CDlgFixDataPage3::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
//	int nItem = pNMListView->iItem;
	int nItem = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED | LVNI_SELECTED);
	if(nItem == -1){
		m_strData = "";
		m_objCmbSpan.SetCurSel(0);
		m_objCmbDays.SetCurSel(0);
	}else if(pNMListView->uOldState != pNMListView->uNewState){
		m_strData = m_objList.GetItemText(nItem, 0);
		CString strSpan = m_objList.GetItemText(nItem, 1);
		CString strDays = m_objList.GetItemText(nItem, 2);
		int nSpan = m_objCmbSpan.FindStringExact(-1, strSpan);
		int nDays = m_objCmbDays.FindStringExact(-1, strDays);
		m_objCmbSpan.SetCurSel(nSpan);
		m_objCmbDays.SetCurSel(nDays);
	}
	UpdateData(FALSE);
}

BOOL CDlgFixDataPage3::PreTranslateMessage(MSG* pMsg) {
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

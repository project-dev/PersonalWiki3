// DlgFixDataPage1.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "DlgFixDataPage1.h"
#include "PWikiDoc.h"
#include "MainFrm.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFixDataPage1 ダイアログ


CDlgFixDataPage1::CDlgFixDataPage1(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFixDataPage1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFixDataPage1)
	m_strData = _T("");
	m_nDay = 1;
	m_nMonth = 1;
	m_bHoliday = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgFixDataPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFixDataPage1)
	DDX_Control(pDX, IDC_CMB_OPTION, m_objCmbOption);
	DDX_Control(pDX, IDC_LIST, m_objList);
	DDX_Text(pDX, IDC_ED_DATA, m_strData);
	DDX_Text(pDX, IDC_ED_DAY, m_nDay);
	DDV_MinMaxInt(pDX, m_nDay, 1, 31);
	DDX_Text(pDX, IDC_ED_MONTH, m_nMonth);
	DDV_MinMaxInt(pDX, m_nMonth, 1, 12);
	DDX_Check(pDX, IDC_CHK_HOLYDAY, m_bHoliday);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFixDataPage1, CDialog)
	//{{AFX_MSG_MAP(CDlgFixDataPage1)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_MOD, OnBtnMod)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFixDataPage1 メッセージ ハンドラ

BOOL CDlgFixDataPage1::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	m_objList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_objList.InsertColumn(0, "月");
	m_objList.InsertColumn(1, "日");
	m_objList.InsertColumn(2, "内容");
	m_objList.InsertColumn(3, "休日");
	m_objList.InsertColumn(4, "オプション");

	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgFixDataPage1::OnInitDialog : pFrm is null");
	}
	CPWikiDoc *pDoc = (CPWikiDoc*)GetDoc();
	int nSize = pDoc->m_objFixedData.GetSize();
	for(int i = 0; i < nSize; i++){
		CEventDate *pData = pDoc->m_objFixedData.GetFixedData(i);
		if(pData->GetType() != SC_FIX_YEAR){
			continue;
		}
		int nMonth;
		int nDay;
		pData->GetMonthDay(nMonth, nDay);
		int nCnt = m_objList.GetItemCount();
		CString strMonth;
		CString strDay;
		CString strData;
		strMonth.Format("%2d", nMonth);
		strDay.Format("%2d", nDay);
		strData = pData->GetName();
		m_objList.InsertItem(nCnt, strMonth, 0);
		m_objList.SetItemText(nCnt, 1, strDay);
		m_objList.SetItemText(nCnt, 2, strData);
		m_objList.SetItemText(nCnt, 3, pData->GetHoliday() ? "Yes" : "No");
		switch(pData->GetOption()){
		case HO_NONE:
			strData = "とくになにもしない";
			break;
		case HO_PREV:
			strData = "休日の場合、翌日にする";
			break;
		case HO_NEXT:
			strData = "休日の場合、前日にする";
			break;
		}
		m_objList.SetItemText(nCnt, 4, strData);
		m_objList.SetItemData(nCnt, (LPARAM)pData);
	}

	SetColumnWidthLC(&m_objList);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDlgFixDataPage1::OnBtnAdd(){
	UpdateData();
	int nCnt = m_objList.GetItemCount();
	CString strMonth;
	CString strDay;
	CString strData;
	strMonth.Format("%d", m_nMonth);
	strDay.Format("%d", m_nDay);
	m_objList.InsertItem(nCnt, strMonth, 0);
	m_objList.SetItemText(nCnt, 1, strDay);
	m_objList.SetItemText(nCnt, 2, m_strData);
	m_objList.SetItemText(nCnt, 3, m_bHoliday ? "Yes" : "No");
	switch(m_objCmbOption.GetCurSel()){
	case HO_NONE:
		strData = "とくになにもしない";
		break;
	case HO_PREV:
		strData = "休日の場合、翌日にする";
		break;
	case HO_NEXT:
		strData = "休日の場合、前日にする";
		break;
	}
	m_objList.SetItemText(nCnt, 4, strData);
/*
	CEventDate objFixDate;
	COleDateTime objDate;
	objFixDate.Create(m_strData, "", &objDate, SC_FIX_YEAR);
	objFixDate.SetMonthDay(m_nMonth, m_nDay);

	CMainFrame *pFrm = GetMainFrame(this);
	CPWikiDoc *pDoc = (CPWikiDoc*)GetDoc();
	int nIndex = pDoc->m_objFixedData.AddFixedData(&objFixDate);
	CEventDate *pDate = pDoc->m_objFixedData.GetFixedData(nIndex);
	m_objList.SetItemData(nCnt, (LPARAM)pDate);
*/
}

void CDlgFixDataPage1::OnBtnDel(){
	UpdateData();
	int nIndex = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED | LVNI_SELECTED);
	if(nIndex == -1){
		return;
	}
	CEventDate* pData = (CEventDate*)m_objList.GetItemData(nIndex);
	if(pData){
		m_arrDelList.Add(pData);
	}
	m_objList.DeleteItem(nIndex);
}

void CDlgFixDataPage1::OnBtnMod(){
	UpdateData();
	int nIndex = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED | LVNI_SELECTED);
	if(nIndex == -1){
		return;
	}
	CString strMonth;
	CString strDay;
	CString strData;
	strMonth.Format("%d", m_nMonth);
	strDay.Format("%d", m_nDay);
	m_objList.SetItemText(nIndex, 0, strMonth);
	m_objList.SetItemText(nIndex, 1, strDay);
	m_objList.SetItemText(nIndex, 2, m_strData);
	m_objList.SetItemText(nIndex, 3, m_bHoliday ? "Yes" : "No");
	switch(m_objCmbOption.GetCurSel()){
	case HO_NONE:
		strData = "とくになにもしない";
		break;
	case HO_PREV:
		strData = "休日の場合、翌日にする";
		break;
	case HO_NEXT:
		strData = "休日の場合、前日にする";
		break;
	}
	m_objList.SetItemText(nIndex, 4, strData);
}

void CDlgFixDataPage1::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
	int nIndex = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED | LVNI_SELECTED);
	if(nIndex == -1){
		m_strData = "";
		m_nMonth = 1;
		m_nDay = 1;
	}else if(pNMListView->uOldState != pNMListView->uNewState){
		CEventDate *pDate = (CEventDate*)m_objList.GetItemData(nIndex);
		m_nMonth = atoi(m_objList.GetItemText(nIndex, 0));
		m_nDay = atoi(m_objList.GetItemText(nIndex, 1));
		m_strData = m_objList.GetItemText(nIndex, 2);
		m_bHoliday = m_objList.GetItemText(nIndex, 3).Compare("Yes") ? FALSE : TRUE;
		CString strOpt = m_objList.GetItemText(nIndex, 4);
		if(!strOpt.Compare("とくになにもしない")){
			m_objCmbOption.SetCurSel(0);
		}else if(!strOpt.Compare("休日の場合、翌日にする")){
			m_objCmbOption.SetCurSel(1);
		}else if(!strOpt.Compare("休日の場合、前日にする")){
			m_objCmbOption.SetCurSel(2);
		}
	}
	UpdateData(FALSE);
}

void CDlgFixDataPage1::OnDataSave(){
	int nCnt = m_objList.GetItemCount();
	CEventDate *pDate;
	CEventDate *pDelDate;
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgFixDataPage1::OnDataSave : pFrm is null");
	}
	CPWikiDoc *pDoc = (CPWikiDoc*)GetDoc();
	for(int i = 0; i < nCnt; i++){
		int nMonth = atoi(m_objList.GetItemText(i, 0));
		int nDay = atoi(m_objList.GetItemText(i, 1));
		CString strName = m_objList.GetItemText(i, 2);

		BOOL bHoliday = m_objList.GetItemText(i, 3).Compare("Yes") ? FALSE : TRUE;
		CString strOpt = m_objList.GetItemText(i, 4);
		ePLAN_HOLYDAY eOption;
		if(!strOpt.Compare("とくになにもしない")){
			eOption = HO_NONE;
		}else if(!strOpt.Compare("休日の場合、翌日にする")){
			eOption = HO_PREV;
		}else if(!strOpt.Compare("休日の場合、前日にする")){
			eOption = HO_NEXT;
		}	
		
		pDate = (CEventDate*)m_objList.GetItemData(i);
		if(pDate){
			pDate->SetMonthDay(nMonth, nDay);
			pDate->SetName(strName);
			pDate->SetHoliday(bHoliday);
			pDate->SetOption(eOption);
		}else{
			CEventDate objData;
			objData.Create(strName, "", NULL, SC_FIX_YEAR);
			objData.SetMonthDay(nMonth, nDay);
			objData.SetHoliday(bHoliday);
			objData.SetOption(eOption);
			pDoc->m_objFixedData.AddFixedData(&objData);
		}
	}

	//削除対象を削除する
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
	m_arrDelList.RemoveAll();
}

BOOL CDlgFixDataPage1::PreTranslateMessage(MSG* pMsg){
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

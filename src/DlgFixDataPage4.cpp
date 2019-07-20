// DlgFixDataPage4.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "DlgFixDataPage4.h"
#include "PWikiDoc.h"
#include "MainFrm.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFixDataPage4 ダイアログ


CDlgFixDataPage4::CDlgFixDataPage4(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFixDataPage4::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFixDataPage4)
	m_bMon = FALSE;
	m_bFri = FALSE;
	m_bSat = FALSE;
	m_bSun = FALSE;
	m_bThu = FALSE;
	m_bTue = FALSE;
	m_bWed = FALSE;
	m_strData = _T("");
	//}}AFX_DATA_INIT
}


void CDlgFixDataPage4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFixDataPage4)
	DDX_Control(pDX, IDC_LIST, m_objList);
	DDX_Check(pDX, IDC_CHK_MON, m_bMon);
	DDX_Check(pDX, IDC_CHK_FRI, m_bFri);
	DDX_Check(pDX, IDC_CHK_SAT, m_bSat);
	DDX_Check(pDX, IDC_CHK_SUN, m_bSun);
	DDX_Check(pDX, IDC_CHK_THU, m_bThu);
	DDX_Check(pDX, IDC_CHK_TUE, m_bTue);
	DDX_Check(pDX, IDC_CHK_WED, m_bWed);
	DDX_Text(pDX, IDC_ED_DATA, m_strData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFixDataPage4, CDialog)
	//{{AFX_MSG_MAP(CDlgFixDataPage4)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_MOD, OnBtnMod)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFixDataPage4 メッセージ ハンドラ

int CDlgFixDataPage4::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

BOOL CDlgFixDataPage4::OnInitDialog(){
	CDialog::OnInitDialog();
	m_objList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_objList.InsertColumn(0, "内容");
	m_objList.InsertColumn(1, "日");
	m_objList.InsertColumn(2, "月");
	m_objList.InsertColumn(3, "火");
	m_objList.InsertColumn(4, "水");
	m_objList.InsertColumn(5, "木");
	m_objList.InsertColumn(6, "金");
	m_objList.InsertColumn(7, "土");

	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgFixDataPage4::OnInitDialog : pFrm is null");
	}
	CPWikiDoc *pDoc = (CPWikiDoc*)GetDoc();
	int nSize = pDoc->m_objFixedData.GetSize();

	for(int i = 0; i < nSize; i++){
		CEventDate *pData = pDoc->m_objFixedData.GetFixedData(i);
		if(pData->GetType() != SC_FIX_WEEK){
			continue;
		}
		int nCnt = m_objList.GetItemCount();
		CString strData;
		strData = pData->GetName();
		m_objList.InsertItem(nCnt, strData, 0);

		for(int nDay = 0; nDay < 7; nDay++){
			strData = pData->GetWeekDay(nDay) ? "○" : "";
			m_objList.SetItemText(nCnt, nDay + 1, strData);
		}

		m_objList.SetItemData(nCnt, (LPARAM)pData);
	}

	SetColumnWidthLC(&m_objList);
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDlgFixDataPage4::OnBtnAdd(){
	UpdateData(TRUE);
	int nCnt = m_objList.GetItemCount();
	m_objList.InsertItem(nCnt, m_strData, 0);
	m_objList.SetItemText(nCnt, 1, m_bSun ? "○" : "");
	m_objList.SetItemText(nCnt, 2, m_bMon ? "○" : "");
	m_objList.SetItemText(nCnt, 3, m_bTue ? "○" : "");
	m_objList.SetItemText(nCnt, 4, m_bWed ? "○" : "");
	m_objList.SetItemText(nCnt, 5, m_bThu ? "○" : "");
	m_objList.SetItemText(nCnt, 6, m_bFri ? "○" : "");
	m_objList.SetItemText(nCnt, 7, m_bSat ? "○" : "");
}

void CDlgFixDataPage4::OnBtnDel(){
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

void CDlgFixDataPage4::OnBtnMod(){
	UpdateData(TRUE);
	int nSelItem = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if(nSelItem == -1){
		return;
	}
	m_objList.SetItemText(nSelItem, 0, m_strData);
	m_objList.SetItemText(nSelItem, 1, m_bSun ? "○" : "");
	m_objList.SetItemText(nSelItem, 2, m_bMon ? "○" : "");
	m_objList.SetItemText(nSelItem, 3, m_bTue ? "○" : "");
	m_objList.SetItemText(nSelItem, 4, m_bWed ? "○" : "");
	m_objList.SetItemText(nSelItem, 5, m_bThu ? "○" : "");
	m_objList.SetItemText(nSelItem, 6, m_bFri ? "○" : "");
	m_objList.SetItemText(nSelItem, 7, m_bSat ? "○" : "");
}

void CDlgFixDataPage4::OnDataSave(){
	int nCnt = m_objList.GetItemCount();
	CEventDate *pDate;
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgFixDataPage4::OnDataSave : pFrm is null");
	}
	CPWikiDoc *pDoc = (CPWikiDoc*)GetDoc();
	for(int i = 0; i < nCnt; i++){
		CString strName = m_objList.GetItemText(i, 0);
		pDate = (CEventDate*)m_objList.GetItemData(i);
		if(pDate){
			CString strOldName = pDate->GetName();
			if(strOldName.Compare(strName)){
				pDate->SetName(strName);
			}
			for(int nWeek = 0; nWeek < 7; nWeek++){
				CString strUse = m_objList.GetItemText(i, nWeek + 1);
				if(!strUse.Compare("○")){
					pDate->SetWeekDay(nWeek, TRUE);
				}else{
					pDate->SetWeekDay(nWeek, FALSE);
				}
			}
		}else if(!strName.IsEmpty()){
			CEventDate objData;
			objData.Create(strName, "", NULL, SC_FIX_WEEK);
			for(int nWeek = 0; nWeek < 7; nWeek++){
				CString strUse = m_objList.GetItemText(i, nWeek + 1);
				if(!strUse.Compare("○")){
					objData.SetWeekDay(nWeek, TRUE);
				}else{
					objData.SetWeekDay(nWeek, FALSE);
				}
			}
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
			if(pDelDate){
				if(*pDelDate == *pDate){
					pDelDate = NULL;
					pDoc->m_objFixedData.DelFixedData(j);
					break;
				}
			}
		}
		if(pDelDate){
			delete pDelDate;
		}
	}

}

void CDlgFixDataPage4::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult){
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
//	int nItem = pNMListView->iItem;
	int nItem = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED | LVNI_SELECTED);
	BOOL* arrUse[] = {&m_bSun, &m_bMon, &m_bTue, &m_bWed, &m_bThu, &m_bFri, &m_bSat};
	if(nItem == -1){
		m_strData = "";
		for(int nWeek = 1; nWeek <= 7; nWeek++){
			*arrUse[nWeek -1] = FALSE;
		}
	}else if(pNMListView->uOldState != pNMListView->uNewState){
		m_strData = m_objList.GetItemText(nItem, 0);
		for(int nWeek = 1; nWeek <= 7; nWeek++){
			CString strData = m_objList.GetItemText(nItem, nWeek);
			if(!strData.Compare("○")){
				*arrUse[nWeek -1] = TRUE;
			}else{
				*arrUse[nWeek -1] = FALSE;
			}
		}
	}
	UpdateData(FALSE);

}

BOOL CDlgFixDataPage4::PreTranslateMessage(MSG* pMsg) {
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

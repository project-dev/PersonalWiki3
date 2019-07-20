// ToDoView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "ToDoView.h"
#include "PWikiDoc.h"
#include "DlgToDoInp.h"
#include "LogFile.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToDoView

IMPLEMENT_DYNCREATE(CToDoView, CView)

CToDoView::CToDoView(){
}

CToDoView::~CToDoView(){
}


BEGIN_MESSAGE_MAP(CToDoView, CView)
	//{{AFX_MSG_MAP(CToDoView)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDM_TODO_ADD, OnTodoAdd)
	ON_UPDATE_COMMAND_UI(IDM_TODO_ADD, OnUpdateTodoAdd)
	ON_COMMAND(IDM_TODO_DEL, OnTodoDel)
	ON_UPDATE_COMMAND_UI(IDM_TODO_DEL, OnUpdateTodoDel)
	ON_COMMAND(IDM_TODO_EDIT, OnTodoEdit)
	ON_UPDATE_COMMAND_UI(IDM_TODO_EDIT, OnUpdateTodoEdit)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TODOTAB, OnTabChange)
	ON_NOTIFY(LVN_COLUMNCLICK, IDS_TODOLIST1, OnColumnClick)
	ON_NOTIFY(LVN_COLUMNCLICK, IDS_TODOLIST2, OnColumnClick)
	ON_NOTIFY(LVN_COLUMNCLICK, IDS_TODOLIST3, OnColumnClick)
	ON_NOTIFY(LVN_COLUMNCLICK, IDS_TODOLIST4, OnColumnClick)
	ON_NOTIFY(LVN_COLUMNCLICK, IDS_TODOLIST5, OnColumnClick)
	ON_NOTIFY(LVN_COLUMNCLICK, IDS_TODOLIST6, OnColumnClick)
	ON_NOTIFY(LVN_COLUMNCLICK, IDS_TODOLIST7, OnColumnClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToDoView 描画

void CToDoView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: この位置に描画用のコードを追加してください
}

/////////////////////////////////////////////////////////////////////////////
// CToDoView 診断

#ifdef _DEBUG
void CToDoView::AssertValid() const
{
	CView::AssertValid();
}

void CToDoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToDoView メッセージ ハンドラ

void CToDoView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	CRect rect;
	GetClientRect(rect);

	CFont *pFont = GetFont();
	LOGFONT lFont;
	memset(&lFont, 0, sizeof(LOGFONT));
	if(pFont){
		pFont->GetLogFont(&lFont);
	}else{
		strcpy(lFont.lfFaceName, "MS UI Gothic");
		lFont.lfCharSet = DEFAULT_CHARSET;
	}
	lFont.lfHeight = -10;
	m_objFont.CreateFontIndirect(&lFont);

	m_objTab.Create(WS_CHILD | WS_VISIBLE | TCS_SINGLELINE | TCS_TABS /*| TCS_BOTTOM*/, rect, this, IDC_TODOTAB);
	m_objTab.InsertItem(0, "全て", 0);
	m_objTab.InsertItem(1, "未着手", 0);
	m_objTab.InsertItem(2, "対応中", 0);
	m_objTab.InsertItem(3, "確認完", 0);
	m_objTab.InsertItem(4, "待ち", 0);
	m_objTab.InsertItem(5, "完了", 0);
	m_objTab.InsertItem(6, "保留", 0);
	m_objTab.InsertItem(7, "チャート", 0);
	m_objTab.SetFont(&m_objFont);

	CRect rect2;
	m_objTab.GetClientRect(rect2);
	m_objTabRect = rect2;
	m_objTab.AdjustRect(FALSE, rect2);
	m_objTabRect.bottom = rect2.top;
	
	CBitmap m_objStateBmp;
	m_objStateBmp.LoadBitmap(IDB_TODOSTATE);
	m_arrStateImg.Create(16, 16, ILC_COLOR16, 6, 1);
	m_arrStateImg.Add(&m_objStateBmp, RGB(0xFF, 0xFF, 0xee));

	UINT uID;
	for(int i = 0; i < TT_END; i++){
		switch(i){
		case TT_ALL:
			uID = IDS_TODOLIST1;
			break;
		case TT_NONE:
			uID = IDS_TODOLIST2;
			break;
		case TT_PARITY:
			uID = IDS_TODOLIST3;
			break;
		case TT_CHECK:
			uID = IDS_TODOLIST4;
			break;
		case TT_WAIT:
			uID = IDS_TODOLIST5;
			break;
		case TT_FINISH:
			uID = IDS_TODOLIST6;
			break;
		case TT_RESERVE:
			uID = IDS_TODOLIST7;
			break;
		}
		if(i != TT_CHART){
			m_objList[i].Create(WS_CHILD | WS_VISIBLE | LVS_REPORT, rect, this, uID);
			m_objList[i].SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			m_objList[i].InsertColumn(0, "項目名");
			m_objList[i].InsertColumn(1, "カテゴリ");
			m_objList[i].InsertColumn(2, "状態");
			m_objList[i].InsertColumn(3, "進捗");
			m_objList[i].InsertColumn(4, "開始予定");
			m_objList[i].InsertColumn(5, "開始日");
			m_objList[i].InsertColumn(6, "終了予定");
			m_objList[i].InsertColumn(7, "終了日");
			m_objList[i].SetImageList(&m_arrStateImg, LVSIL_SMALL);

			m_objList[i].SetColumnWidth(0,  LVSCW_AUTOSIZE_USEHEADER );
			m_objList[i].SetColumnWidth(1,  LVSCW_AUTOSIZE_USEHEADER );
			m_objList[i].SetColumnWidth(2,  LVSCW_AUTOSIZE_USEHEADER );
			m_objList[i].SetColumnWidth(3,  LVSCW_AUTOSIZE_USEHEADER );
			m_objList[i].SetColumnWidth(4,  LVSCW_AUTOSIZE_USEHEADER );
			m_objList[i].SetColumnWidth(5,  LVSCW_AUTOSIZE_USEHEADER );
			m_objList[i].SetColumnWidth(6,  LVSCW_AUTOSIZE_USEHEADER );
			m_objList[i].SetColumnWidth(7,  LVSCW_AUTOSIZE_USEHEADER );
		}
	}

	m_objChartWnd.Create(WS_CHILD, rect, this, (CPWikiDoc*)GetDocument(), IDS_TODOLIST8);
	m_objChartWnd.SetImageList(&m_arrStateImg);
	m_objChartWnd.SetFont(&m_objFont);

	UpdateToDo();	
	DelCheckToDo();
	SetTimer(IDS_TODOCHKTIMER, 1000, NULL);
}

void CToDoView::UpdateToDo(){
	int nActive = m_objTab.GetCurSel();
	if((nActive == -1) 
	|| (nActive == TT_CHART && !::IsWindow(m_objChartWnd.m_hWnd)) 
	|| (nActive != TT_CHART && !::IsWindow(m_objList[nActive].m_hWnd))
	){
		return;
	}
	CPWikiDoc* pDoc = (CPWikiDoc*)GetDocument();
	int nSize = pDoc->m_objToDoData.GetSize();
	int nSelect = -1;
	if(nActive == TT_CHART){
		nSelect = m_objChartWnd.GetSelectItemIndex();
	}else{
		nSelect = m_objList[nActive].GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED | LVNI_SELECTED);
	}
	CEventDate *pData;
	CString strName;
	double dPar;
	CString strPar;
	COleDateTime objStartDT;
	COleDateTime objStartEnd;
	for(int j = 0; j <  TT_END; j++){
		if(j == TT_CHART){
			m_objChartWnd.UpdateBuffer();
			m_objChartWnd.InvalidateRect(NULL);
		}else{
			if(nActive == j){
				m_objList[j].SetRedraw(FALSE);
			}
			m_objList[j].DeleteAllItems();
			for(int i = 0; i < nSize; i++){
				pData = pDoc->m_objToDoData.GetToDo(i);

				int nState = pData->GetState();
				if((j != 0) && (nState != (j - 1))){
					continue;
				}
				strName = pData->GetName();
				int nCnt = m_objList[j].GetItemCount();
				int nIndex = m_objList[j].InsertItem(nCnt, strName, nState);

				CString strCategory = pData->GetCategory();
				m_objList[j].SetItemText(nIndex, 1, strCategory);

				m_objList[j].SetItemText(nIndex, 2, pData->GetStateString());

				dPar = pData->GetProcess();
				strPar;
				strPar.Format("%8.3f", dPar);
				m_objList[j].SetItemText(nIndex, 3, strPar);

				pData->GetPlan(&objStartDT, &objStartEnd);
				m_objList[j].SetItemText(nIndex, 4, objStartDT.Format("%Y/%m/%d"));
				m_objList[j].SetItemText(nIndex, 6, objStartEnd.Format("%Y/%m/%d"));

				switch(nState){
				case 0:	//未実施
					m_objList[j].SetItemText(nIndex, 5, "----/--/--");
					m_objList[j].SetItemText(nIndex, 7, "----/--/--");
					break;
				case 1:	//対応中
				case 2: //待ち
				case 3:	//確認完
				case 5:	//保留
					pData->GetProgress(&objStartDT, &objStartEnd);
					m_objList[j].SetItemText(nIndex, 5, objStartDT.Format("%Y/%m/%d"));
					m_objList[j].SetItemText(nIndex, 7, "----/--/--");
					break;
				case 4:	//完了
					pData->GetProgress(&objStartDT, &objStartEnd);
					m_objList[j].SetItemText(nIndex, 5, objStartDT.Format("%Y/%m/%d"));
					m_objList[j].SetItemText(nIndex, 7, objStartEnd.Format("%Y/%m/%d"));
					break;
				}
				m_objList[j].SetItemData(nIndex, (LPARAM)pData);
			}
			SetColumnWidthLC(&m_objList[j]);
			if(nActive == j){
				m_objList[j].SetRedraw(TRUE);
				m_objList[j].InvalidateRect(NULL);
			}
		}
	}
}

void CToDoView::OnSize(UINT nType, int cx, int cy) {
	CView::OnSize(nType, cx, cy);
	SetCtrlPos();
}

void CToDoView::OnShowWindow(BOOL bShow, UINT nStatus){
	CView::OnShowWindow(bShow, nStatus);
}

void CToDoView::OnContextMenu(CWnd* pWnd, CPoint point){
	int nActive = m_objTab.GetCurSel();
	if(nActive == -1){
		return;
	}
	CMenu menu;
	menu.LoadMenu(IDR_EDIT_MENU);
	CMenu *pMenu = menu.GetSubMenu(0);
	int nIndex = -1;
	if(nActive == TT_CHART){
		nIndex = m_objChartWnd.GetSelectItemIndex();
	}else{
		nIndex = m_objList[nActive].GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED | LVNI_SELECTED);
	}
	if(nIndex == -1){
		pMenu->EnableMenuItem(IDM_TODO_EDIT, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED) ; 
		pMenu->EnableMenuItem(IDM_TODO_DEL, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED) ; 
	}else{
		pMenu->EnableMenuItem(IDM_TODO_EDIT, MF_BYCOMMAND | MF_ENABLED);
		pMenu->EnableMenuItem(IDM_TODO_DEL, MF_BYCOMMAND | MF_ENABLED);
	}
	pMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}

void CToDoView::OnTodoAdd(){
	CDlgToDoInp dlg;
	CPWikiDoc* pDoc = (CPWikiDoc*)GetDocument();
	dlg.m_strCategory = "";

	if(dlg.DoModal() == IDCANCEL){
		return;
	}
	CEventDate objDate;
	objDate.Create(dlg.m_strName, dlg.m_strDetail, NULL, SC_TODO);
	objDate.SetPlan(&dlg.m_objPlanStart, &dlg.m_objPlanEnd);
	objDate.SetProgress(&dlg.m_objProgressStart, &dlg.m_objProgressEnd);
	objDate.SetProcess(dlg.m_dProcessPar);
	objDate.SetCategory(dlg.m_strCategory);
	objDate.SetState(dlg.m_nState);
	pDoc->m_objToDoData.AddToDo(&objDate);
	UpdateToDo();
	m_objChartWnd.UpdateCategory();
}

void CToDoView::OnUpdateTodoAdd(CCmdUI* pCmdUI){
}

void CToDoView::OnTodoDel(){
	int nActive = m_objTab.GetCurSel();
	if(nActive == -1){
		return;
	}
	int nIndex = -1;
	if(nActive == TT_CHART){
		nIndex = m_objChartWnd.GetSelectItemIndex();
	}else{
		nIndex = m_objList[nActive].GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED | LVNI_SELECTED);
	}
	if(nIndex == -1){
		return;
	}
	CPWikiDoc* pDoc = (CPWikiDoc*)GetDocument();
	CEventDate *pDate = NULL;
	if(nActive == TT_CHART){
		pDate = m_objChartWnd.GetItemData(nIndex);
		if(pDate){
			pDoc->m_objToDoData.DelToDo(pDate);
		}
	}else{
		pDate = (CEventDate*)m_objList[nActive].GetItemData(nIndex);
		pDoc->m_objToDoData.DelToDo(pDate);
		m_objList[nActive].DeleteItem(nIndex);
	}
	UpdateToDo();
}

void CToDoView::OnUpdateTodoDel(CCmdUI* pCmdUI){
	int nActive = m_objTab.GetCurSel();
	if(nActive == -1){
		return;
	}
	int nIndex = 0;
	if(nActive == TT_CHART){
		nIndex = m_objChartWnd.GetSelectItemIndex();
	}else{
		nIndex = m_objList[nActive].GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED | LVNI_SELECTED);
	}
	if(nIndex == -1){
		pCmdUI->Enable(FALSE);
	}else{
		pCmdUI->Enable(TRUE);
	}
}

void CToDoView::OnTodoEdit(){
	int nActive = m_objTab.GetCurSel();
	if(nActive == -1){
		return;
	}
	int nIndex = -1;
	if(nActive == TT_CHART){
		nIndex = m_objChartWnd.GetSelectItemIndex();
	}else{
		nIndex = m_objList[nActive].GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED | LVNI_SELECTED);
	}
	if(nIndex == -1){
		return;
	}
	CPWikiDoc *pDoc = (CPWikiDoc*)GetDocument();
	CEventDate *pDate = NULL;
	if(nActive == TT_CHART){
		pDate = m_objChartWnd.GetItemData(nIndex);
	}else{
		pDate = (CEventDate*)m_objList[nActive].GetItemData(nIndex);
	}

	if(!pDate){
		return;
	}
	CDlgToDoInp dlg;
	dlg.m_strCategory = pDate->GetCategory();
	dlg.m_strName = pDate->GetName();
	dlg.m_strDetail = pDate->GetDetail();
	pDate->GetPlan(&dlg.m_objPlanStart, &dlg.m_objPlanEnd); 
	pDate->GetProgress(&dlg.m_objProgressStart, &dlg.m_objProgressEnd); 
	if(dlg.m_objPlanStart.GetStatus() != COleDateTime::valid){
		dlg.m_objPlanStart = COleDateTime::GetCurrentTime();
	}
	if(dlg.m_objPlanEnd.GetStatus() != COleDateTime::valid){
		dlg.m_objPlanEnd = COleDateTime::GetCurrentTime();
	}
	if(dlg.m_objProgressStart.GetStatus() != COleDateTime::valid){
		dlg.m_objProgressStart = COleDateTime::GetCurrentTime();
	}
	if(dlg.m_objProgressEnd.GetStatus() != COleDateTime::valid){
		dlg.m_objProgressEnd = COleDateTime::GetCurrentTime();
	}

	dlg.m_nState = pDate->GetState();
	dlg.m_dProcessPar = pDate->GetProcess();

	if(dlg.DoModal() == IDCANCEL){
		return;
	}
	pDate->SetName(dlg.m_strName);
	pDate->SetDetail(dlg.m_strDetail);
	pDate->SetCategory(dlg.m_strCategory);
	pDate->SetPlan(&dlg.m_objPlanStart, &dlg.m_objPlanEnd);
	pDate->SetProgress(&dlg.m_objProgressStart, &dlg.m_objProgressEnd);
	pDate->SetProcess(dlg.m_dProcessPar);
	pDate->SetState(dlg.m_nState);
	UpdateToDo();
	m_objChartWnd.UpdateCategory();

}

void CToDoView::OnUpdateTodoEdit(CCmdUI* pCmdUI){
	int nActive = m_objTab.GetCurSel();
	if(nActive == -1){
		return;
	}
	int nIndex = 0;
	if(nActive == TT_CHART){
		nIndex = m_objChartWnd.GetSelectItemIndex();
	}else{
		nIndex = m_objList[nActive].GetNextItem(-1, LVNI_ALL | LVNI_FOCUSED | LVNI_SELECTED);
	}
}

int CToDoView::OnCreate(LPCREATESTRUCT lpCreateStruct){
	CLogFile::SaveAppLog("CToDoView::OnCreate");
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: この位置に固有の作成用コードを追加してください
	CLogFile::SaveAppLog("CToDoView 生成");	
	m_objPreChkDtm = COleDateTime::GetCurrentTime();
	int nYear = m_objPreChkDtm.GetYear();
	int nMonth = m_objPreChkDtm.GetMonth();
	int nDay = m_objPreChkDtm.GetDay();
	m_objPreChkDtm.SetDateTime(nYear, nMonth, nDay, 0, 0, 0);
	CLogFile::SaveAppLog("CToDoView::OnCreate End");
	return 0;
}

void CToDoView::OnTabChange(LPNMHDR pNmhdr, HRESULT *pResult){
	*pResult = 0;
	SetCtrlPos();
}

void CToDoView::SetCtrlPos(){
	if(::IsWindow(m_objTab.m_hWnd)){
		int nActive = m_objTab.GetCurSel();
		CRect rect;
		GetClientRect(rect);
		m_objTab.SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), m_objTabRect.Height(), SWP_SHOWWINDOW);
		for(int j = 0; j <  TT_END; j++){
			if(j == TT_CHART){
				if(::IsWindow(m_objChartWnd.m_hWnd)){
					if(nActive == j){
						m_objChartWnd.SetWindowPos(&wndTop, rect.left, rect.top + m_objTabRect.Height(), rect.Width(), rect.Height() - m_objTabRect.Height(), SWP_SHOWWINDOW);
					}else{
						m_objChartWnd.ShowWindow(SW_HIDE);
						//m_objChartWnd.SetWindowPos(&wndTop, rect.left, rect.top + m_objTabRect.Height(), rect.Width(), rect.Height() - m_objTabRect.Height(), SWP_HIDEWINDOW);
					}
				}
			}else{
				if(::IsWindow(m_objList[j].m_hWnd)){
					if(nActive == j){
						m_objList[j].SetWindowPos(&wndTop, rect.left, rect.top + m_objTabRect.Height(), rect.Width(), rect.Height() - m_objTabRect.Height(), SWP_SHOWWINDOW);
					}else{
						m_objList[j].ShowWindow(SW_HIDE);
						//m_objList[j].SetWindowPos(&wndTop, rect.left, rect.top + m_objTabRect.Height(), rect.Width(), rect.Height() - m_objTabRect.Height(), SWP_HIDEWINDOW);
					}
				}	
			}
		}
	}
}

void CToDoView::OnColumnClick(LPNMHDR pNmhdr, LRESULT *pResult){
	LPNMLISTVIEW pItem = (LPNMLISTVIEW)pNmhdr;
	*pResult = 0;
	int nIndex = -1;
	PFNLVCOMPARE arrFunc[] = {	CToDoView::SortItemFunc,		CToDoView::SortCategoryFunc, 
								CToDoView::SortStateFunc,		CToDoView::SortProcessFunc,
								CToDoView::SortStPlanFunc,		CToDoView::SortEdPlanFunc,
								CToDoView::SortStProgressFunc,	CToDoView::SortEdProgressFunc};
	if(pItem->hdr.idFrom == IDS_TODOLIST1){
		nIndex = 0;
	}else if(pItem->hdr.idFrom == IDS_TODOLIST2){
		nIndex = 1;
	}else if(pItem->hdr.idFrom == IDS_TODOLIST3){
		nIndex = 2;
	}else if(pItem->hdr.idFrom == IDS_TODOLIST4){
		nIndex = 3;
	}else if(pItem->hdr.idFrom == IDS_TODOLIST5){
		nIndex = 4;
	}else if(pItem->hdr.idFrom == IDS_TODOLIST6){
		nIndex = 5;
	}else if(pItem->hdr.idFrom == IDS_TODOLIST7){
		nIndex = 6;
	}
	if(nIndex == -1){
		return;
	}
	m_objList[nIndex].SortItems(arrFunc[pItem->iSubItem], m_bSortAspect[pItem->iSubItem]);
	m_bSortAspect[pItem->iSubItem] = !m_bSortAspect[pItem->iSubItem];
}

int CALLBACK CToDoView::SortItemFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){
	CEventDate *pDate1 = (CEventDate*)lParam1;
	CEventDate *pDate2 = (CEventDate*)lParam2;
	BOOL bAspect = lParamSort ? TRUE : FALSE;
	CString strCmp1 = pDate1->GetName();
	CString strCmp2 = pDate2->GetName();
	int nCmp = strCmp1.Compare(strCmp2) * (bAspect ? 1 : -1);
	return nCmp;
}
int CALLBACK CToDoView::SortCategoryFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){
	CEventDate *pDate1 = (CEventDate*)lParam1;
	CEventDate *pDate2 = (CEventDate*)lParam2;
	BOOL bAspect = lParamSort ? TRUE : FALSE;
	CString strCmp1 = pDate1->GetCategory();
	CString strCmp2 = pDate2->GetCategory();
	int nCmp = strCmp1.Compare(strCmp2) * (bAspect ? 1 : -1);
	return nCmp;
}
int CALLBACK CToDoView::SortStateFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){
	CEventDate *pDate1 = (CEventDate*)lParam1;
	CEventDate *pDate2 = (CEventDate*)lParam2;
	int nCmp1 = pDate1->GetState();
	int nCmp2 = pDate2->GetState();
	BOOL bAspect = lParamSort ? TRUE : FALSE;
	int nCmp = 0;
	if(nCmp1 < nCmp2){
		nCmp = bAspect ? 1 : -1;
	}else if(nCmp1 > nCmp2){
		nCmp = bAspect ? -1 : 1;
	}
	return nCmp;
}
int CALLBACK CToDoView::SortProcessFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){
	CEventDate *pDate1 = (CEventDate*)lParam1;
	CEventDate *pDate2 = (CEventDate*)lParam2;
	BOOL bAspect = lParamSort ? TRUE : FALSE;
	double dCmp1 = pDate1->GetProcess();
	double dCmp2 = pDate2->GetProcess();
	int nCmp = 0;
	if(dCmp1 < dCmp2){
		nCmp = bAspect ? 1 : -1;
	}else if(dCmp1 > dCmp2){
		nCmp = bAspect ? -1 : 1;
	}
	return nCmp;
}
int CALLBACK CToDoView::SortStPlanFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){
	CEventDate *pDate1 = (CEventDate*)lParam1;
	CEventDate *pDate2 = (CEventDate*)lParam2;
	BOOL bAspect = lParamSort ? TRUE : FALSE;
	COleDateTime objStPl1;
	COleDateTime objStPl2;
	COleDateTime objEdPl1;
	COleDateTime objEdPl2;
	pDate1->GetPlan(&objStPl1, &objEdPl1);
	pDate2->GetPlan(&objStPl2, &objEdPl2);
	int nCmp = 0;
	if(objStPl1 < objStPl2){
		nCmp = bAspect ? 1 : -1;
	}else if(objStPl1 > objStPl2){
		nCmp = bAspect ? -1 : 1;
	}
	return nCmp;
}
int CALLBACK CToDoView::SortEdPlanFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){
	CEventDate *pDate1 = (CEventDate*)lParam1;
	CEventDate *pDate2 = (CEventDate*)lParam2;
	BOOL bAspect = lParamSort ? TRUE : FALSE;
	COleDateTime objStPl1;
	COleDateTime objStPl2;
	COleDateTime objEdPl1;
	COleDateTime objEdPl2;
	pDate1->GetPlan(&objStPl1, &objEdPl1);
	pDate2->GetPlan(&objStPl2, &objEdPl2);
	int nCmp = 0;
	if(objEdPl1 < objEdPl2){
		nCmp = bAspect ? 1 : -1;
	}else if(objEdPl1 > objEdPl2){
		nCmp = bAspect ? -1 : 1;
	}
	return nCmp;
}
int CALLBACK CToDoView::SortStProgressFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){
	CEventDate *pDate1 = (CEventDate*)lParam1;
	CEventDate *pDate2 = (CEventDate*)lParam2;
	BOOL bAspect = lParamSort ? TRUE : FALSE;
	COleDateTime objStPg1;
	COleDateTime objStPg2;
	COleDateTime objEdPg1;
	COleDateTime objEdPg2;
	pDate1->GetProgress(&objStPg1, &objEdPg1);
	pDate2->GetProgress(&objStPg2, &objEdPg2);
	
	int nCmp1 = pDate1->GetState();
	int nCmp2 = pDate2->GetState();
	switch(nCmp1){
	case 0:	//未実施
		//日付無効
		objStPg1.SetDateTime(1900, 1, 1, 0, 0, 0);
		break;
	case 1:	//対応中
	case 2: //待ち
	case 3:	//確認完
	case 5:	//保留
	case 4:	//完了
		//日付有効
		break;
	}

	switch(nCmp2){
	case 0:	//未実施
		//日付無効
		objStPg2.SetDateTime(1900, 1, 1, 0, 0, 0);
		break;
	case 1:	//対応中
	case 2: //待ち
	case 3:	//確認完
	case 5:	//保留
	case 4:	//完了
		//日付有効
		break;
	}
	int nCmp = 0;
	if(objStPg1 < objStPg2){
		nCmp = bAspect ? 1 : -1;
	}else if(objStPg1 > objStPg2){
		nCmp = bAspect ? -1 : 1;
	}
	return nCmp;
}
int CALLBACK CToDoView::SortEdProgressFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){
	CEventDate *pDate1 = (CEventDate*)lParam1;
	CEventDate *pDate2 = (CEventDate*)lParam2;
	BOOL bAspect = lParamSort ? TRUE : FALSE;
	COleDateTime objStPg1;
	COleDateTime objStPg2;
	COleDateTime objEdPg1;
	COleDateTime objEdPg2;
	pDate1->GetProgress(&objStPg1, &objEdPg1);
	pDate2->GetProgress(&objStPg2, &objEdPg2);

	int nCmp1 = pDate1->GetState();
	int nCmp2 = pDate2->GetState();
	switch(nCmp1){
	case 0:	//未実施
	case 1:	//対応中
	case 2: //待ち
	case 3:	//確認完
	case 5:	//保留
		//日付無効
		objEdPg1.SetDateTime(1900, 1, 1, 0, 0, 0);
		break;
	case 4:	//完了
		//日付有効
		break;
	}

	switch(nCmp2){
	case 0:	//未実施
	case 1:	//対応中
	case 2: //待ち
	case 3:	//確認完
	case 5:	//保留
		//日付無効
		objEdPg2.SetDateTime(1900, 1, 1, 0, 0, 0);
		break;
	case 4:	//完了
		//日付有効
		break;
	}

	int nCmp = 0;
	if(objEdPg1 < objEdPg2){
		nCmp = bAspect ? 1 : -1;
	}else if(objEdPg1 > objEdPg2){
		nCmp = bAspect ? -1 : 1;
	}
	return nCmp;
}

void CToDoView::OnTimer(UINT nIDEvent){
	//定期削除監視
	COleDateTime objCur = COleDateTime::GetCurrentTime();
	int nYear = objCur.GetYear();
	int nMonth = objCur.GetMonth();
	int nDay = objCur.GetDay();
	objCur.SetDateTime(nYear, nMonth, nDay, 0, 0, 0);

	COleDateTimeSpan span = objCur - m_objPreChkDtm;
	if(span.GetDays() > 0){
		DelCheckToDo();
	}
	
	CView::OnTimer(nIDEvent);
}

void CToDoView::OnDestroy() 
{
	KillTimer(IDS_TODOCHKTIMER);
	CView::OnDestroy();
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	
}

void CToDoView::DelCheckToDo(){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CToDoView::DelCheckToDo : pFrm is null");
	}
	APPINFO objIni;
	pFrm->m_objIniFile.GetAppInfoIniData(objIni);
	if(!objIni.bEndToDoDel){
		return;
	}
	CPWikiDoc *pDoc = (CPWikiDoc*)GetDocument();
	COleDateTime objCur = COleDateTime::GetCurrentTime();
	int nYear = objCur.GetYear();
	int nMonth = objCur.GetMonth();
	int nDay = objCur.GetDay();
	objCur.SetDateTime(nYear, nMonth, nDay, 0, 0, 0);
	BOOL bDel = FALSE;
	//日付が変わった。
	int nSize = m_objList[0].GetItemCount();
	for(int i = 0; i < nSize; i++){
		CEventDate *pDate = (CEventDate*)m_objList[0].GetItemData(i);
		if(pDate->GetState() == 4){
			COleDateTime objStart;
			COleDateTime objEnd;
			pDate->GetProgress(&objStart, &objEnd);
			COleDateTimeSpan span = objCur - objEnd;
			if((span.GetDays()) >= objIni.nEndToDoDelSpan && (objCur > objEnd)){
				bDel = TRUE;
				pDoc->m_objToDoData.DelToDo(pDate);
				m_objList[0].SetItemData(i, NULL);
			}
		}
	}
	if(bDel){
		UpdateToDo();
	}

}

BOOL CToDoView::PreTranslateMessage(MSG* pMsg){
	int nActive = m_objTab.GetCurSel();
	int nIndex = -1;
	if((nActive != -1) && (nActive == TT_CHART)){
		if(pMsg->hwnd == m_objChartWnd.m_hWnd){
			switch(pMsg->message){
			case WM_LBUTTONDBLCLK:
				OnTodoEdit();
				return TRUE;
			}
		}
	}else if((nActive != -1) && (nActive != TT_CHART)){
		if(pMsg->hwnd == m_objList[nActive].m_hWnd){
			switch(pMsg->message){
			case WM_LBUTTONDBLCLK:
				OnTodoEdit();
				return TRUE;
			}
		}
	}
	return CView::PreTranslateMessage(pMsg);
}

void CToDoView::UpdateSetting(){
	m_objFont.DeleteObject();

	FONTINFO objFontInfo;
	CMainFrame *pFrm = GetMainFrame(this);
	pFrm->m_objIniFile.GetFontInfoIniData(objFontInfo);
	MakeFont(m_objFont, GetDC(), objFontInfo.szEtcFontName, objFontInfo.lEtcHeight);
	m_objTab.SetFont(&m_objFont);
	for(int i = 0; i < TT_END; i++){
		if(i == TT_CHART){
			m_objChartWnd.UpdateSetting();
		}else{
			m_objList[i].SetFont(&m_objFont);
		}
	}
}
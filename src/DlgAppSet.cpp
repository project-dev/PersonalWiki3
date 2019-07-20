// DlgAppSet.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "DlgAppSet.h"
#include "LogFile.h"
#include "MainFrm.h"
#include "CalView.h"
#include "ToDoView.h"
#include "InfoTabView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAppSet ダイアログ


CDlgAppSet::CDlgAppSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAppSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAppSet)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CDlgAppSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAppSet)
	DDX_Control(pDX, IDC_LIST, m_objList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAppSet, CDialog)
	//{{AFX_MSG_MAP(CDlgAppSet)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAppSet メッセージ ハンドラ

BOOL CDlgAppSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CLogFile::SaveAppLog("設定呼び出し");
	CDC* pDC = GetDC();
	
	m_objBmp.LoadBitmap(IDB_SETICON);

	int crBit = ::GetDeviceCaps(pDC->m_hDC, BITSPIXEL);
	UINT uColor = ILC_COLOR8;
	switch(crBit){
	case 16:
		uColor = ILC_COLOR8;
		break;
	case 32:
		uColor = ILC_COLOR16;
		break;
	}
	m_objImgList.Create(32, 32, uColor, 6, 1);
	m_objImgList.Add(&m_objBmp, RGB(0xFF, 0xFF, 0xFe));
	int tabIdx = 0;
	m_objList.InsertItem(tabIdx, "基本設定", 0);
	tabIdx++;
	m_objList.InsertItem(tabIdx, "情報バー", 6);
	tabIdx++;
	m_objList.InsertItem(tabIdx, "カレンダー設定", 1);
	tabIdx++;
	m_objList.InsertItem(tabIdx, "Wiki設定", 3);
	tabIdx++;
	m_objList.InsertItem(tabIdx, "フォント", 2);
	tabIdx++;
	m_objList.InsertItem(tabIdx, "プラグイン", 3);
	tabIdx++;
	m_objList.InsertItem(tabIdx, "MIME Type", 5);
	tabIdx++;
#if defined(USE_USB_DOC)
	m_objList.InsertItem(tabIdx, "外部連携", 3);
	tabIdx++;
#else
	m_objList.InsertItem(tabIdx, "デバッグ", 4);
	tabIdx++;
#endif
	m_objList.SetImageList(&m_objImgList, LVSIL_NORMAL);

	m_objSetPage1.Create(IDD_DLG_APP_SETPAGE1, this);
	m_objSetPage2.Create(IDD_DLG_APP_SETPAGE2, this);
	m_objSetPage3.Create(IDD_DLG_APP_SETPAGE3, this);
	m_objSetPage4.Create(IDD_DLG_APP_SETPAGE4, this);
	m_objSetPage5.Create(IDD_DLG_APP_SETPAGE5, this);
	m_objSetPage6.Create(IDD_DLG_APP_SETPAGE6, this);
	m_objSetPage7.Create(IDD_DLG_APP_SETPAGE7, this);
#if defined(USE_USB_DOC)
	m_objSetPage8.Create(IDD_DLG_APP_SETPAGE8, this);
#endif
	m_objSetPage9.Create(IDD_DLG_APP_SETPAGE9, this);

	SetActivePage();
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDlgAppSet::SetActivePage(){
	CWnd *arrWnd[] = {
		&m_objSetPage1, 
		&m_objSetPage9, 
		&m_objSetPage2, 
		&m_objSetPage3, 
		&m_objSetPage4, 
		&m_objSetPage5,
		&m_objSetPage7,
#if defined(USE_USB_DOC)
		&m_objSetPage8,
#endif
		&m_objSetPage6,
	};
	int nLen = sizeof(arrWnd) / sizeof(CWnd*);
	int nSelIndex = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED | LVNI_FOCUSED);
	int nMarkIndex = m_objList.GetSelectionMark();
	if(nSelIndex == -1){
		if(nMarkIndex == -1){
			nSelIndex = 0;
			m_objList.SetItemState(nSelIndex, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		}else{
			nSelIndex = nMarkIndex;
		}
	}

	CWnd* pWnd = GetDlgItem(IDC_VIEWAREA);
	if(!pWnd || !::IsWindow(pWnd->m_hWnd)){
		return;
	}
	
	CRect rect;
	pWnd->GetClientRect(rect);
	pWnd->MapWindowPoints(this, rect);

	CWnd *pTargetWnd;
	for(int nIndex = 0; nIndex < nLen; nIndex++){
		pTargetWnd = arrWnd[nIndex];
		if(!::IsWindow(pTargetWnd->m_hWnd)){
			continue;
		}
		if(nIndex == nSelIndex){
			pTargetWnd->SetRedraw(FALSE);
			pTargetWnd->ShowWindow(SW_SHOW);
			pTargetWnd->SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
			pTargetWnd->SetRedraw(TRUE);
			pTargetWnd->Invalidate();
		}else{
			pTargetWnd->ShowWindow(SW_HIDE);
		}
	}


}

void CDlgAppSet::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	*pResult = 0;
	SetActivePage();
}

void CDlgAppSet::OnOK(){
	m_objSetPage1.UpdateInfo();
	m_objSetPage2.UpdateInfo();
	m_objSetPage3.UpdateInfo();
	m_objSetPage4.UpdateInfo();
	m_objSetPage5.UpdateInfo();
	m_objSetPage6.UpdateInfo();
	m_objSetPage7.UpdateInfo();
#if defined(USE_USB_DOC)
	m_objSetPage8.UpdateInfo();
#endif
	m_objSetPage9.UpdateInfo();

	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgAppSet::OnItemchangedList : pFrm is null");
	}
	
	DEBUGINFO objDebug;
	pFrm->m_objIniFile.GetDebugInfoIniData(objDebug);
	CLogFile::SetLogState(objDebug.bLogOut);
	CLogFile::SetAppLogState(objDebug.bAppLogOut);
	CLogFile::SetFatalLogState(objDebug.bFatalLogOut);
	CLogFile::SetExceptLogState(objDebug.bExceptLogOut);

	int nCnt = pFrm->m_objPlugins.GetSize();
	for(int i = 0; i < nCnt; i++){
		CPWikiPlugin *pPlug = pFrm->m_objPlugins.GetPlugin(i);
		try{
			pPlug->SetLogFlag(objDebug.bLogOut, objDebug.bAppLogOut, objDebug.bExceptLogOut, objDebug.bFatalLogOut);
		}catch(CPWikiPluginException *pe){
			pe->Delete();
		}
	}

	CCalView* pCalView = pFrm->GetCalView();
	CToDoView* pToDo = pFrm->GetToDoView();
	CInfoTabView* pInfoTab = pFrm->GetInfoTabView();

	pCalView->UpdateSetting();
	pToDo->UpdateSetting();
	pInfoTab->UpdateSetting();

	CLogFile::SaveAppLog("設定完了");
	CDialog::OnOK();
}

BOOL CDlgAppSet::PreTranslateMessage(MSG* pMsg){
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

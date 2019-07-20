// DlgFixData.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "DlgFixData.h"
#include "MainFrm.h"
#include "PWikiDoc.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFixData ダイアログ


CDlgFixData::CDlgFixData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFixData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFixData)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CDlgFixData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFixData)
	DDX_Control(pDX, IDC_TAB, m_objTab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFixData, CDialog)
	//{{AFX_MSG_MAP(CDlgFixData)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFixData メッセージ ハンドラ

BOOL CDlgFixData::OnInitDialog() {
	CDialog::OnInitDialog();
	CLogFile::SaveAppLog("定期データ設定呼び出し");	
	
	// TODO: この位置に初期化の補足処理を追加してください
	m_objPage1.Create(IDD_FIXDATAPAGE1, &m_objTab);
	m_objPage2.Create(IDD_FIXDATAPAGE2, &m_objTab);
	m_objPage3.Create(IDD_FIXDATAPAGE3, &m_objTab);
	m_objPage4.Create(IDD_FIXDATAPAGE4, &m_objTab);
	m_objTab.InsertItem(0, "年間予定");
	m_objTab.InsertItem(1, "月間予定1");
	m_objTab.InsertItem(2, "月間予定2");
	m_objTab.InsertItem(3, "週間予定");
	SetActivePage();
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDlgFixData::SetActivePage(){
	int nSel = m_objTab.GetCurSel();
	CRect rect;
	m_objTab.GetClientRect(rect);
	m_objTab.AdjustRect(FALSE, rect);
	if(nSel == 0){
		m_objPage1.ShowWindow(SW_SHOW);
		m_objPage1.SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
	}else{
		m_objPage1.ShowWindow(SW_HIDE);
	}
	if(nSel == 1){
		m_objPage2.ShowWindow(SW_SHOW);
		m_objPage2.SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
	}else{
		m_objPage2.ShowWindow(SW_HIDE);
	}
	if(nSel == 2){
		m_objPage3.ShowWindow(SW_SHOW);
		m_objPage3.SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
	}else{
		m_objPage3.ShowWindow(SW_HIDE);
	}
	if(nSel == 3){
		m_objPage4.ShowWindow(SW_SHOW);
		m_objPage4.SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
	}else{
		m_objPage4.ShowWindow(SW_HIDE);
	}

}

void CDlgFixData::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult){
	*pResult = 0;
	SetActivePage();
}


void CDlgFixData::OnOK(){
	CDialog::OnOK();
	m_objPage1.OnDataSave();
	m_objPage2.OnDataSave();
	m_objPage3.OnDataSave();
	m_objPage4.OnDataSave();
}

BOOL CDlgFixData::PreTranslateMessage(MSG* pMsg){
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

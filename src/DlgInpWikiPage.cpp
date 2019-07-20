// DlgInpWikiPage.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "personalwiki.h"
#include "DlgInpWikiPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInpWikiPage ダイアログ


CDlgInpWikiPage::CDlgInpWikiPage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInpWikiPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInpWikiPage)
	m_strWikiName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgInpWikiPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInpWikiPage)
	DDX_Text(pDX, IDC_ED_NAME, m_strWikiName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInpWikiPage, CDialog)
	//{{AFX_MSG_MAP(CDlgInpWikiPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInpWikiPage メッセージ ハンドラ

void CDlgInpWikiPage::OnOK(){
	UpdateData();	
	CDialog::OnOK();
}

BOOL CDlgInpWikiPage::PreTranslateMessage(MSG* pMsg) {
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

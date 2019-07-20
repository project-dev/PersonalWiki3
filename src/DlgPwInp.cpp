// DlgPwInp.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "personalwiki.h"
#include "DlgPwInp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPwInp ダイアログ


CDlgPwInp::CDlgPwInp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPwInp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPwInp)
	m_strPassWord = _T("");
	//}}AFX_DATA_INIT
}


void CDlgPwInp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPwInp)
	DDX_Text(pDX, IDC_ED_PASSWORD, m_strPassWord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPwInp, CDialog)
	//{{AFX_MSG_MAP(CDlgPwInp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPwInp メッセージ ハンドラ

BOOL CDlgPwInp::PreTranslateMessage(MSG* pMsg){
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

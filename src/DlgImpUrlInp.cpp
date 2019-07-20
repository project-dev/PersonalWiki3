// DlgImpUrlInp.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "personalwiki.h"
#include "DlgImpUrlInp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgImpUrlInp ダイアログ


CDlgImpUrlInp::CDlgImpUrlInp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImpUrlInp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgImpUrlInp)
	m_strID = _T("");
	m_strPage = _T("");
	m_strPass = _T("");
	m_strUrl = _T("");
	//}}AFX_DATA_INIT
}


void CDlgImpUrlInp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgImpUrlInp)
	DDX_Text(pDX, IDC_ED_ID, m_strID);
	DDX_Text(pDX, IDC_ED_PAGE, m_strPage);
	DDX_Text(pDX, IDC_ED_PW, m_strPass);
	DDX_Text(pDX, IDC_ED_URL, m_strUrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgImpUrlInp, CDialog)
	//{{AFX_MSG_MAP(CDlgImpUrlInp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgImpUrlInp メッセージ ハンドラ

// DlgPluginExport.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "personalwiki.h"
#include "DlgPluginExport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPluginExport ダイアログ


CDlgPluginExport::CDlgPluginExport(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPluginExport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPluginExport)
	m_strWikiPath = _T("");
	//}}AFX_DATA_INIT
}


void CDlgPluginExport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPluginExport)
	DDX_Control(pDX, IDC_CMB_EXPORT, m_objExpCmb);
	DDX_Text(pDX, IDC_ED_WIKIPATH, m_strWikiPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPluginExport, CDialog)
	//{{AFX_MSG_MAP(CDlgPluginExport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPluginExport メッセージ ハンドラ

BOOL CDlgPluginExport::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください

	int nSize = m_arrPluginName.GetSize();
	for(int i = 0; i < nSize; i++){
		m_objExpCmb.AddString(m_arrPluginName.GetAt(i));
	}
	m_objExpCmb.SetCurSel(0);

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDlgPluginExport::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	m_objExpCmb.GetWindowText(m_strSelPlugin);
	CDialog::OnOK();
}

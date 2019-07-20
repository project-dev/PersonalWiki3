// DlgDateInp.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "DlgDateInp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDateInp ダイアログ


CDlgDateInp::CDlgDateInp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDateInp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDateInp)
	m_strDetail = _T("");
	m_strHelp = _T("");
	//}}AFX_DATA_INIT
}


void CDlgDateInp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDateInp)
//	DDX_Control(pDX, IDC_CMB_CATEGORY, m_objCmbCategory);
	DDX_Text(pDX, IDC_ED_DETAIL, m_strDetail);
	DDX_Text(pDX, IDC_ED_HELP, m_strHelp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDateInp, CDialog)
	//{{AFX_MSG_MAP(CDlgDateInp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDateInp メッセージ ハンドラ

BOOL CDlgDateInp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	CString strTitle;
	strTitle.Format("%sの予定入力", m_ojbDate.Format("%Y/%m/%d"));
	SetWindowText(strTitle);
	m_strHelp = "書式についてのヘルプ\r\n"
				"Wiki形式の書式で文字列に装飾を施したり出来ます。\r\n"
				"\r\n"
				"■太字\r\n"
				"選択文字列を太字にします。\r\n"
				"　''文字列''\r\n"
				"\r\n"
				"■斜体\r\n"
				"選択文字列を斜体にします。\r\n"
				"　'''文字列'''\r\n"
				"\r\n"
				"■打ち消し線\r\n"
				"選択文字列を打ち消します。\r\n"
				"　%%%文字列%%%\r\n"
				"\r\n"
				"■リンク\r\n"
				"選択文字列をリンクにします。\r\n"
				"　[[URL]]\r\n"
				"　[[名前:URL]]\r\n"
				"　[[YYYY/MM/DD形式]]\r\n"
				"\r\n"
				"■画像\r\n"
				"画像を表示します。\r\n"
				"　&img{ファイル名};\r\n";

	UpdateData(FALSE);


	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

BOOL CDlgDateInp::PreTranslateMessage(MSG* pMsg){
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

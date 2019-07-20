#if !defined(AFX_DLGDATEINP_H__379FE3DA_0AEC_4D6A_8BE1_E1BF60601C78__INCLUDED_)
#define AFX_DLGDATEINP_H__379FE3DA_0AEC_4D6A_8BE1_E1BF60601C78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDateInp.h : ヘッダー ファイル
//

#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDateInp ダイアログ

class CDlgDateInp : public CDialog, CAbstractBaseWnd
{
// コンストラクション
public:
	CDlgDateInp(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgDateInp)
	enum { IDD = IDD_DLGINPDATE };
//	CComboBox	m_objCmbCategory;
	CString	m_strDetail;
	CString	m_strHelp;
	//}}AFX_DATA

	COleDateTime m_ojbDate;

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgDateInp)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgDateInp)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGDATEINP_H__379FE3DA_0AEC_4D6A_8BE1_E1BF60601C78__INCLUDED_)

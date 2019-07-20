#if !defined(AFX_DLGPWINP_H__32BD1111_D57F_49E1_934C_D9562D841EEA__INCLUDED_)
#define AFX_DLGPWINP_H__32BD1111_D57F_49E1_934C_D9562D841EEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPwInp.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPwInp ダイアログ

#include "AbstractWnd.h"

class CDlgPwInp : public CDialog, CAbstractWnd
{
// コンストラクション
public:
	CDlgPwInp(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgPwInp)
	enum { IDD = IDD_DLG_PW_INP };
	CString	m_strPassWord;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgPwInp)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgPwInp)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGPWINP_H__32BD1111_D57F_49E1_934C_D9562D841EEA__INCLUDED_)

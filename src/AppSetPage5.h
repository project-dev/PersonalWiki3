#if !defined(AFX_APPSETPAGE5_H__B9276E64_197C_4CA5_9DDD_8825DF521C2C__INCLUDED_)
#define AFX_APPSETPAGE5_H__B9276E64_197C_4CA5_9DDD_8825DF521C2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage5.h : ヘッダー ファイル
//
#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage5 ダイアログ

class CAppSetPage5 : public CDialog, CAbstractBaseWnd
{
// コンストラクション
public:
	BOOL UpdateInfo();
	CAppSetPage5(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CAppSetPage5)
	enum { IDD = IDD_DLG_APP_SETPAGE5 };
	CListCtrl	m_objList;
	CString	m_strDetail;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAppSetPage5)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAppSetPage5)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPlgSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_APPSETPAGE5_H__B9276E64_197C_4CA5_9DDD_8825DF521C2C__INCLUDED_)

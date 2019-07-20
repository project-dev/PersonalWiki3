#if !defined(AFX_APPSETPAGE9_H__4A9C997B_C3B9_41FB_AFBF_CDA6C7C62058__INCLUDED_)
#define AFX_APPSETPAGE9_H__4A9C997B_C3B9_41FB_AFBF_CDA6C7C62058__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage9.h : ヘッダー ファイル
//
#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage9 ダイアログ

class CAppSetPage9 : public CDialog, CAbstractBaseWnd
{
// コンストラクション
public:
	void UpdateInfo();
	CAppSetPage9(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CAppSetPage9)
	enum { IDD = IDD_DLG_APP_SETPAGE9 };
	BOOL	m_bShowSec;
	BOOL	m_bShowSc;
	BOOL	m_bShowTodo;
	BOOL	m_bShowTime;
	BOOL	m_bShowFix;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAppSetPage9)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAppSetPage9)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_APPSETPAGE9_H__4A9C997B_C3B9_41FB_AFBF_CDA6C7C62058__INCLUDED_)

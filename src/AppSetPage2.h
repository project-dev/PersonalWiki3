#if !defined(AFX_APPSETPAGE2_H__7BC5EB2F_04FE_48B7_88FA_157129418E94__INCLUDED_)
#define AFX_APPSETPAGE2_H__7BC5EB2F_04FE_48B7_88FA_157129418E94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage2.h : ヘッダー ファイル
//
#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage2 ダイアログ

class CAppSetPage2 : public CDialog, CAbstractBaseWnd
{
// コンストラクション
public:
	BOOL UpdateInfo();
	CAppSetPage2(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CAppSetPage2)
	enum { IDD = IDD_DLG_APP_SETPAGE2 };
	CListCtrl	m_objSpDayList;
	BOOL	m_bFri;
	BOOL	m_bMon;
	BOOL	m_bSat;
	BOOL	m_bSun;
	BOOL	m_bThu;
	BOOL	m_bTue;
	BOOL	m_bWed;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAppSetPage2)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAppSetPage2)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_APPSETPAGE2_H__7BC5EB2F_04FE_48B7_88FA_157129418E94__INCLUDED_)

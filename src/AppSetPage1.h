#if !defined(AFX_APPSETPAGE1_H__9742F6E2_CDE8_4AA8_8C91_F3AA6DD85580__INCLUDED_)
#define AFX_APPSETPAGE1_H__9742F6E2_CDE8_4AA8_8C91_F3AA6DD85580__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage1.h : ヘッダー ファイル
//
#include "AbstractBaseWnd.h"
/////////////////////////////////////////////////////////////////////////////
// CAppSetPage1 ダイアログ

class CAppSetPage1 : public CDialog, CAbstractBaseWnd
{
// コンストラクション
public:
	BOOL UpdateInfo();
	CAppSetPage1(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CAppSetPage1)
	enum { IDD = IDD_DLG_APP_SETPAGE1 };
	CListBox	m_objCtgList;
	BOOL	m_bEndToDoDel;
	int		m_nEndToDoDelSpan;
	BOOL	m_bUsePassWord;
	CString	m_strPassWord;
	CString	m_strCategory;
	BOOL	m_bUseToDay;
	BOOL	m_bRunMainWndShow;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAppSetPage1)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAppSetPage1)
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnMod();
	afx_msg void OnSelchangeCategorylist();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_APPSETPAGE1_H__9742F6E2_CDE8_4AA8_8C91_F3AA6DD85580__INCLUDED_)

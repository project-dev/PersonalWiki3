#if !defined(AFX_APPSETPAGE7_H__FAC632CA_5242_435F_8920_0EF66565DA26__INCLUDED_)
#define AFX_APPSETPAGE7_H__FAC632CA_5242_435F_8920_0EF66565DA26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage7.h : ヘッダー ファイル
//
#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage7 ダイアログ

class CAppSetPage7 : public CDialog, CAbstractBaseWnd
{
// コンストラクション
public:
	void UpdateInfo();
	CAppSetPage7(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CAppSetPage7)
	enum { IDD = IDD_DLG_APP_SETPAGE7 };
	CListCtrl	m_objList;
	CString	m_strExt;
	CString	m_strMIME;
	BOOL	m_bUse;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAppSetPage7)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAppSetPage7)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnMod();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_APPSETPAGE7_H__FAC632CA_5242_435F_8920_0EF66565DA26__INCLUDED_)

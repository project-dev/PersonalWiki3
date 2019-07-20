#if !defined(AFX_DLGFIXDATAPAGE4_H__F44F7C18_385B_4B36_B497_0E2AFC06F1BD__INCLUDED_)
#define AFX_DLGFIXDATAPAGE4_H__F44F7C18_385B_4B36_B497_0E2AFC06F1BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFixDataPage4.h : ヘッダー ファイル
//
#include "AbstractBaseWnd.h"
#include <AfxTempl.h>
#include "EventDate.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgFixDataPage4 ダイアログ

class CDlgFixDataPage4 : public CDialog, CAbstractBaseWnd
{
// コンストラクション
public:
	void OnDataSave();
	CDlgFixDataPage4(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgFixDataPage4)
	enum { IDD = IDD_FIXDATAPAGE4 };
	CListCtrl	m_objList;
	BOOL	m_bMon;
	BOOL	m_bFri;
	BOOL	m_bSat;
	BOOL	m_bSun;
	BOOL	m_bThu;
	BOOL	m_bTue;
	BOOL	m_bWed;
	CString	m_strData;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgFixDataPage4)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgFixDataPage4)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnMod();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CArray<CEventDate*, CEventDate*> m_arrDelList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGFIXDATAPAGE4_H__F44F7C18_385B_4B36_B497_0E2AFC06F1BD__INCLUDED_)

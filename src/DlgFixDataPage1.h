#if !defined(AFX_DLGFIXDATAPAGE1_H__1FA35AF8_8C28_49D8_88AB_ADB7E77354F7__INCLUDED_)
#define AFX_DLGFIXDATAPAGE1_H__1FA35AF8_8C28_49D8_88AB_ADB7E77354F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFixDataPage1.h : ヘッダー ファイル
//
#include "AbstractBaseWnd.h"
#include <AfxTempl.h>
/////////////////////////////////////////////////////////////////////////////
// CDlgFixDataPage1 ダイアログ
class CEventDate;
class CDlgFixDataPage1 : public CDialog , CAbstractBaseWnd
{
// コンストラクション
public:
	void OnDataSave();
	CDlgFixDataPage1(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgFixDataPage1)
	enum { IDD = IDD_FIXDATAPAGE1 };
	CComboBox	m_objCmbOption;
	CListCtrl	m_objList;
	CString	m_strData;
	int		m_nDay;
	int		m_nMonth;
	BOOL	m_bHoliday;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgFixDataPage1)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgFixDataPage1)
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

#endif // !defined(AFX_DLGFIXDATAPAGE1_H__1FA35AF8_8C28_49D8_88AB_ADB7E77354F7__INCLUDED_)

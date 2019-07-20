#if !defined(AFX_DLGFIXDATA_H__59790931_7651_46E9_8E16_2E39A88C3C12__INCLUDED_)
#define AFX_DLGFIXDATA_H__59790931_7651_46E9_8E16_2E39A88C3C12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFixData.h : ヘッダー ファイル
//
#include "DlgFixDataPage1.h"
#include "DlgFixDataPage2.h"
#include "DlgFixDataPage3.h"
#include "DlgFixDataPage4.h"
#include "AbstractWnd.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgFixData ダイアログ

class CDlgFixData : public CDialog, CAbstractWnd
{
// コンストラクション
public:
	void SetActivePage();
	CDlgFixData(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgFixData)
	enum { IDD = IDD_DlgFixedData };
	CTabCtrl	m_objTab;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgFixData)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgFixData)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CDlgFixDataPage1 m_objPage1;
	CDlgFixDataPage2 m_objPage2;
	CDlgFixDataPage3 m_objPage3;
	CDlgFixDataPage4 m_objPage4;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGFIXDATA_H__59790931_7651_46E9_8E16_2E39A88C3C12__INCLUDED_)

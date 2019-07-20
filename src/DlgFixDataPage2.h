#if !defined(AFX_DLGFIXDATAPAGE2_H__EEF9FBF3_C9D4_4748_8BD5_A30AE80A4151__INCLUDED_)
#define AFX_DLGFIXDATAPAGE2_H__EEF9FBF3_C9D4_4748_8BD5_A30AE80A4151__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFixDataPage2.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFixDataPage2 ダイアログ
#include "AbstractBaseWnd.h"

class CDlgFixDataPage2 : public CDialog, CAbstractBaseWnd
{
// コンストラクション
public:
	void OnDataSave();
	CDlgFixDataPage2(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgFixDataPage2)
	enum { IDD = IDD_FIXDATAPAGE2 };
	CListCtrl	m_objList;
	CString	m_strData;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgFixDataPage2)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgFixDataPage2)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnMod();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGFIXDATAPAGE2_H__EEF9FBF3_C9D4_4748_8BD5_A30AE80A4151__INCLUDED_)

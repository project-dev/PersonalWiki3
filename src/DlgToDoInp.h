#if !defined(AFX_DLGTODOINP_H__C7B3C282_E986_4A06_BD5B_2DB9732E5367__INCLUDED_)
#define AFX_DLGTODOINP_H__C7B3C282_E986_4A06_BD5B_2DB9732E5367__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgToDoInp.h : ヘッダー ファイル
//

#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgToDoInp ダイアログ

class CDlgToDoInp : public CDialog, CAbstractBaseWnd
{
// コンストラクション
public:
	CDlgToDoInp(CWnd* pParent = NULL);   // 標準のコンストラクタ
	CString m_strCategory;
// ダイアログ データ
	//{{AFX_DATA(CDlgToDoInp)
	enum { IDD = IDD_DLGINPTODO };
	CComboBox	m_objCmbState;
	CComboBox	m_objCmbCategory;
	COleDateTime	m_objPlanEnd;
	COleDateTime	m_objPlanStart;
	COleDateTime	m_objProgressEnd;
	COleDateTime	m_objProgressStart;
	CString	m_strDetail;
	CString	m_strName;
	double	m_dProcessPar;
	int		m_nState;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgToDoInp)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgToDoInp)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelendokCmbState();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGTODOINP_H__C7B3C282_E986_4A06_BD5B_2DB9732E5367__INCLUDED_)

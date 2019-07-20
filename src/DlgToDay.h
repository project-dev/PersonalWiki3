#if !defined(AFX_DLGTODAY_H__542B78E8_73BF_44DA_B261_603300091B03__INCLUDED_)
#define AFX_DLGTODAY_H__542B78E8_73BF_44DA_B261_603300091B03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgToDay.h : ヘッダー ファイル
//
#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgToDay ダイアログ

class CDlgToDay : public CDialog, CAbstractBaseWnd
{
// コンストラクション
public:
	void UpdateToDay();
	CDlgToDay(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgToDay)
	enum { IDD = IDD_DLG_TODAY };
	CString	m_strToDay;
	CString	m_strNextDay;
	CString	m_strNextNextDay;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgToDay)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgToDay)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGTODAY_H__542B78E8_73BF_44DA_B261_603300091B03__INCLUDED_)

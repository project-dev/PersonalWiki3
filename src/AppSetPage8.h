#if !defined(AFX_APPSETPAGE8_H__EBD86DE1_50C2_4F4E_84A5_5ABECCA1574C__INCLUDED_)
#define AFX_APPSETPAGE8_H__EBD86DE1_50C2_4F4E_84A5_5ABECCA1574C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage8.h : ヘッダー ファイル
//
#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage8 ダイアログ

class CAppSetPage8 : public CDialog, CAbstractBaseWnd
{
// コンストラクション
public:
	void UpdateInfo();
	CAppSetPage8(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CAppSetPage8)
	enum { IDD = IDD_DLG_APP_SETPAGE8 };
	BOOL	m_bUseUSBLink;
	CString	m_strPath1;
	CString	m_strPath2;
	CString	m_strPath3;
	CString	m_strPath4;
	BOOL	m_bUseNetDrv;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAppSetPage8)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAppSetPage8)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_APPSETPAGE8_H__EBD86DE1_50C2_4F4E_84A5_5ABECCA1574C__INCLUDED_)

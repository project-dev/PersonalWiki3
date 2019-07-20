#if !defined(AFX_APPSETPAGE3_H__3ECCA135_82FD_4453_AE01_FBE4405B63FA__INCLUDED_)
#define AFX_APPSETPAGE3_H__3ECCA135_82FD_4453_AE01_FBE4405B63FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage3.h : ヘッダー ファイル
//
#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage3 ダイアログ

class CAppSetPage3 : public CDialog, CAbstractBaseWnd
{
// コンストラクション
public:
	void FindCSS();
	BOOL UpdateInfo();
	CAppSetPage3(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CAppSetPage3)
	enum { IDD = IDD_DLG_APP_SETPAGE3 };
	CComboBox	m_objCmbCss;
	BOOL	m_bUseRet;
	BOOL	m_bUseTBLink;
	BOOL	m_bShowAttach;
	BOOL	m_bUseConvTime;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAppSetPage3)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAppSetPage3)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_APPSETPAGE3_H__3ECCA135_82FD_4453_AE01_FBE4405B63FA__INCLUDED_)

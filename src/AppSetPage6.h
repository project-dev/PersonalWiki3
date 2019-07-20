#if !defined(AFX_APPSETPAGE6_H__573B8B63_0764_4D20_B29C_8BBDC410E782__INCLUDED_)
#define AFX_APPSETPAGE6_H__573B8B63_0764_4D20_B29C_8BBDC410E782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage6.h : ヘッダー ファイル
//
#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage6 ダイアログ

class CAppSetPage6 : public CDialog, CAbstractBaseWnd
{
// コンストラクション
public:
	BOOL UpdateInfo();
	CAppSetPage6(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CAppSetPage6)
	enum { IDD = IDD_DLG_APP_SETPAGE6 };
	BOOL	m_bUseFatalLog;
	BOOL	m_bUseStateLog;
	BOOL	m_bUseLog;
	BOOL	m_bUseExceptLog;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAppSetPage6)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAppSetPage6)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_APPSETPAGE6_H__573B8B63_0764_4D20_B29C_8BBDC410E782__INCLUDED_)

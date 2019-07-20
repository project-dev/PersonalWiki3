#if !defined(AFX_DLGINPWIKIPAGE_H__1B0F23F7_C11E_4185_8FAC_869475DC5055__INCLUDED_)
#define AFX_DLGINPWIKIPAGE_H__1B0F23F7_C11E_4185_8FAC_869475DC5055__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInpWikiPage.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInpWikiPage ダイアログ
#include "AbstractBaseWnd.h"
class CDlgInpWikiPage : public CDialog, CAbstractBaseWnd
{
// コンストラクション
public:
	CDlgInpWikiPage(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgInpWikiPage)
	enum { IDD = IDD_DLG_INPWIKIPAGE };
	CString	m_strWikiName;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgInpWikiPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgInpWikiPage)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGINPWIKIPAGE_H__1B0F23F7_C11E_4185_8FAC_869475DC5055__INCLUDED_)

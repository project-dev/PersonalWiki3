#if !defined(AFX_DLGAPPSET_H__EA309C4E_6FD0_43A9_9D05_347444CB0224__INCLUDED_)
#define AFX_DLGAPPSET_H__EA309C4E_6FD0_43A9_9D05_347444CB0224__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAppSet.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAppSet ダイアログ

#include "AppSetPage1.h"
#include "AppSetPage2.h"
#include "AppSetPage3.h"
#include "AppSetPage4.h"
#include "AppSetPage5.h"
#include "AppSetPage6.h"
#include "AppSetPage7.h"
#include "AppSetPage8.h"
#include "AppSetPage9.h"

class CDlgAppSet : public CDialog, CAbstractBaseWnd{
// コンストラクション
public:
	void SetActivePage();
	CDlgAppSet(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgAppSet)
	enum { IDD = IDD_DLG_APP_SET };
	CListCtrl	m_objList;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgAppSet)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgAppSet)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CImageList m_objImgList;
	CBitmap m_objBmp;
	CAppSetPage1 m_objSetPage1;
	CAppSetPage2 m_objSetPage2;
	CAppSetPage3 m_objSetPage3;
	CAppSetPage4 m_objSetPage4;
	CAppSetPage5 m_objSetPage5;
	CAppSetPage6 m_objSetPage6;
	CAppSetPage7 m_objSetPage7;
	CAppSetPage8 m_objSetPage8;
	CAppSetPage9 m_objSetPage9;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGAPPSET_H__EA309C4E_6FD0_43A9_9D05_347444CB0224__INCLUDED_)

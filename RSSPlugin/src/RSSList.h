#if !defined(AFX_RSSLIST_H__F7A9B9D9_C996_4774_8D5E_BC702867E478__INCLUDED_)
#define AFX_RSSLIST_H__F7A9B9D9_C996_4774_8D5E_BC702867E478__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSSList.h : ヘッダー ファイル
//

#include "AbstractWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CRSSList ウィンドウ
class CRssWnd;

class CRSSList : public CListCtrl, CAbstractWnd{
// コンストラクション
public:
	CRSSList();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CRSSList)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CRSSList();
	CRssWnd* m_pRssWnd;

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CRSSList)
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReadrss();
	afx_msg void OnUpdateReadrss(CCmdUI* pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_RSSLIST_H__F7A9B9D9_C996_4774_8D5E_BC702867E478__INCLUDED_)

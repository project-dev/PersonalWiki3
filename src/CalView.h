#if !defined(AFX_CALVIEW_H__05DECB02_381C_495C_8BB2_C83E88F0C14B__INCLUDED_)
#define AFX_CALVIEW_H__05DECB02_381C_495C_8BB2_C83E88F0C14B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalView.h : ヘッダー ファイル
//
#include <afxdtctl.h>
#include "AbstractBaseWnd.h"
#include "CalenderWnd.h"
#include "WikiWnd.h"
#include "FindWnd.h"



#define USE_DEVLIB_TAB


#if defined(USE_DEVLIB_TAB)
#include "HwndTabCtrl.h"
#endif
/////////////////////////////////////////////////////////////////////////////
// CCalView ビュー
class CEventDate;
class CCalView : public CView, CAbstractBaseWnd{
protected:
	CCalView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CCalView)

// アトリビュート
public:

// オペレーション
public:
	void UpdateShowPluginTab();
	void ActiveWikiPage(LPCTSTR pszWikiPath);
	void SetCtrlPos();
//	void UpdateInfo();
	void UpdateCalender();
	void UpdateWikiTree(BOOL bUSBTree = FALSE);
	CWikiWnd* GetWikiWnd();
	virtual void UpdateSetting();
// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CCalView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CCalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CCalView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
#if !defined(USE_DEVLIB_TAB)
	afx_msg void OnTabChange(LPNMHDR pNmhdr, HRESULT *pResult);
#endif
	DECLARE_MESSAGE_MAP()
#if defined(USE_DEVLIB_TAB)
	CHwndTabCtrl	m_objTab;
#else
	CTabCtrl	m_objTab;
#endif
	CCalenderWnd m_objCalWnd;
	CWikiWnd m_objWikiWnd;
	CFindWnd m_objFindWnd;
	CFont m_objFont;
	CRect m_objTabRect;
private:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CALVIEW_H__05DECB02_381C_495C_8BB2_C83E88F0C14B__INCLUDED_)

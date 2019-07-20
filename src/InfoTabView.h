#if !defined(AFX_INFOTABVIEW_H__1FB677CE_564B_448D_B150_DE36EC1E24A4__INCLUDED_)
#define AFX_INFOTABVIEW_H__1FB677CE_564B_448D_B150_DE36EC1E24A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoTabView.h : ヘッダー ファイル
//
#include "AbstractWikiWnd.h"
#include "WndTabCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CInfoTabView ビュー
#include "WikiEditWnd.h"
#include "InfoView.h"

class CInfoTabView : public CView, CAbstractWikiWnd{
protected:
	CInfoTabView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CInfoTabView)

// アトリビュート
public:

// オペレーション
public:
	BOOL CreateChildWnd();
	void GetHtmlHead(CString &strHtml, LPCTSTR pszTitle);
	void UpdateInfo(COleDateTime *pDate);
	void UpdateInfo(CString &strWikiPath);
	void UpdateInfoUSB(CString &strBasePath, LPCTSTR pszBasePath);
	virtual void UpdateSetting();
// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CInfoTabView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CInfoTabView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
protected:
	CWndTabCtrl	m_objTab;
	CFont m_objFont;
	CRect m_objTabRect;
	//{{AFX_MSG(CInfoTabView)
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnWikiBold();
	afx_msg void OnUpdateWikiBold(CCmdUI* pCmdUI);
	afx_msg void OnWikiHead();
	afx_msg void OnUpdateWikiHead(CCmdUI* pCmdUI);
	afx_msg void OnWikiHline();
	afx_msg void OnUpdateWikiHline(CCmdUI* pCmdUI);
	afx_msg void OnWikiItalic();
	afx_msg void OnUpdateWikiItalic(CCmdUI* pCmdUI);
	afx_msg void OnWikiLink();
	afx_msg void OnUpdateWikiLink(CCmdUI* pCmdUI);
	afx_msg void OnWikiList();
	afx_msg void OnUpdateWikiList(CCmdUI* pCmdUI);
	afx_msg void OnWikiNumlist();
	afx_msg void OnUpdateWikiNumlist(CCmdUI* pCmdUI);
	afx_msg void OnWikiRet();
	afx_msg void OnUpdateWikiRet(CCmdUI* pCmdUI);
	afx_msg void OnWikiStrike();
	afx_msg void OnUpdateWikiStrike(CCmdUI* pCmdUI);
	afx_msg void OnWikiUnderline();
	afx_msg void OnUpdateWikiUnderline(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg long OnHwndTabChange(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTabChange(LPNMHDR pNmhdr, HRESULT *pResult);
	DECLARE_MESSAGE_MAP()
private:
	CWikiEditWnd* m_pEditWnd;
	CInfoView* m_pHtmlView;

	void SetCtrlPos();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_INFOTABVIEW_H__1FB677CE_564B_448D_B150_DE36EC1E24A4__INCLUDED_)

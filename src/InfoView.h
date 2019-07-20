#if !defined(AFX_INFOVIEW_H__564914E9_7B14_45ED_924E_029E2E33EF10__INCLUDED_)
#define AFX_INFOVIEW_H__564914E9_7B14_45ED_924E_029E2E33EF10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FixHtmlView.h"

// InfoView.h : ヘッダー ファイル
//
/////////////////////////////////////////////////////////////////////////////
// CInfoView HTML ビュー

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>
#include "AnalisysWiki.h"
#include "AbstractWikiWnd.h"

class CInfoView : public CFixHtmlView, CAbstractWikiWnd{
protected:
	CInfoView();           // 動的生成で使用される protected コンストラクタ
	DECLARE_DYNCREATE(CInfoView)

// html Data
public:
	//{{AFX_DATA(CInfoView)
		// メモ: この位置に ClassWizard によってデータ メンバが追加されます。
	//}}AFX_DATA

// アトリビュート
public:

// オペレーション
public:
	void GetHtmlHead(CString &strHtml, LPCTSTR pszTitle);
/*
	void UpdateInfo(COleDateTime *pDate);
	void UpdateInfo(CString &strWikiPath);
	void UpdateInfoUSB(CString &strBasePath, LPCTSTR pszBasePath);
*/
// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CInfoView)
	public:
	virtual void OnInitialUpdate();
	virtual void OnDownloadBegin();
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CInfoView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CAnalisysWiki m_objAnalisys;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_INFOVIEW_H__564914E9_7B14_45ED_924E_029E2E33EF10__INCLUDED_)

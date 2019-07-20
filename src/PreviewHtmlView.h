#if !defined(AFX_PREVIEWHTMLVIEW_H__65EF8D43_0A43_48FF_AB8B_1BEADF2FA1BE__INCLUDED_)
#define AFX_PREVIEWHTMLVIEW_H__65EF8D43_0A43_48FF_AB8B_1BEADF2FA1BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreviewHtmlView.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CPreviewHtmlView HTML ビュー

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>
#include "AbstractBaseWnd.h"

class CPreviewHtmlView : public CHtmlView, CAbstractBaseWnd
{
protected:
	CPreviewHtmlView();           // 動的生成で使用される protected コンストラクタ
	DECLARE_DYNCREATE(CPreviewHtmlView)

// html Data
public:
	//{{AFX_DATA(CPreviewHtmlView)
		// メモ: この位置に ClassWizard によってデータ メンバが追加されます。
	//}}AFX_DATA

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CPreviewHtmlView)
	public:
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CPreviewHtmlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CPreviewHtmlView)
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PREVIEWHTMLVIEW_H__65EF8D43_0A43_48FF_AB8B_1BEADF2FA1BE__INCLUDED_)

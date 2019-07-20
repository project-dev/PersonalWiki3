#if !defined(AFX_FIXHTMLVIEW_H__36306C70_FFD5_4E10_B5B3_0ECA329904F9__INCLUDED_)
#define AFX_FIXHTMLVIEW_H__36306C70_FFD5_4E10_B5B3_0ECA329904F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FixHtmlView.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CFixHtmlView HTML ビュー

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

class CFixHtmlView : public CHtmlView
{
protected:
	CFixHtmlView();           // 動的生成で使用される protected コンストラクタ
	DECLARE_DYNCREATE(CFixHtmlView)

// html Data
public:
	//{{AFX_DATA(CFixHtmlView)
		// メモ: この位置に ClassWizard によってデータ メンバが追加されます。
	//}}AFX_DATA

	//CHtmlViewのバグ対応 http://support.microsoft.com/kb/241750/ja
    CString GetFullName() const;
    CString GetType() const;
    CString GetLocationName() const;
    CString GetLocationURL() const;

    void Navigate(LPCTSTR lpszURL, DWORD dwFlags = 0 ,  
                  LPCTSTR lpszTargetFrameName = NULL ,  
                  LPCTSTR lpszHeaders = NULL, LPVOID lpvPostData = NULL,  
                  DWORD dwPostDataLen = 0);
    BOOL LoadFromResource(LPCTSTR lpszResource);
    BOOL LoadFromResource(UINT nRes);

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CFixHtmlView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CFixHtmlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CFixHtmlView)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_FIXHTMLVIEW_H__36306C70_FFD5_4E10_B5B3_0ECA329904F9__INCLUDED_)

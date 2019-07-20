#if !defined(AFX_DLGWIKIPROP_H__1DAF6431_547E_4034_A850_59D55582A6D3__INCLUDED_)
#define AFX_DLGWIKIPROP_H__1DAF6431_547E_4034_A850_59D55582A6D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWikiProp.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWikiProp ダイアログ

class CDlgWikiProp : public CDialog{
// コンストラクション
public:
	CDlgWikiProp(CWnd* pParent = NULL);   // 標準のコンストラクタ
	CString m_strRealPath;

// ダイアログ データ
	//{{AFX_DATA(CDlgWikiProp)
	enum { IDD = IDD_DLG_WIKI_PROP };
	BOOL	m_bCold;
	BOOL	m_bCrypt;
	COleDateTime	m_objUpdateDt;
	COleDateTime	m_objCreateDt;
	CString	m_strWikiPath;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgWikiProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgWikiProp)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CString m_strPropFile;
	BOOL m_bPreCrypt;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGWIKIPROP_H__1DAF6431_547E_4034_A850_59D55582A6D3__INCLUDED_)

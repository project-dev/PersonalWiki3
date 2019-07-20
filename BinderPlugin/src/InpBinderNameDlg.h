#if !defined(AFX_INPBINDERNAMEDLG_H__5B522644_B7F6_4781_8E07_9C342175FEB3__INCLUDED_)
#define AFX_INPBINDERNAMEDLG_H__5B522644_B7F6_4781_8E07_9C342175FEB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InpBinderNameDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CInpBinderNameDlg ダイアログ

class CInpBinderNameDlg : public CDialog
{
// コンストラクション
public:
	CInpBinderNameDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CInpBinderNameDlg)
	enum { IDD = IDD_INP_BINDER_NAME_DLG };
	CString	m_strName;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CInpBinderNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CInpBinderNameDlg)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_INPBINDERNAMEDLG_H__5B522644_B7F6_4781_8E07_9C342175FEB3__INCLUDED_)

#if !defined(AFX_DLGIMPURLINP_H__CFD0C665_0830_47D7_B4E3_44BDC6CA3D36__INCLUDED_)
#define AFX_DLGIMPURLINP_H__CFD0C665_0830_47D7_B4E3_44BDC6CA3D36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgImpUrlInp.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDlgImpUrlInp ダイアログ

class CDlgImpUrlInp : public CDialog
{
// コンストラクション
public:
	CDlgImpUrlInp(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgImpUrlInp)
	enum { IDD = IDD_DLGURLIMP };
	CString	m_strID;
	CString	m_strPage;
	CString	m_strPass;
	CString	m_strUrl;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgImpUrlInp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgImpUrlInp)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGIMPURLINP_H__CFD0C665_0830_47D7_B4E3_44BDC6CA3D36__INCLUDED_)

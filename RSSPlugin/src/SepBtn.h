#if !defined(AFX_SEPBTN_H__AC4CB803_6FFA_4284_85D9_0CC12D02E6A6__INCLUDED_)
#define AFX_SEPBTN_H__AC4CB803_6FFA_4284_85D9_0CC12D02E6A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SepBtn.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSepBtn ウィンドウ

class CSepBtn : public CButton
{
// コンストラクション
public:
	CSepBtn();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSepBtn)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	void SetSepalatorUD(CWnd *pUp, CWnd *pDown);
	virtual ~CSepBtn();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CSepBtn)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	CWnd* m_pUpWnd;
	CWnd* m_pDwWnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SEPBTN_H__AC4CB803_6FFA_4284_85D9_0CC12D02E6A6__INCLUDED_)

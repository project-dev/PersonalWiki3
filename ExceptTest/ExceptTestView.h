// ExceptTestView.h : CExceptTestView クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCEPTTESTVIEW_H__380A063C_5B42_4A91_856A_3914811FD00A__INCLUDED_)
#define AFX_EXCEPTTESTVIEW_H__380A063C_5B42_4A91_856A_3914811FD00A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExceptTestView : public CView
{
protected: // シリアライズ機能のみから作成します。
	CExceptTestView();
	DECLARE_DYNCREATE(CExceptTestView)

// アトリビュート
public:
	CExceptTestDoc* GetDocument();

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CExceptTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画する際にオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CExceptTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CExceptTestView)
		// メモ -  ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ExceptTestView.cpp ファイルがデバッグ環境の時使用されます。
inline CExceptTestDoc* CExceptTestView::GetDocument()
   { return (CExceptTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_EXCEPTTESTVIEW_H__380A063C_5B42_4A91_856A_3914811FD00A__INCLUDED_)

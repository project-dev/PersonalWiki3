#if !defined(AFX_TODOVIEW_H__03173B17_BB44_45AD_9189_1671C53D9E4D__INCLUDED_)
#define AFX_TODOVIEW_H__03173B17_BB44_45AD_9189_1671C53D9E4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToDoView.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CToDoView ビュー
#include "AbstractBaseWnd.h"
#include "ChartWnd.h"

class CToDoView : public CView, CAbstractBaseWnd{
protected:
	CToDoView();           // 動的生成に使用されるプロテクト コンストラクタ
	void SetCtrlPos();
	DECLARE_DYNCREATE(CToDoView)
	static int CALLBACK SortItemFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK SortCategoryFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK SortStateFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK SortProcessFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK SortStPlanFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK SortEdPlanFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK SortStProgressFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK SortEdProgressFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	BOOL m_bSortAspect[8];

// アトリビュート
public:
	virtual void UpdateSetting();
// オペレーション
public:
	void DelCheckToDo();
	void UpdateToDo();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CToDoView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CToDoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CToDoView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnTodoAdd();
	afx_msg void OnUpdateTodoAdd(CCmdUI* pCmdUI);
	afx_msg void OnTodoDel();
	afx_msg void OnUpdateTodoDel(CCmdUI* pCmdUI);
	afx_msg void OnTodoEdit();
	afx_msg void OnUpdateTodoEdit(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg void OnTabChange(LPNMHDR pNmhdr, HRESULT *pResult);
	afx_msg void OnColumnClick(LPNMHDR pNmhdr, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

	typedef enum eTABTYPE{
		TT_ALL = 0,		//全て
		TT_NONE,		//未着手
		TT_PARITY,		//対応中
		TT_CHECK,		//確認完
		TT_WAIT,		//待ち	
		TT_FINISH,		//完了
		TT_RESERVE,		//保留
		TT_CHART,		//チャート
		TT_END
	};
		
	CListCtrl m_objList[TT_END];
	CTabCtrl m_objTab;
	CBitmap m_objStateBmp;
	CImageList m_arrStateImg;
	CFont m_objFont;
	CRect m_objTabRect;
	COleDateTime m_objPreChkDtm;
	CChartWnd m_objChartWnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_TODOVIEW_H__03173B17_BB44_45AD_9189_1671C53D9E4D__INCLUDED_)

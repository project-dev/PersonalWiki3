// CalenderWnd.h: CCalenderWnd クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALENDERWND_H__5E29091D_406A_4BED_89F5_F513FBEB6180__INCLUDED_)
#define AFX_CALENDERWND_H__5E29091D_406A_4BED_89F5_F513FBEB6180__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "AbstractBaseWnd.h"
class CPWikiDoc;
class CCalenderWnd : public CWnd, CAbstractBaseWnd{
public:
	void SetCtrlPos();
	void CreateBuffer();
	CCalenderWnd();
	virtual ~CCalenderWnd();
	BOOL Create(DWORD dwStyle, const RECT &rect, CWnd *pParent, UINT uID);
	void UpdateInfo();
	void UpdateCalender();
	virtual void UpdateSetting();

	//{{AFX_VIRTUAL(CCalenderWnd)
	public:
	protected:
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(CCalenderWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	afx_msg void OnNextBtnClick();
	afx_msg void OnPrevBtnClick();
	afx_msg void OnTodayBtnClick();
	afx_msg void OnDtChange(NMHDR *pNmHdr, HRESULT *pResult);
	DECLARE_MESSAGE_MAP()

private:
	CPWikiDoc* GetDocument();

	CDC*		m_pBackDC;
	CBitmap*	m_pBackBmp;
	CBitmap*	m_pOldBmp;
	CRect		m_objCalRect;
	CSize		m_obj1DaySize;
	CFont		m_objFont;
	CFont		m_objCtrlFont;
	CScrollBar	m_objScV;
	CScrollBar	m_objScH;
	CBitmapButton	m_objPrevMonth;
	CBitmapButton	m_objNextMonth;
	CBitmapButton	m_objBtnToDay;
	CDateTimeCtrl	m_objDtCtrl;
	COleDateTime	m_objToDay;
	UINT m_uTimerID;
};

#endif // !defined(AFX_CALENDERWND_H__5E29091D_406A_4BED_89F5_F513FBEB6180__INCLUDED_)

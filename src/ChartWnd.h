// ChartWnd.h: CChartWnd クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARTWND_H__76AD3A66_0AC1_4735_A14F_579CEC32C1EF__INCLUDED_)
#define AFX_CHARTWND_H__76AD3A66_0AC1_4735_A14F_579CEC32C1EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "AbstractBaseWnd.h"

class CPWikiDoc;
class CEventDate;

#define USE_FILTER

#define COLSPAN 6
#define COLSPAN_HALF (COLSPAN / 2)

#if defined(SUBITEMHITTEST_SUPPORT)
typedef enum tagCW_CURPOINT{
	ON_ICON,
	ON_LABEL
}CW_CURPOINT;

typedef struct tagCWHITTEST{
	POINT pos;			/*in*/
	CW_CURPOINT curPos;	/*out*/
	int nIndex;			/*out*/
	int nSubItem;		/*out*/
}CWHITTEST, *PCWHITTEST;
#endif

class CChartWnd : public CWnd, 	public CAbstractBaseWnd {
public:
	void UpdateCategory();
	int GetSelectItemIndex();
	BOOL Create(DWORD dwStyle, RECT& rect, CWnd *pParent, CPWikiDoc* pDoc, UINT uID);
	CChartWnd();
	virtual ~CChartWnd();

	void UpdateBuffer();
	virtual CScrollBar* GetScrollBarCtrl( int nBar );
	CEventDate* GetItemData(int nIndex);
	void SetImageList(CImageList* pImgList);
	virtual void UpdateSetting();

	//{{AFX_VIRTUAL(CChartWnd)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CChartWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateFont();
	void ResetTime(COleDateTime& objDt);
	int HitTest(CPoint pos);
#if defined(SUBITEMHITTEST_SUPPORT)
	int SubitemHitTest(CWHITTEST &objHitTest);
#endif
	void GetItemWidth();
	int m_nNameWidth;
	int m_nCategoryWidth;
	int m_nProgressWidth;
	void DrawItemString(CRect& rect, CString& str, COLORREF crBkColor, BOOL bDrawBtn = FALSE, int nImgIndex = -1);
	void DrawItemProgress(CRect& rect, CString& str, double dProgress, COLORREF crBkColor);
	CScrollBar m_objHScrollCtrl;
	CScrollBar m_objVScrollCtrl;
	void SetCtrlPos();
	int UpdateDatas(BOOL bDrawUpdate, LPPOINT pos);

	CFont m_objFont;
	CFont m_objCtrlFont;
	CDC* m_pBackDC;
	CBitmap* m_pBackBmp;
	void CreateBuffer();
	CPWikiDoc* m_pDoc;
	COleDateTime m_objCurTime;
	COleDateTime m_objMinTime;
	COleDateTime m_objMaxTime;
	int m_nIconSize;
	int m_nSelIndex;
#if defined(USE_FILTER)
	CComboBox m_objCmbCategory;
	CComboBox m_objCmbState;
#endif

#if 0
	CEdit m_objEdit;
	CComboBox m_objCmbBox;
#endif
	CImageList m_objImgList;

};

#endif // !defined(AFX_CHARTWND_H__76AD3A66_0AC1_4735_A14F_579CEC32C1EF__INCLUDED_)

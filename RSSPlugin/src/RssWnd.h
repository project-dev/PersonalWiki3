// RssWnd.h: CRssWnd クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RSSWND_H__D5765FAD_2269_499E_8859_2D3267CF55F2__INCLUDED_)
#define AFX_RSSWND_H__D5765FAD_2269_499E_8859_2D3267CF55F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxhtml.h>
#include <afxtempl.h>
#include "AbstractWnd.h"
#include "RSSList.h"
#include "RSSBase.h"
#include "SepBtn.h"
#include "FixHtmlView.h"

static const UINT g_uRssID = ::RegisterWindowMessage("PWIKI_RSSLIST_ID");
static const UINT g_uHtmID = ::RegisterWindowMessage("PWIKI_HTML_ID");
static const UINT g_uTmID  = ::RegisterWindowMessage("PWIKI_RSSRIMER");
static const UINT g_uSepID  = ::RegisterWindowMessage("PWIKI_SEP_ID");

class CRssWnd : public CWnd, CRSSBase, CAbstractWnd{
public:
	void UpdateConfig();
	void UpdateRSSHtml();
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	BOOL SetCtrlPos();
	CRssWnd();

	void OnUpdateRSS(int iItem);
	
	
	virtual ~CRssWnd();
	//{{AFX_VIRTUAL(CRssWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(CRssWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReadrss();
	afx_msg void OnUpdateReadrss(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnLoadOneData(const PRSSINFO pInfo) ;
	virtual BOOL OnSaveOneData(int nCnt, RSSINFO &objInfo) ;
private:
	CRSSList m_objRssList;
	CFixHtmlView* m_pHtmlView;
	CSepBtn m_objSepBtn;
	void ReleaseData();
	UINT m_uTimerID;
	CStringArray m_arrHtml;
};

#endif // !defined(AFX_RSSWND_H__D5765FAD_2269_499E_8859_2D3267CF55F2__INCLUDED_)

// BinderWnd.h: CBinderWnd クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BINDERWND_H__29AD53C9_105F_4F49_8351_102AF3E002B1__INCLUDED_)
#define AFX_BINDERWND_H__29AD53C9_105F_4F49_8351_102AF3E002B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <AfxTempl.h>
#include "Binder.h"
#include "BinderDropTarget.h"
#include "AbstractWnd.h"

#define USE_TOOLTIP_BINDER

static UINT WM_ANALISYS_DROP = ::RegisterWindowMessage("BINDER_PLUGIN_ANALISYS_MSG");

class CBinderWnd : public CWnd, CAbstractWnd{
public:
	CBinderWnd();
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	virtual ~CBinderWnd();
//	BOOL AnalyzeDropHTML(COleDataObject *pObject);
	BOOL AnalyzeDropHTML(LPCTSTR szText);

	//{{AFX_VIRTUAL(CBinderWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
//	PPWIKIPLUGIN m_pPlgInfo;
public:
	void SetCtrlPos();
	CBinderDropTarget  m_objDropTarget;
	CString m_strAnalisysData;
	static UINT Analisys( LPVOID pParam );

protected:
	//{{AFX_MSG(CBinderWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnAddbinder();
	afx_msg void OnAddfile();
	afx_msg void OnClipcopy();
	afx_msg void OnFiledel();
	afx_msg void OnUpdateAddbinder(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddfile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateClipcopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFiledel(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	afx_msg void OnTreeDBClick(NMHDR * pNotifyStruct, LRESULT * result );
//	afx_msg void OnTreeClick(NMHDR * pNotifyStruct, LRESULT * result );
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
#if defined(USE_TOOLTIP_BINDER)
	afx_msg BOOL OnToolTipNotifyEx(UINT id, NMHDR *pTTTStruct, LRESULT *pResult);
	afx_msg void OnToolTipNotify(NMHDR *pTTTStruct, LRESULT *pResult);
#endif
	afx_msg LRESULT OnAnalisys(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	static int CALLBACK CompareBinder(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort); 
	static int CALLBACK CompareBinderItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort); 
	void SaveIni();
	void LoadIni();
	int RegistDropFile(HDROP hDropInfo);
	BOOL DownloadFile(LPCTSTR pszURL, LPCTSTR pszSavePath);
	
	LPCTSTR GetFindItem(LPCTSTR pszKey, HTREEITEM hItem);
	void UpdateTree();
	int GetItemIcon(CBinder *pBinder, PBINDERITEM pItem);
	void LoadDataFile(LPCTSTR pszFileName, CBinder *pStaticBinder = NULL, HTREEITEM hStaticItem = NULL);
	BOOL AddBinder();
	CBinder* GetActiveBinder();
	void SetActiveBinder(CBinder *pBinder);
#if defined(USE_TOOLTIP_BINDER)
	virtual void GetToolTipText(NMHDR *pTTTStruct, CString &strTipText);
	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI ) const;
#endif

	CBitmap m_objTreeBmp;
	CTreeCtrl m_objTree;
	CImageList m_arrImg;
	HTREEITEM m_hRoot;
	HTREEITEM m_hDust;
	HTREEITEM m_hClip;
	HTREEITEM m_hClipText;
	HTREEITEM m_hClipGraph;
	HTREEITEM m_hClipHtml;
	HTREEITEM m_hHtml;
	CStringList			 m_arrExtList;
	CArray<HICON, HICON> m_arrIcon;
	CArray<int, int>	 m_arrIconIndex;
	HACCEL		m_objAcl;
	CString	m_strAppPath;
	CString	m_strIniFile;
	CBinder *m_pActiveBinder;
	CToolBar	m_wndToolBar;
	CRect		m_objTbRect;
	CToolTipCtrl m_objToolTip;

	HACCEL m_hAccel;

	//Iniファイル用
	BOOL m_bIsSecure;
	CString m_strToolPath;

};

#endif // !defined(AFX_BINDERWND_H__29AD53C9_105F_4F49_8351_102AF3E002B1__INCLUDED_)

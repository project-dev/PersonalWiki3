// WikiWnd.h: CWikiWnd クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIKIWND_H__C8D16071_F498_439F_AFCF_AF6511C96406__INCLUDED_)
#define AFX_WIKIWND_H__C8D16071_F498_439F_AFCF_AF6511C96406__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "AbstractWikiWnd.h"

#define USE_TOOLTIP_WIKIWIND

class CPWikiDoc;
class CWikiWnd : public CWnd, CAbstractWikiWnd{
public:
	CString GetBasePath(BOOL bActiveTree = FALSE);
	CTreeCtrl* GetTree(int nSel);
	BOOL GetUSBPath(CString& strWikiPath, CString& strBasePath);
	void ActiveTreeItem(LPCTSTR pszWikipath);
	typedef enum EXP_TYPE{
		EXP_HTML,
		EXP_TEXT,
	};
	BOOL Export(EXP_TYPE eExpType);
	void OnCtrlState();
	HTREEITEM IsAlive(CTreeCtrl *pTree, LPCTSTR pszText, HTREEITEM hParent);
	void GetWikiPath(CTreeCtrl* pTree, HTREEITEM hItem, CString &strPath);
	void FindWikiDoc(LPCTSTR pszDir = NULL, HTREEITEM hTree = NULL);
	void FindWikiDocUSB(LPCTSTR pszDir = NULL, HTREEITEM hTree = NULL);
	void FindWikiDocUSBFotChild(CTreeCtrl* pTree, LPCTSTR pszDir, HTREEITEM hParent, LPCTSTR pszBasePath);
	void SetCtrlPos();
	CWikiWnd();
	BOOL Create(DWORD dwStyle, const RECT &rect, CWnd *pParent, UINT uID);

	virtual void UpdateSetting();

	virtual ~CWikiWnd();
	//{{AFX_VIRTUAL(CWikiWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(CWikiWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnAddwiki();
	afx_msg void OnDelwiki();
	afx_msg void OnEditwiki();
	afx_msg void OnExpHtml();
	afx_msg void OnExpText();
	afx_msg void OnRenameWiki();
	afx_msg void OnUpdateAddwiki(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDelwiki(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditwiki(CCmdUI* pCmdUI);
	afx_msg void OnUpdateExpHtml(CCmdUI* pCmdUI);
	afx_msg void OnUpdateExpText(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRenameWiki(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBtnTreerefresh();
	afx_msg void OnUpdateBtnTreerefresh(CCmdUI* pCmdUI);
	afx_msg void OnUrlImport();
	afx_msg void OnUpdateUrlImport(CCmdUI* pCmdUI);
	afx_msg void OnProperty();
	afx_msg void OnUpdateProperty(CCmdUI* pCmdUI);
	afx_msg void OnPluginExport();
	afx_msg void OnUpdatePluginExport(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnSelChanged(NMHDR * pNotifyStruct, LRESULT * result );
	afx_msg void OnClick(NMHDR * pNotifyStruct, LRESULT * result );
#if defined(USE_TOOLTIP_WIKIWIND)
	afx_msg BOOL OnToolTipNotifyEx(UINT id, NMHDR *pTTTStruct, LRESULT *pResult);
	afx_msg void OnToolTipNotify(NMHDR *pTTTStruct, LRESULT *pResult);
#endif
	afx_msg BOOL OnDeviceChange( UINT nEventType, DWORD dwData );
	afx_msg void OnTabChange(LPNMHDR pNmhdr, HRESULT *pResult);

	DECLARE_MESSAGE_MAP()
	void OnClickWikiAdd();
	void OnClickWikiEdit();
	void OnClickWikiDel();
#if defined(USE_TOOLTIP_WIKIWIND)
	virtual void GetToolTipText(NMHDR *pTTTStruct, CString &strTipText);
	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI ) const;
#endif
	BOOL CopyFiles(LPCTSTR pszFrom, LPCTSTR pszTo);
private:
	BOOL DownloadFile(LPCTSTR pszURL, CString& strRetData, LPCTSTR pszUserID = NULL, LPCTSTR pszPass = NULL);
	CPWikiDoc* GetDocument();
	CTreeCtrl m_objTree;
	CMapStringToPtr m_mapTree;
	CBitmap m_objTreeBmp;
	CImageList m_arrImgList;
	CBitmap m_objTbBmp;
	CToolBar m_objToolBar;
	CRect m_objTbRect;
	CTabCtrl	m_objTab;
	CFont m_objFont;
#if defined(USE_TOOLTIP_WIKIWIND)
	CToolTipCtrl m_objToolTip;
#endif
};

#endif // !defined(AFX_WIKIWND_H__C8D16071_F498_439F_AFCF_AF6511C96406__INCLUDED_)

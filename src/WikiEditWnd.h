// WikiEditWnd.h: CWikiEditWnd クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIKIEDITWND_H__AA5F890B_DEF0_4FB4_84CC_B29A023E82D4__INCLUDED_)
#define AFX_WIKIEDITWND_H__AA5F890B_DEF0_4FB4_84CC_B29A023E82D4__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "AbstractWikiWnd.h"

//#include "RichEditCtrlEx.h"
//#include <Richole.h>
//class _AFX_RICHEDIT_STATE;


typedef enum eOPENMODE{
	OP_WIKI,
	OP_USB,
	OP_DATE,
}OPENMODE;

class CWikiEditWnd : public CWnd, CAbstractWikiWnd {
public:
	void FindAttachFile();
	void SaveText();
	void SetText(LPCTSTR lpWiki, LPCTSTR pszPathName, OPENMODE opMode);
	void SetCtrlPos();
	CWikiEditWnd();
	virtual ~CWikiEditWnd();
	virtual void UpdateSetting();

	//{{AFX_VIRTUAL(CWikiEditWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	//}}AFX_VIRTUAL

//	LPRICHEDITOLE m_lpRichEditOle;
private:
//	CRichEditCtrlEx m_objEdit;
	CEdit m_objEdit;
	CFont m_objFont;
	CString m_strPathName;
	OPENMODE m_opMode;
	CString m_strOldText;
	void SetEditorOpt();
	CToolTipCtrl m_objToolTip;
	CToolBar	m_objToolBar;
	CRect		m_objTbRect;
	CListCtrl	m_objAttList;

	HACCEL m_hAccelTable;
protected:
	//{{AFX_MSG(CWikiEditWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWikiBold();
	afx_msg void OnWikiHead();
	afx_msg void OnWikiHline();
	afx_msg void OnWikiItalic();
	afx_msg void OnWikiLink();
	afx_msg void OnWikiList();
	afx_msg void OnWikiNumlist();
	afx_msg void OnWikiRet();
	afx_msg void OnWikiStrike();
	afx_msg void OnWikiUnderline();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnEditUndo();
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg BOOL OnToolTipNotifyEx(UINT id, NMHDR *pTTTStruct, LRESULT *pResult);
	afx_msg void OnToolTipNotify(NMHDR *pTTTStruct, LRESULT *pResult);

public:
	afx_msg void OnUpdateWikiBold(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWikiHead(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWikiHline(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWikiItalic(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWikiLink(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWikiList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWikiNumlist(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWikiRet(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWikiStrike(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWikiUnderline(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
protected:
	DECLARE_MESSAGE_MAP()
	virtual void GetToolTipText(NMHDR *pTTTStruct, CString &strTipText);
	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI ) const;

//public:
//	//AFXRICH.Hより
//	BEGIN_INTERFACE_PART(RichEditOleCallback, IRichEditOleCallback)
//		INIT_INTERFACE_PART(CWikiEditWnd, RichEditOleCallback)
//		STDMETHOD(GetNewStorage) (LPSTORAGE*);
//		STDMETHOD(GetInPlaceContext) (LPOLEINPLACEFRAME*,
//									  LPOLEINPLACEUIWINDOW*,
//									  LPOLEINPLACEFRAMEINFO);
//		STDMETHOD(ShowContainerUI) (BOOL);
//		STDMETHOD(QueryInsertObject) (LPCLSID, LPSTORAGE, LONG);
//		STDMETHOD(DeleteObject) (LPOLEOBJECT);
//		STDMETHOD(QueryAcceptData) (LPDATAOBJECT, CLIPFORMAT*, DWORD,BOOL, HGLOBAL);
//		STDMETHOD(ContextSensitiveHelp) (BOOL);
//		STDMETHOD(GetClipboardData) (CHARRANGE*, DWORD, LPDATAOBJECT*);
//		STDMETHOD(GetDragDropEffect) (BOOL, DWORD, LPDWORD);
//		STDMETHOD(GetContextMenu) (WORD, LPOLEOBJECT, CHARRANGE*, HMENU*);
//	END_INTERFACE_PART(RichEditOleCallback)
//
//	DECLARE_INTERFACE_MAP()
};

#endif // !defined(AFX_WIKIEDITWND_H__AA5F890B_DEF0_4FB4_84CC_B29A023E82D4__INCLUDED_)

// FindWnd.h: CFindWnd クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FINDWND_H__227B3152_0C1D_4EC7_B8EF_326C5D7383AD__INCLUDED_)
#define AFX_FINDWND_H__227B3152_0C1D_4EC7_B8EF_326C5D7383AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractBaseWnd.h"
class CPWikiDoc;

class CFindWnd : public CWnd, CAbstractBaseWnd{
public:
	void LoadFindText();
	void SaveFindText();
	void SetCtrlPos();
	CFindWnd();
	virtual ~CFindWnd();
	BOOL Create(DWORD dwStyle, const RECT &rect, CWnd *pParent, UINT uID);
	//{{AFX_VIRTUAL(CFindWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(CFindWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg LRESULT OnFindUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg void OnColumnClick(LPNMHDR pNmhdr, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
	static UINT FindThread( LPVOID pParam );
	static CString m_strFindText;
	static BOOL CALLBACK PreFindNextProc();
	static BOOL CALLBACK FindProc(LPCTSTR pszDir, WIN32_FIND_DATA &wfd);
private:
	CPWikiDoc* GetDocument();
	CFont		m_objFont;
	CComboBox m_objCmbText;
	CButton m_objBtnFind;
	CListCtrl m_objList;
	HANDLE m_hThread;
	CWinThread *m_pThread;
	static HANDLE m_hThreadEnd;
	static CStringArray m_arrHitFileName;
	static CStringArray m_arrHitString;
};

#endif // !defined(AFX_FINDWND_H__227B3152_0C1D_4EC7_B8EF_326C5D7383AD__INCLUDED_)

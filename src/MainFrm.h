// MainFrm.h : CMainFrame クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__E86B7CB9_F6E5_457B_86A7_14D340258C7B__INCLUDED_)
#define AFX_MAINFRM_H__E86B7CB9_F6E5_457B_86A7_14D340258C7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CToDoView;
class CCalView;
class CInfoTabView;
class CInfoView;
#define		WM_TRYCLICK			WM_APP + 0x010

static UINT WM_TASKBERCREATED = ::RegisterWindowMessage(_T("PWikiTaskbarCreated"));
#include "DlgInfo.h"
#include "PWikiIniFile.h"
#include "MimeType.h"
#include "PWikiPlgList.h"

class CMainFrame : public CFrameWnd, CAbstractWnd {
	
protected: // シリアライズ機能のみから作成します。
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// アトリビュート
public:
	CToDoView*	GetToDoView();
	CCalView*	GetCalView();
	CInfoTabView*	GetInfoTabView();
	void SetToDayIinfo(LPCTSTR pszInfo);
	COleDateTime	m_objNowDate;
	CPWikiIniFile		m_objIniFile;
	CMimeType		m_objMimeTypes;
	BOOL SetTrayMode(BOOL bOnTray = TRUE);
	CPWikiPlgList	m_objPlugins;

	static USB_STATE m_arrUsbState[27];	//A-Z
// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	void SetWndRectToIniFile();
	BOOL IsEndSession();
	void ApplExit();
	void CreateDlgInfo();
	BOOL EnumDevice();
	void GetUSBDevDrv(CStringArray& arrDrv);
	virtual ~CMainFrame();
	CInfoView* m_pHtmlView;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // コントロール バー用メンバ
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

	CSplitterWnd m_wndSplitter1;	//カレンダーとm_wndSplitter2
	CSplitterWnd m_wndSplitter2;	//詳細表示とToDo
	CDlgInfo	m_objDlgInfo;
	NOTIFYICONDATA m_objNotifyIcon;
	BOOL m_bEndSession;
	BOOL m_bEndCall;

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnFixedData();
	afx_msg void OnPwikiSet();
	afx_msg void OnAppClose();
	afx_msg void OnDummy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRule();
	afx_msg void OnHelp();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg BOOL OnQueryEndSession();
	afx_msg void OnAppEnd();
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	afx_msg BOOL OnDeviceChange( UINT nEventType, DWORD dwData );
	afx_msg LRESULT OnTrayClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTaskbarCreated(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MAINFRM_H__E86B7CB9_F6E5_457B_86A7_14D340258C7B__INCLUDED_)

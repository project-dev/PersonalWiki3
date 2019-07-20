// MainFrm.h : CMainFrame �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
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
	
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// �A�g���r���[�g
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
// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
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

protected:  // �R���g���[�� �o�[�p�����o
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

	CSplitterWnd m_wndSplitter1;	//�J�����_�[��m_wndSplitter2
	CSplitterWnd m_wndSplitter2;	//�ڍו\����ToDo
	CDlgInfo	m_objDlgInfo;
	NOTIFYICONDATA m_objNotifyIcon;
	BOOL m_bEndSession;
	BOOL m_bEndCall;

// �������ꂽ���b�Z�[�W �}�b�v�֐�
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
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MAINFRM_H__E86B7CB9_F6E5_457B_86A7_14D340258C7B__INCLUDED_)

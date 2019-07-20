#if !defined(AFX_DLGINFO_H__CCD27F41_E665_4EE2_BC62_BCCC9401E72C__INCLUDED_)
#define AFX_DLGINFO_H__CCD27F41_E665_4EE2_BC62_BCCC9401E72C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfo.h : �w�b�_�[ �t�@�C��
//
#include "AbstractBaseWnd.h"
#include "DlgToDay.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgInfo �_�C�A���O
class CMainFrame;

#define USE_TOOLTIPCTRL

class CDlgInfo : public CDialog, CAbstractBaseWnd{
// �R���X�g���N�V����
public:
	void SetCtrl();
	void UpdateDisp();
	void SetInfo(LPCTSTR pszInfo);
	void GetTextOutRect(CRect &rect);
	BOOL CreateBackBuff();
	void CreateScrollText(CString &strText);
	BOOL UpdateViewSetting();
	void SetMainFrame(CMainFrame *pFrm);
	int CalcTextCount();
	CDlgInfo(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	virtual ~CDlgInfo();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgInfo)
	enum { IDD = IDD_DLGINFO };
	CStatic	m_objTime;
	CString	m_strTime;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgInfo)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL
	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI ) const;

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgInfo)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnClose();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnFixedData();
	afx_msg void OnPwikiSet();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg BOOL OnToolTipNotifyEx(UINT id, NMHDR *pTTTStruct, LRESULT *pResult);
	afx_msg void OnToolTipNotify(NMHDR *pTTTStruct, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
	virtual void GetToolTipText(NMHDR *pTTTStruct, CString &strTipText);
	void ShowToDay(BOOL bForce = FALSE);

	CButton m_objMenuBtn;
	int m_nScrPos;
	CMainFrame* m_pMainFrm ;
	CPoint m_objOldCurPos;

	CFont m_objFont;
	CRect m_objBtnRect;
	CDC *m_pBackDC;
	CBitmap *m_pBackBmp;
	CBitmap *m_pOldBmp;
	CFont *m_pOldFont;
	CString m_strInfo;
	UINT m_uTimerID;
	CDlgToDay m_objDlgToDay;

	COleDateTime m_objChkDate;

	HICON m_hIcon;
#if defined(USE_TOOLTIPCTRL)
	CToolTipCtrl m_objToolTip;
#endif
	CRect m_objDefRect;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGINFO_H__CCD27F41_E665_4EE2_BC62_BCCC9401E72C__INCLUDED_)

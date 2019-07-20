#if !defined(AFX_CALVIEW_H__05DECB02_381C_495C_8BB2_C83E88F0C14B__INCLUDED_)
#define AFX_CALVIEW_H__05DECB02_381C_495C_8BB2_C83E88F0C14B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalView.h : �w�b�_�[ �t�@�C��
//
#include <afxdtctl.h>
#include "AbstractBaseWnd.h"
#include "CalenderWnd.h"
#include "WikiWnd.h"
#include "FindWnd.h"



#define USE_DEVLIB_TAB


#if defined(USE_DEVLIB_TAB)
#include "HwndTabCtrl.h"
#endif
/////////////////////////////////////////////////////////////////////////////
// CCalView �r���[
class CEventDate;
class CCalView : public CView, CAbstractBaseWnd{
protected:
	CCalView();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
	DECLARE_DYNCREATE(CCalView)

// �A�g���r���[�g
public:

// �I�y���[�V����
public:
	void UpdateShowPluginTab();
	void ActiveWikiPage(LPCTSTR pszWikiPath);
	void SetCtrlPos();
//	void UpdateInfo();
	void UpdateCalender();
	void UpdateWikiTree(BOOL bUSBTree = FALSE);
	CWikiWnd* GetWikiWnd();
	virtual void UpdateSetting();
// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CCalView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h���܂����B
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~CCalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CCalView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
#if !defined(USE_DEVLIB_TAB)
	afx_msg void OnTabChange(LPNMHDR pNmhdr, HRESULT *pResult);
#endif
	DECLARE_MESSAGE_MAP()
#if defined(USE_DEVLIB_TAB)
	CHwndTabCtrl	m_objTab;
#else
	CTabCtrl	m_objTab;
#endif
	CCalenderWnd m_objCalWnd;
	CWikiWnd m_objWikiWnd;
	CFindWnd m_objFindWnd;
	CFont m_objFont;
	CRect m_objTabRect;
private:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CALVIEW_H__05DECB02_381C_495C_8BB2_C83E88F0C14B__INCLUDED_)

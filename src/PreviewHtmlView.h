#if !defined(AFX_PREVIEWHTMLVIEW_H__65EF8D43_0A43_48FF_AB8B_1BEADF2FA1BE__INCLUDED_)
#define AFX_PREVIEWHTMLVIEW_H__65EF8D43_0A43_48FF_AB8B_1BEADF2FA1BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreviewHtmlView.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CPreviewHtmlView HTML �r���[

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>
#include "AbstractBaseWnd.h"

class CPreviewHtmlView : public CHtmlView, CAbstractBaseWnd
{
protected:
	CPreviewHtmlView();           // ���I�����Ŏg�p����� protected �R���X�g���N�^
	DECLARE_DYNCREATE(CPreviewHtmlView)

// html Data
public:
	//{{AFX_DATA(CPreviewHtmlView)
		// ����: ���̈ʒu�� ClassWizard �ɂ���ăf�[�^ �����o���ǉ�����܂��B
	//}}AFX_DATA

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂�
	//{{AFX_VIRTUAL(CPreviewHtmlView)
	public:
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~CPreviewHtmlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CPreviewHtmlView)
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PREVIEWHTMLVIEW_H__65EF8D43_0A43_48FF_AB8B_1BEADF2FA1BE__INCLUDED_)

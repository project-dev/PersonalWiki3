#if !defined(AFX_INFOVIEW_H__564914E9_7B14_45ED_924E_029E2E33EF10__INCLUDED_)
#define AFX_INFOVIEW_H__564914E9_7B14_45ED_924E_029E2E33EF10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FixHtmlView.h"

// InfoView.h : �w�b�_�[ �t�@�C��
//
/////////////////////////////////////////////////////////////////////////////
// CInfoView HTML �r���[

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>
#include "AnalisysWiki.h"
#include "AbstractWikiWnd.h"

class CInfoView : public CFixHtmlView, CAbstractWikiWnd{
protected:
	CInfoView();           // ���I�����Ŏg�p����� protected �R���X�g���N�^
	DECLARE_DYNCREATE(CInfoView)

// html Data
public:
	//{{AFX_DATA(CInfoView)
		// ����: ���̈ʒu�� ClassWizard �ɂ���ăf�[�^ �����o���ǉ�����܂��B
	//}}AFX_DATA

// �A�g���r���[�g
public:

// �I�y���[�V����
public:
	void GetHtmlHead(CString &strHtml, LPCTSTR pszTitle);
/*
	void UpdateInfo(COleDateTime *pDate);
	void UpdateInfo(CString &strWikiPath);
	void UpdateInfoUSB(CString &strBasePath, LPCTSTR pszBasePath);
*/
// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂�
	//{{AFX_VIRTUAL(CInfoView)
	public:
	virtual void OnInitialUpdate();
	virtual void OnDownloadBegin();
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~CInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CInfoView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CAnalisysWiki m_objAnalisys;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_INFOVIEW_H__564914E9_7B14_45ED_924E_029E2E33EF10__INCLUDED_)

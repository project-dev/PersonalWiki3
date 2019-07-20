#if !defined(AFX_DLGFIXDATA_H__59790931_7651_46E9_8E16_2E39A88C3C12__INCLUDED_)
#define AFX_DLGFIXDATA_H__59790931_7651_46E9_8E16_2E39A88C3C12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFixData.h : �w�b�_�[ �t�@�C��
//
#include "DlgFixDataPage1.h"
#include "DlgFixDataPage2.h"
#include "DlgFixDataPage3.h"
#include "DlgFixDataPage4.h"
#include "AbstractWnd.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgFixData �_�C�A���O

class CDlgFixData : public CDialog, CAbstractWnd
{
// �R���X�g���N�V����
public:
	void SetActivePage();
	CDlgFixData(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgFixData)
	enum { IDD = IDD_DlgFixedData };
	CTabCtrl	m_objTab;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgFixData)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgFixData)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CDlgFixDataPage1 m_objPage1;
	CDlgFixDataPage2 m_objPage2;
	CDlgFixDataPage3 m_objPage3;
	CDlgFixDataPage4 m_objPage4;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGFIXDATA_H__59790931_7651_46E9_8E16_2E39A88C3C12__INCLUDED_)

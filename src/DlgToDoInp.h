#if !defined(AFX_DLGTODOINP_H__C7B3C282_E986_4A06_BD5B_2DB9732E5367__INCLUDED_)
#define AFX_DLGTODOINP_H__C7B3C282_E986_4A06_BD5B_2DB9732E5367__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgToDoInp.h : �w�b�_�[ �t�@�C��
//

#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgToDoInp �_�C�A���O

class CDlgToDoInp : public CDialog, CAbstractBaseWnd
{
// �R���X�g���N�V����
public:
	CDlgToDoInp(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	CString m_strCategory;
// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgToDoInp)
	enum { IDD = IDD_DLGINPTODO };
	CComboBox	m_objCmbState;
	CComboBox	m_objCmbCategory;
	COleDateTime	m_objPlanEnd;
	COleDateTime	m_objPlanStart;
	COleDateTime	m_objProgressEnd;
	COleDateTime	m_objProgressStart;
	CString	m_strDetail;
	CString	m_strName;
	double	m_dProcessPar;
	int		m_nState;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgToDoInp)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgToDoInp)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelendokCmbState();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGTODOINP_H__C7B3C282_E986_4A06_BD5B_2DB9732E5367__INCLUDED_)

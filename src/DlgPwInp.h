#if !defined(AFX_DLGPWINP_H__32BD1111_D57F_49E1_934C_D9562D841EEA__INCLUDED_)
#define AFX_DLGPWINP_H__32BD1111_D57F_49E1_934C_D9562D841EEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPwInp.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPwInp �_�C�A���O

#include "AbstractWnd.h"

class CDlgPwInp : public CDialog, CAbstractWnd
{
// �R���X�g���N�V����
public:
	CDlgPwInp(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgPwInp)
	enum { IDD = IDD_DLG_PW_INP };
	CString	m_strPassWord;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgPwInp)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgPwInp)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGPWINP_H__32BD1111_D57F_49E1_934C_D9562D841EEA__INCLUDED_)

#if !defined(AFX_DLGDATEINP_H__379FE3DA_0AEC_4D6A_8BE1_E1BF60601C78__INCLUDED_)
#define AFX_DLGDATEINP_H__379FE3DA_0AEC_4D6A_8BE1_E1BF60601C78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDateInp.h : �w�b�_�[ �t�@�C��
//

#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDateInp �_�C�A���O

class CDlgDateInp : public CDialog, CAbstractBaseWnd
{
// �R���X�g���N�V����
public:
	CDlgDateInp(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgDateInp)
	enum { IDD = IDD_DLGINPDATE };
//	CComboBox	m_objCmbCategory;
	CString	m_strDetail;
	CString	m_strHelp;
	//}}AFX_DATA

	COleDateTime m_ojbDate;

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgDateInp)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgDateInp)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGDATEINP_H__379FE3DA_0AEC_4D6A_8BE1_E1BF60601C78__INCLUDED_)

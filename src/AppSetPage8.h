#if !defined(AFX_APPSETPAGE8_H__EBD86DE1_50C2_4F4E_84A5_5ABECCA1574C__INCLUDED_)
#define AFX_APPSETPAGE8_H__EBD86DE1_50C2_4F4E_84A5_5ABECCA1574C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage8.h : �w�b�_�[ �t�@�C��
//
#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage8 �_�C�A���O

class CAppSetPage8 : public CDialog, CAbstractBaseWnd
{
// �R���X�g���N�V����
public:
	void UpdateInfo();
	CAppSetPage8(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAppSetPage8)
	enum { IDD = IDD_DLG_APP_SETPAGE8 };
	BOOL	m_bUseUSBLink;
	CString	m_strPath1;
	CString	m_strPath2;
	CString	m_strPath3;
	CString	m_strPath4;
	BOOL	m_bUseNetDrv;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAppSetPage8)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAppSetPage8)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_APPSETPAGE8_H__EBD86DE1_50C2_4F4E_84A5_5ABECCA1574C__INCLUDED_)

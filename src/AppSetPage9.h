#if !defined(AFX_APPSETPAGE9_H__4A9C997B_C3B9_41FB_AFBF_CDA6C7C62058__INCLUDED_)
#define AFX_APPSETPAGE9_H__4A9C997B_C3B9_41FB_AFBF_CDA6C7C62058__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage9.h : �w�b�_�[ �t�@�C��
//
#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage9 �_�C�A���O

class CAppSetPage9 : public CDialog, CAbstractBaseWnd
{
// �R���X�g���N�V����
public:
	void UpdateInfo();
	CAppSetPage9(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAppSetPage9)
	enum { IDD = IDD_DLG_APP_SETPAGE9 };
	BOOL	m_bShowSec;
	BOOL	m_bShowSc;
	BOOL	m_bShowTodo;
	BOOL	m_bShowTime;
	BOOL	m_bShowFix;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAppSetPage9)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAppSetPage9)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_APPSETPAGE9_H__4A9C997B_C3B9_41FB_AFBF_CDA6C7C62058__INCLUDED_)

#if !defined(AFX_APPSETPAGE6_H__573B8B63_0764_4D20_B29C_8BBDC410E782__INCLUDED_)
#define AFX_APPSETPAGE6_H__573B8B63_0764_4D20_B29C_8BBDC410E782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage6.h : �w�b�_�[ �t�@�C��
//
#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage6 �_�C�A���O

class CAppSetPage6 : public CDialog, CAbstractBaseWnd
{
// �R���X�g���N�V����
public:
	BOOL UpdateInfo();
	CAppSetPage6(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAppSetPage6)
	enum { IDD = IDD_DLG_APP_SETPAGE6 };
	BOOL	m_bUseFatalLog;
	BOOL	m_bUseStateLog;
	BOOL	m_bUseLog;
	BOOL	m_bUseExceptLog;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAppSetPage6)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAppSetPage6)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_APPSETPAGE6_H__573B8B63_0764_4D20_B29C_8BBDC410E782__INCLUDED_)

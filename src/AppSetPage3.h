#if !defined(AFX_APPSETPAGE3_H__3ECCA135_82FD_4453_AE01_FBE4405B63FA__INCLUDED_)
#define AFX_APPSETPAGE3_H__3ECCA135_82FD_4453_AE01_FBE4405B63FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage3.h : �w�b�_�[ �t�@�C��
//
#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage3 �_�C�A���O

class CAppSetPage3 : public CDialog, CAbstractBaseWnd
{
// �R���X�g���N�V����
public:
	void FindCSS();
	BOOL UpdateInfo();
	CAppSetPage3(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAppSetPage3)
	enum { IDD = IDD_DLG_APP_SETPAGE3 };
	CComboBox	m_objCmbCss;
	BOOL	m_bUseRet;
	BOOL	m_bUseTBLink;
	BOOL	m_bShowAttach;
	BOOL	m_bUseConvTime;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAppSetPage3)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAppSetPage3)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_APPSETPAGE3_H__3ECCA135_82FD_4453_AE01_FBE4405B63FA__INCLUDED_)

#if !defined(AFX_APPSETPAGE5_H__B9276E64_197C_4CA5_9DDD_8825DF521C2C__INCLUDED_)
#define AFX_APPSETPAGE5_H__B9276E64_197C_4CA5_9DDD_8825DF521C2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage5.h : �w�b�_�[ �t�@�C��
//
#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage5 �_�C�A���O

class CAppSetPage5 : public CDialog, CAbstractBaseWnd
{
// �R���X�g���N�V����
public:
	BOOL UpdateInfo();
	CAppSetPage5(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAppSetPage5)
	enum { IDD = IDD_DLG_APP_SETPAGE5 };
	CListCtrl	m_objList;
	CString	m_strDetail;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAppSetPage5)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAppSetPage5)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPlgSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_APPSETPAGE5_H__B9276E64_197C_4CA5_9DDD_8825DF521C2C__INCLUDED_)

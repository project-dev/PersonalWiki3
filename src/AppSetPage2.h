#if !defined(AFX_APPSETPAGE2_H__7BC5EB2F_04FE_48B7_88FA_157129418E94__INCLUDED_)
#define AFX_APPSETPAGE2_H__7BC5EB2F_04FE_48B7_88FA_157129418E94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage2.h : �w�b�_�[ �t�@�C��
//
#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage2 �_�C�A���O

class CAppSetPage2 : public CDialog, CAbstractBaseWnd
{
// �R���X�g���N�V����
public:
	BOOL UpdateInfo();
	CAppSetPage2(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAppSetPage2)
	enum { IDD = IDD_DLG_APP_SETPAGE2 };
	CListCtrl	m_objSpDayList;
	BOOL	m_bFri;
	BOOL	m_bMon;
	BOOL	m_bSat;
	BOOL	m_bSun;
	BOOL	m_bThu;
	BOOL	m_bTue;
	BOOL	m_bWed;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAppSetPage2)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAppSetPage2)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_APPSETPAGE2_H__7BC5EB2F_04FE_48B7_88FA_157129418E94__INCLUDED_)

#if !defined(AFX_APPSETPAGE1_H__9742F6E2_CDE8_4AA8_8C91_F3AA6DD85580__INCLUDED_)
#define AFX_APPSETPAGE1_H__9742F6E2_CDE8_4AA8_8C91_F3AA6DD85580__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage1.h : �w�b�_�[ �t�@�C��
//
#include "AbstractBaseWnd.h"
/////////////////////////////////////////////////////////////////////////////
// CAppSetPage1 �_�C�A���O

class CAppSetPage1 : public CDialog, CAbstractBaseWnd
{
// �R���X�g���N�V����
public:
	BOOL UpdateInfo();
	CAppSetPage1(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAppSetPage1)
	enum { IDD = IDD_DLG_APP_SETPAGE1 };
	CListBox	m_objCtgList;
	BOOL	m_bEndToDoDel;
	int		m_nEndToDoDelSpan;
	BOOL	m_bUsePassWord;
	CString	m_strPassWord;
	CString	m_strCategory;
	BOOL	m_bUseToDay;
	BOOL	m_bRunMainWndShow;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAppSetPage1)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAppSetPage1)
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnMod();
	afx_msg void OnSelchangeCategorylist();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_APPSETPAGE1_H__9742F6E2_CDE8_4AA8_8C91_F3AA6DD85580__INCLUDED_)

#if !defined(AFX_APPSETPAGE7_H__FAC632CA_5242_435F_8920_0EF66565DA26__INCLUDED_)
#define AFX_APPSETPAGE7_H__FAC632CA_5242_435F_8920_0EF66565DA26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage7.h : �w�b�_�[ �t�@�C��
//
#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage7 �_�C�A���O

class CAppSetPage7 : public CDialog, CAbstractBaseWnd
{
// �R���X�g���N�V����
public:
	void UpdateInfo();
	CAppSetPage7(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAppSetPage7)
	enum { IDD = IDD_DLG_APP_SETPAGE7 };
	CListCtrl	m_objList;
	CString	m_strExt;
	CString	m_strMIME;
	BOOL	m_bUse;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAppSetPage7)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAppSetPage7)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnMod();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_APPSETPAGE7_H__FAC632CA_5242_435F_8920_0EF66565DA26__INCLUDED_)

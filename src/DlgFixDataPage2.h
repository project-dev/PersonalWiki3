#if !defined(AFX_DLGFIXDATAPAGE2_H__EEF9FBF3_C9D4_4748_8BD5_A30AE80A4151__INCLUDED_)
#define AFX_DLGFIXDATAPAGE2_H__EEF9FBF3_C9D4_4748_8BD5_A30AE80A4151__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFixDataPage2.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFixDataPage2 �_�C�A���O
#include "AbstractBaseWnd.h"

class CDlgFixDataPage2 : public CDialog, CAbstractBaseWnd
{
// �R���X�g���N�V����
public:
	void OnDataSave();
	CDlgFixDataPage2(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgFixDataPage2)
	enum { IDD = IDD_FIXDATAPAGE2 };
	CListCtrl	m_objList;
	CString	m_strData;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgFixDataPage2)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgFixDataPage2)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnMod();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGFIXDATAPAGE2_H__EEF9FBF3_C9D4_4748_8BD5_A30AE80A4151__INCLUDED_)

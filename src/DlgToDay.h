#if !defined(AFX_DLGTODAY_H__542B78E8_73BF_44DA_B261_603300091B03__INCLUDED_)
#define AFX_DLGTODAY_H__542B78E8_73BF_44DA_B261_603300091B03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgToDay.h : �w�b�_�[ �t�@�C��
//
#include "AbstractBaseWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgToDay �_�C�A���O

class CDlgToDay : public CDialog, CAbstractBaseWnd
{
// �R���X�g���N�V����
public:
	void UpdateToDay();
	CDlgToDay(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgToDay)
	enum { IDD = IDD_DLG_TODAY };
	CString	m_strToDay;
	CString	m_strNextDay;
	CString	m_strNextNextDay;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgToDay)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgToDay)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGTODAY_H__542B78E8_73BF_44DA_B261_603300091B03__INCLUDED_)

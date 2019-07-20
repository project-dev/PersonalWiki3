#if !defined(AFX_DLGFIXDATAPAGE3_H__515309DC_10B8_4678_BAF3_B904847A28C5__INCLUDED_)
#define AFX_DLGFIXDATAPAGE3_H__515309DC_10B8_4678_BAF3_B904847A28C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFixDataPage3.h : �w�b�_�[ �t�@�C��
//

#include "AbstractBaseWnd.h"
#include <AfxTempl.h>
#include "EventDate.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgFixDataPage3 �_�C�A���O

class CDlgFixDataPage3 : public CDialog, CAbstractBaseWnd
{
// �R���X�g���N�V����
public:
	void OnDataSave();
	CDlgFixDataPage3(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgFixDataPage3)
	enum { IDD = IDD_FIXDATAPAGE3 };
	CComboBox	m_objCmbSpan;
	CComboBox	m_objCmbDays;
	CListCtrl	m_objList;
	CString	m_strData;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgFixDataPage3)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgFixDataPage3)
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnMod();
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CArray<CEventDate*, CEventDate*> m_arrDelList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGFIXDATAPAGE3_H__515309DC_10B8_4678_BAF3_B904847A28C5__INCLUDED_)

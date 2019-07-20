#if !defined(AFX_SETDLG_H__7BA820F4_DDA8_4E30_954C_CDFA4758F1EE__INCLUDED_)
#define AFX_SETDLG_H__7BA820F4_DDA8_4E30_954C_CDFA4758F1EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDlg.h : �w�b�_�[ �t�@�C��
//
#include "RSSBase.h"
#include "AbstractWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CSetDlg �_�C�A���O

class CSetDlg : public CDialog, CRSSBase, CAbstractWnd{
// �R���X�g���N�V����
public:
	void ReleaseData();
	CSetDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSetDlg)
	enum { IDD = IDD_SET_DLG };
	CListCtrl	m_objList;
	CString	m_strName;
	CString	m_strURL;
	CString	m_strID;
	CString	m_strPass;
	BOOL	m_bUseCheck;
	int		m_nChkSpan;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSetDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedRsslist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnApply();
	afx_msg void OnBtnDel();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnLoadOneData(const PRSSINFO pInfo) ;
	virtual BOOL OnSaveOneData(int nCnt, RSSINFO &objInfo) ;
	static void SetColumnWidthLC(CListCtrl *pList);
		
	CString m_strData;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SETDLG_H__7BA820F4_DDA8_4E30_954C_CDFA4758F1EE__INCLUDED_)

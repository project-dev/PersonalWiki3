#if !defined(AFX_DLGWIKIINP_H__B687EC49_D3C8_48B4_B9DA_3C66CDD2FEEE__INCLUDED_)
#define AFX_DLGWIKIINP_H__B687EC49_D3C8_48B4_B9DA_3C66CDD2FEEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWikiInp.h : �w�b�_�[ �t�@�C��
//

#include "AbstractBaseWnd.h"
#include "PreviewHtmlView.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgWikiInp �_�C�A���O

class CDlgWikiInp : public CDialog, CAbstractBaseWnd{
// �R���X�g���N�V����
public:
	CDlgWikiInp(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	CString m_strSetText;
	CString m_strWikiPath;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgWikiInp)
	enum { IDD = IDD_DLG_WIKIINP };
	CButton	m_objDummy;
	CRichEditCtrl	m_objEdit;
	CListCtrl	m_objAttList;
	CString	m_strText;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgWikiInp)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgWikiInp)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPreview();
	virtual void OnOK();
	afx_msg void OnWikiBold();
	afx_msg void OnUpdateWikiBold(CCmdUI* pCmdUI);
	afx_msg void OnWikiHead();
	afx_msg void OnUpdateWikiHead(CCmdUI* pCmdUI);
	afx_msg void OnWikiHline();
	afx_msg void OnUpdateWikiHline(CCmdUI* pCmdUI);
	afx_msg void OnWikiItalic();
	afx_msg void OnUpdateWikiItalic(CCmdUI* pCmdUI);
	afx_msg void OnWikiLink();
	afx_msg void OnUpdateWikiLink(CCmdUI* pCmdUI);
	afx_msg void OnWikiList();
	afx_msg void OnUpdateWikiList(CCmdUI* pCmdUI);
	afx_msg void OnWikiNumlist();
	afx_msg void OnUpdateWikiNumlist(CCmdUI* pCmdUI);
	afx_msg void OnWikiRet();
	afx_msg void OnUpdateWikiRet(CCmdUI* pCmdUI);
	afx_msg void OnWikiStrike();
	afx_msg void OnUpdateWikiStrike(CCmdUI* pCmdUI);
	afx_msg void OnWikiUnderline();
	afx_msg void OnUpdateWikiUnderline(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg BOOL OnToolTipNotifyEx(UINT id, NMHDR *pTTTStruct, LRESULT *pResult);
	afx_msg void OnToolTipNotify(NMHDR *pTTTStruct, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
	virtual void GetToolTipText(NMHDR *pTTTStruct, CString &strTipText);
	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI ) const;
	CToolTipCtrl m_objToolTip;
	CToolBar	m_objToolBar;
	CRect		m_objTbRect;
	CPreviewHtmlView*	m_pPreview;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGWIKIINP_H__B687EC49_D3C8_48B4_B9DA_3C66CDD2FEEE__INCLUDED_)

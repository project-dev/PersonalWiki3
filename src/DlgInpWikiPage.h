#if !defined(AFX_DLGINPWIKIPAGE_H__1B0F23F7_C11E_4185_8FAC_869475DC5055__INCLUDED_)
#define AFX_DLGINPWIKIPAGE_H__1B0F23F7_C11E_4185_8FAC_869475DC5055__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInpWikiPage.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInpWikiPage �_�C�A���O
#include "AbstractBaseWnd.h"
class CDlgInpWikiPage : public CDialog, CAbstractBaseWnd
{
// �R���X�g���N�V����
public:
	CDlgInpWikiPage(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgInpWikiPage)
	enum { IDD = IDD_DLG_INPWIKIPAGE };
	CString	m_strWikiName;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgInpWikiPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgInpWikiPage)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGINPWIKIPAGE_H__1B0F23F7_C11E_4185_8FAC_869475DC5055__INCLUDED_)

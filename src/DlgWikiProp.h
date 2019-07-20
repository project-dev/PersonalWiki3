#if !defined(AFX_DLGWIKIPROP_H__1DAF6431_547E_4034_A850_59D55582A6D3__INCLUDED_)
#define AFX_DLGWIKIPROP_H__1DAF6431_547E_4034_A850_59D55582A6D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWikiProp.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWikiProp �_�C�A���O

class CDlgWikiProp : public CDialog{
// �R���X�g���N�V����
public:
	CDlgWikiProp(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	CString m_strRealPath;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgWikiProp)
	enum { IDD = IDD_DLG_WIKI_PROP };
	BOOL	m_bCold;
	BOOL	m_bCrypt;
	COleDateTime	m_objUpdateDt;
	COleDateTime	m_objCreateDt;
	CString	m_strWikiPath;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgWikiProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgWikiProp)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CString m_strPropFile;
	BOOL m_bPreCrypt;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGWIKIPROP_H__1DAF6431_547E_4034_A850_59D55582A6D3__INCLUDED_)

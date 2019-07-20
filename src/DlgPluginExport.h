#if !defined(AFX_DLGPLUGINEXPORT_H__550304F9_4C41_4892_BF58_25482F5D67A9__INCLUDED_)
#define AFX_DLGPLUGINEXPORT_H__550304F9_4C41_4892_BF58_25482F5D67A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPluginExport.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPluginExport �_�C�A���O
#include "AbstractBaseWnd.h"
class CDlgPluginExport : public CDialog, CAbstractBaseWnd{
// �R���X�g���N�V����
public:
	CDlgPluginExport(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgPluginExport)
	enum { IDD = IDD_DLG_PLUGIN_EXPORT };
	CComboBox	m_objExpCmb;
	CString	m_strWikiPath;
	//}}AFX_DATA

	CStringArray m_arrPluginName;
	CString m_strSelPlugin;

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgPluginExport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgPluginExport)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGPLUGINEXPORT_H__550304F9_4C41_4892_BF58_25482F5D67A9__INCLUDED_)

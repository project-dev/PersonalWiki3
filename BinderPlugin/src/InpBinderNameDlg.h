#if !defined(AFX_INPBINDERNAMEDLG_H__5B522644_B7F6_4781_8E07_9C342175FEB3__INCLUDED_)
#define AFX_INPBINDERNAMEDLG_H__5B522644_B7F6_4781_8E07_9C342175FEB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InpBinderNameDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CInpBinderNameDlg �_�C�A���O

class CInpBinderNameDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CInpBinderNameDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CInpBinderNameDlg)
	enum { IDD = IDD_INP_BINDER_NAME_DLG };
	CString	m_strName;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CInpBinderNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CInpBinderNameDlg)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_INPBINDERNAMEDLG_H__5B522644_B7F6_4781_8E07_9C342175FEB3__INCLUDED_)

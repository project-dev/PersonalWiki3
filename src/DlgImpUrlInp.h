#if !defined(AFX_DLGIMPURLINP_H__CFD0C665_0830_47D7_B4E3_44BDC6CA3D36__INCLUDED_)
#define AFX_DLGIMPURLINP_H__CFD0C665_0830_47D7_B4E3_44BDC6CA3D36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgImpUrlInp.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgImpUrlInp �_�C�A���O

class CDlgImpUrlInp : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgImpUrlInp(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgImpUrlInp)
	enum { IDD = IDD_DLGURLIMP };
	CString	m_strID;
	CString	m_strPage;
	CString	m_strPass;
	CString	m_strUrl;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgImpUrlInp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgImpUrlInp)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGIMPURLINP_H__CFD0C665_0830_47D7_B4E3_44BDC6CA3D36__INCLUDED_)

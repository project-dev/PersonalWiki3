// InpBinderNameDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "binderplugin.h"
#include "InpBinderNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInpBinderNameDlg �_�C�A���O


CInpBinderNameDlg::CInpBinderNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInpBinderNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInpBinderNameDlg)
	m_strName = _T("");
	//}}AFX_DATA_INIT
}


void CInpBinderNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInpBinderNameDlg)
	DDX_Text(pDX, IDC_BINDER_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInpBinderNameDlg, CDialog)
	//{{AFX_MSG_MAP(CInpBinderNameDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInpBinderNameDlg ���b�Z�[�W �n���h��

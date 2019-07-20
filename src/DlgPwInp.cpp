// DlgPwInp.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "personalwiki.h"
#include "DlgPwInp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPwInp �_�C�A���O


CDlgPwInp::CDlgPwInp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPwInp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPwInp)
	m_strPassWord = _T("");
	//}}AFX_DATA_INIT
}


void CDlgPwInp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPwInp)
	DDX_Text(pDX, IDC_ED_PASSWORD, m_strPassWord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPwInp, CDialog)
	//{{AFX_MSG_MAP(CDlgPwInp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPwInp ���b�Z�[�W �n���h��

BOOL CDlgPwInp::PreTranslateMessage(MSG* pMsg){
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

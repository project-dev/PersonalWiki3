// DlgPluginExport.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "personalwiki.h"
#include "DlgPluginExport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPluginExport �_�C�A���O


CDlgPluginExport::CDlgPluginExport(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPluginExport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPluginExport)
	m_strWikiPath = _T("");
	//}}AFX_DATA_INIT
}


void CDlgPluginExport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPluginExport)
	DDX_Control(pDX, IDC_CMB_EXPORT, m_objExpCmb);
	DDX_Text(pDX, IDC_ED_WIKIPATH, m_strWikiPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPluginExport, CDialog)
	//{{AFX_MSG_MAP(CDlgPluginExport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPluginExport ���b�Z�[�W �n���h��

BOOL CDlgPluginExport::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������

	int nSize = m_arrPluginName.GetSize();
	for(int i = 0; i < nSize; i++){
		m_objExpCmb.AddString(m_arrPluginName.GetAt(i));
	}
	m_objExpCmb.SetCurSel(0);

	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CDlgPluginExport::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	m_objExpCmb.GetWindowText(m_strSelPlugin);
	CDialog::OnOK();
}

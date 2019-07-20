// DlgDateInp.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "DlgDateInp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDateInp �_�C�A���O


CDlgDateInp::CDlgDateInp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDateInp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDateInp)
	m_strDetail = _T("");
	m_strHelp = _T("");
	//}}AFX_DATA_INIT
}


void CDlgDateInp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDateInp)
//	DDX_Control(pDX, IDC_CMB_CATEGORY, m_objCmbCategory);
	DDX_Text(pDX, IDC_ED_DETAIL, m_strDetail);
	DDX_Text(pDX, IDC_ED_HELP, m_strHelp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDateInp, CDialog)
	//{{AFX_MSG_MAP(CDlgDateInp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDateInp ���b�Z�[�W �n���h��

BOOL CDlgDateInp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	CString strTitle;
	strTitle.Format("%s�̗\�����", m_ojbDate.Format("%Y/%m/%d"));
	SetWindowText(strTitle);
	m_strHelp = "�����ɂ��Ẵw���v\r\n"
				"Wiki�`���̏����ŕ�����ɑ������{������o���܂��B\r\n"
				"\r\n"
				"������\r\n"
				"�I�𕶎���𑾎��ɂ��܂��B\r\n"
				"�@''������''\r\n"
				"\r\n"
				"���Α�\r\n"
				"�I�𕶎�����Α̂ɂ��܂��B\r\n"
				"�@'''������'''\r\n"
				"\r\n"
				"���ł�������\r\n"
				"�I�𕶎����ł������܂��B\r\n"
				"�@%%%������%%%\r\n"
				"\r\n"
				"�������N\r\n"
				"�I�𕶎���������N�ɂ��܂��B\r\n"
				"�@[[URL]]\r\n"
				"�@[[���O:URL]]\r\n"
				"�@[[YYYY/MM/DD�`��]]\r\n"
				"\r\n"
				"���摜\r\n"
				"�摜��\�����܂��B\r\n"
				"�@&img{�t�@�C����};\r\n";

	UpdateData(FALSE);


	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

BOOL CDlgDateInp::PreTranslateMessage(MSG* pMsg){
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

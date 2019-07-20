// DlgWikiProp.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "personalwiki.h"
#include "DlgWikiProp.h"
#include "devlib.h"
#include "Cryptography.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWikiProp �_�C�A���O


CDlgWikiProp::CDlgWikiProp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWikiProp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWikiProp)
	m_bCold = FALSE;
	m_bCrypt = FALSE;
	m_objUpdateDt = COleDateTime::GetCurrentTime();
	m_objCreateDt = COleDateTime::GetCurrentTime();
	m_strWikiPath = _T("");
	//}}AFX_DATA_INIT
}


void CDlgWikiProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWikiProp)
	DDX_Check(pDX, IDC_CHK_COLD, m_bCold);
	DDX_Check(pDX, IDC_CHK_CRYPT, m_bCrypt);
	DDX_Text(pDX, IDC_ED_UPDATEDATE, m_objUpdateDt);
	DDX_Text(pDX, IDC_ED_CREATEDATE, m_objCreateDt);
	DDX_Text(pDX, IDC_ED_WIKIPATH, m_strWikiPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWikiProp, CDialog)
	//{{AFX_MSG_MAP(CDlgWikiProp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWikiProp ���b�Z�[�W �n���h��

BOOL CDlgWikiProp::OnInitDialog(){
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	CFileStatus state;
	if(CFile::GetStatus(m_strRealPath, state)){
		m_objCreateDt = state.m_ctime.GetTime();
		m_objUpdateDt = state.m_mtime.GetTime();
	}

	m_strPropFile = m_strRealPath;
	m_strPropFile.MakeLower();
	m_strPropFile.Replace(".pwd", "\\.property");

	m_bCold = ::GetPrivateProfileInt("Status", "Cold", 0, m_strPropFile);
	m_bCrypt = ::GetPrivateProfileInt("Status", "Cryptography", 0, m_strPropFile);
//	::GetPrivateProfileInt("Status", "Comment", 0, m_strPropFile);
//	m_strComment = "";
	m_bPreCrypt = m_bCrypt;
	UpdateData(FALSE);
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CDlgWikiProp::OnOK() {
	UpdateData(TRUE);
	CString strDir = m_strRealPath;
	strDir.Replace(".pwd", "");
	::CreateDir(strDir, NULL);
	CString strVal;
	::WritePrivateProfileString("Status", "Cold", m_bCold ? "1" : "0", m_strPropFile);
	::WritePrivateProfileString("Status", "Cryptography", m_bCrypt ? "1" : "0", m_strPropFile);

	CCryptography cryp;
	BOOL bSave = FALSE;

	CStdioFile file;
	if(!file.Open(m_strRealPath, CFile::modeRead)){
		throw(0);
	}

	CString strWikiText = "";
	CString strLine = "";
	while(file.ReadString(strLine)){
		strWikiText += strLine;
		if(!m_bPreCrypt){
			strWikiText += "\r\n";
		}
	}
	file.Close();
	
	if(!m_bPreCrypt && m_bCrypt){
		bSave = TRUE;

		//�Í�������
		int nLen = strWikiText.GetLength();
		byte *pBuff = NULL;
		char *pszFrom = strWikiText.GetBuffer(strWikiText.GetLength());
		cryp.EncodeData((byte*)pszFrom, nLen, "PersonalWiki", pBuff);
		strWikiText.ReleaseBuffer();
		strWikiText = pBuff;

	}else if(m_bPreCrypt && !m_bCrypt){
		bSave = TRUE;

		//����������
		int nLen = strWikiText.GetLength();
		byte *pBuff = NULL;
		char *pszFrom = strWikiText.GetBuffer(strWikiText.GetLength());
		cryp.DecodeData((byte*)pszFrom, nLen, "PersonalWiki", pBuff);
		strWikiText.ReleaseBuffer();
		if(pBuff){
			strWikiText = pBuff;
		}else{
			strWikiText.Empty();
		}
	}
	if(bSave){
		CFile file;
		file.Open(m_strRealPath, CFile::modeCreate | CFile::modeNoInherit | CFile::modeReadWrite);
		file.Write(strWikiText.GetBuffer(0), strWikiText.GetLength());
		file.Flush();
		file.Close();
	}
	CDialog::OnOK();
}

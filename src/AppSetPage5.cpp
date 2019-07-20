// AppSetPage5.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "AppSetPage5.h"
#include "MainFrm.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage5 �_�C�A���O


CAppSetPage5::CAppSetPage5(CWnd* pParent /*=NULL*/)
	: CDialog(CAppSetPage5::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAppSetPage5)
	m_strDetail = _T("");
	//}}AFX_DATA_INIT
}


void CAppSetPage5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppSetPage5)
	DDX_Control(pDX, IDC_PLG_LIST, m_objList);
	DDX_Text(pDX, IDC_ED_PLG_DETAIL, m_strDetail);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppSetPage5, CDialog)
	//{{AFX_MSG_MAP(CAppSetPage5)
	ON_BN_CLICKED(IDC_BTN_PLG_SET, OnBtnPlgSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage5 ���b�Z�[�W �n���h��

BOOL CAppSetPage5::UpdateInfo(){

	int nCnt = m_objList.GetItemCount();
	CPWikiPlugin* pPlug;
	for(int i = 0; i < nCnt; i++){
		pPlug = (CPWikiPlugin*)m_objList.GetItemData(i);
		pPlug->SetUse(m_objList.GetCheck(i));
	}
	
	return TRUE;
}

BOOL CAppSetPage5::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_objList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_objList.InsertColumn(0, "���p");
	m_objList.InsertColumn(1, "���O");
	m_objList.InsertColumn(2, "�o�[�W����");
	m_objList.InsertColumn(3, "�^�C�v");
	m_objList.InsertColumn(4, "�T�v");
	
	
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage5::OnInitDialog : pFrm is null");
	}
	int nCnt = pFrm->m_objPlugins.GetSize();
	CString strVer;
	CString strTypes;
	CString strType;
	for(int i = 0; i < nCnt; i++){
		CPWikiPlugin *pPlug = pFrm->m_objPlugins.GetPlugin(i);
		int nIndex = m_objList.InsertItem(i, "", 0);
		m_objList.SetItemText(nIndex, 1, pPlug->m_objInfo.szName);
		strVer.Format("%d.%d.%d",
					pPlug->m_objInfo.nPlgVersion[0],
					pPlug->m_objInfo.nPlgVersion[1],
					pPlug->m_objInfo.nPlgVersion[2]);
		m_objList.SetItemText(nIndex, 2, strVer);
		strTypes = "";
		for(int i = 0; i < eTypeEnd; i++){
			if(!pPlug->m_objInfo.arrType[i]){
				continue;
			}
			switch(i){
			case eTypeWikiFormat:
				strType = "����";
				break;
			case eTypeTabExtend:
				strType = "�^�u";
				break;
			case eTypeExportExtend:
				strType = "�G�N�X�|�[�g";
				break;
			case eTypeInfoExtend:
				strType = "���o�[";
				break;
			default:
				strType = "";
				break;
			}
			if(!strType.IsEmpty() && !strTypes.IsEmpty()){
				strType = "/" + strType ;
			}
			strTypes += strType;
		}

		m_objList.SetItemText(nIndex, 3, strTypes);
		m_objList.SetItemText(nIndex, 4, pPlug->m_objInfo.szInfo);
		m_objList.SetItemData(nIndex, (LPARAM)pPlug);
		m_objList.SetCheck(nIndex, pPlug->GetUse());
	}
	
	SetColumnWidthLC(&m_objList);
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CAppSetPage5::OnBtnPlgSet(){
	int nIndex = m_objList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if(nIndex == -1){
		return;
	}
	CPWikiPlugin *pPlug = (CPWikiPlugin*)m_objList.GetItemData(nIndex);
	pPlug->ShowSetupDlg();
}

BOOL CAppSetPage5::PreTranslateMessage(MSG* pMsg){
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

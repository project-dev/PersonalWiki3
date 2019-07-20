// AppSetPage8.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "personalwiki.h"
#include "AppSetPage8.h"
#include "MainFrm.h"
#include "IniFile.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage8 ダイアログ


CAppSetPage8::CAppSetPage8(CWnd* pParent /*=NULL*/)
	: CDialog(CAppSetPage8::IDD, pParent)
{
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage8::CAppSetPage8 : pFrm is null");
	}
	LINKINFO objLink;
	pFrm->m_objIniFile.GetLinkInfoIniData(objLink);

	//{{AFX_DATA_INIT(CAppSetPage8)
	m_bUseUSBLink = objLink.bUseUSBLink;
	m_strPath1 = objLink.szLinkDir[0];
	m_strPath2 = objLink.szLinkDir[1];
	m_strPath3 = objLink.szLinkDir[2];
	m_strPath4 = objLink.szLinkDir[3];
	m_bUseNetDrv = objLink.bUseNetDrv;
	//}}AFX_DATA_INIT
}


void CAppSetPage8::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppSetPage8)
	DDX_Check(pDX, IDC_CHK_USE_USB_LINK, m_bUseUSBLink);
	DDX_Text(pDX, IDC_ED_PATH1, m_strPath1);
	DDV_MaxChars(pDX, m_strPath1, 255);
	DDX_Text(pDX, IDC_ED_PATH2, m_strPath2);
	DDV_MaxChars(pDX, m_strPath2, 255);
	DDX_Text(pDX, IDC_ED_PATH3, m_strPath3);
	DDV_MaxChars(pDX, m_strPath3, 255);
	DDX_Text(pDX, IDC_ED_PATH4, m_strPath4);
	DDV_MaxChars(pDX, m_strPath4, 255);
	DDX_Check(pDX, IDC_CHK_NETDRV, m_bUseNetDrv);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppSetPage8, CDialog)
	//{{AFX_MSG_MAP(CAppSetPage8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage8 メッセージ ハンドラ
void CAppSetPage8::UpdateInfo(){
	UpdateData(TRUE);
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage8::UpdateInfo : pFrm is null");
	}
	LINKINFO objIni;
	objIni.bUseUSBLink	= m_bUseUSBLink;
	objIni.bUseNetDrv	= m_bUseNetDrv;
	strncpy(objIni.szLinkDir[0], m_strPath1, MAX_PATH);
	strncpy(objIni.szLinkDir[1], m_strPath2, MAX_PATH);
	strncpy(objIni.szLinkDir[2], m_strPath3, MAX_PATH);
	strncpy(objIni.szLinkDir[3], m_strPath4, MAX_PATH);

	pFrm->m_objIniFile.SetLinkInfoIniData(&objIni);

}

BOOL CAppSetPage8::PreTranslateMessage(MSG* pMsg){
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CAppSetPage8::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

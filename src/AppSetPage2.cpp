// AppSetPage2.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "AppSetPage2.h"
#include "MainFrm.h"
#include "PWikiDoc.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage2 ダイアログ


CAppSetPage2::CAppSetPage2(CWnd* pParent /*=NULL*/)
	: CDialog(CAppSetPage2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAppSetPage2)
	m_bFri = FALSE;
	m_bMon = FALSE;
	m_bSat = FALSE;
	m_bSun = FALSE;
	m_bThu = FALSE;
	m_bTue = FALSE;
	m_bWed = FALSE;
	//}}AFX_DATA_INIT
}


void CAppSetPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppSetPage2)
	DDX_Control(pDX, IDC_SPDAY_LIST, m_objSpDayList);
	DDX_Check(pDX, IDC_CHK_FRIDAY, m_bFri);
	DDX_Check(pDX, IDC_CHK_MONDAY, m_bMon);
	DDX_Check(pDX, IDC_CHK_SATDAY, m_bSat);
	DDX_Check(pDX, IDC_CHK_SUNDAY, m_bSun);
	DDX_Check(pDX, IDC_CHK_THUDAY, m_bThu);
	DDX_Check(pDX, IDC_CHK_TUEDAY, m_bTue);
	DDX_Check(pDX, IDC_CHK_WEDDAY, m_bWed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppSetPage2, CDialog)
	//{{AFX_MSG_MAP(CAppSetPage2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage2 メッセージ ハンドラ

BOOL CAppSetPage2::UpdateInfo(){
	UpdateData();
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage2::UpdateInfo : pFrm is null");
	}
	HOLIDAYINFO objIni;
	CButton *pBtn1;
	CButton *pBtn2;
	CButton *pBtn3;
	pBtn1 = (CButton*)GetDlgItem(IDC_RAD_NONE);
	pBtn2 = (CButton*)GetDlgItem(IDC_RAD_2HOLIDAY);
	pBtn3 = (CButton*)GetDlgItem(IDC_RAD_CUSTOM1);

	if(pBtn1->GetCheck()){
		objIni.eType = HT_NONE;
	}else if(pBtn2->GetCheck()){
		objIni.eType = HT_WEEK2HOLIDAY;
	}else{
		objIni.eType = HT_SEL_WEEKDAY;
	}
	objIni.bWeekDays[0] = m_bSun;
	objIni.bWeekDays[1] = m_bMon;
	objIni.bWeekDays[2] = m_bTue;
	objIni.bWeekDays[3] = m_bWed;
	objIni.bWeekDays[4] = m_bThu;
	objIni.bWeekDays[5] = m_bFri;
	objIni.bWeekDays[6] = m_bSat;

	pFrm->m_objIniFile.SetHolidayInfoIniData(&objIni);

	int nCnt = m_objSpDayList.GetItemCount();
	for(int i = 0; i < nCnt; i++){
		BOOL bCheck = m_objSpDayList.GetCheck(i);
		CString strName = m_objSpDayList.GetItemText(i, 2);
		CString strSpFile;
		strSpFile.Format("%sSpDay\\%s", GetBasePath(), strName);
		::WritePrivateProfileString("Setting", "Use", bCheck ? "1" : "0", strSpFile);
	}

	return TRUE;
}

BOOL CAppSetPage2::OnInitDialog() {
	CDialog::OnInitDialog();
	
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage2::OnInitDialog : pFrm is null");
	}
	HOLIDAYINFO objIni;
	pFrm->m_objIniFile.GetHolidayInfoIniData(objIni);
	CButton *pBtn;
	switch(objIni.eType){
	case HT_NONE:
		pBtn = (CButton*)GetDlgItem(IDC_RAD_NONE);
		break;
	case HT_WEEK2HOLIDAY:
		pBtn = (CButton*)GetDlgItem(IDC_RAD_2HOLIDAY);
		break;
	case HT_SEL_WEEKDAY:
		pBtn = (CButton*)GetDlgItem(IDC_RAD_CUSTOM1);
		break;
	}
	pBtn->SetCheck(1);
	
	m_bSun = objIni.bWeekDays[0];
	m_bMon = objIni.bWeekDays[1];
	m_bTue = objIni.bWeekDays[2];
	m_bWed = objIni.bWeekDays[3];
	m_bThu = objIni.bWeekDays[4];
	m_bFri = objIni.bWeekDays[5];
	m_bSat = objIni.bWeekDays[6];
	UpdateData(FALSE);

	m_objSpDayList.InsertColumn(0, "名前");
	m_objSpDayList.InsertColumn(1, "ファイル名");
	m_objSpDayList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);

	CString strBase = GetBasePath();
	CString strSpDir = strBase + "SpDay";
	CString strFind = strSpDir + "\\*.spd";
	BOOL bFirst = TRUE;
	WIN32_FIND_DATA wfd;
	HANDLE hRet = NULL;
	while(TRUE){
		if(bFirst){
			hRet = ::FindFirstFile(strFind, &wfd);
			if(hRet == INVALID_HANDLE_VALUE){
				break;
			}
			bFirst = FALSE;
		}else{
			if(!::FindNextFile(hRet, &wfd)){
				break;
			}
		}
		CString strIni;
		char szVal[MAX_PATH + 1];
		CString strName;
		memset(szVal, 0, MAX_PATH + 1);
		strIni = strSpDir + "\\" + wfd.cFileName;
		::GetPrivateProfileString("Name", "Name", "", szVal, MAX_PATH, strIni);
		strName = szVal;

		if(!strName.IsEmpty()){
			int nUse = ::GetPrivateProfileInt("Setting", "Use", 1, strIni);
			int nIndex = m_objSpDayList.InsertItem(m_objSpDayList.GetItemCount(), szVal, 0);
			m_objSpDayList.SetItemText(nIndex, 1, wfd.cFileName);
			m_objSpDayList.SetCheck(nIndex, nUse);
		}
	}
	::FindClose(hRet);
	SetColumnWidthLC(&m_objSpDayList);

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

BOOL CAppSetPage2::PreTranslateMessage(MSG* pMsg){
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

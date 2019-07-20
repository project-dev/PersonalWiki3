// PWikiIniFile.cpp: CPWikiIniFile クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "personalwiki.h"
#include "PWikiIniFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
DLGINFO		CPWikiIniFile::m_objDlgInfo;
MAININFO	CPWikiIniFile::m_objMainInfo;
APPINFO		CPWikiIniFile::m_objAppInfo;
WIKIINFO	CPWikiIniFile::m_objWikiInfo;
DEBUGINFO	CPWikiIniFile::m_objDebugInfo;
HOLIDAYINFO	CPWikiIniFile::m_objHolidayInfo;
LINKINFO	CPWikiIniFile::m_objLinkInfo;
FONTINFO	CPWikiIniFile::m_objFontInfo;

INIDATA CPWikiIniFile::arrData[] = {
	//Type		Secssion	Key					Data											Default					Len
	//メインウィンドウ情報
	{IT_INT,	"MAIN",		"X",				&CPWikiIniFile::m_objMainInfo.nX,				(LPVOID)0,				0},
	{IT_INT,	"MAIN",		"Y",				&CPWikiIniFile::m_objMainInfo.nY,				(LPVOID)0,				0},
	{IT_INT,	"MAIN",		"WIDTH",			&CPWikiIniFile::m_objMainInfo.nWidth,			(LPVOID)640,			0},
	{IT_INT,	"MAIN",		"HEIGHT",			&CPWikiIniFile::m_objMainInfo.nHeight,			(LPVOID)480,			0},
	{IT_INT,	"MAIN",		"SPLITLW",			&CPWikiIniFile::m_objMainInfo.nSplitLWidth,		(LPVOID)200,			0},
	{IT_INT,	"MAIN",		"SPLITTH",			&CPWikiIniFile::m_objMainInfo.nSplitTHeight,	(LPVOID)100,			0},

	//休暇設定
	{IT_INT,	"HOLIDAY",	"TYPE",				&CPWikiIniFile::m_objHolidayInfo.eType,			(LPVOID)0,				0},
	{IT_INT,	"HOLIDAY",	"SUN",				&CPWikiIniFile::m_objHolidayInfo.bWeekDays[0],	(LPVOID)0,				0},
	{IT_INT,	"HOLIDAY",	"MON",				&CPWikiIniFile::m_objHolidayInfo.bWeekDays[1],	(LPVOID)0,				0},
	{IT_INT,	"HOLIDAY",	"TUE",				&CPWikiIniFile::m_objHolidayInfo.bWeekDays[2],	(LPVOID)0,				0},
	{IT_INT,	"HOLIDAY",	"WED",				&CPWikiIniFile::m_objHolidayInfo.bWeekDays[3],	(LPVOID)0,				0},
	{IT_INT,	"HOLIDAY",	"THU",				&CPWikiIniFile::m_objHolidayInfo.bWeekDays[4],	(LPVOID)0,				0},
	{IT_INT,	"HOLIDAY",	"FRI",				&CPWikiIniFile::m_objHolidayInfo.bWeekDays[5],	(LPVOID)0,				0},
	{IT_INT,	"HOLIDAY",	"SAT",				&CPWikiIniFile::m_objHolidayInfo.bWeekDays[6],	(LPVOID)0,				0},

	//情報ダイアログ情報
	{IT_INT,	"DLGINFO",	"X",				&CPWikiIniFile::m_objDlgInfo.nX,				(LPVOID)0,				0},
	{IT_INT,	"DLGINFO",	"Y",				&CPWikiIniFile::m_objDlgInfo.nY,				(LPVOID)0,				0},
	{IT_BOOL,	"DLGINFO",	"ShowSc",			&CPWikiIniFile::m_objDlgInfo.bShowSc,			(LPVOID)TRUE,			0},
	{IT_BOOL,	"DLGINFO",	"ShowFix",			&CPWikiIniFile::m_objDlgInfo.bShowFix,			(LPVOID)TRUE,			0},
	{IT_BOOL,	"DLGINFO",	"ShowToDo",			&CPWikiIniFile::m_objDlgInfo.bShowToDo,			(LPVOID)TRUE,			0},
	{IT_BOOL,	"DLGINFO",	"ShowSec",			&CPWikiIniFile::m_objDlgInfo.bIsShowSec,		(LPVOID)TRUE,			0},
	{IT_BOOL,	"DLGINFO",	"ShowTime",			&CPWikiIniFile::m_objDlgInfo.bShowTime,			(LPVOID)TRUE,			0},

	//基本設定
	{IT_BOOL,	"APPINFO",	"DelEndToDo",		&CPWikiIniFile::m_objAppInfo.bEndToDoDel,		(LPVOID)FALSE,			0},
	{IT_INT,	"APPINFO",	"DelEndToDoSpan",	&CPWikiIniFile::m_objAppInfo.nEndToDoDelSpan,	(LPVOID)30,				0},
	{IT_BOOL,	"APPINFO",	"UsePassWord",		&CPWikiIniFile::m_objAppInfo.bUsePassWord,		(LPVOID)FALSE,			0},
	{IT_STRING,	"APPINFO",	"PassWord",			&CPWikiIniFile::m_objAppInfo.szPassWord,		(LPVOID)"",				33},
	{IT_INT,	"APPINFO",	"StartActiveTab",	&CPWikiIniFile::m_objAppInfo.nStartActTab,		(LPVOID)0,				0},
	{IT_BOOL,	"APPINFO",	"UseToDay",			&CPWikiIniFile::m_objAppInfo.bUseToDay,			(LPVOID)FALSE,			0},
	{IT_BOOL,	"APPINFO",	"RunMainShow",		&CPWikiIniFile::m_objAppInfo.bRunMainWndShow,	(LPVOID)FALSE,			0},

	//Wiki設定
	{IT_BOOL,	"WIKINFO",	"UseRet",			&CPWikiIniFile::m_objWikiInfo.bUseRet,			(LPVOID)FALSE,			0},
	{IT_STRING,	"WIKINFO",	"CSS_NAME",			&CPWikiIniFile::m_objWikiInfo.szCss,			(LPVOID)"style.css",	MAX_PATH},
	{IT_BOOL,	"WIKINFO",	"UseTBLink",		&CPWikiIniFile::m_objWikiInfo.bUseTopBtmLnk,	(LPVOID)TRUE,			0},
	{IT_BOOL,	"WIKINFO",	"UseShowAttach",	&CPWikiIniFile::m_objWikiInfo.bUseShowAttach,	(LPVOID)TRUE,			0},
	{IT_BOOL,	"WIKINFO",	"UseShowConvTime",	&CPWikiIniFile::m_objWikiInfo.bUseShowConvTime,	(LPVOID)TRUE,			0},

	//デバッグ
	{IT_BOOL,	"DEBUGINFO","LogOut",			&CPWikiIniFile::m_objDebugInfo.bLogOut,			(LPVOID)FALSE,			0},
	{IT_BOOL,	"DEBUGINFO","FatalLogOut",		&CPWikiIniFile::m_objDebugInfo.bFatalLogOut,	(LPVOID)FALSE,			0},
	{IT_BOOL,	"DEBUGINFO","AppLogOut",		&CPWikiIniFile::m_objDebugInfo.bAppLogOut,		(LPVOID)FALSE,			0},
	{IT_BOOL,	"DEBUGINFO","ExceptLogOut",		&CPWikiIniFile::m_objDebugInfo.bExceptLogOut,	(LPVOID)FALSE,			0},

	//連携機能
	{IT_BOOL,	"LINKINFO","UseLink",			&CPWikiIniFile::m_objLinkInfo.bUseUSBLink,		(LPVOID)FALSE,			0},
	{IT_STRING,	"LINKINFO","PATH_01",			&CPWikiIniFile::m_objLinkInfo.szLinkDir[0],		(LPVOID)"Wiki",			MAX_PATH},
	{IT_STRING,	"LINKINFO","PATH_02",			&CPWikiIniFile::m_objLinkInfo.szLinkDir[1],		(LPVOID)"PersonalWiki",	MAX_PATH},
	{IT_STRING,	"LINKINFO","PATH_03",			&CPWikiIniFile::m_objLinkInfo.szLinkDir[2],		(LPVOID)"",				MAX_PATH},
	{IT_STRING,	"LINKINFO","PATH_04",			&CPWikiIniFile::m_objLinkInfo.szLinkDir[3],		(LPVOID)"",				MAX_PATH},
	{IT_BOOL,	"LINKINFO","NETDRV",			&CPWikiIniFile::m_objLinkInfo.bUseNetDrv,		(LPVOID)FALSE,			0},

	//フォント
	{IT_STRING,	"FONT",		"CAL_FONT_NAME",	&CPWikiIniFile::m_objFontInfo.szCalFontName,	(LPVOID)"ＭＳ ゴシック",LF_FACESIZE},
	{IT_INT,	"FONT",		"CAL_FONT_HEIGHT",	&CPWikiIniFile::m_objFontInfo.lCalHeight,		(LPVOID)10,				0},
	{IT_STRING,	"FONT",		"EDIT_FONT_NAME",	&CPWikiIniFile::m_objFontInfo.szEditFontName,	(LPVOID)"ＭＳ ゴシック",LF_FACESIZE},
	{IT_INT,	"FONT",		"EDIT_FONT_HEIGHT",	&CPWikiIniFile::m_objFontInfo.lEditHeight,		(LPVOID)10,				0},
	{IT_STRING,	"FONT",		"TODO_FONT_NAME",	&CPWikiIniFile::m_objFontInfo.szToDoFontName,	(LPVOID)"ＭＳ ゴシック",LF_FACESIZE},
	{IT_INT,	"FONT",		"TODO_FONT_HEIGHT",	&CPWikiIniFile::m_objFontInfo.lToDoHeight,		(LPVOID)10,				0},
	{IT_STRING,	"FONT",		"ETC_FONT_NAME",	&CPWikiIniFile::m_objFontInfo.szEtcFontName,	(LPVOID)"ＭＳ ゴシック",LF_FACESIZE},
	{IT_INT,	"FONT",		"ETC_FONT_HEIGHT",	&CPWikiIniFile::m_objFontInfo.lEtcHeight,		(LPVOID)10,				0},
	
};

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CPWikiIniFile::CPWikiIniFile(){
	memset(&m_objDlgInfo, 0, sizeof(DLGINFO));
	memset(&m_objMainInfo, 0, sizeof(MAININFO));
	memset(&m_objAppInfo, 0, sizeof(APPINFO));
	memset(&m_objWikiInfo, 0, sizeof(WIKIINFO));
	memset(&m_objDebugInfo, 0, sizeof(DEBUGINFO));
	memset(&m_objHolidayInfo, 0, sizeof(HOLIDAYINFO));
	memset(&m_objLinkInfo, 0, sizeof(LINKINFO));
	memset(&m_objFontInfo, 0, sizeof(FONTINFO));
}

CPWikiIniFile::~CPWikiIniFile(){

}

BOOL CPWikiIniFile::OnIniFileAccess(INIDATA* &pIniData, int &nCnt){
	pIniData = arrData;
	nCnt = sizeof(arrData) / sizeof(INIDATA);
	return TRUE;
}

void CPWikiIniFile::GetDlgInfoIniData(DLGINFO &objDlgInfo){
	memcpy(&objDlgInfo, &m_objDlgInfo, sizeof(m_objDlgInfo));
}
void CPWikiIniFile::SetDlgInfoIniData(PDLGINFO pDlgInfo){
	memcpy(&m_objDlgInfo, pDlgInfo, sizeof(m_objDlgInfo));
}

void CPWikiIniFile::GetMainInfoIniData(MAININFO &objMainInfo){
	memcpy(&objMainInfo, &m_objMainInfo, sizeof(m_objMainInfo));
}
void CPWikiIniFile::SetMainInfoIniData(PMAININFO pMainInfo){
	memcpy(&m_objMainInfo, pMainInfo, sizeof(m_objMainInfo));
}

void CPWikiIniFile::GetAppInfoIniData(APPINFO &objAppInfo){
	memcpy(&objAppInfo, &m_objAppInfo, sizeof(m_objAppInfo));
}
void CPWikiIniFile::SetAppInfoIniData(PAPPINFO pAppInfo){
	memcpy(&m_objAppInfo, pAppInfo, sizeof(m_objAppInfo));
}

void CPWikiIniFile::GetWikiInfoIniData(WIKIINFO &objWikiInfo){
	memcpy(&objWikiInfo, &m_objWikiInfo, sizeof(m_objWikiInfo));
}
void CPWikiIniFile::SetWikiInfoIniData(PWIKIINFO pWikiInfo){
	memcpy(&m_objWikiInfo, pWikiInfo, sizeof(m_objWikiInfo));
}

void CPWikiIniFile::GetDebugInfoIniData(DEBUGINFO &objDebugInfo){
	memcpy(&objDebugInfo, &m_objDebugInfo, sizeof(objDebugInfo));
}
void CPWikiIniFile::SetDebugInfoIniData(PDEBUGINFO pDebugInfo){
	memcpy(&m_objDebugInfo, pDebugInfo, sizeof(m_objDebugInfo));
}

void CPWikiIniFile::GetHolidayInfoIniData(HOLIDAYINFO &objHolidayInfo){
	memcpy(&objHolidayInfo, &m_objHolidayInfo, sizeof(objHolidayInfo));
}
void CPWikiIniFile::SetHolidayInfoIniData(PHOLIDAYINFO pHolidayInfo){
	memcpy(&m_objHolidayInfo, pHolidayInfo, sizeof(m_objHolidayInfo));
}

void CPWikiIniFile::SetLinkInfoIniData(PLINKINFO pLinkInfo){
	memcpy(&m_objLinkInfo, pLinkInfo, sizeof(m_objLinkInfo));
}
void CPWikiIniFile::GetLinkInfoIniData(LINKINFO &objLinkInfo){
	memcpy(&objLinkInfo, &m_objLinkInfo, sizeof(m_objLinkInfo));
}

void CPWikiIniFile::SetFontInfoIniData(PFONTINFO pFontInfo){
	memcpy(&m_objFontInfo, pFontInfo, sizeof(m_objFontInfo));
}
void CPWikiIniFile::GetFontInfoIniData(FONTINFO &objFontInfo){
	memcpy(&objFontInfo, &m_objFontInfo, sizeof(m_objFontInfo));
}


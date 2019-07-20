// PWikiIniFile.h: CPWikiIniFile クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PWIKIINIFILE_H__A80952B8_EC3A_4533_BB1E_D989DEFCE1B8__INCLUDED_)
#define AFX_PWIKIINIFILE_H__A80952B8_EC3A_4533_BB1E_D989DEFCE1B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IniFile.h"

/**
 * @brif 情報バー設定
 */
typedef struct tagDLGINFO{
	int nX;							//ウィンドウX座標 
	int nY;							//ウィンドウY座標 
	BOOL		bShowSc;			//情報バーにスケジュール表示
	BOOL		bShowFix;			//情報バーに定期スケジュール表示
	BOOL		bShowToDo;			//情報バーにToDo表示
	BOOL		bIsShowSec;
	BOOL		bShowTime;
}DLGINFO, *PDLGINFO;

/**
 * @brif メインウィンドウ設定
 */
typedef struct tagMAININFO{
	int nX;							//ウィンドウX座標 
	int nY;							//ウィンドウY座標
	int nWidth;						//ウィンドウ幅
	int nHeight;					//ウィンドウ高さ
	int nSplitLWidth;				//スプリット左
	int nSplitTHeight;				//スプリット左
}MAININFO, *PMAININFO;

/**
 * @brif 基本設定
 */
typedef struct tagAPPINFO{
	BOOL		bEndToDoDel;		//完了したToDoを削除
	int			nEndToDoDelSpan;	//完了したToDoを削除するまでの日数
	BOOL		bUsePassWord;		//パスワードを利用
	char		szPassWord[33];		//パスワード
	int			nStartActTab;		//起動時のアクティブタブ
	BOOL		bUseToDay;			//PersonalWiki ToDayの使用
	BOOL		bRunMainWndShow;	//起動時にメインウィンドウも表示
}APPINFO, *PAPPINFO;

/**
 * @brif デバッグ設定
 */
typedef struct tagDEBUGINFO{
	BOOL		bLogOut;			//ログ出力
	BOOL		bFatalLogOut;		//致命的エラーログ
	BOOL		bAppLogOut;			//状態ログ
	BOOL		bExceptLogOut;		//例外ログ
}DEBUGINFO, *PDEBUGINFO;

/**
 * @brif Wiki設定
 */
typedef struct tagWIKIINFO{
	BOOL		bUseRet;			//改行文字の使用
	char		szCss[MAX_PATH];	//CSSファイル名
	BOOL		bUseTopBtmLnk;
	BOOL		bUseShowAttach;
	BOOL		bUseShowConvTime;
}WIKIINFO, *PWIKIINFO;


/**
 * @brif 連携機能
 */
typedef struct tagLINKINFO{
	BOOL	bUseUSBLink;					//USBデバイス(外部メディア)との連携を利用
	char	szLinkDir[4][MAX_PATH + 1];		//連携対象パス名(最大4個まで)
	BOOL	bUseNetDrv;						//ドライブの割り当てられたネットワークドライブも対象
}LINKINFO, *PLINKINFO;

typedef enum eHolidayType{
	HT_NONE,
	HT_WEEK2HOLIDAY,
	HT_SEL_WEEKDAY,
};

typedef struct tagHOLIDAYINFO{
	eHolidayType eType;
	BOOL bWeekDays[7];
}HOLIDAYINFO, *PHOLIDAYINFO;

typedef struct tagFONTINFO{
	TCHAR	szCalFontName[LF_FACESIZE];
	LONG	lCalHeight;
	
	TCHAR	szEditFontName[LF_FACESIZE];
	LONG	lEditHeight;
	
	TCHAR	szToDoFontName[LF_FACESIZE];
	LONG	lToDoHeight;

	TCHAR	szEtcFontName[LF_FACESIZE];
	LONG	lEtcHeight;
}FONTINFO, *PFONTINFO;

class CPWikiIniFile : public CIniFile  {
public:
	CPWikiIniFile();
	virtual ~CPWikiIniFile();

	static void SetDlgInfoIniData(PDLGINFO pDlgInfo);
	static void SetMainInfoIniData(PMAININFO pMainInfo);
	static void SetAppInfoIniData(PAPPINFO pAppInfo);
	static void SetWikiInfoIniData(PWIKIINFO pWikiInfo);
	static void SetDebugInfoIniData(PDEBUGINFO pDebugInfo);
	static void SetHolidayInfoIniData(PHOLIDAYINFO pHolidayInfo);
	static void SetLinkInfoIniData(PLINKINFO pLinkInfo);
	static void SetFontInfoIniData(PFONTINFO pFontInfo);

	static void GetDlgInfoIniData(DLGINFO &objDlgInfo);
	static void GetMainInfoIniData(MAININFO &objMainInfo);
	static void GetAppInfoIniData(APPINFO &objAppInfo);
	static void GetWikiInfoIniData(WIKIINFO &objWikiInfo);
	static void GetDebugInfoIniData(DEBUGINFO &objDebugInfo);
	static void GetHolidayInfoIniData(HOLIDAYINFO &objHolidayInfo);
	static void GetLinkInfoIniData(LINKINFO &objLinkInfo);
	static void GetFontInfoIniData(FONTINFO &objFontInfo);

protected:
	virtual BOOL OnIniFileAccess(INIDATA* &pIniData, int &nCnt);
private:
	static DLGINFO	m_objDlgInfo;
	static MAININFO	m_objMainInfo;
	static APPINFO	m_objAppInfo;
	static WIKIINFO	m_objWikiInfo;
	static DEBUGINFO	m_objDebugInfo;
	static HOLIDAYINFO	m_objHolidayInfo;
	static LINKINFO	m_objLinkInfo;
	static FONTINFO m_objFontInfo;
	static INIDATA	arrData[];
};

#endif // !defined(AFX_PWIKIINIFILE_H__A80952B8_EC3A_4533_BB1E_D989DEFCE1B8__INCLUDED_)

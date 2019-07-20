// PWikiIniFile.h: CPWikiIniFile �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PWIKIINIFILE_H__A80952B8_EC3A_4533_BB1E_D989DEFCE1B8__INCLUDED_)
#define AFX_PWIKIINIFILE_H__A80952B8_EC3A_4533_BB1E_D989DEFCE1B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IniFile.h"

/**
 * @brif ���o�[�ݒ�
 */
typedef struct tagDLGINFO{
	int nX;							//�E�B���h�EX���W 
	int nY;							//�E�B���h�EY���W 
	BOOL		bShowSc;			//���o�[�ɃX�P�W���[���\��
	BOOL		bShowFix;			//���o�[�ɒ���X�P�W���[���\��
	BOOL		bShowToDo;			//���o�[��ToDo�\��
	BOOL		bIsShowSec;
	BOOL		bShowTime;
}DLGINFO, *PDLGINFO;

/**
 * @brif ���C���E�B���h�E�ݒ�
 */
typedef struct tagMAININFO{
	int nX;							//�E�B���h�EX���W 
	int nY;							//�E�B���h�EY���W
	int nWidth;						//�E�B���h�E��
	int nHeight;					//�E�B���h�E����
	int nSplitLWidth;				//�X�v���b�g��
	int nSplitTHeight;				//�X�v���b�g��
}MAININFO, *PMAININFO;

/**
 * @brif ��{�ݒ�
 */
typedef struct tagAPPINFO{
	BOOL		bEndToDoDel;		//��������ToDo���폜
	int			nEndToDoDelSpan;	//��������ToDo���폜����܂ł̓���
	BOOL		bUsePassWord;		//�p�X���[�h�𗘗p
	char		szPassWord[33];		//�p�X���[�h
	int			nStartActTab;		//�N�����̃A�N�e�B�u�^�u
	BOOL		bUseToDay;			//PersonalWiki ToDay�̎g�p
	BOOL		bRunMainWndShow;	//�N�����Ƀ��C���E�B���h�E���\��
}APPINFO, *PAPPINFO;

/**
 * @brif �f�o�b�O�ݒ�
 */
typedef struct tagDEBUGINFO{
	BOOL		bLogOut;			//���O�o��
	BOOL		bFatalLogOut;		//�v���I�G���[���O
	BOOL		bAppLogOut;			//��ԃ��O
	BOOL		bExceptLogOut;		//��O���O
}DEBUGINFO, *PDEBUGINFO;

/**
 * @brif Wiki�ݒ�
 */
typedef struct tagWIKIINFO{
	BOOL		bUseRet;			//���s�����̎g�p
	char		szCss[MAX_PATH];	//CSS�t�@�C����
	BOOL		bUseTopBtmLnk;
	BOOL		bUseShowAttach;
	BOOL		bUseShowConvTime;
}WIKIINFO, *PWIKIINFO;


/**
 * @brif �A�g�@�\
 */
typedef struct tagLINKINFO{
	BOOL	bUseUSBLink;					//USB�f�o�C�X(�O�����f�B�A)�Ƃ̘A�g�𗘗p
	char	szLinkDir[4][MAX_PATH + 1];		//�A�g�Ώۃp�X��(�ő�4�܂�)
	BOOL	bUseNetDrv;						//�h���C�u�̊��蓖�Ă�ꂽ�l�b�g���[�N�h���C�u���Ώ�
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

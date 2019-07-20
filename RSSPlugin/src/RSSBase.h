// RSSBase.h: CRSSBase クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RSSBASE_H__77A16A79_319B_403C_BF96_5A7F13BE5671__INCLUDED_)
#define AFX_RSSBASE_H__77A16A79_319B_403C_BF96_5A7F13BE5671__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseData.h"
#include "RSSPluginCommon.h"

typedef struct tagRSSINFO{
	BOOL bUse;
	char szURL[1024];
	char szName[1024];
	char szUserID[64];
	char szPassWord[64];
	char dummy[1024];
}RSSINFO, *PRSSINFO;


class CRSSBase : public CBaseData{
public:
	CRSSBase();
	virtual ~CRSSBase();

protected:
	CString m_strDataPath;
	CString m_strIni;
	CString m_strRssBase;

protected:
	void LoadIniData();
	void SaveIniData();
	BOOL LoadRSSData();
	BOOL SaveRSSData(int nCnt);
	virtual BOOL OnLoadOneData(const PRSSINFO pInfo) = 0;
	virtual BOOL OnSaveOneData(int nCnt, RSSINFO &objInfo) = 0;
//	CString m_strBasePath;
	BOOL m_bUseCheckIni;
	int  m_nChkSpanIni;
};

#endif // !defined(AFX_RSSBASE_H__77A16A79_319B_403C_BF96_5A7F13BE5671__INCLUDED_)

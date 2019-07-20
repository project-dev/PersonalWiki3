// RSSBase.cpp: CRSSBase クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "rssplugin.h"
#include "RSSBase.h"
#include "Cryptography.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CRSSBase::CRSSBase(){
	char szPath[MAX_PATH + 1];
	char szDrv[MAX_PATH];
	char szDir[MAX_PATH];
	memset(szPath, 0, MAX_PATH + 1);
	memset(szDrv, 0, MAX_PATH);
	memset(szDir, 0, MAX_PATH);
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	_splitpath(szPath, szDrv, szDir, NULL, NULL);
	m_strRssBase.Format("%s%splugins\\", szDrv, szDir);
	m_strDataPath.Format("%s%splugins\\RSSList.dat", szDrv, szDir);
	m_strIni.Format("%s%splugins\\RSSPlugin.ini", szDrv, szDir);
}

CRSSBase::~CRSSBase(){

}

BOOL CRSSBase::LoadRSSData(){
	CFile file;
	int nBuffSize = sizeof(RSSINFO);
	CCryptography crypt;
	if(file.Open(m_strDataPath, CFile::modeRead)){
		byte *pszBuff = new byte[nBuffSize];
		byte *pszRetBuff;
		while(TRUE){
			memset(pszBuff, 0, nBuffSize);
			int nRet = file.Read(pszBuff, nBuffSize);
			if(nRet < nBuffSize){
				break;
			}
			crypt.DecodeData(pszBuff, nBuffSize, "RSSPlugin", pszRetBuff);
			RSSINFO objRss;
			memset(&objRss, 0, sizeof(RSSINFO));
			memcpy(&objRss, pszRetBuff, nBuffSize);
			if(!OnLoadOneData(&objRss)){
				//中断する
				break;
			}
		}
		file.Close();
		delete[] pszBuff;
	}
	return TRUE;
}

BOOL CRSSBase::SaveRSSData(int nCnt){
	CFile file;
	int nBuffSize = sizeof(RSSINFO);
	byte* pszRetBuff;
	file.Open(m_strDataPath, CFile::modeCreate | CFile::modeWrite);
	CCryptography crypt;
	RSSINFO objRss;
	for(int i = 0; i < nCnt; i++){
		memset(&objRss, 0, sizeof(RSSINFO));
		if(OnSaveOneData(i, objRss)){
			crypt.EncodeData((unsigned char*)&objRss, nBuffSize, "RSSPlugin", pszRetBuff);
			file.Write(pszRetBuff, nBuffSize);
		}
	}
	file.Close();
	return TRUE;
}

void CRSSBase::LoadIniData(){
	m_bUseCheckIni = ::GetPrivateProfileInt("RSS", "UseSpan", 0, m_strIni);
	m_nChkSpanIni  = ::GetPrivateProfileInt("RSS", "Span", 60, m_strIni);

}
void CRSSBase::SaveIniData(){
	CString strVal;
	strVal.Format("%d", m_nChkSpanIni);
	::WritePrivateProfileString("RSS", "UseSpan", m_bUseCheckIni ? "1" : "0", m_strIni);
	::WritePrivateProfileString("RSS", "Span", strVal, m_strIni);
}

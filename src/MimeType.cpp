// MimeType.cpp: CMimeType クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "personalwiki.h"
#include "MimeType.h"
#include "LogFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MIME_SESSION		"MIME"
#define MIME_KEY			"MIME_%d"
#define MIME_TYPE_KEY		"MIME_TYPE%d"
#define MIME_EXT_KEY		"MIME_EXT%d"
#define MIME_USE_KEY		"MIME_USE%d"
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CMimeType::CMimeType(){

}

CMimeType::~CMimeType(){

}

void CMimeType::Add(LPCTSTR pszExt, LPCTSTR pszMime, BOOL bUse){

}

void CMimeType::Mod(LPCTSTR pszExt, LPCTSTR pszMime, BOOL bUse){

}

int CMimeType::Find(LPCTSTR pszExt, LPCTSTR pszMime){
	if(!pszExt && !pszMime){
		return -1;
	}
	int nSize = GetDataSize();
	for(int nCnt = 0; nCnt < nSize; nCnt++){
		if(pszExt){
			if(m_arrExt.GetAt(nSize).CompareNoCase(pszExt)){
				continue;
			}
		}
		if(pszMime){
			if(m_arrMimeType.GetAt(nSize).CompareNoCase(pszMime)){
				continue;
			}
		}
		return nCnt;
	}
	return -1;
}

BOOL CMimeType::Del(int nIndex){
	return TRUE;
}

BOOL CMimeType::Del(LPCTSTR pszExt, LPCTSTR pszMime){
	return TRUE;
}

BOOL CMimeType::LoadMIME(LPCTSTR pszPath){
	CLogFile::SaveAppLog("MIME load start.");
	if(!pszPath){
		CLogFile::SaveAppLog("MIME file name is NULL.");
		return FALSE;
	}
	CString strLog;
	strLog.Format("filename=%s", pszPath);
	CLogFile::SaveAppLog(strLog);

	
	CString strSession = MIME_SESSION;
	int nCnt = 0;
	CString strKey;
	char szRetVal[1025];
	CString strMime;
	int nType;
	CString strExt;
	BOOL bUse;
	while(TRUE){
		strKey.Format(MIME_KEY, nCnt);
		memset(szRetVal, 0, 1025);
		::GetPrivateProfileString(strSession, strKey, "", szRetVal, 1024, pszPath);
		strMime = szRetVal;

		strKey.Format(MIME_TYPE_KEY, nCnt);
		nType = ::GetPrivateProfileInt(strSession, strKey, -1, pszPath);

		strKey.Format(MIME_EXT_KEY, nCnt);
		memset(szRetVal, 0, 1025);
		::GetPrivateProfileString(strSession, strKey, "", szRetVal, 1024, pszPath);
		strExt = szRetVal;

		strKey.Format(MIME_USE_KEY, nCnt);
		bUse = ::GetPrivateProfileInt(strSession, strKey, -1, pszPath);
		
		if(strMime.IsEmpty() && strExt.IsEmpty() && (nType == -1) && (bUse == -1)){
			//終わり
			break;
		}

		//登録
		m_arrMimeType.Add(strMime);
		m_arrExt.Add(strExt);
		m_arrUse.Add(bUse);
		m_arrType.Add(nType);
		nCnt++;
	}
	
	CLogFile::SaveAppLog("MIME load end.");
	return TRUE;
}

BOOL CMimeType::SaveMIME(LPCTSTR pszPath){
	CLogFile::SaveAppLog("MIME save start.");
	if(!pszPath){
		CLogFile::SaveAppLog("MIME path is null.");
		return FALSE;
	}
	
	CString strSession = MIME_SESSION;
	int nSize = GetDataSize();
	if(nSize == 0){
		CLogFile::SaveAppLog("MIME save end.(no data, no save)");
		return TRUE;
	}

	//一度消す
	::DeleteFile(pszPath);

	CString strMime;
	CString strExt;
	int nType;
	BOOL bUse;
	CString strVal;
	CString strKey;
	for(int nCnt = 0; nCnt < nSize; nCnt++){
		strMime	= m_arrMimeType.GetAt(nCnt);
		strExt	= m_arrExt.GetAt(nCnt);
		nType	= m_arrType.GetAt(nCnt);
		bUse	= m_arrUse.GetAt(nCnt);

		strKey.Format(MIME_KEY, nCnt);
		::WritePrivateProfileString(strSession, strKey, strMime, pszPath);

		strKey.Format(MIME_TYPE_KEY, nCnt);
		strVal.Format("%d", nType);
		::WritePrivateProfileString(strSession, strKey, strVal, pszPath);

		strKey.Format(MIME_EXT_KEY, nCnt);
		::WritePrivateProfileString(strSession, strKey, strExt, pszPath);

		strKey.Format(MIME_USE_KEY, nCnt);
		strVal.Format("%d", bUse ? 1 : 0);
		::WritePrivateProfileString(strSession, strKey, strVal, pszPath);
	}
	CLogFile::SaveAppLog("MIME save end.");
	return TRUE;
}

void CMimeType::DelAll(){
	m_arrUse.RemoveAll();
	m_arrMimeType.RemoveAll();
	m_arrExt.RemoveAll();
}

int CMimeType::GetDataSize(){
	int nExtSize = m_arrExt.GetSize();
	int nMimeSize = m_arrMimeType.GetSize();
	int nUseSize = m_arrUse.GetSize();
	int nTypeSize = m_arrType.GetSize();
	int nSize = nExtSize;
	if((nExtSize != nMimeSize) || (nExtSize != nUseSize) || (nExtSize != nTypeSize)){
		//最小サイズを求める
		if((nExtSize <= nMimeSize) && (nExtSize <= nUseSize) && (nExtSize <= nTypeSize)){
			nSize = nExtSize;
		}else if((nMimeSize <= nExtSize) && (nMimeSize <= nUseSize) && (nMimeSize <= nTypeSize)){
			nSize = nMimeSize;
		}else if((nUseSize <= nExtSize) && (nUseSize <= nMimeSize) && (nUseSize <= nTypeSize)){
			nSize = nUseSize;
		}else{
			nSize = nTypeSize;
		}
	}
	return nSize;
}
LPCTSTR CMimeType::GetMimeType(int nIndex){
	if(m_arrMimeType.GetSize() <= nIndex){
		return NULL;
	}
	return m_arrMimeType.GetAt(nIndex);
}

LPCTSTR CMimeType::GetExt(int nIndex){
	if(m_arrExt.GetSize() <= nIndex){
		return NULL;
	}
	return m_arrExt.GetAt(nIndex);
}

int CMimeType::GetType(int nIndex){
	if(m_arrType.GetSize() <= nIndex){
		return -1;
	}
	return m_arrType.GetAt(nIndex);
}

BOOL CMimeType::GetUse(int nIndex){
	if(m_arrUse.GetSize() <= nIndex){
		return FALSE;
	}
	return m_arrUse.GetAt(nIndex);
}

BOOL CMimeType::Copy(CMimeType* pFrom, CMimeType* pTo){
	if(!pFrom || !pTo){
		return FALSE;
	}
	pTo->m_arrUse.Append(pFrom->m_arrUse);
	pTo->m_arrType.Append(pFrom->m_arrType);
	pTo->m_arrMimeType.Append(pFrom->m_arrMimeType);
	pTo->m_arrExt.Append(pFrom->m_arrExt);
	return TRUE;
}


// ScDateData.cpp: CScDateData クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PersonalWiki.h"
#include "ScDateData.h"
#include "devlib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "EventDate.h"
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CScDateData::CScDateData(){

}

CScDateData::~CScDateData(){
	ReleaseDate();
}

BOOL CScDateData::LoadDate(COleDateTime *pDate /*= NULL*/, BOOL bDateOnly /* = FALSE*/){
	if(!pDate && !ReleaseDate()){
		return FALSE;
	}
	CString strFindPath;
	if(pDate){
		if(bDateOnly){
			strFindPath.Format("%s%s.dat", m_strDataDir, pDate->Format("%Y%m%d"));
		}else{
			strFindPath.Format("%s%s*.dat", m_strDataDir, pDate->Format("%Y%m"));
		}
	}else{
		strFindPath.Format("%s*.dat", m_strDataDir);
	}

	WIN32_FIND_DATA wfd;
	HANDLE hRet = NULL;
	BOOL bEnd = FALSE;
	BOOL bFirst = TRUE;

	while(!bEnd){
		if(bFirst){
			bFirst = FALSE;
			hRet = ::FindFirstFile(strFindPath, &wfd);
			if(hRet == INVALID_HANDLE_VALUE){
				break;
			}
		}else{
			if(!::FindNextFile(hRet, &wfd)){
				break;
			}
		}
		CFile file;
		CString strFileName;
		strFileName.Format("%s%s", m_strDataDir, wfd.cFileName);
		CEventDate *pDate = new CEventDate();
		if(!pDate->LoadEvent(strFileName)){
			delete pDate;
		}else{
			char szFile[MAX_PATH];
			memset(szFile, 0, MAX_PATH);
			_splitpath(strFileName, NULL, NULL, szFile, NULL);
			char szYear[5];
			char szMonth[3];
			char szDay[3];
			memset(szYear, 0, 5);
			memset(szMonth, 0, 3);
			memset(szDay, 0, 3);
			strncpy(szYear, &szFile[0], 4);
			strncpy(szMonth, &szFile[4], 2);
			strncpy(szDay, &szFile[6], 2);
			CString strDate;
			strDate.Format("%s/%s/%s", szYear, szMonth, szDay);
			LPVOID pChkData;
			if(!m_mapDate.Lookup(strDate, pChkData)){
				m_mapDate.SetAt(strDate, pDate);
			}else{
				delete pDate;
			}
		}
	}
	if(hRet != NULL){
		::FindClose(hRet);
	}
	return TRUE;
}

BOOL CScDateData::SaveDate(){
	int nSize = m_mapDate.GetCount();
	CEventDate *pDate;
//	if(!::CreateDir(m_strDataDir, NULL)){
//		return FALSE;
//	}
	POSITION pos = m_mapDate.GetStartPosition();
	LPVOID pData;
	CString strKey;
	CString strFileName;
	while(pos){
		m_mapDate.GetNextAssoc(pos, strKey, pData);
		pDate = (CEventDate*)pData;
		COleDateTime objDate;
		pDate->GetDate(&objDate);
		strFileName.Format("%s%s.dat", m_strDataDir, objDate.Format("%Y%m%d"));
		pDate->SaveEvent(strFileName);
	}
	return TRUE;
}

BOOL CScDateData::AddDate(CEventDate *pFromDate){
	if(!pFromDate){
		return FALSE;
	}
	COleDateTime objDate;
	pFromDate->GetDate(&objDate);
	CString strKey = objDate.Format("%Y/%m/%d");
	CEventDate *pDate = GetDate(objDate);
	if(pDate){
		UpdateDate(pDate);
	}else{
		pDate = new CEventDate();
		if(!pDate){
			return FALSE;
		}
		pDate->Create(pFromDate->GetName(), pFromDate->GetDetail(), &objDate);
		m_mapDate.SetAt(strKey, (LPVOID)pDate);
	}
	return TRUE;
}

BOOL CScDateData::DelDate(CEventDate *pDate){
	if(!pDate){
		return FALSE;
	}
	if(pDate->DeleteEvent(m_strDataDir)){
		COleDateTime objDate;
		pDate->GetDate(&objDate);
		m_mapDate.RemoveKey(objDate.Format("%Y/%m/%d"));
		delete pDate;
	}else{
		AfxMessageBox("スケジュールの削除に失敗しました");
		return FALSE;
	}
	return TRUE;
}

int CScDateData::GetSize(){
	return m_mapDate.GetCount();
}

CEventDate* CScDateData::GetDate(COleDateTime &objDate){
	CEventDate *pDate = NULL;
	LPVOID pData = NULL;
	CString strKey = objDate.Format("%Y/%m/%d");
	m_mapDate.Lookup(strKey, pData);
	if(pData == NULL){
		if(LoadDate(&objDate, TRUE)){
			m_mapDate.Lookup(strKey, pData);
		}
	}
	pDate = (CEventDate*)pData;
	return pDate;
}

BOOL CScDateData::UpdateDate(CEventDate* pFromDate){
	if(!pFromDate){
		return FALSE;
	}
	CString strDetail = pFromDate->GetDetail();

	CEventDate *pDate = NULL;
	COleDateTime objDate;
	pFromDate->GetDate(&objDate);
	CString strKey = objDate.Format("%Y/%m/%d");

	LPVOID pData = NULL;
	m_mapDate.Lookup(strKey, pData);
	if(!pData){
		return FALSE;
	}
	pDate = (CEventDate*)pData;

	if(strDetail.IsEmpty()){
		//削除
		m_mapDate.RemoveKey(strKey);
		pDate->DeleteEvent(m_strDataDir);
		delete pDate;
	}else{
		pDate->SetDetail(pFromDate->GetDetail());
	}
	return TRUE;
}

BOOL CScDateData::ReleaseDate(){
	POSITION pos = m_mapDate.GetStartPosition();
	CEventDate *pDate = NULL;
	CString strKey = "";
	LPVOID pData;
	while(pos){
		pData = NULL;
		m_mapDate.GetNextAssoc(pos, strKey, pData);
		pDate = (CEventDate*)pData;
		if(pDate){
			delete pDate;
		}
	}
	m_mapDate.RemoveAll();
	return TRUE;

}

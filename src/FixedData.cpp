// FixedData.cpp: CFixedData クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PersonalWiki.h"
#include "FixedData.h"
#include "EventDate.h"
#include "devlib.h"
#include "LogFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CFixedData::CFixedData(){
}

CFixedData::~CFixedData(){
	ReleaseFixedData();
}

BOOL CFixedData::LoadFixedData(){
	CLogFile::SaveAppLog("定期データの読み込み");
	if(!ReleaseFixedData()){
		return FALSE;
	}
	CString strFindPath;
	strFindPath.Format("%s*.dat", m_strDataDir);

	WIN32_FIND_DATA wfd;
	HANDLE hRet;
	BOOL bEnd = FALSE;
	BOOL bFirst = TRUE;
	CString strLog;
	
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
		if(!pDate->LoadEvent(strFileName, TRUE)){
			strLog.Format("%s 読み込み失敗", strFileName);
			delete pDate;
		}else{
			strLog.Format("%s 読み込み完了", strFileName);
			m_arrFixedData.Add(pDate);
		}
	}
	::FindClose(hRet);
	return TRUE;
}

BOOL CFixedData::SaveFixedData(){
	int nSize = m_arrFixedData.GetSize();
	CEventDate *pDate;
//	if(!::CreateDir(pszDataPath, NULL)){
//		return FALSE;
//	}
	for(int i = 0; i < nSize; i++){
		pDate = m_arrFixedData.GetAt(i);
		CString strFileName;
		int nMonth;
		int nDay;
		pDate->GetMonthDay(nMonth, nDay);
		switch(pDate->GetType()){
		case SC_FIX_YEAR:
			strFileName.Format("%sFIXED_Y_%02d%02d.dat", m_strDataDir, nMonth, nDay);
			break;
		case SC_FIX_MONTH1:
			strFileName.Format("%sFIXED_M1_%02d.dat", m_strDataDir, nDay);
			break;
		case SC_FIX_MONTH2:
			strFileName.Format("%sFIXED_M2_%s.dat", m_strDataDir, pDate->GetEventID());
			break;
		case SC_FIX_WEEK:
			strFileName.Format("%sFIXED_W_%s.dat", m_strDataDir, pDate->GetEventID());
			break;
		default:
			strFileName = "";
			break;
		}
		if(strFileName.IsEmpty()){
			continue;
		}
		pDate->SaveEvent(strFileName, TRUE);
	}
	return TRUE;
}

int CFixedData::AddFixedData(CEventDate *pDate){
	CEventDate *pNewDate = new CEventDate();
	*pNewDate = *pDate;
	return m_arrFixedData.Add(pNewDate);
}

BOOL CFixedData::DelFixedData(CEventDate *pDate){
	return TRUE;
}
BOOL CFixedData::DelFixedData(int i){
	CEventDate *pDate = m_arrFixedData.GetAt(i);
	if(pDate){
		CString strFileName;
		int nMonth;
		int nDay;
		pDate->GetMonthDay(nMonth, nDay);
		switch(pDate->GetType()){
		case SC_FIX_YEAR:
			strFileName.Format("%sFIXED_Y_%02d%02d.dat", m_strDataDir, nMonth, nDay);
			break;
		case SC_FIX_MONTH1:
			strFileName.Format("%sFIXED_M1_%02d.dat", m_strDataDir, nDay);
			break;
		case SC_FIX_MONTH2:
			strFileName.Format("%sFIXED_M2_%s.dat", m_strDataDir, pDate->GetEventID());
			break;
		case SC_FIX_WEEK:
			strFileName.Format("%sFIXED_W_%s.dat", m_strDataDir, pDate->GetEventID());
			break;
		default:
			strFileName = "";
			break;
		}
		delete pDate;
		m_arrFixedData.RemoveAt(i);
		::DeleteFile(strFileName);
	}
	return TRUE;
}

int CFixedData::GetSize(){
	return m_arrFixedData.GetSize();
}

CEventDate* CFixedData::GetFixedData(int nIndex){
	return m_arrFixedData.GetAt(nIndex);
}

BOOL CFixedData::UpdateFixedData(CEventDate* pToDo){
	return TRUE;
}

BOOL CFixedData::ReleaseFixedData(){
	int nSize = m_arrFixedData.GetSize();
	for(int i = 0; i < nSize; i++){
		CEventDate *pDate = m_arrFixedData.GetAt(i);
		delete pDate;
	}
	m_arrFixedData.RemoveAll();
	return TRUE;
}

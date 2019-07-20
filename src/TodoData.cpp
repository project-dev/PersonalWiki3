// TodoData.cpp: CTodoData クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PersonalWiki.h"
#include "TodoData.h"
#include "devlib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CTodoData::CTodoData(){

}

CTodoData::~CTodoData(){
	ReleaseToDo();
}

BOOL CTodoData::AddToDo(CEventDate *pDate){
	CEventDate *pNewDate = new CEventDate();
	*pNewDate = *pDate;
	m_arrToDo.Add(pNewDate);
	return TRUE;
}

BOOL CTodoData::UpdateToDo(CEventDate* pToDo){
	return TRUE;
}

BOOL CTodoData::DelToDo(CEventDate *pDate){
	int nSize = m_arrToDo.GetSize();
	for(int i = 0; i < nSize; i++){
		CEventDate *pChkDate = m_arrToDo.GetAt(i);
		if(*pChkDate == *pDate){
			return DelToDo(i);
		}
	}
	return FALSE;
}

BOOL CTodoData::DelToDo(int nIndex){
	CEventDate *pDate = m_arrToDo.GetAt(nIndex);
	if(pDate){
		CString strFile;
		strFile.Format("%s%s.todo", m_strDataDir, pDate->GetEventID());
		delete pDate;
		m_arrToDo.RemoveAt(nIndex);
		::DeleteFile(strFile);
	}
	return TRUE;
}

int CTodoData::GetSize(){
	return m_arrToDo.GetSize();

}

CEventDate* CTodoData::GetToDo(int nIndex){
	return m_arrToDo.GetAt(nIndex);

}

BOOL CTodoData::LoadToDo(){
	if(!ReleaseToDo()){
		return FALSE;
	}
	CString strFindPath;
	strFindPath.Format("%s*.todo", m_strDataDir);

	WIN32_FIND_DATA wfd;
	HANDLE hRet;
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
//		if(wfd.dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY){
//			continue;
//		}
		CFile file;
		CString strFileName;
		strFileName.Format("%s%s", m_strDataDir, wfd.cFileName);
		CEventDate *pDate = new CEventDate();
		if(!pDate->LoadEvent(strFileName, TRUE)){
			delete pDate;
		}else{
			m_arrToDo.Add(pDate);
		}
	}
	::FindClose(hRet);

	return TRUE;
}

BOOL CTodoData::SaveToDo(){
	int nSize = m_arrToDo.GetSize();
	CEventDate *pDate;
//	if(!::CreateDir(pszDataPath, NULL)){
//		return FALSE;
//	}
	for(int i = 0; i < nSize; i++){
		pDate = m_arrToDo.GetAt(i);
		CString strFileName;
		strFileName.Format("%s%s.todo", m_strDataDir, pDate->GetEventID());
		pDate->SaveEvent(strFileName, TRUE);
	}
	return TRUE;
}
BOOL CTodoData::ReleaseToDo(){
	int nSize = m_arrToDo.GetSize();
	for(int i = 0; i < nSize; i++){
		CEventDate *pDate = m_arrToDo.GetAt(i);
		delete pDate;
	}
	m_arrToDo.RemoveAll();
	return TRUE;
}


// BinderDropTarget.cpp: CBinderDropTarget クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "binderplugin.h"
#include "BinderDropTarget.h"
#include "BinderWnd.h"
#include "LogFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CBinderDropTarget::CBinderDropTarget(){

}

CBinderDropTarget::~CBinderDropTarget(){
	m_pBinderWnd = NULL;

}

void CBinderDropTarget::SetBinderWnd(CBinderWnd* pWnd){
	m_pBinderWnd = pWnd;
}

DROPEFFECT CBinderDropTarget::OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point ){
	if( pDataObject->IsDataAvailable(CF_HTML) ) {
		return DROPEFFECT_COPY;
	}else if( pDataObject->IsDataAvailable(CF_TEXT) ) {
		return DROPEFFECT_COPY;
	}
	return DROPEFFECT_NONE ;
}
/*
void CBinderDropTarget::OnDragLeave( CWnd* pWnd ){
}
*/
DROPEFFECT CBinderDropTarget::OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point ){
	if( pDataObject->IsDataAvailable(CF_TEXT) ) {
		return DROPEFFECT_COPY;
	}else if( pDataObject->IsDataAvailable(CF_HTML) ) {
		return DROPEFFECT_COPY;
	}
	return DROPEFFECT_NONE;
}
/*
DROPEFFECT CBinderDropTarget::OnDragScroll( CWnd* pWnd, DWORD dwKeyState, CPoint point ){
	return;
}
*/
BOOL CBinderDropTarget::OnDrop( CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point ){
	if( pDataObject->IsDataAvailable(CF_HTML) ) {
		try{
			CString strData;
			HGLOBAL hGrobal = NULL;
			hGrobal = pDataObject->GetGlobalData(CF_HTML);
			if(!hGrobal){
				CString strError;
				DWORD dwErr = GetLastError();
				strError.Format("GetLastError = %d", dwErr);
				CLogFile::SaveAppLog(strError);
				return FALSE;
			}
			char *pszText = (char*)GlobalLock(hGrobal);
			m_pBinderWnd->m_strAnalisysData = pszText;
			if(!::GlobalUnlock(hGrobal)){
				CString strError;
				DWORD dwErr = GetLastError();
				strError.Format("GetLastError = %d", dwErr);
				CLogFile::SaveAppLog(strError);
			}
			if(::GlobalFree(hGrobal)){
				CString strError;
				DWORD dwErr = GetLastError();
				strError.Format("GetLastError = %d", dwErr);
				CLogFile::SaveAppLog(strError);
			}
			hGrobal = NULL;

			pDataObject->Release();
			m_pBinderWnd->PostMessage(WM_ANALISYS_DROP, 0, 0);
		}catch(CException &e){
			char szErr[1025];
			memset(szErr, 0, 1025);
			e.GetErrorMessage(szErr, 1024);
			CLogFile::SaveAppLog(szErr);
		}
		return TRUE;
	}else if( pDataObject->IsDataAvailable(CF_TEXT) ) {
		return TRUE;
	}
	return FALSE;
}
/*
DROPEFFECT CBinderDropTarget::OnDropEx( CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point ){
	return DROPEFFECT_COPY;
}
*/
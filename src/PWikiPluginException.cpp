// PWikiPluginException.cpp: CPWikiPluginException クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "personalwiki.h"
#include "PWikiPluginException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

/**
 * @brif 
 */
CPWikiPluginException::CPWikiPluginException(LPCTSTR pszErrMsg, BOOL b_AutoDelete /* = TRUE*/)
 : CException(b_AutoDelete){
	m_strErrMsg = pszErrMsg;
}

/**
 * @brif 
 */
CPWikiPluginException::~CPWikiPluginException(){

}

/**
 * @brif 
 */
BOOL CPWikiPluginException::GetErrorMessage( LPTSTR lpszError, UINT nMaxError,	PUINT pnHelpContext /*= NULL*/ ){
	if(!lpszError){
		return TRUE;
	}
	strncpy(lpszError, m_strErrMsg, nMaxError);
	return TRUE;
}

/**
 * @brif 
 */
void CPWikiPluginException::GetErrorMessage( CString& strError ){
	strError = m_strErrMsg;
}

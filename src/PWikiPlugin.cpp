// PWikiPlugin.cpp: CPWikiPlugin �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "personalwiki.h"
#include "PWikiPlugin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////
/**
 * @brif 
 */
CPWikiPlugin::CPWikiPlugin(){
	PGetPluginSDKVersion = NULL;
	PGetPluginInfo = NULL;
	PShowSetupDlg = NULL;
	PGetUse = NULL;
	PSetUse = NULL;
	PGetTabWnd = NULL;
	PExitPlugin = NULL;
	PSetLogFlag = NULL;

}

/**
 * @brif 
 */
CPWikiPlugin::~CPWikiPlugin(){
	ReleasePlugin();
}

/**
 * @brif 
 */
BOOL CPWikiPlugin::LoadPlugin(LPCTSTR pszPath){
	BOOL bRet = TRUE;
	m_strModName = pszPath;
	try{
		m_hPlugin = AfxLoadLibrary(m_strModName);
		if(!m_hPlugin){
			DWORD dwErr = GetLastError();
			throw(0);
		}
//		PGetPluginSDKVersion	= ::GetProcAddress(m_hPlugin, "GetPluginSDKVersion");
		PGetPluginInfo			= ::GetProcAddress(m_hPlugin, "GetPluginInfo");
		PShowSetupDlg			= ::GetProcAddress(m_hPlugin, "ShowSetupDlg");
		PGetUse					= ::GetProcAddress(m_hPlugin, "GetUse");
		PSetUse					= ::GetProcAddress(m_hPlugin, "SetUse");
		PExitPlugin				= ::GetProcAddress(m_hPlugin, "ExitPlugin");

		PGetTabWnd				= ::GetProcAddress(m_hPlugin, "GetTabWnd");

		PReqDataType		    = ::GetProcAddress(m_hPlugin, "ReqDataType");
		PExport					= ::GetProcAddress(m_hPlugin, "Export");

		PSetLogFlag		        = ::GetProcAddress(m_hPlugin, "SetLogFlag");

		//�K�{�֐��Ȃ�
		if(!PGetPluginInfo || !PExitPlugin || !PGetUse || !PSetUse){
			throw(0);
		}
	}catch(int nErr){
		ReleasePlugin();
		bRet = FALSE;
	}
	return bRet;
}

/**
 * @brif 
 */
BOOL CPWikiPlugin::ReleasePlugin(){
	BOOL bRet = TRUE;
	if(AfxFreeLibrary(m_hPlugin)){
		m_hPlugin = NULL;
	}else{
		bRet = FALSE;
	}
	return TRUE;
}

/**
 * @brif 
 */
LPCTSTR CPWikiPlugin::GetPluginSDKVersion(){
	return NULL;
}

/**
 * @brif 
 */
BOOL CPWikiPlugin::GetPluginInfo(){
	if(!PGetPluginInfo){
		CString strMsg;
		strMsg.Format("%s �ɂ� GetPluginInfo �͎�������Ă��܂���", m_strModName);
		throw new CPWikiPluginException(strMsg, TRUE);
	}
	return ((PGetPluginInfoFunc)PGetPluginInfo)(&m_objInfo);
}

/**
 * @brif 
 */
BOOL CPWikiPlugin::ShowSetupDlg(){
	if(!PShowSetupDlg){
		CString strMsg;
		strMsg.Format("%s �ɂ� ShowSetupDlg �͎�������Ă��܂���", m_strModName);
		throw new CPWikiPluginException(strMsg, TRUE);
	}
	return ((PShowSetupDlgFunc)PShowSetupDlg)();
}

/**
 * @brif 
 */
BOOL CPWikiPlugin::GetUse(){
	if(!PGetUse){
		CString strMsg;
		strMsg.Format("%s �ɂ� GetUse �͎�������Ă��܂���", m_strModName);
		throw new CPWikiPluginException(strMsg, TRUE);
	}
	return ((PGetUseFunc)PGetUse)();
}

/**
 * @brif 
 */
void CPWikiPlugin::SetUse(BOOL bUse){
	if(!PSetUse){
		CString strMsg;
		strMsg.Format("%s �ɂ� SetUse �͎�������Ă��܂���", m_strModName);
		throw new CPWikiPluginException(strMsg, TRUE);
	}
	((PSetUseFunc)PSetUse)(bUse);
}

/**
 * @brif 
 */
HWND CPWikiPlugin::GetTabWnd(HWND hParent){
	if(!PGetTabWnd){
		CString strMsg;
		strMsg.Format("%s �ɂ� GetTabWnd �͎�������Ă��܂���", m_strModName);
		throw new CPWikiPluginException(strMsg, TRUE);
	}
	return ((PGetTabWndFunc)PGetTabWnd)(hParent);
}

/**
 * @brif 
 */
BOOL CPWikiPlugin::ExitPlugin(){
	if(!PExitPlugin){
		CString strMsg;
		strMsg.Format("%s �ɂ� ExitPlugin �͎�������Ă��܂���", m_strModName);
		throw new CPWikiPluginException(strMsg, TRUE);
	}
	return ((PExitPluginFunc)PExitPlugin)();
}

void CPWikiPlugin::SetLogFlag(BOOL bLogState, BOOL bAppLogState, BOOL bExceptLogState, BOOL bFatalLogState){
	if(!PSetLogFlag){
		CString strMsg;
		strMsg.Format("%s �ɂ� SetLogFlag �͎�������Ă��܂���", m_strModName);
		throw new CPWikiPluginException(strMsg, TRUE);
	}
	((PSetLogFlagFunc)PSetLogFlag)(bLogState, bAppLogState, bExceptLogState, bFatalLogState);
}

eExportDataType CPWikiPlugin::ReqDataType(){
	if(!PReqDataType){
		CString strMsg;
		strMsg.Format("%s �ɂ� ReqDataType �͎�������Ă��܂���", m_strModName);
		throw new CPWikiPluginException(strMsg, TRUE);
	}
	return ((PReqDataTypeFunc)PReqDataType)();
}

BOOL CPWikiPlugin::Export(char* pszWikiBuff){
	if(!PExport){
		CString strMsg;
		strMsg.Format("%s �ɂ� Export �͎�������Ă��܂���", m_strModName);
		throw new CPWikiPluginException(strMsg, TRUE);
	}
	return ((PExportFunc)PExport)(pszWikiBuff);
}

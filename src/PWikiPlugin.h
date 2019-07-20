// PWikiPlugin.h: CPWikiPlugin クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PWIKIPLUGIN_H__3CE5FF5A_E133_42A8_BC3D_06EF44488456__INCLUDED_)
#define AFX_PWIKIPLUGIN_H__3CE5FF5A_E133_42A8_BC3D_06EF44488456__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PWikiPluginSDK.h"
#include "PWikiPluginException.h"


class CPWikiPlugin {
public:
	BOOL ReleasePlugin();
	BOOL LoadPlugin(LPCTSTR pszPath);
	CPWikiPlugin();
	virtual ~CPWikiPlugin();

	//プラグイン関数
	LPCTSTR GetPluginSDKVersion();
	BOOL GetPluginInfo();
	BOOL ShowSetupDlg();
	BOOL GetUse();
	void SetUse(BOOL bUse);
	HWND GetTabWnd(HWND hParent);
	eExportDataType ReqDataType();
	BOOL Export(char* pszWikiBuff);
	BOOL ExitPlugin();
	void SetLogFlag(BOOL bLogState, BOOL bAppLogState, BOOL bExceptLogState, BOOL bFatalLogState);

	PWIKIPLUGIN m_objInfo;

private:
	HMODULE m_hPlugin;
	CString m_strModName;
	LPVOID PGetPluginSDKVersion;
	LPVOID PGetPluginInfo;
	LPVOID PShowSetupDlg;
	LPVOID PGetUse;
	LPVOID PSetUse;
	LPVOID PGetTabWnd;
	LPVOID PExitPlugin;
	LPVOID PReqDataType;
	LPVOID PExport;
	LPVOID PSetLogFlag;
};

#endif // !defined(AFX_PWIKIPLUGIN_H__3CE5FF5A_E133_42A8_BC3D_06EF44488456__INCLUDED_)

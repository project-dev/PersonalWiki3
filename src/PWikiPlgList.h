// PWikiPlgList.h: CPWikiPlgList クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PWIKIPLGLIST_H__48C21B6F_1E0B_4C9E_A4CA_06EDD3493FD9__INCLUDED_)
#define AFX_PWIKIPLGLIST_H__48C21B6F_1E0B_4C9E_A4CA_06EDD3493FD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxTempl.h>
#include "PWikiPlugin.h"

class CPWikiPlgList {
public:
	int GetSize();
	CPWikiPlugin* GetPlugin(int nIndex);
	BOOL Create(LPCTSTR pszPluginDir);
	void ReleasePlugins();
	void EnumPlugins(BOOL bLogOut, BOOL bAppLog, BOOL bExceptLog, BOOL bFatalLog);
	CPWikiPlgList();
	virtual ~CPWikiPlgList();
private:
	CMapStringToPtr m_mapPlugin;
	CString m_strPluginPath;
};

#endif // !defined(AFX_PWIKIPLGLIST_H__48C21B6F_1E0B_4C9E_A4CA_06EDD3493FD9__INCLUDED_)

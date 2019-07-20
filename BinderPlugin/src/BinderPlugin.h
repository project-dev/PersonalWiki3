// BinderPlugin.h : BINDERPLUGIN アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_BINDERPLUGIN_H__0C507A85_B6F3_43E2_8FA6_7BDCF3024DE5__INCLUDED_)
#define AFX_BINDERPLUGIN_H__0C507A85_B6F3_43E2_8FA6_7BDCF3024DE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

#include "PWikiPluginSDK.h"

#define PLUGIN_EXT_CLASS		 __declspec(dllexport)

//プラグイン関数
//必須関数
PLUGIN_EXT_CLASS BOOL WINAPI GetPluginInfo(PPWIKIPLUGIN pInfo);
PLUGIN_EXT_CLASS BOOL WINAPI ShowSetupDlg();
PLUGIN_EXT_CLASS BOOL WINAPI GetUse();
PLUGIN_EXT_CLASS void WINAPI SetUse(BOOL bUse);
PLUGIN_EXT_CLASS BOOL WINAPI ExitPlugin();

//タブ用関数
PLUGIN_EXT_CLASS HWND WINAPI GetTabWnd(HWND hParent);

//デバッグ用
PLUGIN_EXT_CLASS void WINAPI SetLogFlag(BOOL bLogState, BOOL bAppLogState, BOOL bExceptLogState, BOOL bFatalLogState);

/////////////////////////////////////////////////////////////////////////////
// CBinderPluginApp
// このクラスの動作の定義に関しては BinderPlugin.cpp ファイルを参照してください。
//

class CBinderPluginApp : public CWinApp
{
public:
	CBinderPluginApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CBinderPluginApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CBinderPluginApp)
		// メモ -  ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_BINDERPLUGIN_H__0C507A85_B6F3_43E2_8FA6_7BDCF3024DE5__INCLUDED_)

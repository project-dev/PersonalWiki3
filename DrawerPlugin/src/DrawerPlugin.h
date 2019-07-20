// DrawerPlugin.h : DRAWERPLUGIN アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_DRAWERPLUGIN_H__65A738FE_B78E_449B_9FD9_3C4587E8DBF7__INCLUDED_)
#define AFX_DRAWERPLUGIN_H__65A738FE_B78E_449B_9FD9_3C4587E8DBF7__INCLUDED_

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


/////////////////////////////////////////////////////////////////////////////
// CDrawerPluginApp
// このクラスの動作の定義に関しては DrawerPlugin.cpp ファイルを参照してください。
//

class CDrawerPluginApp : public CWinApp{
public:
	CDrawerPluginApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDrawerPluginApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDrawerPluginApp)
		// メモ -  ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DRAWERPLUGIN_H__65A738FE_B78E_449B_9FD9_3C4587E8DBF7__INCLUDED_)

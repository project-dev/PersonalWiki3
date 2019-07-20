// RSSPlugin.h : RSSPLUGIN アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_RSSPLUGIN_H__3CC0C0FB_6CCD_471A_B10F_D9824FEDC3C1__INCLUDED_)
#define AFX_RSSPLUGIN_H__3CC0C0FB_6CCD_471A_B10F_D9824FEDC3C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル
#include "PWikiPluginSDK.h"
#include "RSSPluginCommon.h"

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


/////////////////////////////////////////////////////////////////////////////
// CRSSPluginApp
// このクラスの動作の定義に関しては RSSPlugin.cpp ファイルを参照してください。
//


class CRSSPluginApp : public CWinApp{
public:
	CRSSPluginApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CRSSPluginApp)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CRSSPluginApp)
		// メモ -  ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。



#endif // !defined(AFX_RSSPLUGIN_H__3CC0C0FB_6CCD_471A_B10F_D9824FEDC3C1__INCLUDED_)

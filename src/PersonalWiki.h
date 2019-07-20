// PersonalWiki.h : PERSONALWIKI アプリケーションのメイン ヘッダー ファイル
//

#if !defined(AFX_PERSONALWIKI_H__A9018661_040C_45C3_9493_1A732D5FEB76__INCLUDED_)
#define AFX_PERSONALWIKI_H__A9018661_040C_45C3_9493_1A732D5FEB76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // メイン シンボル

//USBを使う
#define USE_USB_DOC
#if defined(USE_USB_DOC
typedef struct tagUSB_STATE{
	char szDrv;		//ドライブ
	BOOL bAlive;	//生きているか
	char szPath[4][MAX_PATH + 1];
}USB_STATE, *PUSB_STATE;
#endif

//#define USE_CREATE_VIEW

/////////////////////////////////////////////////////////////////////////////
// CPWikiApp:
// このクラスの動作の定義に関しては PersonalWiki.cpp ファイルを参照してください。
//
class CPWikiApp : public CWinApp
{
public:
	CPWikiApp();
	BOOL ProcessShellCommand( CCommandLineInfo& rCmdInfo );

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CPWikiApp)
	public:
	virtual BOOL InitInstance();
	virtual int Run();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
	//{{AFX_MSG(CPWikiApp)
	afx_msg void OnAppAbout();
	afx_msg void OnDevModeChange(LPTSTR lpDeviceName);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PERSONALWIKI_H__A9018661_040C_45C3_9493_1A732D5FEB76__INCLUDED_)

// ExceptTest.h : EXCEPTTEST アプリケーションのメイン ヘッダー ファイル
//

#if !defined(AFX_EXCEPTTEST_H__0A0DDBA4_3BBB_4012_9BAD_0845D94FE85B__INCLUDED_)
#define AFX_EXCEPTTEST_H__0A0DDBA4_3BBB_4012_9BAD_0845D94FE85B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CExceptTestApp:
// このクラスの動作の定義に関しては ExceptTest.cpp ファイルを参照してください。
//

class CExceptTestApp : public CWinApp
{
public:
	CExceptTestApp();
	static int Except(LPEXCEPTION_POINTERS pExp);
	BOOL ProcessShellCommand( CCommandLineInfo& rCmdInfo );


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CExceptTestApp)
	public:
	virtual BOOL InitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// インプリメンテーション
	//{{AFX_MSG(CExceptTestApp)
	afx_msg void OnAppAbout();
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_EXCEPTTEST_H__0A0DDBA4_3BBB_4012_9BAD_0845D94FE85B__INCLUDED_)

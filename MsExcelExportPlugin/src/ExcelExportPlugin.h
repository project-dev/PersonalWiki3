// ExcelExportPlugin.h : EXCELEXPORTPLUGIN アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_EXCELEXPORTPLUGIN_H__B535DB4E_9B25_4D10_A582_7AE27753D834__INCLUDED_)
#define AFX_EXCELEXPORTPLUGIN_H__B535DB4E_9B25_4D10_A582_7AE27753D834__INCLUDED_

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

//エクスポート用
PLUGIN_EXT_CLASS eExportDataType WINAPI ReqDataType();
PLUGIN_EXT_CLASS BOOL WINAPI Export(char* pszWikiBuff);

/////////////////////////////////////////////////////////////////////////////
// CExcelExportPluginApp
// このクラスの動作の定義に関しては ExcelExportPlugin.cpp ファイルを参照してください。
//

class CExcelExportPluginApp : public CWinApp
{
public:
	CExcelExportPluginApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CExcelExportPluginApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CExcelExportPluginApp)
		// メモ -  ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_EXCELEXPORTPLUGIN_H__B535DB4E_9B25_4D10_A582_7AE27753D834__INCLUDED_)

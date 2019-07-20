// stdafx.h : 標準のシステム インクルード ファイル、
//            または参照回数が多く、かつあまり変更されない
//            プロジェクト専用のインクルード ファイルを記述します。
//

#if !defined(AFX_STDAFX_H__52105AE9_35B7_453A_BA6E_4E9AC128B19C__INCLUDED_)
#define AFX_STDAFX_H__52105AE9_35B7_453A_BA6E_4E9AC128B19C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Windows ヘッダーから殆ど使用されないスタッフを除外します。

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC の OLE クラス
#include <afxodlgs.h>       // MFC の OLE ダイアログ クラス
#include <afxdisp.h>        // MFC のオートメーション クラス
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC データベース クラス
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO データベース クラス
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC の Internet Explorer 4 コモン コントロール サポート
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC の Windows コモン コントロール サポート
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

//#define USE_OFFICE9
//#define USE_OFFICE10
//#define USE_OFFICE11
#define USE_OFFICE15

// MSO.DLLのインポート
#if defined(USE_OFFICE9)
	#import "C:\Program Files\Microsoft Office\Office\MSO9.DLL"
#elif defined(USE_OFFICE10)
	#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE10\MSO.DLL"
#elif defined(USE_OFFICE11)
	#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE11\MSO.DLL"
	#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB"
#elif defined(USE_OFFICE15)
	#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE15\MSO.DLL"
	#import "C:\Program Files (x86)\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB"
#endif

//MS WORD
#if defined(USE_OFFICE9)
	#import "C:\Program Files\Microsoft Office\Office\Mso9.dll"\
	no_namespace rename("DocumentProperties", "DocumentPropertiesACC")
	#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\Vbe6ext.olb" no_namespace
	#import "C:\Program Files\Microsoft Office\Office\MSWORD9.OLB"\
	rename("ExitWindows", "ExitWindowsForWord")
#elif defined(USE_OFFICE10)

#elif defined(USE_OFFICE11)
	#import "C:\Program Files\Microsoft Office\OFFICE11\MSWORD.OLB"\
	rename("ExitWindows", "ExitWindowsForWord")
#elif defined(USE_OFFICE15)
	#import "C:\Program Files\Microsoft Office\OFFICE15\MSWORD.OLB"\
	rename("ExitWindows", "ExitWindowsForWord")
#endif

/*
//MS EXCEL
#if defined(USE_OFFICE9)
	#import "C:\Program Files\Microsoft Office\Office\EXCEL9.OLB" \
	rename("DialogBox", "DialogBoxForExcel") rename( "RGB", "RGBForExcel")
#elif defined(USE_OFFICE10)
#elif defined(USE_OFFICE11)
	#import "C:\Program Files\Microsoft Office\OFFICE11\XL5JP32.OLB"\
	rename("DialogBox", "DialogBoxForExcel") rename( "RGB", "RGBForExcel")
#endif
*/
#endif // !defined(AFX_STDAFX_H__52105AE9_35B7_453A_BA6E_4E9AC128B19C__INCLUDED_)

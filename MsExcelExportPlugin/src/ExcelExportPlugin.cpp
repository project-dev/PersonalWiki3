// ExcelExportPlugin.cpp : DLL 用の初期化処理の定義を行います。
//

#include "stdafx.h"
#include "ExcelExportPlugin.h"
#include "FileDialogEx.h"
#include <AfxPriv2.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	メモ!
//
//		この DLL が MFC DLL に対して動的にリンクされる場合、
//		MFC 内で呼び出されるこの DLL からエクスポートされた
//		どの関数も関数の最初に追加される AFX_MANAGE_STATE 
//		マクロを含んでいなければなりません。
//
//		例:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 通常関数の本体はこの位置にあります
//		}
//
//		このマクロが各関数に含まれていること、MFC 内の
//		どの呼び出しより優先することは非常に重要です。
//		これは関数内の最初のステートメントでなければな
//		らないことを意味します、コンストラクタが MFC 
//		DLL 内への呼び出しを行う可能性があるので、オブ
//		ジェクト変数の宣言よりも前でなければなりません。
//
//		詳細については MFC テクニカル ノート 33 および
//		58 を参照してください。
//

/////////////////////////////////////////////////////////////////////////////
// CExcelExportPluginApp

BEGIN_MESSAGE_MAP(CExcelExportPluginApp, CWinApp)
	//{{AFX_MSG_MAP(CExcelExportPluginApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExcelExportPluginApp の構築

CExcelExportPluginApp::CExcelExportPluginApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance の中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CExcelExportPluginApp オブジェクト

CExcelExportPluginApp theApp;

/**
 * @brif 
 */
BOOL WINAPI GetPluginInfo(PPWIKIPLUGIN pInfo){
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	if(!pInfo){
		return FALSE;
	}
	memset(pInfo, 0, sizeof(PWIKIPLUGIN));
	strcpy(pInfo->szName, "MS Excel エクスポートプラグイン");
	strcpy(pInfo->szInfo, "Wikiドキュメントをエクセル文書にエクスポートする");
	pInfo->arrType[eTypeExportExtend] = TRUE;
	pInfo->nPlgVersion[0] = 1;
	pInfo->nPlgVersion[1] = 0;
	pInfo->nPlgVersion[2] = 0;
	return TRUE;
}

/**
 * @brif 
 */
BOOL WINAPI ShowSetupDlg(){
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
//	CSetDlg dlg;
//	if(dlg.DoModal() == IDOK){
//		//設定変更を反映させる
//		g_rssWnd.UpdateConfig();
//	}
	return TRUE;
}

/**
 * @brif 
 */
BOOL WINAPI GetUse(){
	char szPath[MAX_PATH + 1];
	char szDrv[MAX_PATH];
	char szDir[MAX_PATH];
	memset(szPath, 0, MAX_PATH + 1);
	memset(szDrv, 0, MAX_PATH);
	memset(szDir, 0, MAX_PATH);
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	_splitpath(szPath, szDrv, szDir, NULL, NULL);
	CString strIni;
	strIni.Format("%s%splugins\\MsExcelExportPlugin.ini", szDrv, szDir);
	return ::GetPrivateProfileInt("MsExcelExportPlugin", "IsUse", 0, strIni);
}

/**
 * @brif 
 */
void WINAPI SetUse(BOOL bUse){
	char szPath[MAX_PATH + 1];
	char szDrv[MAX_PATH];
	char szDir[MAX_PATH];
	memset(szPath, 0, MAX_PATH + 1);
	memset(szDrv, 0, MAX_PATH);
	memset(szDir, 0, MAX_PATH);
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	_splitpath(szPath, szDrv, szDir, NULL, NULL);
	CString strIni;
	strIni.Format("%s%splugins\\MsExcelExportPlugin.ini", szDrv, szDir);
	::WritePrivateProfileString("MsExcelExportPlugin", "IsUse", bUse ? "1" : "0", strIni);
}

/**
 * @brif 
 */
BOOL WINAPI ExitPlugin(){
	return TRUE;
}

eExportDataType WINAPI ReqDataType(){
	return EXP_HTMLFILE;
}

BOOL WINAPI Export(char* pszWikiBuff){
	Excel::_ApplicationPtr pExcel = NULL;
	Excel::WorkbooksPtr pBooks = NULL;
	Excel::_WorkbookPtr pCurBook = NULL;
	BOOL bRet = TRUE;
	CString strErr = "";
	try{
		if ( !::AfxOleInit()){
//			m_strErrMsg = "OLEを初期化できません。";
//			ShowErrorMsg();
			return FALSE;
		}

		// OLE コントロールを包含することを宣言する
		::AfxEnableControlContainer();
		HRESULT hRes = ::CoInitialize(NULL);
		if((hRes != S_OK) && (hRes != S_FALSE)){
			return FALSE;
		}
		hRes = pExcel.CreateInstance( "Excel.Application");

		if(hRes != S_OK){
			return FALSE;
		}
		pBooks = pExcel->GetWorkbooks();

		pCurBook = pBooks->Open(pszWikiBuff);

		if(pCurBook != NULL){
			CString strSaveFileName = "";
			CFileDialogEx dlg(NULL, NULL, "*.xls", "", "*.xls", 0, NULL, "Excelエクスポート", ".xls");
			if(dlg.DoModal() == IDOK){
				strSaveFileName = dlg.GetFileName();
				_variant_t vFileName;
				BSTR bStrFileName = strSaveFileName.AllocSysString();
				vFileName = bStrFileName;
				_variant_t vFormat;
				vFormat = (long)Excel::xlWorkbookNormal;

				hRes = pCurBook->SaveAs(vFileName,					//FileName
										vFormat,					//FileFormat
										vtMissing,					//PassWord
										vtMissing,					//WriteResPassword
										vtMissing,					//ReadOnlyRecommended
										vtMissing,					//CreateBackup
										Excel::xlExclusive);		//AccessMode
				::SysFreeString(bStrFileName);
			}
		}
	}catch(_com_error e){
		bRet = FALSE;

		CString strErrMsg = "";
		BSTR bError = e.Description();
		const TCHAR *pszMsg = e.ErrorMessage();

		CString strError;
		AfxBSTR2CString(&strError, bError);
		strErrMsg.Format("%s\n%s", pszMsg, strError);
		AfxMessageBox(strErrMsg);
	}
	try{
		if(pCurBook){
			pCurBook->Close();
			pCurBook.Release();
			pCurBook = NULL;
		}
		if(pBooks){
			pBooks.Release();
			pBooks = NULL;
		}
		
		if(pExcel){
			pExcel->Quit();
			pExcel.Release();
			pExcel = NULL;
		}
	}catch(_com_error e){
		bRet = FALSE;

		CString strErrMsg = "";
		BSTR bError = e.Description();
		const TCHAR *pszMsg = e.ErrorMessage();

		CString strError;
		AfxBSTR2CString(&strError, bError);
		strErrMsg.Format("%s\n%s", pszMsg, strError);
		AfxMessageBox(strErrMsg);
	}
	::CoUninitialize();

	return TRUE;
}


// ExcelExportPlugin.cpp : DLL �p�̏����������̒�`���s���܂��B
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
//	����!
//
//		���� DLL �� MFC DLL �ɑ΂��ē��I�Ƀ����N�����ꍇ�A
//		MFC ���ŌĂяo����邱�� DLL ����G�N�X�|�[�g���ꂽ
//		�ǂ̊֐����֐��̍ŏ��ɒǉ������ AFX_MANAGE_STATE 
//		�}�N�����܂�ł��Ȃ���΂Ȃ�܂���B
//
//		��:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �ʏ�֐��̖{�̂͂��̈ʒu�ɂ���܂�
//		}
//
//		���̃}�N�����e�֐��Ɋ܂܂�Ă��邱�ƁAMFC ����
//		�ǂ̌Ăяo�����D�悷�邱�Ƃ͔��ɏd�v�ł��B
//		����͊֐����̍ŏ��̃X�e�[�g�����g�łȂ���΂�
//		��Ȃ����Ƃ��Ӗ����܂��A�R���X�g���N�^�� MFC 
//		DLL ���ւ̌Ăяo�����s���\��������̂ŁA�I�u
//		�W�F�N�g�ϐ��̐錾�����O�łȂ���΂Ȃ�܂���B
//
//		�ڍׂɂ��Ă� MFC �e�N�j�J�� �m�[�g 33 �����
//		58 ���Q�Ƃ��Ă��������B
//

/////////////////////////////////////////////////////////////////////////////
// CExcelExportPluginApp

BEGIN_MESSAGE_MAP(CExcelExportPluginApp, CWinApp)
	//{{AFX_MSG_MAP(CExcelExportPluginApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExcelExportPluginApp �̍\�z

CExcelExportPluginApp::CExcelExportPluginApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance �̒��̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CExcelExportPluginApp �I�u�W�F�N�g

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
	strcpy(pInfo->szName, "MS Excel �G�N�X�|�[�g�v���O�C��");
	strcpy(pInfo->szInfo, "Wiki�h�L�������g���G�N�Z�������ɃG�N�X�|�[�g����");
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
//		//�ݒ�ύX�𔽉f������
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
//			m_strErrMsg = "OLE���������ł��܂���B";
//			ShowErrorMsg();
			return FALSE;
		}

		// OLE �R���g���[�����܂��邱�Ƃ�錾����
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
			CFileDialogEx dlg(NULL, NULL, "*.xls", "", "*.xls", 0, NULL, "Excel�G�N�X�|�[�g", ".xls");
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


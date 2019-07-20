// BinderPlugin.cpp : DLL �p�̏����������̒�`���s���܂��B
//

#include "stdafx.h"
#include "BinderPlugin.h"
#include "BinderWnd.h"
#include "LogFile.h"

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
// CBinderPluginApp

BEGIN_MESSAGE_MAP(CBinderPluginApp, CWinApp)
	//{{AFX_MSG_MAP(CBinderPluginApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBinderPluginApp �̍\�z

CBinderPluginApp::CBinderPluginApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance �̒��̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CBinderPluginApp �I�u�W�F�N�g

CBinderPluginApp theApp;
CBinderWnd g_binderWnd;
static const UINT g_uTabID = ::RegisterWindowMessage("PWIKI_BINDERPLUGIN_TAB_WND");

/**
 * @brif 
 */
BOOL WINAPI GetPluginInfo(PPWIKIPLUGIN pInfo){
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	if(!pInfo){
		return FALSE;
	}
	memset(pInfo, 0, sizeof(PWIKIPLUGIN));
	strcpy(pInfo->szName, "Binder Plugin");
	strcpy(pInfo->szInfo, "WEB�T�C�g�̋L�����o�C���h���܂�");
	pInfo->arrType[eTypeTabExtend]  = TRUE;
	pInfo->arrType[eTypeWikiFormat] = TRUE;
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
/*
	CSetDlg dlg;
	if(dlg.DoModal() == IDOK){
		//�ݒ�ύX�𔽉f������
		g_rssWnd.UpdateConfig();
	}
*/
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
	strIni.Format("%s%splugins\\BinderPlugin.ini", szDrv, szDir);
	return ::GetPrivateProfileInt("BinderPlugin", "IsUse", 0, strIni);
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
	strIni.Format("%s%splugins\\BinderPlugin.ini", szDrv, szDir);
	::WritePrivateProfileString("BinderPlugin", "IsUse", bUse ? "1" : "0", strIni);
}

/**
 * @brif 
 */
BOOL WINAPI ExitPlugin(){
	if(::IsWindow(g_binderWnd.m_hWnd)){
		g_binderWnd.SendMessage(WM_CLOSE);
	}
	return TRUE;
}

/**
 * @brif 
 */
HWND WINAPI GetTabWnd(HWND hParent){
	if(::IsWindow(g_binderWnd.m_hWnd)){
		return g_binderWnd.m_hWnd;
	}
	CRect rect(0, 0, 1, 1);
	CWnd *pWnd = CWnd::FromHandle(hParent);
	g_binderWnd.DestroyWindow();
	g_binderWnd.Create(WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, rect, pWnd, g_uTabID);
	return g_binderWnd.m_hWnd;
}

void WINAPI SetLogFlag(BOOL bLogState, BOOL bAppLogState, BOOL bExceptLogState, BOOL bFatalLogState){
	CLogFile::SetLogState(bLogState);
	CLogFile::SetAppLogState(bAppLogState);	
	CLogFile::SetExceptLogState(bExceptLogState);
	CLogFile::SetFatalLogState(bFatalLogState);
}
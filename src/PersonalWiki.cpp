// PersonalWiki.cpp : �A�v���P�[�V�����p�N���X�̋@�\��`���s���܂��B
//

#include "stdafx.h"
#include "PersonalWiki.h"

#include "MainFrm.h"
#include "PWikiDoc.h"
#include "PWikiView.h"
#include "InfoView.h"
#include "InfoTabView.h"
#include "LogFile.h" 
#include "DlgPwInp.h"
#include "PWikiPlugin.h"
#include "DebugSupport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HANDLE gMutex = NULL;
const TCHAR gMutexName[] = _T("PersonalWiki Exclusive Mutex");

/////////////////////////////////////////////////////////////////////////////
// CPWikiApp

BEGIN_MESSAGE_MAP(CPWikiApp, CWinApp)
	//{{AFX_MSG_MAP(CPWikiApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_WM_DEVMODECHANGE()
	//}}AFX_MSG_MAP
	// �W���̃t�@�C����{�h�L�������g �R�}���h
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// �W���̈���Z�b�g�A�b�v �R�}���h
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPWikiApp �N���X�̍\�z

CPWikiApp::CPWikiApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CPWikiApp �I�u�W�F�N�g

CPWikiApp theApp;
#include "AbstractWnd.h"
/////////////////////////////////////////////////////////////////////////////
// CPWikiApp �N���X�̏�����

BOOL CPWikiApp::InitInstance()
{
	AfxEnableControlContainer();
	AfxInitRichEdit();

	CPWikiIniFile objIniFile;
	char szPath[MAX_PATH + 1];
	memset(szPath, 0, MAX_PATH + 1);
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	CString strIniPath = szPath;
	strIniPath.Replace(".exe", ".ini");
	objIniFile.IniFileAccess(strIniPath, FALSE);
	APPINFO objAppInfo;
	DEBUGINFO objDbgInfo;
	objIniFile.GetAppInfoIniData(objAppInfo);
	objIniFile.GetDebugInfoIniData(objDbgInfo);	

	CLogFile::SetLogState(objDbgInfo.bLogOut);
	CLogFile::SetAppLogState(objDbgInfo.bAppLogOut);
	CLogFile::SetFatalLogState(objDbgInfo.bFatalLogOut);
	CLogFile::SetExceptLogState(objDbgInfo.bExceptLogOut);

	CLogFile::SaveAppLog("--------------------------------------------------");
 	CLogFile::SaveAppLog("�N��");


	//----------------------------------------------------------------------
	//���d�N���h�~
	gMutex = ::CreateMutex(NULL, FALSE, gMutexName);
	if (gMutex == NULL) { 
		return FALSE; 
	} 
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		CLogFile::SaveAppLog("���d�N���`�F�b�N�ŏI��");
		::ReleaseMutex(gMutex);
		return FALSE;
	}

	//----------------------------------------------------------------------
	//�p�X���[�h
	if(objAppInfo.bUsePassWord){
		CDlgPwInp dlg;
		while(TRUE){
			if(dlg.DoModal() == IDCANCEL){
				CLogFile::SaveAppLog("�p�X���[�h���̓L�����Z���ŏI��");
				return FALSE;
			}
			if(!dlg.m_strPassWord.Compare(objAppInfo.szPassWord)){
				break;
			}
		}
	}

	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������
	// ��������Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ���
	// ���폜���Ă��������B

	CAbstractWnd::SetPath();

#ifdef _AFXDLL
	Enable3dControls();		// ���L DLL �̒��� MFC ���g�p����ꍇ�ɂ͂������Ăяo���Ă��������B
#else
	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N���Ă���ꍇ�ɂ͂������Ăяo���Ă��������B
#endif


	//�v���O�C���̓ǂݍ���(�\��)


//	// �ݒ肪�ۑ�����鉺�̃��W�X�g�� �L�[��ύX���܂��B
//	// TODO: ���̕�������A��Ж��܂��͏����ȂǓK�؂Ȃ��̂�
//	// �ύX���Ă��������B
//	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
//
//	LoadStdProfileSettings(0);  // �W���� INI �t�@�C���̃I�v�V���������[�ނ��܂� (MRU ���܂�)

	// �A�v���P�[�V�����p�̃h�L�������g �e���v���[�g��o�^���܂��B�h�L�������g �e���v���[�g
	//  �̓h�L�������g�A�t���[�� �E�B���h�E�ƃr���[���������邽�߂ɋ@�\���܂��B

//	CAbstractWnd::SetMainFrame(RUNTIME_CLASS(CMainFrame));

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPWikiDoc),
		RUNTIME_CLASS(CMainFrame),       // ���C�� SDI �t���[�� �E�B���h�E
		RUNTIME_CLASS(CInfoTabView));
	AddDocTemplate(pDocTemplate);

	// DDE�Afile open �ȂǕW���̃V�F�� �R�}���h�̃R�}���h���C������͂��܂��B
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// �R�}���h���C���Ńf�B�X�p�b�` �R�}���h���w�肵�܂��B
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// ���C�� �E�B���h�E�����������ꂽ�̂ŁA�\���ƍX�V���s���܂��B
	APPINFO objIni;
	memset(&objIni, 0, sizeof(APPINFO));
	((CMainFrame*)m_pMainWnd)->m_objIniFile.GetAppInfoIniData(objIni);
	if(objIni.bRunMainWndShow){
		m_pMainWnd->ShowWindow(SW_SHOW);
	}else{
		m_pMainWnd->ShowWindow(SW_HIDE);
	}
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// �A�v���P�[�V�����̃o�[�W�������Ŏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard ���z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	//{{AFX_MSG(CAboutDlg)
		// ���b�Z�[�W �n���h���͂���܂���B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// ���b�Z�[�W �n���h���͂���܂���B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// �_�C�A���O�����s���邽�߂̃A�v���P�[�V���� �R�}���h
void CPWikiApp::OnAppAbout(){
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPWikiApp ���b�Z�[�W �n���h��
BOOL CPWikiApp::ProcessShellCommand( CCommandLineInfo& rCmdInfo ){
	__try{
		return CWinApp::ProcessShellCommand(rCmdInfo);
	}__except(CDebugSupport::Except(GetExceptionInformation())){
		return FALSE;
	}
}

int CPWikiApp::Run(){
#if defined(_DEBUG)
	return CWinApp::Run();
#else
	__try{
		return CWinApp::Run();
	}__except(CDebugSupport::Except(GetExceptionInformation())){
		return 1;
	}
#endif
	return 0;
}

int CPWikiApp::ExitInstance() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CLogFile::SaveAppLog("�I��");
	CLogFile::SaveAppLog("--------------------------------------------------");
	::ReleaseMutex(gMutex);
	gMutex = NULL;
	return CWinApp::ExitInstance();
}

void CPWikiApp::OnDevModeChange(LPTSTR lpDeviceName){
	TRACE("DEVICE CHANGE");
}

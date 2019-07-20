// ExceptTest.cpp : �A�v���P�[�V�����p�N���X�̋@�\��`���s���܂��B
//

#include "stdafx.h"
#include "ExceptTest.h"

#include "MainFrm.h"
#include "ExceptTestDoc.h"
#include "ExceptTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExceptTestApp

BEGIN_MESSAGE_MAP(CExceptTestApp, CWinApp)
	//{{AFX_MSG_MAP(CExceptTestApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
	// �W���̃t�@�C����{�h�L�������g �R�}���h
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// �W���̈���Z�b�g�A�b�v �R�}���h
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExceptTestApp �N���X�̍\�z

CExceptTestApp::CExceptTestApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CExceptTestApp �I�u�W�F�N�g

CExceptTestApp theApp;

int CExceptTestApp::Except(LPEXCEPTION_POINTERS pExp){
	if(pExp){
		CString strExpCode = "UNKNOW";
		switch(pExp->ExceptionRecord->ExceptionCode){
		case EXCEPTION_ACCESS_VIOLATION:
			strExpCode = "EXCEPTION_ACCESS_VIOLATION";
			break;
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
			strExpCode = "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
			break;
		case EXCEPTION_BREAKPOINT:
			strExpCode = "EXCEPTION_BREAKPOINT";
			break;
		case EXCEPTION_DATATYPE_MISALIGNMENT:
			strExpCode = "EXCEPTION_DATATYPE_MISALIGNMENT";
			break;
		case EXCEPTION_FLT_DENORMAL_OPERAND:
			strExpCode = "EXCEPTION_FLT_DENORMAL_OPERAND";
			break;
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:
			strExpCode = "EXCEPTION_FLT_DIVIDE_BY_ZERO";
			break;
		case EXCEPTION_FLT_INEXACT_RESULT:
			strExpCode = "EXCEPTION_FLT_INEXACT_RESULT";
			break;
		case EXCEPTION_FLT_INVALID_OPERATION:
			strExpCode = "EXCEPTION_FLT_INVALID_OPERATION";
			break;
		case EXCEPTION_FLT_OVERFLOW:
			strExpCode = "EXCEPTION_FLT_OVERFLOW";
			break;
		case EXCEPTION_FLT_STACK_CHECK:
			strExpCode = "EXCEPTION_FLT_STACK_CHECK";
			break;
		case EXCEPTION_FLT_UNDERFLOW:
			strExpCode = "EXCEPTION_FLT_UNDERFLOW";
			break;
		case EXCEPTION_ILLEGAL_INSTRUCTION:
			strExpCode = "EXCEPTION_ILLEGAL_INSTRUCTION";
			break;
		case EXCEPTION_IN_PAGE_ERROR:
			strExpCode = "EXCEPTION_IN_PAGE_ERROR";
			break;
		case EXCEPTION_INT_DIVIDE_BY_ZERO:
			strExpCode = "EXCEPTION_INT_DIVIDE_BY_ZERO";
			break;
		case EXCEPTION_INT_OVERFLOW:
			strExpCode = "EXCEPTION_INT_OVERFLOW";
			break;
		case EXCEPTION_INVALID_DISPOSITION:
			strExpCode = "EXCEPTION_INVALID_DISPOSITION";
			break;
		case EXCEPTION_NONCONTINUABLE_EXCEPTION:
			strExpCode = "EXCEPTION_NONCONTINUABLE_EXCEPTION";
			break;
		case EXCEPTION_PRIV_INSTRUCTION:
			strExpCode = "EXCEPTION_PRIV_INSTRUCTION";
			break;
		case EXCEPTION_SINGLE_STEP :
			strExpCode = "EXCEPTION_SINGLE_STEP";
			break;
		case EXCEPTION_STACK_OVERFLOW:
			strExpCode = "EXCEPTION_STACK_OVERFLOW";
			break;
		default:
			break;
		}
		CString strExpInfo;
		strExpInfo.Format("%d[0x%08X] : %s\r\n"
						  "           Flag = 0x%08X\r\n"
						  "           Address = 0x%08X\r\n"
						,pExp->ExceptionRecord->ExceptionCode
						,pExp->ExceptionRecord->ExceptionCode
						,strExpCode
						,pExp->ExceptionRecord->ExceptionFlags
						,pExp->ExceptionRecord->ExceptionAddress);
//		pExp->ExceptionRecord.ExceptionFlags;
//		pExp->ExceptionRecord.ExceptionRecord ;
//		pExp->ExceptionRecord.ExceptionAddress;
//		pExp->NumberParameters;
//		pExp->ExceptionInformation;
		AfxMessageBox(strExpInfo);
	}
//	return EXCEPTION_CONTINUE_EXECUTION(-1);
	return 0;
//	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CExceptTestApp �N���X�̏�����

BOOL CExceptTestApp::InitInstance()
{
	AfxEnableControlContainer();

	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������
	// ��������Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ���
	// ���폜���Ă��������B

#ifdef _AFXDLL
	Enable3dControls();		// ���L DLL �̒��� MFC ���g�p����ꍇ�ɂ͂������Ăяo���Ă��������B
#else
	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N���Ă���ꍇ�ɂ͂������Ăяo���Ă��������B
#endif

	// �ݒ肪�ۑ�����鉺�̃��W�X�g�� �L�[��ύX���܂��B
	// TODO: ���̕�������A��Ж��܂��͏����ȂǓK�؂Ȃ��̂�
	// �ύX���Ă��������B
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // �W���� INI �t�@�C���̃I�v�V���������[�ނ��܂� (MRU ���܂�)

	// �A�v���P�[�V�����p�̃h�L�������g �e���v���[�g��o�^���܂��B�h�L�������g �e���v���[�g
	//  �̓h�L�������g�A�t���[�� �E�B���h�E�ƃr���[���������邽�߂ɋ@�\���܂��B

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CExceptTestDoc),
		RUNTIME_CLASS(CMainFrame),       // ���C�� SDI �t���[�� �E�B���h�E
		RUNTIME_CLASS(CExceptTestView));
	AddDocTemplate(pDocTemplate);

	// DDE�Afile open �ȂǕW���̃V�F�� �R�}���h�̃R�}���h���C������͂��܂��B
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// �R�}���h���C���Ńf�B�X�p�b�` �R�}���h���w�肵�܂��B
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// ���C�� �E�B���h�E�����������ꂽ�̂ŁA�\���ƍX�V���s���܂��B
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}
BOOL CExceptTestApp::ProcessShellCommand( CCommandLineInfo& rCmdInfo ){
	__try{
		return CWinApp::ProcessShellCommand(rCmdInfo);
	}__except(Except(GetExceptionInformation())){
		return FALSE;
	}
}



int CExceptTestApp::Run() {
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	int nRet = -1;
	__try{	
		nRet = CWinApp::Run();
	}__except(Except(GetExceptionInformation())){
		//��O�����̂܂ܕԋp���āA�A�v���P�[�V�������I��������
	}

	return nRet;
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
void CExceptTestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CExceptTestApp ���b�Z�[�W �n���h��


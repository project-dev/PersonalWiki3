// PersonalWiki.cpp : アプリケーション用クラスの機能定義を行います。
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
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// 標準の印刷セットアップ コマンド
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPWikiApp クラスの構築

CPWikiApp::CPWikiApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CPWikiApp オブジェクト

CPWikiApp theApp;
#include "AbstractWnd.h"
/////////////////////////////////////////////////////////////////////////////
// CPWikiApp クラスの初期化

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
 	CLogFile::SaveAppLog("起動");


	//----------------------------------------------------------------------
	//多重起動防止
	gMutex = ::CreateMutex(NULL, FALSE, gMutexName);
	if (gMutex == NULL) { 
		return FALSE; 
	} 
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		CLogFile::SaveAppLog("多重起動チェックで終了");
		::ReleaseMutex(gMutex);
		return FALSE;
	}

	//----------------------------------------------------------------------
	//パスワード
	if(objAppInfo.bUsePassWord){
		CDlgPwInp dlg;
		while(TRUE){
			if(dlg.DoModal() == IDCANCEL){
				CLogFile::SaveAppLog("パスワード入力キャンセルで終了");
				return FALSE;
			}
			if(!dlg.m_strPassWord.Compare(objAppInfo.szPassWord)){
				break;
			}
		}
	}

	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さく
	// したければ以下の特定の初期化ルーチンの中から不必要なもの
	// を削除してください。

	CAbstractWnd::SetPath();

#ifdef _AFXDLL
	Enable3dControls();		// 共有 DLL の中で MFC を使用する場合にはここを呼び出してください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクしている場合にはここを呼び出してください。
#endif


	//プラグインの読み込み(予定)


//	// 設定が保存される下のレジストリ キーを変更します。
//	// TODO: この文字列を、会社名または所属など適切なものに
//	// 変更してください。
//	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
//
//	LoadStdProfileSettings(0);  // 標準の INI ファイルのオプションをローﾄﾞします (MRU を含む)

	// アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
	//  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。

//	CAbstractWnd::SetMainFrame(RUNTIME_CLASS(CMainFrame));

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPWikiDoc),
		RUNTIME_CLASS(CMainFrame),       // メイン SDI フレーム ウィンドウ
		RUNTIME_CLASS(CInfoTabView));
	AddDocTemplate(pDocTemplate);

	// DDE、file open など標準のシェル コマンドのコマンドラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// コマンドラインでディスパッチ コマンドを指定します。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// メイン ウィンドウが初期化されたので、表示と更新を行います。
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
// アプリケーションのバージョン情報で使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard 仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
		// メッセージ ハンドラはありません。
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
		// メッセージ ハンドラはありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// ダイアログを実行するためのアプリケーション コマンド
void CPWikiApp::OnAppAbout(){
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPWikiApp メッセージ ハンドラ
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
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CLogFile::SaveAppLog("終了");
	CLogFile::SaveAppLog("--------------------------------------------------");
	::ReleaseMutex(gMutex);
	gMutex = NULL;
	return CWinApp::ExitInstance();
}

void CPWikiApp::OnDevModeChange(LPTSTR lpDeviceName){
	TRACE("DEVICE CHANGE");
}

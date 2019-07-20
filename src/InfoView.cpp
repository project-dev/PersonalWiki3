// InfoView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "InfoView.h"
#include "EventDate.h"
#include "PWikiDoc.h"
#include "MainFrm.h"
#include "LogFile.h"
#include "FindFile.h"
#include "DlgWikiInp.h"
#include "CalView.h"
#include "FileCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoView

IMPLEMENT_DYNCREATE(CInfoView, CHtmlView)

CInfoView::CInfoView()
{
	//{{AFX_DATA_INIT(CInfoView)
		// メモ: ClassWizard はこの位置にメンバの初期化処理を追加します。
	//}}AFX_DATA_INIT
}

CInfoView::~CInfoView()
{
}

void CInfoView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoView)
		// メモ: ClassWizard はこの位置に DDX と DDV の呼び出しコードを追加します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfoView, CHtmlView)
	//{{AFX_MSG_MAP(CInfoView)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoView diagnostics

#ifdef _DEBUG
void CInfoView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CInfoView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInfoView message handlers

void CInfoView::OnInitialUpdate(){
	CLogFile::SaveAppLog("CInfoView::OnInitialUpdate Start");
	CString strBasePath = GetBasePath();
	CString strTmpHtml;
	strTmpHtml.Format("%sTmp.html", strBasePath);
	CStdioFile file;

	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CInfoView::OnInitialUpdate : pFrm is null");
	}
	WIKIINFO objInfo;
	pFrm->m_objIniFile.GetWikiInfoIniData(objInfo);

	CString strHtml;
	CString strBody;
	strBody.Format(
		"<TABLE class=\"body\"><TR><TD class=\"body\">"
		"Personal Wiki(仮名)は、カレンダーとメモをベースとし、Wiki書式で書き込みが出来るソフトです。<BR>"
		"そのため、文字の修飾、画像の表示を行うことが出来ます。<BR>"
		"Wiki書式がわからなくても、メモを残すことも可能です。<BR>"
		"プラグインで機能を拡張することも予定しています。<BR>"
		"<BR>"
		"情報バーで今日の予定を表示するので、デスクトップのスペースを占有することもありません。<BR>"
		"<BR>"
		"<hr>"
		"記念日一覧は<A href=\"http://ja.wikipedia.org/\" target=\"_blank\">Wikipedia</a>の<A href=\"http://ja.wikipedia.org/wiki/%%E6%%97%%A5%%E6%%9C%%AC%%E3%%81%%AE%%E8%%A8%%98%%E5%%BF%%B5%%E6%%97%%A5%%E4%%B8%%80%%E8%%A6%%A7\" target=\"_blank\">記事</a>を参考にしました。");
	CAnalisysWiki objAna;
	objAna.CreateHTML(strHtml, objInfo.szCss, "PersonalWiki(仮)", strBody);
	
	try{
		if(!file.Open(strTmpHtml, CFile::modeCreate | CFile::modeReadWrite)){
			throw(0);
		}
		file.WriteString(strHtml);
		file.Flush();
		file.Close();
	}catch(CFileException &fe){
		char szErr[1025];
		memset(szErr,  0, 1025);
		fe.GetErrorMessage(szErr, 1024);
		AfxMessageBox(szErr);
		file.Close();
		CLogFile::SaveExceptionLog(&fe, "CInfoView::OnInitialUpdate");
	}catch(...){
		file.Close();
		CLogFile::SaveExceptionLog("CInfoView::OnInitialUpdate");
	}

	Navigate2(strTmpHtml,NULL,NULL);
	CLogFile::SaveAppLog("CInfoView::OnInitialUpdate End");
}
/*
void CInfoView::UpdateInfo(COleDateTime *pTargetDate){
}

void CInfoView::UpdateInfo(CString &strWikiPath){
}

void CInfoView::UpdateInfoUSB(CString &strWikiPath, LPCTSTR pszBasePath){
}
*/
void CInfoView::OnDownloadBegin() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
	CHtmlView::OnDownloadBegin();
}

void CInfoView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel){
	CString strURL = lpszURL;
	CString strWiki = "wiki://";
	if(strURL.GetLength() >= strWiki.GetLength()){
		if(!strURL.Left(strWiki.GetLength()).CompareNoCase(strWiki)){
			//内部ドキュメントへのリンク
			strURL = strURL.Right(strURL.GetLength() - strWiki.GetLength());
			
			int nYear = 0;
			int nMonth = 0;
			int nDay = 0;
			if(strURL.GetLength() == (int)strlen("yyyy/mm/dd")){
				nYear = atoi(strURL.Left(4));
				nMonth = atoi(strURL.Mid(5, 2));
				nDay = atoi(strURL.Mid(8, 2));
			}

			if((nYear > 1900) && (nMonth >= 1) && (nMonth <= 12) && (nDay >= 1) && (nDay <= 31)) {
				//指定日付を表示させる。
				COleDateTime objDate;
				objDate.SetDate(nYear, nMonth, nDay);
				UpdateInfoSc(&objDate);
			}else{
				int nPos = strURL.ReverseFind('\\');
				if(nPos != -1){
					CString strBase = strURL.Left(nPos) + "\\";
					strURL = strURL.Mid(nPos + 5);
					UpdateInfoUSB(strURL, strBase);
				}else{
					UpdateInfo(strURL);
				}
			}

			//キャンセルさせる
			*pbCancel = TRUE;
			CHtmlView::OnBeforeNavigate2(lpszURL, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
			return;
		}
	}
	CHtmlView::OnBeforeNavigate2(lpszURL, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
}

void CInfoView::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
	CHtmlView::OnNewWindow2(ppDisp, Cancel);
}

int CInfoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CHtmlView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: この位置に固有の作成用コードを追加してください
	m_pInfo = this;
#if defined(USE_CREATE_VIEW)
	GetMainFrame(this)->m_pHtmlView = this;
#endif
	CLogFile::SaveAppLog("CInfoView 生成");	
	return 0;
}

void CInfoView::OnShowWindow(BOOL bShow, UINT nStatus) {
	CHtmlView::OnShowWindow(bShow, nStatus);

}

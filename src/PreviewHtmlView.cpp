// PreviewHtmlView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "personalwiki.h"
#include "PreviewHtmlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreviewHtmlView

IMPLEMENT_DYNCREATE(CPreviewHtmlView, CHtmlView)

CPreviewHtmlView::CPreviewHtmlView()
{
	//{{AFX_DATA_INIT(CPreviewHtmlView)
		// メモ: ClassWizard はこの位置にメンバの初期化処理を追加します。
	//}}AFX_DATA_INIT
}

CPreviewHtmlView::~CPreviewHtmlView()
{
}

void CPreviewHtmlView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreviewHtmlView)
		// メモ: ClassWizard はこの位置に DDX と DDV の呼び出しコードを追加します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreviewHtmlView, CHtmlView)
	//{{AFX_MSG_MAP(CPreviewHtmlView)
	ON_WM_MOUSEACTIVATE()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreviewHtmlView diagnostics

#ifdef _DEBUG
void CPreviewHtmlView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CPreviewHtmlView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPreviewHtmlView message handlers

int CPreviewHtmlView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message){
//	return CHtmlView::OnMouseActivate(pDesktopWnd, nHitTest, message);
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CPreviewHtmlView::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized){
	CHtmlView::OnActivate(nState, pWndOther, bMinimized);
}

void CPreviewHtmlView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CString strTmpPath;
	strTmpPath.Format("%sprev.html", GetBasePath());
	CString strURL = lpszURL;
	strURL.Replace("file://", "");
	strURL.Replace("/", "\\");
	if(strTmpPath.CompareNoCase(strURL)){
		AfxMessageBox("プレビューでは他のページに遷移することはできません。");
		*pbCancel = TRUE;
	}
	
	CHtmlView::OnBeforeNavigate2(lpszURL, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
}

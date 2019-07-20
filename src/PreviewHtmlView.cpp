// PreviewHtmlView.cpp : �C���v�������e�[�V���� �t�@�C��
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
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�̏�����������ǉ����܂��B
	//}}AFX_DATA_INIT
}

CPreviewHtmlView::~CPreviewHtmlView()
{
}

void CPreviewHtmlView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreviewHtmlView)
		// ����: ClassWizard �͂��̈ʒu�� DDX �� DDV �̌Ăяo���R�[�h��ǉ����܂��B
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
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CString strTmpPath;
	strTmpPath.Format("%sprev.html", GetBasePath());
	CString strURL = lpszURL;
	strURL.Replace("file://", "");
	strURL.Replace("/", "\\");
	if(strTmpPath.CompareNoCase(strURL)){
		AfxMessageBox("�v���r���[�ł͑��̃y�[�W�ɑJ�ڂ��邱�Ƃ͂ł��܂���B");
		*pbCancel = TRUE;
	}
	
	CHtmlView::OnBeforeNavigate2(lpszURL, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
}

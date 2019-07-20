// InfoView.cpp : �C���v�������e�[�V���� �t�@�C��
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
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�̏�����������ǉ����܂��B
	//}}AFX_DATA_INIT
}

CInfoView::~CInfoView()
{
}

void CInfoView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoView)
		// ����: ClassWizard �͂��̈ʒu�� DDX �� DDV �̌Ăяo���R�[�h��ǉ����܂��B
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
		"Personal Wiki(����)�́A�J�����_�[�ƃ������x�[�X�Ƃ��AWiki�����ŏ������݂��o����\�t�g�ł��B<BR>"
		"���̂��߁A�����̏C���A�摜�̕\�����s�����Ƃ��o���܂��B<BR>"
		"Wiki�������킩��Ȃ��Ă��A�������c�����Ƃ��\�ł��B<BR>"
		"�v���O�C���ŋ@�\���g�����邱�Ƃ��\�肵�Ă��܂��B<BR>"
		"<BR>"
		"���o�[�ō����̗\���\������̂ŁA�f�X�N�g�b�v�̃X�y�[�X���L���邱�Ƃ�����܂���B<BR>"
		"<BR>"
		"<hr>"
		"�L�O���ꗗ��<A href=\"http://ja.wikipedia.org/\" target=\"_blank\">Wikipedia</a>��<A href=\"http://ja.wikipedia.org/wiki/%%E6%%97%%A5%%E6%%9C%%AC%%E3%%81%%AE%%E8%%A8%%98%%E5%%BF%%B5%%E6%%97%%A5%%E4%%B8%%80%%E8%%A6%%A7\" target=\"_blank\">�L��</a>���Q�l�ɂ��܂����B");
	CAnalisysWiki objAna;
	objAna.CreateHTML(strHtml, objInfo.szCss, "PersonalWiki(��)", strBody);
	
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
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
	CHtmlView::OnDownloadBegin();
}

void CInfoView::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel){
	CString strURL = lpszURL;
	CString strWiki = "wiki://";
	if(strURL.GetLength() >= strWiki.GetLength()){
		if(!strURL.Left(strWiki.GetLength()).CompareNoCase(strWiki)){
			//�����h�L�������g�ւ̃����N
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
				//�w����t��\��������B
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

			//�L�����Z��������
			*pbCancel = TRUE;
			CHtmlView::OnBeforeNavigate2(lpszURL, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
			return;
		}
	}
	CHtmlView::OnBeforeNavigate2(lpszURL, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
}

void CInfoView::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel) 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
	CHtmlView::OnNewWindow2(ppDisp, Cancel);
}

int CInfoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CHtmlView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: ���̈ʒu�ɌŗL�̍쐬�p�R�[�h��ǉ����Ă�������
	m_pInfo = this;
#if defined(USE_CREATE_VIEW)
	GetMainFrame(this)->m_pHtmlView = this;
#endif
	CLogFile::SaveAppLog("CInfoView ����");	
	return 0;
}

void CInfoView::OnShowWindow(BOOL bShow, UINT nStatus) {
	CHtmlView::OnShowWindow(bShow, nStatus);

}

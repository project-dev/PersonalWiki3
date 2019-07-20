// AbstractBaseWnd.cpp: CAbstractBaseWnd クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "personalwiki.h"
#include "AbstractBaseWnd.h"
#include "MainFrm.h"
#include "LogFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CAbstractBaseWnd::CAbstractBaseWnd(){

}

CAbstractBaseWnd::~CAbstractBaseWnd(){

}

CMainFrame* CAbstractBaseWnd::GetMainFrame(CWnd *pMyWnd){
	CMainFrame *pFrm = NULL;
	CRuntimeClass *pMainFrm = RUNTIME_CLASS(CMainFrame);
	try{
		if(!IsWindowSafe(pMyWnd)){
			throw(0);
		}
		CWnd *pWnd = AfxGetMainWnd();
		if(IsWindowSafe(pWnd)){
			if(pWnd->IsKindOf(pMainFrm)){
				return (CMainFrame*)pWnd;
			}
		}
		pWnd = pMyWnd->GetParent();
		while(pWnd){
			if(!IsWindowSafe(pWnd)){
				throw(0);
			}
			if(pWnd->IsKindOf(pMainFrm)){
				pFrm = (CMainFrame*)pWnd;
				break;		
			}
			pWnd = pWnd->GetParent();
		}
	}catch(...){
		pFrm = NULL;
		CLogFile::SaveExceptionLog("CAbstractWnd::GetMainFrame");
	}

	return pFrm;
}

void CAbstractBaseWnd::UpdateSetting(){
}

CDocument* CAbstractBaseWnd::GetDoc(){
	CWinApp* pApp = AfxGetApp();
	POSITION pos = pApp->GetFirstDocTemplatePosition();
	CDocTemplate* pDocTempl = pApp->GetNextDocTemplate(pos);
	pos = pDocTempl->GetFirstDocPosition();
	return pDocTempl->GetNextDoc(pos);

}

void CAbstractBaseWnd::UpdateAllWnd(){

}
void CAbstractBaseWnd::MakeFont(CFont& objFont, CDC *pDC, LPCTSTR pszFontFace, int nHeight){
	objFont.DeleteObject();
	int nSizeY = -MulDiv(nHeight, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	LOGFONT lFont;
	memset(&lFont, 0, sizeof(LOGFONT));
	lFont.lfHeight = nSizeY;
	strcpy(lFont.lfFaceName, pszFontFace);
	lFont.lfCharSet = DEFAULT_CHARSET;
	objFont.CreateFontIndirect(&lFont);
}

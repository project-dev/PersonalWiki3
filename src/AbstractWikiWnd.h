// AbstractWikiWnd.h: CAbstractWikiWnd クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSTRACTWIKIWND_H__90AC1294_271F_432B_A0E1_AB9EA6AC7F4B__INCLUDED_)
#define AFX_ABSTRACTWIKIWND_H__90AC1294_271F_432B_A0E1_AB9EA6AC7F4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "AbstractBaseWnd.h"
#include "AnalisysWiki.h"

class CPWikiDoc;
class CInfoView;
class CWikiEditWnd;

typedef enum eLOADSTATE{
	LD_OK,
	LD_NG,
	LD_NEW,
};

class CAbstractWikiWnd : public CAbstractBaseWnd{
public:
	eLOADSTATE LoadWikiText(LPCTSTR pszWikiPath, LPCTSTR pszBasePath, CString &strBuff);
	CAbstractWikiWnd();
	virtual ~CAbstractWikiWnd();
	void GetHtmlHead(CString &strHtml, LPCTSTR pszTitle);
	void UpdateInfoSc(COleDateTime *pDate);
	void UpdateInfo(CString &strWikiPath);
	void UpdateInfoUSB(CString &strBasePath, LPCTSTR pszBasePath);

private:
	CAnalisysWiki m_objAnalisys;

protected:
	static CString m_strDataBasePath;
	static CString m_strWikiPath;
	static CMainFrame* m_pFrm;
	static CPWikiDoc* m_pDoc;
	static CInfoView* m_pInfo;
	static CWikiEditWnd* m_pEdit;
};

#endif // !defined(AFX_ABSTRACTWIKIWND_H__90AC1294_271F_432B_A0E1_AB9EA6AC7F4B__INCLUDED_)

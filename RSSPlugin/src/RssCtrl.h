// RssCtrl.h: CRssCtrl クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RSSCTRL_H__7779111B_0117_4329_9B8A_944BBBB20C1B__INCLUDED_)
#define AFX_RSSCTRL_H__7779111B_0117_4329_9B8A_944BBBB20C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#import "msxml.dll" named_guids raw_interfaces_only
using namespace MSXML;

#include <atlbase.h>
#include "RSSPluginCommon.h"

class CRssCtrl{
public:
	BOOL GetRSS(CString &strRSS);
	BOOL Create(LPCTSTR pszURL, LPCTSTR pszUserID, LPCTSTR pszPass);
	CRssCtrl();
	BOOL ConvertHTML(LPCTSTR szRSS, CString &strOutHtml);
	virtual ~CRssCtrl();
private:
	//RDFで始まるRSS解析
	BOOL RDFAnalyzer(IXMLDOMElementPtr pRoot);
	BOOL RDFChildAnalyze(IXMLDOMNodePtr pNode, BOOL bCannel);

	//RSSで始まるRSS解析
	BOOL RSSAnalyzer(IXMLDOMElementPtr pRoot);
	BOOL RSSChildV2Analyze(IXMLDOMNodePtr pNode, BOOL bCannel);

	BOOL EncodString(CString &strBuff);

	void GetXMLText( CComBSTR &bstrText, CString &strText );
	void GetIXMLErrMsg( IXMLDOMParseErrorPtr error, CString &strMsg );
	void GetRSSDate(LPCTSTR pszDate, CString &strDate, BOOL bShort);

	CString				m_strErrMsg;
	CString				m_strURL;
	CString				m_strUser;
	CString				m_strPass;
	CString				m_strContents;
	IXMLDOMDocumentPtr	m_pXMLDoc;
	CString				m_strRSSContents;
	CString				m_strTopics;
	CString				m_strTitle;
	CString				m_strLink;
};

#endif // !defined(AFX_RSSCTRL_H__7779111B_0117_4329_9B8A_944BBBB20C1B__INCLUDED_)

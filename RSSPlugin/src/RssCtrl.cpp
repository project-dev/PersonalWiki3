// RssCtrl.cpp: CRssCtrl クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RssCtrl.h"
#include <afxinet.h>
//#include <wincrypt.h>
#include "StringEncode.h"
#include "devlib.h"
#include "devstring.h"
#include "RSSPluginCommon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

typedef enum GETRSSRESULT{
	DONT_GET_SERVERNAME = 0,
	DONT_GET_CONNECTION,
	DONT_OPEN_REQUEST,
	DONT_SET_USERID,
	DONT_SET_PASSWORD,
	DONT_SEND_REQUEST,
	FAILD_REQUEST_STATUS,
};

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CRssCtrl::CRssCtrl(){
	m_strErrMsg = "";
	m_strURL = "";
	m_strUser = "";
	m_strPass = "";
	m_strContents = "";
}

CRssCtrl::~CRssCtrl(){

}

BOOL CRssCtrl::Create(LPCTSTR pszURL, LPCTSTR pszUserID, LPCTSTR pszPass){
	m_strErrMsg = "";
	m_strURL = pszURL;
	m_strUser = pszUserID;
	m_strPass = pszPass;
	m_strContents = "";
	return TRUE;
}



BOOL CRssCtrl::GetRSS(CString &strRSS){
	m_strErrMsg = "";
	strRSS = "";
	::SetEvent(RSS_EVENT);
	if(::InternetAttemptConnect(0) != ERROR_SUCCESS){
		//ネットワークに接続できていないので何もしない
		m_strErrMsg = "";
		return FALSE;
	}
	CHttpConnection		*pHttp			= NULL;
	CHttpFile			*pHttpFile		= NULL;
	INTERNET_PORT		nPort			= INTERNET_DEFAULT_HTTP_PORT;
	DWORD				dwServiceType	= 0;
	CString				strServer		= "";
	CString				strObject		= "";
//	CInternetSession	objSession("Personal Wiki", 0,
	CInternetSession	objSession("Personal Wiki", 1,
									INTERNET_OPEN_TYPE_PRECONFIG,
									NULL, NULL,
									INTERNET_FLAG_DONT_CACHE);
	BOOL bRet = TRUE;
	BOOL bHttps = FALSE;
	try{
		//---------------------------------------------------------------------------------
		//サーバー名の取得
		bRet = AfxParseURL(m_strURL, dwServiceType, strServer, strObject, nPort);
		if(!bRet){
			throw(DONT_GET_SERVERNAME);
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);

		//---------------------------------------------------------------------------------
		//
		DWORD dwReqFlag = INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE;
		if(dwServiceType == AFX_INET_SERVICE_HTTPS){
			dwReqFlag |=   INTERNET_FLAG_SECURE 
						 | INTERNET_FLAG_IGNORE_CERT_CN_INVALID
						 | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID;
			nPort = INTERNET_DEFAULT_HTTPS_PORT;
			bHttps = TRUE;
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);

		//---------------------------------------------------------------------------------
		//
		pHttp = objSession.GetHttpConnection(strServer, 
											 nPort, 
											 m_strUser, 
											 m_strPass);
		if( !pHttp ){
			throw(DONT_GET_CONNECTION);
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);

		//---------------------------------------------------------------------------------
		//
		pHttpFile = pHttp->OpenRequest(CHttpConnection::HTTP_VERB_GET,
									   strObject, 
									   NULL, 
									   1, 
									   NULL, 
									   NULL, 
									   dwReqFlag);
		if( !pHttpFile ){
			throw(DONT_OPEN_REQUEST);
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);

		//---------------------------------------------------------------------------------
		//ユーザーID/パスワードの設定する。
		if(!m_strUser.IsEmpty() || !m_strPass.IsEmpty()){
			//ユーザーID
			bRet = ::InternetSetOption(*pHttpFile, 
									 INTERNET_OPTION_USERNAME, 
									 (LPVOID)(LPCTSTR)m_strUser,  
									 m_strUser.GetLength());

			if(!bRet){
				throw(DONT_SET_USERID);
			}

			//パスワード
			bRet = ::InternetSetOption(*pHttpFile, 
									 INTERNET_OPTION_PASSWORD, 
									 (LPVOID)(LPCTSTR)m_strPass,  
									 m_strPass.GetLength());

			if(!bRet){
				throw(DONT_SET_PASSWORD);
			}
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);
		if(bHttps){
			DWORD dwFlags =
//							SECURITY_FLAG_128BIT
//						  | SECURITY_FLAG_40BIT 
//						  | SECURITY_FLAG_56BIT 
//						  | SECURITY_FLAG_FORTEZZA						//ないといわれた
//						  | SECURITY_FLAG_IETFSSL4 
						    SECURITY_FLAG_IGNORE_CERT_CN_INVALID 
						  | SECURITY_FLAG_IGNORE_CERT_DATE_INVALID 
						  | SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP 
						  | SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS 
//						  | SECURITY_FLAG_IGNORE_REVOCATION 
						  | SECURITY_FLAG_IGNORE_UNKNOWN_CA 
//						  | SECURITY_FLAG_IGNORE_WRONG_USAGE 
//						  | SECURITY_FLAG_NORMALBITNESS 
//						  | SECURITY_FLAG_PCT 
//						  | SECURITY_FLAG_PCT4 
//						  | SECURITY_FLAG_SECURE 
//						  | SECURITY_FLAG_SSL 
//						  | SECURITY_FLAG_SSL3 
//						  | SECURITY_FLAG_STRENGTH_MEDIUM 
//						  | SECURITY_FLAG_STRENGTH_STRONG 
//						  | SECURITY_FLAG_STRENGTH_WEAK 
//						  | SECURITY_FLAG_UNKNOWNBIT 
							,
			bRet = ::InternetSetOption(*pHttpFile, 
									 INTERNET_OPTION_SECURITY_FLAGS, 
									 &dwFlags,
									 sizeof(dwFlags));

			::PumpMessage(WM_TIMER, WM_TIMER);
			::PumpMessage(WM_PAINT, WM_PAINT);
			if(!bRet){
				throw(DONT_SET_PASSWORD);
			}
		}

		//---------------------------------------------------------------------------------
		//リクエストの送信
		if(!pHttpFile->SendRequest()){
			DWORD dwErr = GetLastError();
			if(dwErr == ERROR_INTERNET_FORCE_RETRY){
				::PumpMessage(WM_TIMER, WM_TIMER);
				::PumpMessage(WM_PAINT, WM_PAINT);
				//やり直し
				if(!pHttpFile->SendRequestEx(0)){
					throw(DONT_SEND_REQUEST);
				}
			}else{
				throw(DONT_SEND_REQUEST);
			}
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);
		DWORD dwErr = GetLastError();
		if(dwErr == 2){
			throw(DONT_SEND_REQUEST);
		}else if(dwErr){
			throw(DONT_SEND_REQUEST);
		}
	
		//---------------------------------------------------------------------------------
		//リクエストの送信
		DWORD dwRc = 0;
		pHttpFile->QueryInfoStatusCode(dwRc);										
		if (dwRc != HTTP_STATUS_OK){
			throw(FAILD_REQUEST_STATUS);
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);

		//---------------------------------------------------------------------------------
		//リクエストの送信
		CString strLine;
		while(pHttpFile->ReadString(strLine)){
			strRSS += strLine;
			strRSS += "\r\n";
			::PumpMessage(WM_TIMER, WM_TIMER);
			::PumpMessage(WM_PAINT, WM_PAINT);
		}
		if(!strRSS.IsEmpty()){
			int nStPos = strRSS.Find("encoding=\"", 0);
			int nEndPos = strRSS.Find("\"", nStPos + strlen("encoding=\""));
			CString strEnc = strRSS.Mid(nStPos, nEndPos - nStPos + 1);
			nStPos += strlen("encoding=\"");
			CString strCode = strRSS.Mid(nStPos, nEndPos - nStPos);
			strCode.TrimLeft();
			strCode.TrimRight();
			if(!EncodString(strRSS)){
				m_strContents.Empty();
			}else{
				strRSS = m_strContents;
				strRSS.Replace(strEnc, "encoding=\"Shift_JIS\"");
			}
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);
	}catch(GETRSSRESULT eErr){
		switch(eErr){
		case DONT_GET_SERVERNAME:
			m_strErrMsg = "サーバー名が取得できません";
			break;
		case DONT_GET_CONNECTION:
			m_strErrMsg = "コネクションの取得に失敗";
			break;
		case DONT_OPEN_REQUEST:
			m_strErrMsg = "リクエストのオープンに失敗";
			break;
		case DONT_SET_USERID:
		case DONT_SET_PASSWORD:
			m_strErrMsg = "ユーザーID/パスワードの設定に失敗しました";
			break;
		case DONT_SEND_REQUEST:
		case FAILD_REQUEST_STATUS:
			m_strErrMsg = "リクエストの送信に失敗しました";
			break;
		}
		strRSS = "";
	}catch(CInternetException& e){
		char szErr[1025];
		memset(szErr, 0, 1025);
		e.GetErrorMessage(szErr, 1024);
		m_strErrMsg = szErr;
		strRSS = "";
	}
	if(pHttpFile){
		pHttpFile->Close();
		delete pHttpFile;
	}
	if(pHttp){
		pHttp->Close();
		delete pHttp;
	}
	objSession.Close();
	::ResetEvent(RSS_EVENT);
	return bRet;
}

BOOL CRssCtrl::EncodString(CString &strBuff) {
	CStringEncode objStrEnc;
	CString strEncProc;
	CString strMsg;
	int nEnc = objStrEnc.CheckCode(strBuff.GetBuffer(strBuff.GetLength()));
	char *pszContents = NULL;

	if(nEnc == -1){
		//XMLに記述されたコードを利用
		int nPos = strBuff.Find("encoding=\"", 0);
		if(nPos != -1){
			CString strEnc = strBuff.Right(strBuff.GetLength() - nPos - strlen("encoding=\""));
			nPos = strEnc.Find("\"", 0);
			strEnc = strEnc.Left(nPos);
			if(strEnc.CompareNoCase("UTF-8")){
				nEnc = CStringEncode::UTF8;
			}else if(strEnc.CompareNoCase("EUC-JP")){
				nEnc = CStringEncode::EUC;
			}else if(strEnc.CompareNoCase("JIS")){
				nEnc = CStringEncode::JIS;
			}else if(strEnc.CompareNoCase("Shift-JIS")){
				nEnc = CStringEncode::SJIS;
			}
		}
	}


	switch(nEnc){
	case CStringEncode::UTF8:
		pszContents = CStringEncode::utf82sjis((LPSTR)(LPCTSTR)strBuff);
		strEncProc = "UTF82SJIS";
		break;

	case CStringEncode::EUC:
		pszContents = CStringEncode::euc2sjis((LPSTR)(LPCTSTR)strBuff);
		strEncProc = "EUC2SJIS";
		break;

	case CStringEncode::JIS:
		pszContents = CStringEncode::jis2sjis((LPSTR)(LPCTSTR)strBuff);
		strEncProc = "JI2SJIS";
		break;

	case CStringEncode::SJIS:
		m_strContents = strBuff;
		return TRUE;

	default:
		m_strContents = "";
		return TRUE;
		
	}

	if(!pszContents){
		m_strContents = "";
		return FALSE;
	}

	m_strContents = pszContents;
	if(pszContents){
		CStringEncode::ReleaseBuff(pszContents);
		//delete pszContents;
		pszContents = NULL;
	}
	
	return TRUE;
}

BOOL CRssCtrl::ConvertHTML(LPCTSTR szRSS, CString &strOutHtml){
	
	HRESULT hCoRes = ::CoInitialize( NULL );
	CString strMsg;
	if(hCoRes == S_OK){
	}else if(hCoRes == S_FALSE){
	}else{
	}
	HRESULT hRes = NULL;
	try{
		IXMLDOMParseErrorPtr error;
		CString strErr;

		hRes = m_pXMLDoc.CreateInstance( __uuidof(DOMDocument) ) ;
		if ( FAILED(hRes) ){
			throw(0);
		}
		if(m_pXMLDoc == NULL){
			throw(0);
		}

		hRes = m_pXMLDoc->put_async( VARIANT_FALSE ) ;
		if ( FAILED(hRes) ){
			throw(0);
		}

		BSTR bStr = m_strContents.AllocSysString();
		VARIANT_BOOL vBool;
		hRes = m_pXMLDoc->loadXML(bStr, &vBool);
		if ( FAILED(hRes) ){
			m_pXMLDoc->get_parseError(&error);
			GetIXMLErrMsg(error, strErr);
			::SysFreeString(bStr);
			throw(0);
		}
		::SysFreeString(bStr);

		IXMLDOMDocumentTypePtr pDocType;
		m_pXMLDoc->get_doctype(&pDocType);

		//解析開始
		m_strRSSContents = "";
		m_strTopics		 = "";
		IXMLDOMElementPtr pElemRoot;
		m_pXMLDoc->get_documentElement(&pElemRoot);
		if(NULL == pElemRoot){
			m_pXMLDoc->get_parseError(&error);
			GetIXMLErrMsg(error, strErr);
			throw(0);
		}

		//0.91 RSS
		//0.92 RSS
		//1.0  RDF
		//2.0  RSS
		CComBSTR bstrText;
		CString nodeStr;
		pElemRoot->get_baseName(&bstrText);
		GetXMLText(bstrText, nodeStr);
		if(nodeStr.Compare("rss") == 0){
			if(!RSSAnalyzer(pElemRoot)){
				throw(0);
			}
		
		}else if(nodeStr.Compare("RDF") == 0){
			//実質RSS Version 1.0の解析
			if(!RDFAnalyzer(pElemRoot)){
				throw(0);
			}
		
		}else{
			//解析結果ファイルではないと判断
			throw(0);
		}
		strOutHtml = m_strRSSContents;
	}catch(int nErr){
		m_pXMLDoc.Release();
		m_pXMLDoc = NULL;
		::CoUninitialize() ;
		return FALSE;
	}catch(CException& e){
		char szError[1024];
		e.GetErrorMessage(szError, 1024);
		m_strRSSContents = "<b><i>RSS 解析エラー</i></b>";
		m_pXMLDoc.Release();
		m_pXMLDoc = NULL;
		::CoUninitialize() ;
		return FALSE;
	}
	m_pXMLDoc.Release();
	m_pXMLDoc = NULL;
	::CoUninitialize() ;
	return TRUE;
}

BOOL CRssCtrl::RDFAnalyzer(IXMLDOMElementPtr pRoot){
	::PumpMessage(WM_TIMER, WM_TIMER);
	::PumpMessage(WM_PAINT, WM_PAINT);
	IXMLDOMNodeListPtr pChildList;
	HRESULT hRes = pRoot->get_childNodes(&pChildList);
	if ( FAILED(hRes) ){
		return FALSE;
	}

	LONG lLen;
	pChildList->get_length(&lLen);
	IXMLDOMNodePtr pItem;
	BSTR bstrName;
	CString strName;

	for(LONG i = 0; i < lLen; i++){
		pChildList->get_item(i, &pItem);
		pItem->get_baseName(&bstrName);
		GetXMLText((CComBSTR)bstrName, strName);
		if(strName.Compare("channel") == 0){
			RDFChildAnalyze(pItem, TRUE);
		}else if(strName.Compare("item") == 0){
			RDFChildAnalyze(pItem, FALSE);
		}
		::SysFreeString(bstrName);
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);
	}
	return TRUE;
}

BOOL CRssCtrl::RDFChildAnalyze(IXMLDOMNodePtr pNode, BOOL bCannel){
	TRY{
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);
		IXMLDOMNodeListPtr pChildList;
		LONG lLen;
		BSTR bstrName;
		CString strName;
		IXMLDOMNodePtr pChild;
		CString strTitle;
		CString strLink;
		CString strDc;
		CString strDescription;
		CString strAttrName;
		CString strPublisher;
		CString strCreator;

		HRESULT hRes = pNode->get_childNodes(&pChildList);
		if ( FAILED(hRes) ){
			return FALSE;
		}
		pNode->get_childNodes(&pChildList);	
		pChildList->get_length(&lLen);
		BSTR bstrValue;
		for(int j = 0; j < lLen; j++){
			//title,link,dcを取得し、リンクを作成する
			pChildList->get_item(j, &pChild);
			pChild->get_text(&bstrValue);
			pChild->get_baseName(&bstrName);

			GetXMLText((CComBSTR)bstrName, strName);
			
			if(strName.Compare("title") == 0){
				GetXMLText((CComBSTR)bstrValue, strTitle);
			}
			if(strName.Compare("link") == 0){
				GetXMLText((CComBSTR)bstrValue, strLink);
			}
			if(strName.Compare("date") == 0){
				GetXMLText((CComBSTR)bstrValue, strDc);
			}
			if(strName.Compare("description") == 0){
				GetXMLText((CComBSTR)bstrValue, strDescription);
			}
			if(strName.Compare("dc:description") == 0){
				GetXMLText((CComBSTR)bstrValue, strDescription);
			}
			if(strName.Compare("publisher") == 0){
				GetXMLText((CComBSTR)bstrValue, strPublisher);
			}
			if(strName.Compare("creator") == 0){
				GetXMLText((CComBSTR)bstrValue, strCreator);
			}
			
			::SysFreeString(bstrName);
			::SysFreeString(bstrValue);
			::PumpMessage(WM_TIMER, WM_TIMER);
			::PumpMessage(WM_PAINT, WM_PAINT);
		}

		if(bCannel){
			CString strLine;
			CString strTitleDate = strTitle;
			CString strDate = "";
			m_strTitle = strTitle;
			m_strLink = strLink;
		}else{
			//実際の見出し
			CString strTitleDate = strTitle;
			if(!strDc.IsEmpty()){
				GetRSSDate(strDc, strDc, TRUE);
				CString strDateTitle;
				strDateTitle.Format("%s : %s", strDc, strTitle);
				strTitleDate = strDateTitle;
			}
/*
			CDevString strData = strDescription;
			int nLen = strData.GetTextLength();
			if(nLen > 40){
				CDevString strCutStr = strData.LeftText(40);
				strDescription = strCutStr.GetBuffer();
				strDescription += "...";
				strCutStr.ReleaseBuffer();
			}
*/			
			CString strLine;
//			CString strTarget = m_bWikiPlugin ? "target=\"_blank\"" : "" ;
			CString strTarget = "target=\"_target\"";
			strLine.Format("<tr><td colspan=\"2\" class=\"rss_head\">"
						   "<a name=\"%s\">"
						   "<a href=\"%s\" title=\"%s\" class=\"rss_normal\" %s>%s</a>"
						   "</td></tr>\r\n"
						   "<tr><td class=\"rss_normal\"><nobr>更新</nobr></td><td width=\"100%%\" class=\"rss_normal\">%s</td></tr>"
						   "<tr><td colspan=\"2\" class=\"rss_normal\">%s</td></tr>\r\n"
						   ,strTitle
						   ,strLink ,strTitle ,strTarget ,strTitle
						   ,strDc.IsEmpty()		? "---" : strDc 
						   ,strDescription);
			m_strRSSContents += strLine;

			CString strTopics;
			strTopics.Format(" ■%s - %s ", 
							strDc.IsEmpty()	? "---" : strDc,
							strTitle);
			strTopics.Replace("&", "&amp;");
			strTopics.Replace(" ", "&nbsp;");
			strTopics.Replace("<", "&lt;");
			strTopics.Replace(">", "&gt;");
			m_strTopics += strTopics;
		}
	}CATCH_ALL(e){
		char szError[1024];
		e->GetErrorMessage(szError, 1024);
		m_strRSSContents = "<b><i>RSS 解析エラー</i></b>";
		return FALSE;
	}END_CATCH_ALL
	return TRUE;
}

BOOL CRssCtrl::RSSAnalyzer(IXMLDOMElementPtr pRoot){
	IXMLDOMNamedNodeMapPtr pAttr;
	IXMLDOMNodePtr pAttrNode;
	BSTR bstrValue;
	BSTR bstrName;
	CString strVersion = "";
	CString strName = "";
	LONG lLen;

	pRoot->get_attributes(&pAttr);
	pAttr->get_length(&lLen);

	for(int j = 0; j < lLen; j++){
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);
		//title,link,dcを取得し、リンクを作成する
		pAttr->get_item(j, &pAttrNode);
		pAttrNode->get_text(&bstrValue);
		pAttrNode->get_baseName(&bstrName);

		GetXMLText((CComBSTR)bstrName, strName);
		
		if(strName.Compare("version") == 0){
			GetXMLText((CComBSTR)bstrValue, strVersion);
		}
		::SysFreeString(bstrName);
		::SysFreeString(bstrValue);
	}
	
	IXMLDOMNodeListPtr pChildList;
	HRESULT hRes = pRoot->get_childNodes(&pChildList);
	if ( FAILED(hRes) ){

		return FALSE;
	}

	{
		IXMLDOMNodeListPtr pChildList;
		HRESULT hRes = pRoot->get_childNodes(&pChildList);
		if ( FAILED(hRes) ){

			return FALSE;
		}

		//子階層の解析
		LONG lLen;
		pChildList->get_length(&lLen);
		IXMLDOMNodePtr pItem;
		BSTR bstrName;
		CString strName;

		for(LONG i = 0; i < lLen; i++){
			pChildList->get_item(i, &pItem);
			pItem->get_baseName(&bstrName);
			GetXMLText((CComBSTR)bstrName, strName);
			if(strName.Compare("channel") == 0){
				if(!strVersion.CompareNoCase("0.91")){
					RSSChildV2Analyze(pItem, TRUE);
				}else if(!strVersion.CompareNoCase("2.0")){
					RSSChildV2Analyze(pItem, TRUE);
				}
			}
			::SysFreeString(bstrName);
			::PumpMessage(WM_TIMER, WM_TIMER);
			::PumpMessage(WM_PAINT, WM_PAINT);
		}
	}

	return TRUE;

}

BOOL CRssCtrl::RSSChildV2Analyze(IXMLDOMNodePtr pNode, BOOL bCannel){
	TRY{
		IXMLDOMNodeListPtr pChildList;
		LONG lLen;
		BSTR bstrName;
		CString strName;
		IXMLDOMNodePtr pChild;
		CString strTitle		= "";
		CString strLink			= "";
		CString strDc			= "";
		CString strDescription	= "";
		CString strAttrName		= "";
		CString strPublisher	= "";
		CString strCreator		= "";
		CString strSubject		= "";

		HRESULT hRes = pNode->get_childNodes(&pChildList);
		if ( FAILED(hRes) ){
			return FALSE;
		}
		pNode->get_childNodes(&pChildList);	
		pChildList->get_length(&lLen);
		BSTR bstrValue;
		BOOL bFirst = TRUE;
		for(int j = 0; j < lLen; j++){
			::PumpMessage(WM_TIMER, WM_TIMER);
			::PumpMessage(WM_PAINT, WM_PAINT);
			//title,link,dcを取得し、リンクを作成する
			pChildList->get_item(j, &pChild);
			pChild->get_text(&bstrValue);
			pChild->get_baseName(&bstrName);

			GetXMLText((CComBSTR)bstrName, strName);
			
			if(bCannel){
				if(strName.CompareNoCase("title") == 0){
					GetXMLText((CComBSTR)bstrValue, strTitle);
				}
				if(strName.CompareNoCase("link") == 0){
					GetXMLText((CComBSTR)bstrValue, strLink);
				}
				if(strName.CompareNoCase("date") == 0){
					GetXMLText((CComBSTR)bstrValue, strDc);
				}
				if(strName.CompareNoCase("creator") == 0){
					GetXMLText((CComBSTR)bstrValue, strCreator);
				}
				if(strName.CompareNoCase("description") == 0){
					GetXMLText((CComBSTR)bstrValue, strDescription);
				}
				if(strName.CompareNoCase("item") == 0){
					if(bFirst){
						bFirst = FALSE;
						CString strLine;
						CString strTitleDate = strTitle;
						CString strDate = "";
						m_strTitle = strTitle;
						m_strLink = strLink;
					}
					//子階層
					if(!RSSChildV2Analyze(pChild, FALSE)){
						return FALSE;
					}
				}
			}else{
				if(strName.CompareNoCase("title") == 0){
					GetXMLText((CComBSTR)bstrValue, strTitle);
				}
				if(strName.CompareNoCase("link") == 0){
					GetXMLText((CComBSTR)bstrValue, strLink);
				}
				if(strName.CompareNoCase("date") == 0){
					GetXMLText((CComBSTR)bstrValue, strDc);
				}
				if(strName.CompareNoCase("description") == 0){
					GetXMLText((CComBSTR)bstrValue, strDescription);
				}
				if(strName.CompareNoCase("subject") == 0){
					GetXMLText((CComBSTR)bstrValue, strSubject);
				}
				if(strName.CompareNoCase("creator") == 0){
					GetXMLText((CComBSTR)bstrValue, strCreator);
				}
			}		
			::SysFreeString(bstrName);
			::SysFreeString(bstrValue);
		}

		//実際の見出し
		CString strTitleDate = strTitle;
		if(!strDc.IsEmpty()){
			GetRSSDate(strDc, strDc, TRUE);
			CString strDateTitle;
			strDateTitle.Format("%s : %s(%s)", strDc, strTitle, strSubject);
			strTitleDate = strDateTitle;
		}

		if(!strCreator.IsEmpty()){
			strTitleDate += "【作成:" + strCreator + "】";
		}
		CString strLine;
//		CString strTarget = m_bWikiPlugin ? "target=\"_blank\"" : "" ;
		CString strTarget = "target=\"_blank\"";

		strLine.Format("<tr><td colspan=\"2\" class=\"rss_head\">"
					   "<a name=\"%s\">"
					   "<a href=\"%s\" title=\"%s\" class=\"rss_normal\" %s>%s</a>"
					   "</td></tr>\r\n"
					   "<tr><td class=\"rss_normal\"><nobr>更新</nobr></td><td width=\"100%%\" class=\"rss_normal\">%s</td></tr>"
					   "<tr><td colspan=\"2\" class=\"rss_normal\">%s</td></tr>\r\n"
					   ,strTitle
					   ,strLink ,strTitle ,strTarget ,strTitle
					   ,strDc.IsEmpty()		? "---" : strDc 
					   ,strDescription);
		m_strRSSContents += strLine;

		CString strTopics;
		strTopics.Format(" ■%s - %s ", 
						strDc.IsEmpty()	? "---" : strDc,
						strTitle);
		strTopics.Replace("&", "&amp;");
		strTopics.Replace(" ", "&nbsp;");
		strTopics.Replace("<", "&lt;");
		strTopics.Replace(">", "&gt;");
		strTopics.Replace("&quot;", "\"");
		m_strTopics += strTopics;
	}CATCH_ALL(e){
		char szError[1024];
		e->GetErrorMessage(szError, 1024);
		m_strRSSContents = "<b><i>RSS 解析エラー</i></b>";
		return FALSE;
	}END_CATCH_ALL
	return TRUE;
}

void CRssCtrl::GetXMLText( CComBSTR &bstrText, CString &strText ){
	_variant_t varText;
	varText = bstrText;
	strText = varText.bstrVal;
}

void CRssCtrl::GetIXMLErrMsg( IXMLDOMParseErrorPtr error, CString &strMsg ){
	CComBSTR bUrlStr;
	CString errUrlStr;

	CComBSTR bReasonStr;
	CString errReasonStr;

	CComBSTR bSrcStr;
	CString errSrcStr;

	LONG errCode;
	CString strCode;

	LONG errLine;
	CString strLine;

	LONG errLinePos;
	CString strLinePos;

	LONG errFilePos;
	CString strFilePos;

	bUrlStr.Empty();
	bReasonStr.Empty();
	bSrcStr.Empty();

	error->get_errorCode(&errCode);				//エラーコード
	error->get_url(&bUrlStr);					//URL
	error->get_reason(&bReasonStr);				//エラー理由
	error->get_srcText(&bSrcStr);				//テキスト
	error->get_line(&errLine);					//発生行?
	error->get_linepos(&errLinePos);			//発生行の文字数(位置)
	error->get_filepos(&errFilePos);			//ファイルの位置

	GetXMLText(bUrlStr, errUrlStr);
	GetXMLText(bReasonStr, errReasonStr);
	GetXMLText(bSrcStr, errSrcStr);
	strCode.Format("%d", errCode);
	strLine.Format("%d", errLine);
	strLinePos.Format("%d", errLinePos);
	strFilePos.Format("%d", errFilePos);

	CString errStrLine;
	strMsg.Format(	"XML parse error\n"
					"URL           : %s\n"
					"Error Code    : %s\n"
					"Reason        : %s\n"
					"Line          : %s\n"
					"Line Position : %s\n"
					"File Position : %s\n"
					"Source        : %s\n",
					errUrlStr,
					strCode,
					errReasonStr,
					strLine,
					strLinePos,
					strFilePos,
					errSrcStr);
}

void CRssCtrl::GetRSSDate(LPCTSTR pszDate, CString &strDate, BOOL bShort){
	COleDateTime objTime;
	CString strDc = pszDate;
	int nPos = strDc.ReverseFind('+');

	CString strAdd;
	if(nPos != -1){
		strAdd = strDc.Right(strDc.GetLength() - nPos);
		strDc = strDc.Left(nPos);
	}

	strDc.Replace("T", " ");

	if(objTime.ParseDateTime(strDc)){
/*		
		nPos = strAdd.ReverseFind(':');
		CString strAddTime = "";
		if(nPos != -1){
			strAddTime = strAdd.Left(nPos);
			int nAddHour = atoi(strAddTime);
			strAddTime = strAdd.Right(strAdd.GetLength() - nPos -1 );
			int nAddMin  = atoi(strAddTime);
			COleDateTimeSpan span(0, nAddHour, nAddMin, 0);
			objTime += span;
		}
*/
		int nYear	= objTime.GetYear();
		int nMonth	= objTime.GetMonth();
		int nDay	= objTime.GetDay();
		int nHour	= objTime.GetHour();
		int nMin	= objTime.GetMinute();
		int nSec	= objTime.GetSecond();
		CString strMonth;
		CString strDay;
		CString strHour;
		CString strMin;
		CString strSec;
		if(nMonth < 10){
			strMonth.Format("0%d", nMonth);
		}else{
			strMonth.Format("%d", nMonth);
		}

		if(nDay < 10){
			strDay.Format("0%d", nDay);
		}else{
			strDay.Format("%d", nDay);
		}

		if(nHour < 10){
			strHour.Format("0%d", nHour);
		}else{
			strHour.Format("%d", nHour);
		}

		if(nMin < 10){
			strMin.Format("0%d", nMin);
		}else{
			strMin.Format("%d", nMin);
		}

		if(nSec < 10){
			strSec.Format("0%d", nSec);
		}else{
			strSec.Format("%d", nSec);
		}

		if(bShort){
			strDate.Format("%s/%s %s:%s", strMonth, strDay, strHour, strMin);
		}else{
			strDate.Format("%d/%s/%s %s:%s:%s", nYear, strMonth, strDay,
												strHour, strMin, strSec);
		}
	}else{
		strDate = strDc;
	}

}

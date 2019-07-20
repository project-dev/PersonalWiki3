// PWikiPluginException.h: CPWikiPluginException クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PWIKIPLUGINEXCEPTION_H__B472309C_2D76_432B_9074_B6DA2A46C5CA__INCLUDED_)
#define AFX_PWIKIPLUGINEXCEPTION_H__B472309C_2D76_432B_9074_B6DA2A46C5CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPWikiPluginException : public CException  {
public:
	CPWikiPluginException(LPCTSTR pszErrMsg, BOOL b_AutoDelete = TRUE);
	virtual ~CPWikiPluginException();
	virtual BOOL GetErrorMessage( LPTSTR lpszError, UINT nMaxError,	PUINT pnHelpContext = NULL );
	void GetErrorMessage( CString& strError );
private:
	CString m_strErrMsg;
};

#endif // !defined(AFX_PWIKIPLUGINEXCEPTION_H__B472309C_2D76_432B_9074_B6DA2A46C5CA__INCLUDED_)

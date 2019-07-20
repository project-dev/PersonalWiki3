// BregExpRap.h: CBregExpRap クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BREGEXPRAP_H__18B9FBB6_8EF4_4144_810A_7D8C857951D0__INCLUDED_)
#define AFX_BREGEXPRAP_H__18B9FBB6_8EF4_4144_810A_7D8C857951D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bregexp.h"
#include <afxtempl.h>

class CBregExpRap{
public:
	void RefreshPool();
	CBregExpRap();
	virtual ~CBregExpRap();

	BOOL GetFindStrList(CString &strTarget, CString &strText, CStringArray &arrText);
	void GetVersionString(CString &strVersion);
	BOOL GetFindText(CString &strTarget, CString &strRet, CString &strPattern);
	BOOL FindText(CString &strTarget, CString &strPattern);
	BOOL ReplaceText(CString &strTarget, CString &strReturn, CString &strPattern);

private:

	//bragexp構造体の再利用の為のマップ
	CMapStringToOb m_mapStruct;
	

protected:

};

#endif // !defined(AFX_BREGEXPRAP_H__18B9FBB6_8EF4_4144_810A_7D8C857951D0__INCLUDED_)

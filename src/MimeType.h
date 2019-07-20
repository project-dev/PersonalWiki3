// MimeType.h: CMimeType クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIMETYPE_H__CB976FB1_1820_4D3C_B035_F08FFAED6BB6__INCLUDED_)
#define AFX_MIMETYPE_H__CB976FB1_1820_4D3C_B035_F08FFAED6BB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
class CMimeType {
public:
	int GetDataSize();
	BOOL SaveMIME(LPCTSTR pszPath);
	BOOL LoadMIME(LPCTSTR pszPath);
	BOOL Del(LPCTSTR pszExt, LPCTSTR pszMime);
	BOOL Del(int nIndex);
	void DelAll();
	int Find(LPCTSTR pszExt, LPCTSTR pszMime);
	void Mod(LPCTSTR pszExt, LPCTSTR pszMime, BOOL bUse);
	void Add(LPCTSTR pszExt, LPCTSTR pszMime, BOOL bUse);

	LPCTSTR GetMimeType(int nIndex);
	LPCTSTR GetExt(int nIndex);
	int GetType(int nIndex);
	BOOL GetUse(int nIndex);
	
	CMimeType();
	virtual ~CMimeType();
	static BOOL Copy(CMimeType* pFrom, CMimeType* pTo);

private:
	CArray<BOOL, BOOL>	m_arrUse;
	CArray<int, int>	m_arrType;
	CStringArray		m_arrMimeType;
	CStringArray		m_arrExt;
};

#endif // !defined(AFX_MIMETYPE_H__CB976FB1_1820_4D3C_B035_F08FFAED6BB6__INCLUDED_)

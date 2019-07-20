// AbstractBaseWnd.h: CAbstractBaseWnd クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSTRACTBASEWND_H__14AD951C_0E71_4E85_BC4B_85210A8657EB__INCLUDED_)
#define AFX_ABSTRACTBASEWND_H__14AD951C_0E71_4E85_BC4B_85210A8657EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "AbstractWnd.h"

class CMainFrame;
class CDocument;

class CAbstractBaseWnd : public CAbstractWnd {
public:
	void UpdateAllWnd();
	CAbstractBaseWnd();
	virtual ~CAbstractBaseWnd();

	static CMainFrame* GetMainFrame(CWnd *pMyWnd);

	virtual void UpdateSetting();

protected:
	CDocument* GetDoc();
	void MakeFont(CFont& objFont, CDC* pDC, LPCTSTR pszFontFace, int nHeight);

};

#endif // !defined(AFX_ABSTRACTBASEWND_H__14AD951C_0E71_4E85_BC4B_85210A8657EB__INCLUDED_)

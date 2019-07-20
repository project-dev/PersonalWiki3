// BinderDropTarget.h: CBinderDropTarget クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BINDERDROPTARGET_H__620FDDD4_DC30_4310_8E13_FA9417D91D48__INCLUDED_)
#define AFX_BINDERDROPTARGET_H__620FDDD4_DC30_4310_8E13_FA9417D91D48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if !defined(CF_HTML)
#define CF_HTML		::RegisterClipboardFormat("HTML Format")
#endif

#if !defined(CF_RTF)
#define UINT CF_RTF	::RegisterClipboardFormat("CF_RTF")
#endif

class CBinderWnd;

class CBinderDropTarget : public COleDropTarget{
public:
	CBinderDropTarget();
	void SetBinderWnd(CBinderWnd* pWnd);
	virtual ~CBinderDropTarget();
	virtual DROPEFFECT OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point );
//	virtual void OnDragLeave( CWnd* pWnd );
	virtual DROPEFFECT OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point );
//	virtual DROPEFFECT OnDragScroll( CWnd* pWnd, DWORD dwKeyState, CPoint point );

	virtual BOOL OnDrop( CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point );
/*
	virtual DROPEFFECT OnDropEx( CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point );
*/
private:
	CBinderWnd* m_pBinderWnd;
};

#endif // !defined(AFX_BINDERDROPTARGET_H__620FDDD4_DC30_4310_8E13_FA9417D91D48__INCLUDED_)

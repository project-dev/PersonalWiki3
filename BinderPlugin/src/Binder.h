// Binder.h: CBinder クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BINDER_H__77DA20AC_0DF7_4893_99B7_0A312DEC8FD8__INCLUDED_)
#define AFX_BINDER_H__77DA20AC_0DF7_4893_99B7_0A312DEC8FD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

#define FB_UPDATELIST	0x0001
#define FB_UPDATEINFO	0x0002

//BinderItemの開始
typedef enum eICONS{
	IC_ROOT	= 0,		//ルートアイテム
	IC_BINDER = 1,		//バインダー
	IC_NG,				//ファイル無し
	IC_CLIP,			//クリップボードの子
	IC_END


};

//バインダーに登録するアイテムの情報
typedef struct tagBINDERITEM{
	char	pszFilePath[MAX_PATH];		//登録するファイルのフルパス
	char	pszName[100];				//登録名
	BOOL	bRelayApp;					//TRUE : 関連付けられたアプリケーションで開く
	char	pszRelayAppPath[MAX_PATH];	//bRelayApp = FALSEの場合に利用するアプリケーション
	char	pszRelayAppOpt[1024];		//pszRelayAppPathを利用する際の引数
}BINDERITEM, *PBINDERITEM;

#define		MAX_DATALEN					100

#if !defined(CF_HTML)
#define CF_HTML		::RegisterClipboardFormat("HTML Format")
#endif

#if !defined(CF_RTF)
#define UINT CF_RTF	::RegisterClipboardFormat("CF_RTF")
#endif

class CBinder{
public:
	int GetSize();
	void DeleteBinder(LPCTSTR pszRootPath);
	HICON GetIcon(PBINDERITEM pItem);
	CString m_strName;
	BOOL SaveBinderData(LPCTSTR pszRoot);
	PBINDERITEM GetBinderItem(int nIndex);
	BOOL DeleteBinderItem(int nIndex);
	BOOL DeleteBinderItem(PBINDERITEM pItem);
	BOOL SetBinderItem(int nIndex, PBINDERITEM pItem);
	int AddBinderItem(PBINDERITEM pItem);
	CBinder();
	virtual ~CBinder();

private:
	void DeleteItem(PBINDERITEM pItem);
	CList< PBINDERITEM, PBINDERITEM > m_arrBinderItem;
};

#endif // !defined(AFX_BINDER_H__77DA20AC_0DF7_4893_99B7_0A312DEC8FD8__INCLUDED_)

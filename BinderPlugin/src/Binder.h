// Binder.h: CBinder �N���X�̃C���^�[�t�F�C�X
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

//BinderItem�̊J�n
typedef enum eICONS{
	IC_ROOT	= 0,		//���[�g�A�C�e��
	IC_BINDER = 1,		//�o�C���_�[
	IC_NG,				//�t�@�C������
	IC_CLIP,			//�N���b�v�{�[�h�̎q
	IC_END


};

//�o�C���_�[�ɓo�^����A�C�e���̏��
typedef struct tagBINDERITEM{
	char	pszFilePath[MAX_PATH];		//�o�^����t�@�C���̃t���p�X
	char	pszName[100];				//�o�^��
	BOOL	bRelayApp;					//TRUE : �֘A�t����ꂽ�A�v���P�[�V�����ŊJ��
	char	pszRelayAppPath[MAX_PATH];	//bRelayApp = FALSE�̏ꍇ�ɗ��p����A�v���P�[�V����
	char	pszRelayAppOpt[1024];		//pszRelayAppPath�𗘗p����ۂ̈���
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

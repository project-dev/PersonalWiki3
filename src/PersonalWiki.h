// PersonalWiki.h : PERSONALWIKI �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//

#if !defined(AFX_PERSONALWIKI_H__A9018661_040C_45C3_9493_1A732D5FEB76__INCLUDED_)
#define AFX_PERSONALWIKI_H__A9018661_040C_45C3_9493_1A732D5FEB76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // ���C�� �V���{��

//USB���g��
#define USE_USB_DOC
#if defined(USE_USB_DOC
typedef struct tagUSB_STATE{
	char szDrv;		//�h���C�u
	BOOL bAlive;	//�����Ă��邩
	char szPath[4][MAX_PATH + 1];
}USB_STATE, *PUSB_STATE;
#endif

//#define USE_CREATE_VIEW

/////////////////////////////////////////////////////////////////////////////
// CPWikiApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� PersonalWiki.cpp �t�@�C�����Q�Ƃ��Ă��������B
//
class CPWikiApp : public CWinApp
{
public:
	CPWikiApp();
	BOOL ProcessShellCommand( CCommandLineInfo& rCmdInfo );

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CPWikiApp)
	public:
	virtual BOOL InitInstance();
	virtual int Run();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
	//{{AFX_MSG(CPWikiApp)
	afx_msg void OnAppAbout();
	afx_msg void OnDevModeChange(LPTSTR lpDeviceName);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PERSONALWIKI_H__A9018661_040C_45C3_9493_1A732D5FEB76__INCLUDED_)

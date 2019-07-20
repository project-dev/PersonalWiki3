// BinderPlugin.h : BINDERPLUGIN �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_BINDERPLUGIN_H__0C507A85_B6F3_43E2_8FA6_7BDCF3024DE5__INCLUDED_)
#define AFX_BINDERPLUGIN_H__0C507A85_B6F3_43E2_8FA6_7BDCF3024DE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

#include "PWikiPluginSDK.h"

#define PLUGIN_EXT_CLASS		 __declspec(dllexport)

//�v���O�C���֐�
//�K�{�֐�
PLUGIN_EXT_CLASS BOOL WINAPI GetPluginInfo(PPWIKIPLUGIN pInfo);
PLUGIN_EXT_CLASS BOOL WINAPI ShowSetupDlg();
PLUGIN_EXT_CLASS BOOL WINAPI GetUse();
PLUGIN_EXT_CLASS void WINAPI SetUse(BOOL bUse);
PLUGIN_EXT_CLASS BOOL WINAPI ExitPlugin();

//�^�u�p�֐�
PLUGIN_EXT_CLASS HWND WINAPI GetTabWnd(HWND hParent);

//�f�o�b�O�p
PLUGIN_EXT_CLASS void WINAPI SetLogFlag(BOOL bLogState, BOOL bAppLogState, BOOL bExceptLogState, BOOL bFatalLogState);

/////////////////////////////////////////////////////////////////////////////
// CBinderPluginApp
// ���̃N���X�̓���̒�`�Ɋւ��Ă� BinderPlugin.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CBinderPluginApp : public CWinApp
{
public:
	CBinderPluginApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CBinderPluginApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CBinderPluginApp)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_BINDERPLUGIN_H__0C507A85_B6F3_43E2_8FA6_7BDCF3024DE5__INCLUDED_)

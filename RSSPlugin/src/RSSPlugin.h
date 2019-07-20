// RSSPlugin.h : RSSPLUGIN �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_RSSPLUGIN_H__3CC0C0FB_6CCD_471A_B10F_D9824FEDC3C1__INCLUDED_)
#define AFX_RSSPLUGIN_H__3CC0C0FB_6CCD_471A_B10F_D9824FEDC3C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��
#include "PWikiPluginSDK.h"
#include "RSSPluginCommon.h"

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


/////////////////////////////////////////////////////////////////////////////
// CRSSPluginApp
// ���̃N���X�̓���̒�`�Ɋւ��Ă� RSSPlugin.cpp �t�@�C�����Q�Ƃ��Ă��������B
//


class CRSSPluginApp : public CWinApp{
public:
	CRSSPluginApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CRSSPluginApp)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CRSSPluginApp)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B



#endif // !defined(AFX_RSSPLUGIN_H__3CC0C0FB_6CCD_471A_B10F_D9824FEDC3C1__INCLUDED_)

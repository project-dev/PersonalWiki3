// WordExportPlugin.h : WORDEXPORTPLUGIN �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_WORDEXPORTPLUGIN_H__93B772FF_2200_422C_9CA3_028491B3A814__INCLUDED_)
#define AFX_WORDEXPORTPLUGIN_H__93B772FF_2200_422C_9CA3_028491B3A814__INCLUDED_

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

//�G�N�X�|�[�g�p
PLUGIN_EXT_CLASS eExportDataType WINAPI ReqDataType();
PLUGIN_EXT_CLASS BOOL WINAPI Export(char* pszWikiBuff);


/////////////////////////////////////////////////////////////////////////////
// CWordExportPluginApp
// ���̃N���X�̓���̒�`�Ɋւ��Ă� WordExportPlugin.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CWordExportPluginApp : public CWinApp
{
public:
	CWordExportPluginApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CWordExportPluginApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CWordExportPluginApp)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_WORDEXPORTPLUGIN_H__93B772FF_2200_422C_9CA3_028491B3A814__INCLUDED_)

// ExceptTest.h : EXCEPTTEST �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//

#if !defined(AFX_EXCEPTTEST_H__0A0DDBA4_3BBB_4012_9BAD_0845D94FE85B__INCLUDED_)
#define AFX_EXCEPTTEST_H__0A0DDBA4_3BBB_4012_9BAD_0845D94FE85B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CExceptTestApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� ExceptTest.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CExceptTestApp : public CWinApp
{
public:
	CExceptTestApp();
	static int Except(LPEXCEPTION_POINTERS pExp);
	BOOL ProcessShellCommand( CCommandLineInfo& rCmdInfo );


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CExceptTestApp)
	public:
	virtual BOOL InitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
	//{{AFX_MSG(CExceptTestApp)
	afx_msg void OnAppAbout();
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_EXCEPTTEST_H__0A0DDBA4_3BBB_4012_9BAD_0845D94FE85B__INCLUDED_)

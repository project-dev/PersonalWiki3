// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���A
//            �܂��͎Q�Ɖ񐔂������A�����܂�ύX����Ȃ�
//            �v���W�F�N�g��p�̃C���N���[�h �t�@�C�����L�q���܂��B
//

#if !defined(AFX_STDAFX_H__52105AE9_35B7_453A_BA6E_4E9AC128B19C__INCLUDED_)
#define AFX_STDAFX_H__52105AE9_35B7_453A_BA6E_4E9AC128B19C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Windows �w�b�_�[����w�ǎg�p����Ȃ��X�^�b�t�����O���܂��B

#include <afxwin.h>         // MFC �̃R�A����ѕW���R���|�[�l���g
#include <afxext.h>         // MFC �̊g������

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC �� OLE �N���X
#include <afxodlgs.h>       // MFC �� OLE �_�C�A���O �N���X
#include <afxdisp.h>        // MFC �̃I�[�g���[�V���� �N���X
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC �f�[�^�x�[�X �N���X
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO �f�[�^�x�[�X �N���X
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC �� Internet Explorer 4 �R���� �R���g���[�� �T�|�[�g
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC �� Windows �R���� �R���g���[�� �T�|�[�g
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

//#define USE_OFFICE9
//#define USE_OFFICE10
//#define USE_OFFICE11
#define USE_OFFICE15

// MSO.DLL�̃C���|�[�g
#if defined(USE_OFFICE9)
	#import "C:\Program Files\Microsoft Office\Office\MSO9.DLL"
#elif defined(USE_OFFICE10)
	#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE10\MSO.DLL"
#elif defined(USE_OFFICE11)
	#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE11\MSO.DLL"
	#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB"
#elif defined(USE_OFFICE15)
	#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE15\MSO.DLL"
	#import "C:\Program Files (x86)\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB"
#endif

//MS WORD
#if defined(USE_OFFICE9)
	#import "C:\Program Files\Microsoft Office\Office\Mso9.dll"\
	no_namespace rename("DocumentProperties", "DocumentPropertiesACC")
	#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\Vbe6ext.olb" no_namespace
	#import "C:\Program Files\Microsoft Office\Office\MSWORD9.OLB"\
	rename("ExitWindows", "ExitWindowsForWord")
#elif defined(USE_OFFICE10)

#elif defined(USE_OFFICE11)
	#import "C:\Program Files\Microsoft Office\OFFICE11\MSWORD.OLB"\
	rename("ExitWindows", "ExitWindowsForWord")
#elif defined(USE_OFFICE15)
	#import "C:\Program Files\Microsoft Office\OFFICE15\MSWORD.OLB"\
	rename("ExitWindows", "ExitWindowsForWord")
#endif

/*
//MS EXCEL
#if defined(USE_OFFICE9)
	#import "C:\Program Files\Microsoft Office\Office\EXCEL9.OLB" \
	rename("DialogBox", "DialogBoxForExcel") rename( "RGB", "RGBForExcel")
#elif defined(USE_OFFICE10)
#elif defined(USE_OFFICE11)
	#import "C:\Program Files\Microsoft Office\OFFICE11\XL5JP32.OLB"\
	rename("DialogBox", "DialogBoxForExcel") rename( "RGB", "RGBForExcel")
#endif
*/
#endif // !defined(AFX_STDAFX_H__52105AE9_35B7_453A_BA6E_4E9AC128B19C__INCLUDED_)

#if !defined(AFX_FIXHTMLVIEW_H__36306C70_FFD5_4E10_B5B3_0ECA329904F9__INCLUDED_)
#define AFX_FIXHTMLVIEW_H__36306C70_FFD5_4E10_B5B3_0ECA329904F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FixHtmlView.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CFixHtmlView HTML �r���[

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

class CFixHtmlView : public CHtmlView
{
protected:
	CFixHtmlView();           // ���I�����Ŏg�p����� protected �R���X�g���N�^
	DECLARE_DYNCREATE(CFixHtmlView)

// html Data
public:
	//{{AFX_DATA(CFixHtmlView)
		// ����: ���̈ʒu�� ClassWizard �ɂ���ăf�[�^ �����o���ǉ�����܂��B
	//}}AFX_DATA

	//CHtmlView�̃o�O�Ή� http://support.microsoft.com/kb/241750/ja
    CString GetFullName() const;
    CString GetType() const;
    CString GetLocationName() const;
    CString GetLocationURL() const;

    void Navigate(LPCTSTR lpszURL, DWORD dwFlags = 0 ,  
                  LPCTSTR lpszTargetFrameName = NULL ,  
                  LPCTSTR lpszHeaders = NULL, LPVOID lpvPostData = NULL,  
                  DWORD dwPostDataLen = 0);
    BOOL LoadFromResource(LPCTSTR lpszResource);
    BOOL LoadFromResource(UINT nRes);

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂�
	//{{AFX_VIRTUAL(CFixHtmlView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~CFixHtmlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CFixHtmlView)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_FIXHTMLVIEW_H__36306C70_FFD5_4E10_B5B3_0ECA329904F9__INCLUDED_)

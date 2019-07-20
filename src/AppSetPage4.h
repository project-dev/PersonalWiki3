#if !defined(AFX_APPSETPAGE4_H__1DC27DBD_C34C_4615_989C_43CEB06EA200__INCLUDED_)
#define AFX_APPSETPAGE4_H__1DC27DBD_C34C_4615_989C_43CEB06EA200__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppSetPage4.h : �w�b�_�[ �t�@�C��
//
#include "AbstractBaseWnd.h"

////////////////////////////////////////////////////////////////////////////
// CAppSetPage4 �_�C�A���O
#include "PWikiIniFile.h"
#include <AfxTempl.h>

typedef struct tagFONT_DTL_INFO{
	DWORD nType;						//
	LOGFONT lFont;						//
	TEXTMETRIC objTextMatrix;			//
	NEWTEXTMETRICEX ojbNewTextMatrix;	//
}FONT_DTL_INFO, *PFONT_DTL_INFO;

class CAppSetPage4 : public CDialog, CAbstractBaseWnd{
// �R���X�g���N�V����
public:
	BOOL UpdateInfo();
	CAppSetPage4(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	static int CALLBACK EnumFontFamExProc( const LOGFONT *lpelfe, const TEXTMETRIC *lpntme, DWORD FontType, LPARAM lParam );
// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAppSetPage4)
	enum { IDD = IDD_DLG_APP_SETPAGE4 };
	CListCtrl	m_objSceneList;
	CListCtrl	m_objSizeList;
	CListCtrl	m_objNameList;
	CEdit	m_objSample;
	CString	m_strSample;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAppSetPage4)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAppSetPage4)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnItemchangedFontSizeList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedFontNameList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedSetList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CArray<PFONT_DTL_INFO, PFONT_DTL_INFO> m_arrFontInfo;

	CFont *m_pOldSmpFont;
	CFont m_objSmpFont;
	LOGFONT m_objSmpLFont;

	FONTINFO m_objFontInfo;
private:
	int SelectFontName(LPCTSTR pszFontName);
	int SelectFontSize(int nSize);
	void UpdateFontInfo(int nFontIndex = -1, int nSizeIndex = -1);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_APPSETPAGE4_H__1DC27DBD_C34C_4615_989C_43CEB06EA200__INCLUDED_)

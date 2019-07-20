// PWikiDoc.h : CPWikiDoc �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PWIKIDOC_H__407042E7_81C9_4D26_9416_17EFF4B1673F__INCLUDED_)
#define AFX_PWIKIDOC_H__407042E7_81C9_4D26_9416_17EFF4B1673F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TodoData.h"
#include "ScDateData.h"
#include "AbstractBaseWnd.h"
#include "FixedData.h"

class CPWikiDoc : public CDocument, CAbstractBaseWnd{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CPWikiDoc();
	DECLARE_DYNCREATE(CPWikiDoc)

// �A�g���r���[�g
public:
	CTodoData m_objToDoData;
	CScDateData m_objScDateData;
	CFixedData m_objFixedData;

// �I�y���[�V����
public:

//�I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CPWikiDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	BOOL CreateWikiDir(LPCTSTR pszWikiPage, LPCTSTR pszBasePath, CString &strWikiPage, CString &strWikiDir, CString &strWikiAttDir);
	int GetDayOfWeekNum(int nDay);
	int GetWeek(int nYear, int nMonth, int nDay);
	CEventDate* FindDate(int nYear, int nMonth, int nDay);
	void FindFixedDate(int nYear, int nMonth, int nDay, CString &strDetail, BOOL& bHoliday);
	void FindToDoDate(int nYear, int nMonth, int nDay, CString &strDetail, BOOL bGetDetail = FALSE);
	void FindSpecialDay(int nYear, int nMonth, int nDay, CString &strDetail);
	virtual ~CPWikiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CStringArray m_arrCategory;

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CPWikiDoc)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PWIKIDOC_H__407042E7_81C9_4D26_9416_17EFF4B1673F__INCLUDED_)

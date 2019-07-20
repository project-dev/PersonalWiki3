#if !defined(AFX_RSSLIST_H__F7A9B9D9_C996_4774_8D5E_BC702867E478__INCLUDED_)
#define AFX_RSSLIST_H__F7A9B9D9_C996_4774_8D5E_BC702867E478__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSSList.h : �w�b�_�[ �t�@�C��
//

#include "AbstractWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CRSSList �E�B���h�E
class CRssWnd;

class CRSSList : public CListCtrl, CAbstractWnd{
// �R���X�g���N�V����
public:
	CRSSList();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CRSSList)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CRSSList();
	CRssWnd* m_pRssWnd;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CRSSList)
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReadrss();
	afx_msg void OnUpdateReadrss(CCmdUI* pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_RSSLIST_H__F7A9B9D9_C996_4774_8D5E_BC702867E478__INCLUDED_)

#if !defined(AFX_SEPBTN_H__AC4CB803_6FFA_4284_85D9_0CC12D02E6A6__INCLUDED_)
#define AFX_SEPBTN_H__AC4CB803_6FFA_4284_85D9_0CC12D02E6A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SepBtn.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CSepBtn �E�B���h�E

class CSepBtn : public CButton
{
// �R���X�g���N�V����
public:
	CSepBtn();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSepBtn)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	void SetSepalatorUD(CWnd *pUp, CWnd *pDown);
	virtual ~CSepBtn();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CSepBtn)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	CWnd* m_pUpWnd;
	CWnd* m_pDwWnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SEPBTN_H__AC4CB803_6FFA_4284_85D9_0CC12D02E6A6__INCLUDED_)

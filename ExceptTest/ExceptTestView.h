// ExceptTestView.h : CExceptTestView �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCEPTTESTVIEW_H__380A063C_5B42_4A91_856A_3914811FD00A__INCLUDED_)
#define AFX_EXCEPTTESTVIEW_H__380A063C_5B42_4A91_856A_3914811FD00A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExceptTestView : public CView
{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CExceptTestView();
	DECLARE_DYNCREATE(CExceptTestView)

// �A�g���r���[�g
public:
	CExceptTestDoc* GetDocument();

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CExceptTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷��ۂɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CExceptTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CExceptTestView)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ExceptTestView.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline CExceptTestDoc* CExceptTestView::GetDocument()
   { return (CExceptTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_EXCEPTTESTVIEW_H__380A063C_5B42_4A91_856A_3914811FD00A__INCLUDED_)

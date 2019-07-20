// SepBtn.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "rssplugin.h"
#include "SepBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSepBtn

CSepBtn::CSepBtn()
{
	m_pUpWnd = NULL;
	m_pDwWnd = NULL;
}

CSepBtn::~CSepBtn()
{
}


BEGIN_MESSAGE_MAP(CSepBtn, CButton)
	//{{AFX_MSG_MAP(CSepBtn)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSepBtn ���b�Z�[�W �n���h��

void CSepBtn::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	if(nFlags & MK_LBUTTON){
		//�Z�p���[�^�ړ�
		CWnd *pParent = GetParent();
		CRect rect;
		CRect pRect;
		GetClientRect(rect);
		pParent->GetClientRect(pRect);
		CPoint pos = point;
		MapWindowPoints(pParent, rect);
		MapWindowPoints(pParent, &pos, 1);
		int nHeight = rect.Height();
		rect.top = pos.y;
		rect.bottom = pos.y + nHeight;
		SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
		m_pUpWnd->SetWindowPos(&wndTop, 
								rect.left,		pRect.top, 
								rect.Width(),	rect.top - pRect.top, SWP_SHOWWINDOW);
		m_pDwWnd->SetWindowPos(&wndTop, 
								rect.left,		rect.bottom,
								rect.Width(),	pRect.Height() - rect.Height() - rect.top - pRect.top, SWP_SHOWWINDOW);
		m_pUpWnd->InvalidateRect(NULL);
		m_pDwWnd->InvalidateRect(NULL);
	}
	CButton::OnMouseMove(nFlags, point);
}

void CSepBtn::SetSepalatorUD(CWnd *pUp, CWnd *pDown){
	m_pUpWnd = pUp;
	m_pDwWnd = pDown;
}

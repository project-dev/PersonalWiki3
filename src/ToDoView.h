#if !defined(AFX_TODOVIEW_H__03173B17_BB44_45AD_9189_1671C53D9E4D__INCLUDED_)
#define AFX_TODOVIEW_H__03173B17_BB44_45AD_9189_1671C53D9E4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToDoView.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CToDoView �r���[
#include "AbstractBaseWnd.h"
#include "ChartWnd.h"

class CToDoView : public CView, CAbstractBaseWnd{
protected:
	CToDoView();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
	void SetCtrlPos();
	DECLARE_DYNCREATE(CToDoView)
	static int CALLBACK SortItemFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK SortCategoryFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK SortStateFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK SortProcessFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK SortStPlanFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK SortEdPlanFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK SortStProgressFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK SortEdProgressFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	BOOL m_bSortAspect[8];

// �A�g���r���[�g
public:
	virtual void UpdateSetting();
// �I�y���[�V����
public:
	void DelCheckToDo();
	void UpdateToDo();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CToDoView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h���܂����B
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~CToDoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CToDoView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnTodoAdd();
	afx_msg void OnUpdateTodoAdd(CCmdUI* pCmdUI);
	afx_msg void OnTodoDel();
	afx_msg void OnUpdateTodoDel(CCmdUI* pCmdUI);
	afx_msg void OnTodoEdit();
	afx_msg void OnUpdateTodoEdit(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg void OnTabChange(LPNMHDR pNmhdr, HRESULT *pResult);
	afx_msg void OnColumnClick(LPNMHDR pNmhdr, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

	typedef enum eTABTYPE{
		TT_ALL = 0,		//�S��
		TT_NONE,		//������
		TT_PARITY,		//�Ή���
		TT_CHECK,		//�m�F��
		TT_WAIT,		//�҂�	
		TT_FINISH,		//����
		TT_RESERVE,		//�ۗ�
		TT_CHART,		//�`���[�g
		TT_END
	};
		
	CListCtrl m_objList[TT_END];
	CTabCtrl m_objTab;
	CBitmap m_objStateBmp;
	CImageList m_arrStateImg;
	CFont m_objFont;
	CRect m_objTabRect;
	COleDateTime m_objPreChkDtm;
	CChartWnd m_objChartWnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_TODOVIEW_H__03173B17_BB44_45AD_9189_1671C53D9E4D__INCLUDED_)

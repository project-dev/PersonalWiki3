// ExceptTestView.cpp : CExceptTestView �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "ExceptTest.h"

#include "ExceptTestDoc.h"
#include "ExceptTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExceptTestView

IMPLEMENT_DYNCREATE(CExceptTestView, CView)

BEGIN_MESSAGE_MAP(CExceptTestView, CView)
	//{{AFX_MSG_MAP(CExceptTestView)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//    ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
	// �W������R�}���h
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExceptTestView �N���X�̍\�z/����

CExceptTestView::CExceptTestView()
{
	// TODO: ���̏ꏊ�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B

}

CExceptTestView::~CExceptTestView()
{
}

BOOL CExceptTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExceptTestView �N���X�̕`��

void CExceptTestView::OnDraw(CDC* pDC)
{
	CExceptTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
}

/////////////////////////////////////////////////////////////////////////////
// CExceptTestView �N���X�̈��

BOOL CExceptTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �f�t�H���g�̈������
	return DoPreparePrinting(pInfo);
}

void CExceptTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ����O�̓��ʂȏ�����������ǉ����Ă��������B
}

void CExceptTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �����̌㏈����ǉ����Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// CExceptTestView �N���X�̐f�f

#ifdef _DEBUG
void CExceptTestView::AssertValid() const
{
	CView::AssertValid();
}

void CExceptTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExceptTestDoc* CExceptTestView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExceptTestDoc)));
	return (CExceptTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExceptTestView �N���X�̃��b�Z�[�W �n���h��

void CExceptTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	int i = 0;
	int j = 1;
	int k = j / i;
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
}

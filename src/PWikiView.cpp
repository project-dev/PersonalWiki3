// PWikiView.cpp : CPWikiView �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "PersonalWiki.h"

#include "PWikiDoc.h"
#include "PWikiView.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPWikiView

IMPLEMENT_DYNCREATE(CPWikiView, CView)

BEGIN_MESSAGE_MAP(CPWikiView, CView)
	//{{AFX_MSG_MAP(CPWikiView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// �W������R�}���h
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPWikiView �N���X�̍\�z/����

CPWikiView::CPWikiView()
{
	// TODO: ���̏ꏊ�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B

}

CPWikiView::~CPWikiView()
{
}

BOOL CPWikiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPWikiView �N���X�̕`��

void CPWikiView::OnDraw(CDC* pDC)
{
	CPWikiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
}

/////////////////////////////////////////////////////////////////////////////
// CPWikiView �N���X�̈��

BOOL CPWikiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �f�t�H���g�̈������
	return DoPreparePrinting(pInfo);
}

void CPWikiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ����O�̓��ʂȏ�����������ǉ����Ă��������B
}

void CPWikiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �����̌㏈����ǉ����Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// CPWikiView �N���X�̐f�f

#ifdef _DEBUG
void CPWikiView::AssertValid() const
{
	CView::AssertValid();
}

void CPWikiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPWikiDoc* CPWikiView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPWikiDoc)));
	return (CPWikiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPWikiView �N���X�̃��b�Z�[�W �n���h��

int CPWikiView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: ���̈ʒu�ɌŗL�̍쐬�p�R�[�h��ǉ����Ă�������
	CLogFile::SaveAppLog("CPWikiView ����");	
	
	return 0;
}

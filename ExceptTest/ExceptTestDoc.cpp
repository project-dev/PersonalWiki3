// ExceptTestDoc.cpp : CExceptTestDoc �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "ExceptTest.h"

#include "ExceptTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExceptTestDoc

IMPLEMENT_DYNCREATE(CExceptTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CExceptTestDoc, CDocument)
	//{{AFX_MSG_MAP(CExceptTestDoc)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExceptTestDoc �N���X�̍\�z/����

CExceptTestDoc::CExceptTestDoc()
{
	// TODO: ���̈ʒu�ɂP�x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CExceptTestDoc::~CExceptTestDoc()
{
}

BOOL CExceptTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExceptTestDoc �V���A���C�[�[�V����

void CExceptTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���̈ʒu�ɕۑ��p�̃R�[�h��ǉ����Ă��������B
	}
	else
	{
		// TODO: ���̈ʒu�ɓǂݍ��ݗp�̃R�[�h��ǉ����Ă��������B
	}
}

/////////////////////////////////////////////////////////////////////////////
// CExceptTestDoc �N���X�̐f�f

#ifdef _DEBUG
void CExceptTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExceptTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExceptTestDoc �R�}���h
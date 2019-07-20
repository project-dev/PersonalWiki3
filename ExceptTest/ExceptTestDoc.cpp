// ExceptTestDoc.cpp : CExceptTestDoc クラスの動作の定義を行います。
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
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExceptTestDoc クラスの構築/消滅

CExceptTestDoc::CExceptTestDoc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。

}

CExceptTestDoc::~CExceptTestDoc()
{
}

BOOL CExceptTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExceptTestDoc シリアライゼーション

void CExceptTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: この位置に保存用のコードを追加してください。
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください。
	}
}

/////////////////////////////////////////////////////////////////////////////
// CExceptTestDoc クラスの診断

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
// CExceptTestDoc コマンド

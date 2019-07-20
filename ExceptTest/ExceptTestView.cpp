// ExceptTestView.cpp : CExceptTestView クラスの動作の定義を行います。
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
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//    この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExceptTestView クラスの構築/消滅

CExceptTestView::CExceptTestView()
{
	// TODO: この場所に構築用のコードを追加してください。

}

CExceptTestView::~CExceptTestView()
{
}

BOOL CExceptTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExceptTestView クラスの描画

void CExceptTestView::OnDraw(CDC* pDC)
{
	CExceptTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}

/////////////////////////////////////////////////////////////////////////////
// CExceptTestView クラスの印刷

BOOL CExceptTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// デフォルトの印刷準備
	return DoPreparePrinting(pInfo);
}

void CExceptTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CExceptTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

/////////////////////////////////////////////////////////////////////////////
// CExceptTestView クラスの診断

#ifdef _DEBUG
void CExceptTestView::AssertValid() const
{
	CView::AssertValid();
}

void CExceptTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExceptTestDoc* CExceptTestView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExceptTestDoc)));
	return (CExceptTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExceptTestView クラスのメッセージ ハンドラ

void CExceptTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	int i = 0;
	int j = 1;
	int k = j / i;
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
}

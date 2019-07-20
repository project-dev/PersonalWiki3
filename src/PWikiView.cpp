// PWikiView.cpp : CPWikiView クラスの動作の定義を行います。
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
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPWikiView クラスの構築/消滅

CPWikiView::CPWikiView()
{
	// TODO: この場所に構築用のコードを追加してください。

}

CPWikiView::~CPWikiView()
{
}

BOOL CPWikiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPWikiView クラスの描画

void CPWikiView::OnDraw(CDC* pDC)
{
	CPWikiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}

/////////////////////////////////////////////////////////////////////////////
// CPWikiView クラスの印刷

BOOL CPWikiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// デフォルトの印刷準備
	return DoPreparePrinting(pInfo);
}

void CPWikiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CPWikiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}

/////////////////////////////////////////////////////////////////////////////
// CPWikiView クラスの診断

#ifdef _DEBUG
void CPWikiView::AssertValid() const
{
	CView::AssertValid();
}

void CPWikiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPWikiDoc* CPWikiView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPWikiDoc)));
	return (CPWikiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPWikiView クラスのメッセージ ハンドラ

int CPWikiView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: この位置に固有の作成用コードを追加してください
	CLogFile::SaveAppLog("CPWikiView 生成");	
	
	return 0;
}

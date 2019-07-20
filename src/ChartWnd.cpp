// ChartWnd.cpp: CChartWnd クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "personalwiki.h"
#include "ChartWnd.h"
#include "PWikiDoc.h"
#include "PWikiIniFile.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

/**
 * @brif コンストラクタ
 */
CChartWnd::CChartWnd(){
	m_pBackDC = NULL;
	m_pBackBmp = NULL;
	m_pDoc = NULL;
	m_nSelIndex = -1;
	m_nIconSize = 0;
}

/**
 * @brif デストラクタ
 */
CChartWnd::~CChartWnd(){

}

/**
 * @brif メッセージマップ
 */
BEGIN_MESSAGE_MAP(CChartWnd, CWnd)
	//{{AFX_MSG_MAP(CChartWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/**
 * @brif 生成
 */
BOOL CChartWnd::Create(DWORD dwStyle, RECT& rect, CWnd *pParent, CPWikiDoc* pDoc, UINT uID){
	m_pDoc = pDoc;
	if(!CWnd::Create(NULL, NULL, dwStyle, rect, pParent, uID)){
		return FALSE;
	}
	return TRUE;
}

/**
 * @brif WM_CREATEのハンドラ
 */
int CChartWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_objCurTime = COleDateTime::GetCurrentTime();
	ResetTime(m_objCurTime);

	CRect rect;
	GetClientRect(rect);

#if defined(USE_FILTER)
	m_objCmbCategory.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, rect, this, IDS_CMB_FILTER_CATEGORY);
	m_objCmbState.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, rect, this, IDS_CMB_FILTER_STATE);
	m_objCmbCategory.SetFont(&m_objCtrlFont);
	m_objCmbState.SetFont(&m_objCtrlFont);
/*
	m_objCmbCategory.AddString("なし");
	int nSize = m_pDoc->m_arrCategory.GetSize();
	for(int i = 0; i < nSize; i++){
		CString strCategory = m_pDoc->m_arrCategory.GetAt(i);
		m_objCmbCategory.AddString(strCategory);
	}
*/
	UpdateCategory();
	m_objCmbState.AddString("なし");
	m_objCmbState.AddString("未着手");
	m_objCmbState.AddString("対応中");
	m_objCmbState.AddString("確認完");
	m_objCmbState.AddString("待ち");
	m_objCmbState.AddString("完了");
	m_objCmbState.AddString("保留");

	m_objCmbCategory.SetCurSel(0);
	m_objCmbState.SetCurSel(0);
#endif
	
	
	CRect hRect = rect;
	CRect vRect = rect;

	hRect.top = hRect.bottom - 16;
	vRect.left = hRect.right - 16;
	m_objHScrollCtrl.Create(WS_CHILD | SBS_HORZ | WS_VISIBLE, hRect, this, IDS_CH_HSCROLLBAR);
	m_objVScrollCtrl.Create(WS_CHILD | SBS_VERT | WS_VISIBLE, vRect, this, IDS_CH_VSCROLLBAR);


	UpdateSetting();
/*	
	SetCtrlPos();
	CreateBuffer();
	GetItemWidth();	
*/	
	COleDateTimeSpan span = m_objCurTime - m_objMinTime;
	double dSpan = span.GetTotalDays();
	m_objHScrollCtrl.SetScrollPos((int)dSpan);
	m_objVScrollCtrl.SetScrollPos(0);
	UpdateBuffer();
	InvalidateRect(NULL);
	
	return 0;
}

/**
 * @brif コントロールの位置設定
 */
void CChartWnd::SetCtrlPos(){
	CRect rect;
	GetClientRect(rect);

#if defined(USE_FILTER)
	if(::IsWindow(m_objCmbCategory.m_hWnd)){
		m_objCmbCategory.SetWindowPos(&wndTop, 
									  0,  0, 
									  200, 200, 
									  SWP_SHOWWINDOW);
	}
	if(::IsWindow(m_objCmbState.m_hWnd)){
		m_objCmbState.SetWindowPos(&wndTop, 
								   204,  0, 
								   200, 200, 
								   SWP_SHOWWINDOW);
	}
#endif

	CRect hRect = rect;
	CRect vRect = rect;

	hRect.top = hRect.bottom - 16;
	vRect.left = hRect.right - 16;

	hRect.right -= vRect.Width();
	vRect.bottom -= hRect.Height();
	if(::IsWindow(m_objHScrollCtrl.m_hWnd)){
		m_objHScrollCtrl.SetWindowPos(&wndTop, 
									  hRect.left,    hRect.top, 
									  hRect.Width(), hRect.Height(), 
									  SWP_SHOWWINDOW);
	}
	if(::IsWindow(m_objVScrollCtrl.m_hWnd)){
		m_objVScrollCtrl.SetWindowPos(&wndTop, 
									  vRect.left,    vRect.top, 
									  vRect.Width(), vRect.Height(), 
									  SWP_SHOWWINDOW);
	}
}

/**
 * @brif スクロールバー取得
 */
CScrollBar* CChartWnd::GetScrollBarCtrl( int nBar ){
	if(nBar == SB_HORZ){
		return &m_objHScrollCtrl;
	}else if(nBar == SB_VERT){
		return &m_objVScrollCtrl;
	}
	return NULL;
}

/**
 * @brif バックバッファ作成
 */
void CChartWnd::CreateBuffer(){
	CRect rect;
	CRect hsRect;
	CRect vsRect;
	GetClientRect(rect);
	
	if(!::IsWindow(m_objHScrollCtrl.m_hWnd) || !::IsWindow(m_objVScrollCtrl.m_hWnd)){
		return;
	}
	m_objHScrollCtrl.GetClientRect(hsRect);
	m_objVScrollCtrl.GetClientRect(vsRect);
	rect.right -= vsRect.Width();
	rect.bottom -= hsRect.Height();
#if defined(USE_FILTER)
	CRect cbRect;
	m_objCmbCategory.GetClientRect(cbRect);
	rect.bottom -= cbRect.Height();
#endif
	if(m_pBackDC && m_pBackBmp){
		m_pBackBmp->DeleteObject();
		delete m_pBackDC;
		delete m_pBackBmp;
		m_pBackDC = NULL;
		m_pBackBmp = NULL;
	}

	CDC* pDC = GetDC();
	if(!m_pBackDC){
		m_pBackDC = new CDC();
		m_pBackDC->CreateCompatibleDC(pDC);
	}

	if(!m_pBackBmp){
		m_pBackBmp = new CBitmap();
		m_pBackBmp->CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		m_pBackDC->SelectObject(m_pBackBmp);
	}
	m_pBackDC->SetBkMode(TRANSPARENT);

}

/**
 * @brif バックバッファ更新
 */
void CChartWnd::UpdateBuffer(){
	UpdateDatas(TRUE, NULL);
}

/**
 * @brif 
 */
int CChartWnd::HitTest(CPoint pos){
	return UpdateDatas(FALSE, &pos);
}

#if defined(SUBITEMHITTEST_SUPPORT)
int CChartWnd::SubitemHitTest(CWHITTEST &hittest){
	UpdateDatas(FALSE, &hittest.pos);
	
}
#endif

/**
 * @brif 
 */
int CChartWnd::UpdateDatas(BOOL bDrawUpdate, LPPOINT pos){
	const CString arrWeekDay[8][2] = {
		{"", ""},
		{"(SUN)", "(日)"},
		{"(MON)", "(月)"},
		{"(THU)", "(火)"},
		{"(WEB)", "(水)"},
		{"(THI)", "(木)"},
		{"(FRI)", "(金)"},
		{"(SAT)", "(土)"},
	};

	const COLORREF arrWeekDayCr[8][2] = {
		{RGB(0x00, 0x00, 0x00),RGB(0x00, 0x00, 0x00)},
		{RGB(0xFF, 0xEE, 0xEE),RGB(0xFF, 0x00, 0x00)},
		{RGB(0xFF, 0xFF, 0xFF),RGB(0x00, 0x00, 0x00)},
		{RGB(0xFF, 0xFF, 0xFF),RGB(0x00, 0x00, 0x00)},
		{RGB(0xFF, 0xFF, 0xFF),RGB(0x00, 0x00, 0x00)},
		{RGB(0xFF, 0xFF, 0xFF),RGB(0x00, 0x00, 0x00)},
		{RGB(0xFF, 0xFF, 0xFF),RGB(0x00, 0x00, 0x00)},
		{RGB(0xEE, 0xEE, 0xFF),RGB(0x00, 0x00, 0xFF)},
	};	
	
	if(!m_pBackDC || !m_pBackBmp || !m_pDoc || (!bDrawUpdate && !pos)){
		return -1;
	}

	int nSize =m_pDoc->m_objToDoData.GetSize();
	CEventDate *pData;
	COleDateTime objPlan_St;
	COleDateTime objPlan_Ed;
	COleDateTime objProg_St;
	COleDateTime objProg_Ed;

	CString strName;
	CString strCategory;
	CString strProgress;
	double dPar;
	int nState;
	CSize szStr;
	int y = 0;
	int x = 0;

	GetItemWidth();

	CFont *pOldFont = m_pBackDC->SelectObject(&m_objFont);

	CBrush brush;

	CRect rect;
	GetClientRect(rect);
	if(bDrawUpdate){
		brush.CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
		m_pBackDC->FillRect(rect, &brush);
		brush.DeleteObject();
	}

	int nStateWidth = 0;
	CString strState = "ステータス";
	szStr = m_pBackDC->GetTextExtent(strState);
	nStateWidth = szStr.cx + COLSPAN;
	int vPos = m_objVScrollCtrl.GetScrollPos();
	int nAddCnt = 0;
	COLORREF crBkColor = RGB(0xFF, 0xFF, 0xFF);
	COLORREF crTextColor = RGB(0x00, 0x00, 0x00);
	BOOL bSel = FALSE;
	int nScBarCnt = 0;
	BOOL bBtnDraw = FALSE;

#if defined(USE_FILTER)
	CString strFilterState;
	int nFilterState = m_objCmbState.GetCurSel();
	m_objCmbState.GetLBText(nFilterState, strFilterState);

	CString strFilterCategory;
	int nFilterCategory = m_objCmbCategory.GetCurSel();
	m_objCmbCategory.GetLBText(nFilterCategory, strFilterCategory);

#endif

	int nVIndex = 0;
	for(int i = -1; i < nSize; i++){
		//データ取得
		if(i == -1){
			if(bDrawUpdate){
				crBkColor = RGB(0xCC, 0xCC, 0xCC);
				crTextColor = RGB(0x00, 0x00, 0x00);
			}

			strName		= "項目名";
			strCategory	= "カテゴリ";
			strState	= "ステータス";
			strProgress = "進捗";
			bSel = FALSE;
			bBtnDraw = TRUE;
		}else{
			bBtnDraw = FALSE;
			nVIndex = i + vPos;
			if(nVIndex >= nSize){
				break;
			}
			if(bDrawUpdate){
				if(m_nSelIndex == nVIndex){
					crBkColor = RGB(0x00, 0xAA, 0xAA);
					crTextColor = RGB(0xFF, 0xFF, 0xFF);
					bSel = TRUE;
				}else{
					crBkColor = RGB(0xFF, 0xFF, 0xFF);
					crTextColor = RGB(0x00, 0x00, 0x00);
					bSel = FALSE;
				}
			}
			pData = m_pDoc->m_objToDoData.GetToDo(nVIndex);
			strName = pData->GetName();
			if(strName.IsEmpty()){
				strName = " ";
			}
			nState = pData->GetState();
			strState = pData->GetStateString();
			strProgress.Format("%3d%%", (int)pData->GetProcess());
#if defined(USE_FILTER)
			if(nFilterState && strState.Compare(strFilterState)){
				continue;
			}
#endif
			strCategory = pData->GetCategory();
			if(strCategory.IsEmpty()){
				strCategory = " ";
			}
#if defined(USE_FILTER)
			if(nFilterCategory &&strCategory.Compare(strFilterCategory)){
				continue;
			}
#endif
			dPar = pData->GetProcess();
			pData->GetPlan(&objPlan_St, &objPlan_Ed);
			pData->GetProgress(&objProg_St, &objProg_Ed);

			ResetTime(objPlan_St);
			ResetTime(objPlan_Ed);
			ResetTime(objProg_St);
			ResetTime(objProg_Ed);
		}
		if(bDrawUpdate){
			m_pBackDC->SetTextColor(crTextColor);
		}

		double dSpanPos = (double)m_objHScrollCtrl.GetScrollPos();
		COleDateTimeSpan span(dSpanPos);
		COleDateTime drDate = m_objMinTime + span;
		ResetTime(drDate);
		x = 0;

		int nHeight = szStr.cy;
		if((i != -1) && (m_nIconSize > szStr.cy)){
			nHeight = m_nIconSize;
		}

		//項目名描画
		if(bDrawUpdate){
			if(i == -1){
				DrawItemString(CRect(x, y, x + m_nNameWidth, y +  nHeight + COLSPAN), strName, crBkColor, bBtnDraw, -1);
			}else{
				DrawItemString(CRect(x, y, x + m_nNameWidth, y +  nHeight + COLSPAN), strName, crBkColor, bBtnDraw, nState);
			}
		}
		x += m_nNameWidth;

		//カテゴリ表示
		if(bDrawUpdate){
			DrawItemString(CRect(x, y, x + m_nCategoryWidth, y +  nHeight + COLSPAN), strCategory, crBkColor, bBtnDraw);
		}
		x += m_nCategoryWidth;

		//ステータス表示
		if(bDrawUpdate){
			DrawItemString(CRect(x, y, x + nStateWidth, y +  nHeight + COLSPAN), strState, crBkColor, bBtnDraw);
		}
		x += nStateWidth;

		//進捗表示
		if(bDrawUpdate){
			if(i == -1){
				DrawItemString(CRect(x, y, x + m_nProgressWidth, y +  nHeight + COLSPAN), strProgress, crBkColor, bBtnDraw);
			}else{
				DrawItemProgress(CRect(x, y, x + m_nProgressWidth, y +  nHeight + COLSPAN), strProgress, pData->GetProcess(), crBkColor);
			}
		}
		x += m_nProgressWidth;
		
		//スケジュールバー描画
		CString strDate = "";
		strDate = "00/00/00(日)";
		szStr = m_pBackDC->GetTextExtent(strDate);
		nScBarCnt = szStr.cx + COLSPAN;
		while((x < rect.right) && (drDate <= m_objMaxTime)){
			COleDateTime objCurDt = COleDateTime::GetCurrentTime();
			ResetTime(objCurDt);
			BOOL bToDay = objCurDt == drDate;
			int nWeekDay = drDate.GetDayOfWeek();
			if( i == -1){
				strDate.Format("%s%s",drDate.Format("%y/%m/%d"), arrWeekDay[nWeekDay][1]);
			}else if(bDrawUpdate){
				if(bSel){
					crBkColor = RGB(0x00, 0xAA, 0xAA);
					crTextColor = RGB(0xFF, 0xFF, 0xFF);
				}else{
					if(bToDay){
						crBkColor = RGB(0xFF, 0xFF, 0xCC);
					}else{
						crBkColor = arrWeekDayCr[nWeekDay][0];
					}
					crTextColor = arrWeekDayCr[nWeekDay][1];
				}
			}
			CRect dtRect(x, y, x + szStr.cx + COLSPAN, y +  nHeight + COLSPAN);
			if(bDrawUpdate){
				if( i == -1){
					DrawItemString(dtRect, strDate, crBkColor, bBtnDraw);
				}else{
					strDate = " ";
					DrawItemString(dtRect, strDate, crBkColor);
					//予定
					if((objPlan_St <= drDate) && (objPlan_Ed >= drDate)){
						CBrush plBrush;
						plBrush.CreateSolidBrush(bToDay ? RGB(0x66, 0x66, 0xFF) : RGB(0xAA, 0xAA, 0xFF));
						CRect planRect = dtRect;
						planRect.bottom = dtRect.top + dtRect.Height() / 2;
						planRect.left++;
						planRect.top++;
						m_pBackDC->FillRect(planRect, &plBrush);
						plBrush.DeleteObject();
						plBrush.CreateSolidBrush(bToDay ? RGB(0x00, 0x00, 0x66) : RGB(0x00, 0x00, 0xAA));
						m_pBackDC->FrameRect(planRect, &plBrush);
						plBrush.DeleteObject();
					}

					COleDateTime endDate = COleDateTime::GetCurrentTime();
					ResetTime(endDate);

					CRect progRect = dtRect;
					progRect.top = dtRect.top + dtRect.Height() / 2;
					progRect.left++;
					progRect.top++;
					switch(nState){
					case 0:	//未実施
						break;
					case 1:	//対応中
						if((objProg_St <= drDate) && (endDate >= drDate)){
							CBrush prBrush;
							prBrush.CreateSolidBrush(bToDay ? RGB(0x00, 0xEE, 0x00) : RGB(0x00, 0xFF, 0x00));
							m_pBackDC->FillRect(progRect, &prBrush);
							prBrush.DeleteObject();

							prBrush.CreateSolidBrush(bToDay ? RGB(0x00, 0x66, 0x00) : RGB(0x00, 0x88, 0x00));
							m_pBackDC->FrameRect(progRect, &prBrush);
							prBrush.DeleteObject();
						}
						break;
					case 2: //確認完
						if((objProg_St <= drDate) && (endDate >= drDate)){
							CBrush prBrush;
							prBrush.CreateSolidBrush(bToDay ? RGB(0xFF, 0xFF, 0xAA) : RGB(0xFF, 0xFF, 0xCC));
							m_pBackDC->FillRect(progRect, &prBrush);
							prBrush.DeleteObject();

							prBrush.CreateSolidBrush(bToDay ? RGB(0x88, 0x88, 0x00) : RGB(0xAA, 0xAA, 0x00));
							m_pBackDC->FrameRect(progRect, &prBrush);
							prBrush.DeleteObject();
						}
						break;
					case 3:	//待ち
						if((objProg_St <= drDate) && (endDate >= drDate)){
							CBrush prBrush;
							prBrush.CreateSolidBrush(bToDay ? RGB(0xFF, 0xAA, 0xAA) : RGB(0xFF, 0xCC, 0xCC));
							m_pBackDC->FillRect(progRect, &prBrush);
							prBrush.DeleteObject();

							prBrush.CreateSolidBrush(bToDay ? RGB(0x66, 0x00, 0x00) : RGB(0x88, 0x00, 0x00));
							m_pBackDC->FrameRect(progRect, &prBrush);
							prBrush.DeleteObject();
						}
						break;
					case 5:	//保留
						if((objProg_St <= drDate) && (endDate >= drDate)){
							CBrush prBrush;
							prBrush.CreateSolidBrush(bToDay ? RGB(0xFF, 0xAA, 0x00) : RGB(0xFF, 0xCC, 0x00));
							m_pBackDC->FillRect(progRect, &prBrush);
							prBrush.DeleteObject();

							prBrush.CreateSolidBrush(bToDay ? RGB(0x88, 0x66, 0x00) : RGB(0xAA, 0x88, 0x00));
							m_pBackDC->FrameRect(progRect, &prBrush);
							prBrush.DeleteObject();
						}
						break;
					case 4:	//完了
						if((objProg_St <= drDate) && (objProg_Ed >= drDate)){
							CBrush prBrush;
							prBrush.CreateSolidBrush(bToDay ? RGB(0xAA, 0xAA, 0xFF) : RGB(0xCC, 0xCC, 0xFF));
							m_pBackDC->FillRect(progRect, &prBrush);
							prBrush.DeleteObject();

							prBrush.CreateSolidBrush(bToDay ? RGB(0x00, 0x00, 0xAA) : RGB(0x00, 0x00, 0x88));
							m_pBackDC->FrameRect(progRect, &prBrush);
							prBrush.DeleteObject();
						}
						break;
					}

					//区切り線の描画
					CPen sepPen;
					sepPen.CreatePen(PS_DOT, 1, RGB(0xAA, 0xAA, 0xAA));
					CPoint pos[2];
					pos[0].x = dtRect.left;
					pos[0].y = dtRect.top + dtRect.Height() / 2;

					pos[1].x = dtRect.right;
					pos[1].y = dtRect.top + dtRect.Height() / 2;

					CPen* pOldSepPen = m_pBackDC->SelectObject(&sepPen);
					m_pBackDC->Polyline(pos, 2);
					m_pBackDC->SelectObject(pOldSepPen);
					sepPen.DeleteObject();
				}
			}

			x += szStr.cx + COLSPAN;
			int nYear = drDate.GetYear();
			int nMonth = drDate.GetMonth();
			int nDay = drDate.GetDay() + 1; 
			if(drDate.SetDate(nYear, nMonth, nDay) != COleDateTime::valid){
				nDay = 1;
				nMonth++;
				if(nMonth > 12){
					nMonth = 1;
					nYear++;
				}
				drDate.SetDate(nYear, nMonth, nDay);
			}
		}
#if defined(USE_FILTER)
		CRect cmbRect;
		m_objCmbState.GetClientRect(cmbRect);
		int chkY = y + cmbRect.bottom;
		if(!bDrawUpdate
		&& (pos->x >= 0) && (pos->x <= x)
		&& (pos->y >= chkY) && (pos->y <= chkY + nHeight + COLSPAN)){
			m_pBackDC->SelectObject(pOldFont);
			return nVIndex;
		}
#else
		if(!bDrawUpdate
		&& (pos->x >= 0) && (pos->x <= x)
		&& (pos->y >= y) && (pos->y <= y + nHeight + COLSPAN)){
			m_pBackDC->SelectObject(pOldFont);
			return nVIndex;
		}
#endif

		if(i != -1){
			nAddCnt++;
		}
		y += nHeight + COLSPAN;
	}
	m_pBackDC->SelectObject(pOldFont);
	return -1;
}

/**
 * @brif 
 */
void CChartWnd::DrawItemString(CRect& rect, CString& str, COLORREF crBkColor, BOOL bDrawBtn /* = FALSE*/, int nImgIndex /*= -1*/){
	if(bDrawBtn){
		DrawFrameControl(m_pBackDC->GetSafeHdc(), rect, DFC_BUTTON, DFCS_BUTTONPUSH /*| DFCS_FLAT*/);
	}else{
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(0xAA, 0xAA, 0xAA));

		CBrush brush;
		brush.CreateSolidBrush(crBkColor);
		m_pBackDC->FillRect(rect, &brush);
		brush.DeleteObject();

		CPoint pos[5];
		pos[0].x = rect.left;
		pos[0].y = rect.top;

		pos[1].x = rect.right;
		pos[1].y = rect.top;

		pos[2].x = rect.right;
		pos[2].y = rect.bottom;
		
		pos[3].x = rect.left;
		pos[3].y = rect.bottom;

		pos[4].x = rect.left;
		pos[4].y = rect.top;

		CPen* pOldPen = m_pBackDC->SelectObject(&pen);
		m_pBackDC->Polyline(pos, 5);
		m_pBackDC->SelectObject(pOldPen);
		pen.DeleteObject();
	}
	if(m_objImgList.m_hImageList && m_objImgList.GetImageCount() && (nImgIndex > -1)){
		IMAGEINFO imgInfo;
		memset(&imgInfo, 0, sizeof(IMAGEINFO));
		m_objImgList.GetImageInfo(nImgIndex, &imgInfo);

		//アイコン描画
		CPoint pt(rect.left + 1, rect.top + COLSPAN_HALF);
		CSize sz(m_nIconSize, m_nIconSize);
		m_objImgList.DrawIndirect(m_pBackDC, nImgIndex, pt, sz, CPoint(0,0));
		
		CRect txtRect = rect;
		txtRect.left += COLSPAN_HALF + m_nIconSize;
		txtRect.top += COLSPAN_HALF;
		m_pBackDC->DrawText(str, txtRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE );
	}else{
		CRect txtRect = rect;
		txtRect.left += COLSPAN_HALF;
		txtRect.top += COLSPAN_HALF;
		m_pBackDC->DrawText(str, txtRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE );
	}
}

void CChartWnd::DrawItemProgress(CRect& rect, CString& str,double dProgress,  COLORREF crBkColor){
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0xAA, 0xAA, 0xAA));

	CBrush brush;
	brush.CreateSolidBrush(crBkColor);
	m_pBackDC->FillRect(rect, &brush);
	brush.DeleteObject();

	CPoint pos[5];
	pos[0].x = rect.left;
	pos[0].y = rect.top;

	pos[1].x = rect.right;
	pos[1].y = rect.top;

	pos[2].x = rect.right;
	pos[2].y = rect.bottom;
	
	pos[3].x = rect.left;
	pos[3].y = rect.bottom;

	pos[4].x = rect.left;
	pos[4].y = rect.top;

	CPen* pOldPen = m_pBackDC->SelectObject(&pen);
	m_pBackDC->Polyline(pos, 5);
	m_pBackDC->SelectObject(pOldPen);
	pen.DeleteObject();
	COLORREF crOldText = m_pBackDC->GetTextColor();
	COLORREF crText;
	if((int)dProgress > 0){
		CRect prgRect = rect;
		prgRect.left++;
		prgRect.top++;
		prgRect.right = rect.left + (int)(dProgress / 2);
		//rect.bottom--;
/*
		if(dProgress < 25.0){
			crText = RGB(0x00, 0x00, 0x00);
			brush.CreateSolidBrush(RGB(0xFF, 0x00, 0x00));
		}else if(dProgress < 50.0){
			crText = RGB(0x00, 0x00, 0x00);
			brush.CreateSolidBrush(RGB(0x00, 0xFF, 0x00));
		}else if(dProgress < 75.0){
			crText = RGB(0x00, 0x00, 0x00);
			brush.CreateSolidBrush(RGB(0x00, 0xFF, 0xFF));
		}else if(dProgress < 100.0){
			crText = RGB(0xFF, 0xFF, 0xFF);
			brush.CreateSolidBrush(RGB(0x00, 0xCC, 0xCC));
		}else if(dProgress >= 100.0){
			crText = RGB(0xFF, 0xFF, 0xFF);
			brush.CreateSolidBrush(RGB(0x00, 0x00, 0xFF));
		}
*/
		crText = RGB(0x00, 0x00, 0x00);
		brush.CreateSolidBrush(RGB(0x88, 0x88, 0xFF));
		m_pBackDC->SetTextColor(crText);
		m_pBackDC->FillRect(prgRect, &brush);
		brush.DeleteObject();
	}
	m_pBackDC->DrawText(str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	m_pBackDC->SetTextColor(crOldText);
}

/**
 * @brif 
 */
void CChartWnd::GetItemWidth(){
	if(!m_pDoc){
		return;
	}
	CFont *pOldFont = m_pBackDC->SelectObject(&m_objFont);

	int nSize =m_pDoc->m_objToDoData.GetSize();
	CEventDate *pData;
	CString strName;
	CString strCategory;
	CSize szStr;
	COleDateTime objPlan_St;
	COleDateTime objPlan_Ed;
	COleDateTime objProg_St;
	COleDateTime objProg_Ed;

	CString strHName = "項目";
	CString strHCate = "カテゴリ";
	CString strProgress = "進捗";

	szStr = m_pBackDC->GetTextExtent(strHName);
	m_nNameWidth = szStr.cx + COLSPAN;

	szStr = m_pBackDC->GetTextExtent(strHCate);
	m_nCategoryWidth = szStr.cx + COLSPAN;

	m_nProgressWidth = 50;

	m_objMinTime = COleDateTime::GetCurrentTime();
	m_objMaxTime = COleDateTime::GetCurrentTime();
	ResetTime(m_objMinTime);
	ResetTime(m_objMaxTime);
#if defined(USE_FILTER)
	CString strFilterState;
	int nFilterState = m_objCmbState.GetCurSel();
	m_objCmbState.GetLBText(nFilterState, strFilterState);

	CString strFilterCategory;
	int nFilterCategory = m_objCmbCategory.GetCurSel();
	m_objCmbCategory.GetLBText(nFilterCategory, strFilterCategory);
#endif

	m_nIconSize = 0;
	if(m_objImgList.m_hImageList && m_objImgList.GetImageCount()){
		IMAGEINFO imgInfo;
		for(int i = 0; i < m_objImgList.GetImageCount(); i++){
			memset(&imgInfo, 0, sizeof(IMAGEINFO));
			m_objImgList.GetImageInfo(i, &imgInfo);
			if(m_nIconSize < imgInfo.rcImage.right - imgInfo.rcImage.left){
				m_nIconSize = imgInfo.rcImage.right - imgInfo.rcImage.left;
			}
		}
	}
	m_nNameWidth += m_nIconSize;

	int nLineCnt = 0;
	for(int i = 0; i < nSize; i++){
		//データ取得
		pData = m_pDoc->m_objToDoData.GetToDo(i);
		strName = pData->GetName();
		strCategory = pData->GetCategory();
		pData->GetPlan(&objPlan_St, &objPlan_Ed);
		pData->GetProgress(&objProg_St, &objProg_Ed);
		ResetTime(objPlan_St);
		ResetTime(objPlan_Ed);
		ResetTime(objProg_St);
		ResetTime(objProg_Ed);

		szStr = m_pBackDC->GetTextExtent(strName);
		if(m_nNameWidth < (szStr.cx + COLSPAN + m_nIconSize)){
			m_nNameWidth = (szStr.cx + COLSPAN + m_nIconSize);
		}

		szStr = m_pBackDC->GetTextExtent(strCategory);
#if defined(USE_FILTER)
		if(nFilterCategory &&strCategory.Compare(strFilterCategory)){
			continue;
		}
#endif
#if defined(USE_FILTER)
		CString strState = pData->GetStateString();
		if(nFilterState && strState.Compare(strFilterState)){
			continue;
		}
#endif
		if(m_nCategoryWidth < (szStr.cx + COLSPAN)){
			m_nCategoryWidth = (szStr.cx + COLSPAN);
		}
/*
		strProgress.Format("%3d%%", (int)pData->GetProcess());
		szStr = m_pBackDC->GetTextExtent(strCategory);
		if(m_nProgressWidth < (szStr.cx + COLSPAN)){
			m_nProgressWidth = (szStr.cx + COLSPAN);
		}
*/		
		if(m_objMinTime > objPlan_St){
			m_objMinTime = objPlan_St;
		}
		if(m_objMinTime > objProg_St){
			m_objMinTime = objProg_St;
		}
		if(m_objMaxTime < objPlan_Ed){
			m_objMaxTime = objPlan_Ed;
		}
		if(m_objMaxTime < objProg_Ed){
			m_objMaxTime = objProg_Ed;
		}
		nLineCnt++;
	}

	COleDateTimeSpan objSpan = m_objMaxTime - m_objMinTime;
	int nSpan = (int)objSpan.GetTotalDays();

	CRect rect;
	GetClientRect(rect);
	szStr = m_pBackDC->GetTextExtent("00/00/00(日)");
	int nDateLen = szStr.cx + COLSPAN;

	szStr = m_pBackDC->GetTextExtent("ステータス");
	int nStateLen = szStr.cx + COLSPAN;

	int nSpanWidth = (nDateLen + COLSPAN) * nSpan;
	int nViewCnt = (rect.Width() - (nStateLen + m_nNameWidth + m_nCategoryWidth + m_nProgressWidth)) / nDateLen;
	
	nSpan = nSpanWidth / nDateLen;
	if(nSpanWidth % nDateLen){
		nSpan += 1;
	}

	SCROLLINFO objScHInfo;
	memset(&objScHInfo, 0, sizeof(SCROLLINFO));
	m_objHScrollCtrl.GetScrollInfo( &objScHInfo,SIF_ALL);
	objScHInfo.cbSize = sizeof(SCROLLINFO);
	objScHInfo.fMask = SIF_ALL;
	objScHInfo.nMin = 0;
	objScHInfo.nMax = nSpan - nViewCnt;
	objScHInfo.nPage = 1;
	objScHInfo.nTrackPos = 1;
	m_objHScrollCtrl.SetScrollInfo(&objScHInfo);

	int nItemHeight = m_nIconSize > szStr.cy ? m_nIconSize + COLSPAN : szStr.cy + COLSPAN;
#if defined(USE_FILTER)
	CRect cmbRect;
	m_objCmbCategory.GetClientRect(cmbRect);
	int nVCnt = (rect.Height() - nItemHeight - cmbRect.Height()) / nItemHeight;
#else
	int nVCnt = (rect.Height() - nItemHeight) / nItemHeight;
#endif
	if((rect.Height() - nItemHeight) % nItemHeight){
		nVCnt--;
	}

	SCROLLINFO objScVInfo;
	memset(&objScVInfo, 0, sizeof(SCROLLINFO));
	m_objVScrollCtrl.GetScrollInfo( &objScVInfo,SIF_ALL);
	objScVInfo.cbSize = sizeof(SCROLLINFO);
	objScVInfo.fMask = SIF_ALL;
	objScVInfo.nMin = 0;
	objScVInfo.nMax = nLineCnt - nVCnt;
	objScVInfo.nPage = 1;
	objScVInfo.nTrackPos = 1;
	m_objVScrollCtrl.SetScrollInfo(&objScVInfo);
	m_pBackDC->SelectObject(pOldFont);
}

/**
 * @brif 
 */
void CChartWnd::OnPaint(){
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	CRect rect;
	GetClientRect(rect);
	if(m_pBackDC){
#if defined(USE_FILTER)
		CRect cbRect;
		CRect ctrRect = rect;

		m_objCmbCategory.GetClientRect(cbRect);
		rect.top = cbRect.bottom;
		ctrRect.bottom = cbRect.bottom;
		CBrush brush;
		brush.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));
		dc.FillRect(ctrRect, &brush);
#endif
		dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), m_pBackDC, 0, 0, SRCCOPY);
	}
}

/**
 * @brif 
 */
void CChartWnd::OnSize(UINT nType, int cx, int cy){
	CWnd::OnSize(nType, cx, cy);
	SetCtrlPos();
	CreateBuffer();
	UpdateBuffer();
}

/**
 * @brif 
 */
void CChartWnd::OnShowWindow(BOOL bShow, UINT nStatus){
	CWnd::OnShowWindow(bShow, nStatus);
	if(bShow){
		SetCtrlPos();
		CreateBuffer();
		UpdateBuffer();
	}
}

/**
 * @brif 
 */
void CChartWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){
	HScrollFunc(nSBCode, nPos, pScrollBar);
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
	UpdateBuffer();
	InvalidateRect(NULL);
}

/**
 * @brif 
 */
void CChartWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){
	VScrollFunc(nSBCode, nPos, pScrollBar);
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
	UpdateBuffer();
	InvalidateRect(NULL);
}

/**
 * @brif 
 */
void CChartWnd::OnDestroy() {
	if(m_pBackDC){
		delete m_pBackDC;
		m_pBackDC = NULL;
	}
	if(m_pBackBmp){
		m_pBackBmp->DeleteObject();
		delete m_pBackBmp;
		m_pBackBmp = NULL;
	}
	CWnd::OnDestroy();
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	
}

/**
 * @brif 
 */
void CChartWnd::OnLButtonDblClk(UINT nFlags, CPoint point){
	CWnd::OnLButtonDblClk(nFlags, point);
	//ToDoの詳細を表示する
	m_nSelIndex = HitTest(point);
	UpdateBuffer();
	InvalidateRect(NULL);
}

/**
 * @brif 
 */
void CChartWnd::OnLButtonDown(UINT nFlags, CPoint point){
	CWnd::OnLButtonDown(nFlags, point);
	m_nSelIndex = HitTest(point);
	UpdateBuffer();
	InvalidateRect(NULL);
}

/**
 * @brif 
 */
void CChartWnd::OnRButtonDown(UINT nFlags, CPoint point){
	CWnd::OnRButtonDown(nFlags, point);
	m_nSelIndex = HitTest(point);
	UpdateBuffer();
	InvalidateRect(NULL);
}

/**
 * @brif 
 */
int CChartWnd::GetSelectItemIndex(){
	return m_nSelIndex;
}

/**
 * @brif 
 */
CEventDate* CChartWnd::GetItemData(int nIndex){
	if(!m_pDoc){
		return NULL;
	}

	int nSize = m_pDoc->m_objToDoData.GetSize();
	if((nSize <= nIndex) || (nIndex < 0)){
		return NULL;
	}
	return m_pDoc->m_objToDoData.GetToDo(nIndex);
}

/**
 * @brif 
 */
void CChartWnd::OnMouseMove(UINT nFlags, CPoint point){
	CWnd::OnMouseMove(nFlags, point);
}

/**
 * @brif 
 */
void CChartWnd::ResetTime(COleDateTime &objDt){
	int nYear = objDt.GetYear();
	int nMonth = objDt.GetMonth();
	int nDay = objDt.GetDay();
	objDt.SetDateTime(nYear, nMonth, nDay, 0, 0, 0);
}

BOOL CChartWnd::OnCommand(WPARAM wParam, LPARAM lParam){
	DWORD dwCmd = HIWORD(wParam);
	DWORD dwId = LOWORD(wParam);

	if(dwId == IDS_CMB_FILTER_CATEGORY){
		switch(dwCmd){
		case CBN_CLOSEUP:
		case CBN_DBLCLK:
		case CBN_DROPDOWN:
		case CBN_EDITCHANGE:
		case CBN_EDITUPDATE:
		case CBN_ERRSPACE:
		case CBN_KILLFOCUS:
		case CBN_SELENDCANCEL:
		case CBN_SELENDOK:
		case CBN_SETFOCUS:
			break;
		case CBN_SELCHANGE:
			UpdateBuffer();
			InvalidateRect(NULL);
			break;
		}
	}
	if(dwId == IDS_CMB_FILTER_STATE){
		switch(dwCmd){
		case CBN_CLOSEUP:
		case CBN_DBLCLK:
		case CBN_DROPDOWN:
		case CBN_EDITCHANGE:
		case CBN_EDITUPDATE:
		case CBN_ERRSPACE:
		case CBN_KILLFOCUS:
		case CBN_SELENDCANCEL:
		case CBN_SELENDOK:
		case CBN_SETFOCUS:
			break;
		case CBN_SELCHANGE:
			UpdateBuffer();
			InvalidateRect(NULL);
			break;
		}
	}

	return CWnd::OnCommand(wParam, lParam);
}

void CChartWnd::SetImageList(CImageList* pImgList){
	m_objImgList.DeleteImageList();
	if(!pImgList){
		return;
	}
	m_objImgList.Create(pImgList);
}

void CChartWnd::UpdateSetting(){
	m_objFont.DeleteObject();
	m_objCtrlFont.DeleteObject();

	LOGFONT lFont;
	memset(&lFont, 0, sizeof(LOGFONT));
	FONTINFO objFontInfo;
	CMainFrame *pFrm = GetMainFrame(this);
	pFrm->m_objIniFile.GetFontInfoIniData(objFontInfo);

	CDC* pDC = GetDC();

	MakeFont(m_objFont, pDC, objFontInfo.szToDoFontName, objFontInfo.lToDoHeight);
	MakeFont(m_objCtrlFont, pDC, objFontInfo.szEtcFontName, objFontInfo.lEtcHeight);

	if(::IsWindow(m_objCmbCategory.m_hWnd)){
		m_objCmbCategory.SetFont(&m_objCtrlFont);
	}
	if(::IsWindow(m_objCmbState.m_hWnd)){
		m_objCmbState.SetFont(&m_objCtrlFont);
	}
	
//	SetFont(&m_objFont);
	SetCtrlPos();
	CreateBuffer();
	UpdateBuffer();
	InvalidateRect(NULL);
}

void CChartWnd::UpdateFont(){

}

void CChartWnd::UpdateCategory(){
	CString strSelText;
	m_objCmbCategory.GetWindowText(strSelText);
	m_objCmbCategory.ResetContent();
	m_objCmbCategory.AddString("なし");
	int nSize = m_pDoc->m_arrCategory.GetSize();
	for(int i = 0; i < nSize; i++){
		CString strCategory = m_pDoc->m_arrCategory.GetAt(i);
		m_objCmbCategory.AddString(strCategory);
	}
	int nSelIndex = m_objCmbCategory.FindStringExact(-1, strSelText);
	if(nSelIndex != CB_ERR){
		m_objCmbCategory.SetCurSel(nSelIndex);
	}else{
	}


}

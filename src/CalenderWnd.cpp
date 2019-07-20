// CalenderWnd.cpp: CCalenderWnd �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PersonalWiki.h"
#include "CalenderWnd.h"
#include "MainFrm.h"
#include "PWikiDoc.h"
#include "DlgDateInp.h"
#include "InfoView.h"
#include "LogFile.h"
#include "InfoTabView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CCalenderWnd, CWnd)
	//{{AFX_MSG_MAP(CCalenderWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_NEXTBTN, OnNextBtnClick)
	ON_BN_CLICKED(IDC_PREVBTN, OnPrevBtnClick)
	ON_BN_CLICKED(IDC_TODAYBTN, OnTodayBtnClick)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DTCTRL, OnDtChange)
END_MESSAGE_MAP()

CCalenderWnd::CCalenderWnd(){

	m_pBackDC = NULL;
	m_pBackBmp = NULL;
	m_pOldBmp = NULL;
	m_objToDay.SetDate(0, 0, 0);
	m_uTimerID = 0;

}

CCalenderWnd::~CCalenderWnd(){

}

/**
 * @brif WM_CREATE�̃n���h���֐�
 */
int CCalenderWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CLogFile::SaveAppLog("CCalenderWnd::OnCreate");
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: ���̈ʒu�ɌŗL�̍쐬�p�R�[�h��ǉ����Ă�������
	CRect crRect;
	GetClientRect(crRect);
	CRect crScVRect(crRect.right - 16, crRect.top, crRect.right, crRect.bottom);
//	CRect crScHRect(crRect.left, crRect.bottom -16, crRect.right - 16, crRect.bottom);
//	m_objScH.Create(WS_CHILD | SBS_HORZ | WS_VISIBLE, crScHRect, this, 1);
	m_objScV.Create(WS_CHILD | SBS_VERT | WS_VISIBLE, crScVRect, this, 1);

	MakeFont(m_objCtrlFont, GetDC(), "�l�r �S�V�b�N", 10);

	CreateBuffer();

	CRect objNextBtnRect(crRect.right - 24 * 2, crRect.top, crRect.right - 24, crRect.top + 24);
	CRect objPrevBtnRect(crRect.left, crRect.top, crRect.left + 24, crRect.top + 24);
	CRect objTodayBtnRect(crRect.right - 24, crRect.top, crRect.right, crRect.top + 24);
	m_objNextMonth.Create(_T(">>"), WS_CHILD | WS_VISIBLE, objNextBtnRect, this, IDC_NEXTBTN);
	m_objPrevMonth.Create(_T("<<"), WS_CHILD | WS_VISIBLE, objPrevBtnRect, this, IDC_PREVBTN);
	m_objBtnToDay.Create(_T("��"), WS_CHILD | WS_VISIBLE, objTodayBtnRect, this, IDC_TODAYBTN);
	m_objNextMonth.SetFont(&m_objCtrlFont);
	m_objPrevMonth.SetFont(&m_objCtrlFont);
	m_objBtnToDay.SetFont(&m_objCtrlFont);

	CRect dtRect(crRect.left + 24, crRect.top, crRect.right - 24, crRect.top + 24);
	m_objDtCtrl.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | DTS_UPDOWN, dtRect, this, IDC_DTCTRL);
	m_objDtCtrl.SetFormat("yyyy/MM");
	m_objDtCtrl.ModifyStyleEx(WS_EX_CLIENTEDGE | WS_EX_WINDOWEDGE, 0);

	m_objDtCtrl.SetTime(COleDateTime::GetCurrentTime());
	UpdateSetting();
	UpdateInfo();
	UpdateCalender();

	m_uTimerID = SetTimer(1, 1000, NULL);
//	//�����\���̍ہA�G�b�W�����܂��`�悳��Ȃ��̂ŁA��x�T�C�Y0�ɂ���
//	m_objDtCtrl.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_SHOWWINDOW);
//	m_objDtCtrl.SetWindowPos(&wndTop, dtRect.left, dtRect.top, dtRect.Width(), dtRect.Height(), SWP_SHOWWINDOW);
	CLogFile::SaveAppLog("CCalenderWnd::OnCreate End");
	return 0;
}

/**
 * @brif �����֐�
 */
BOOL CCalenderWnd::Create(DWORD dwStyle, const RECT &rect, CWnd *pParent, UINT uID){
	return CWnd::Create(NULL, NULL, dwStyle, rect, pParent, uID);
}

/**
 * @brif CPWikiDoc�̃|�C���^�擾
 */
CPWikiDoc* CCalenderWnd::GetDocument(){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		return NULL;
	}
	CPWikiDoc *pDoc = NULL;
	pDoc = (CPWikiDoc*)GetDoc();
	return pDoc;
}

/**
 * @brif WM_PAINT�̃n���h���֐�
 */
void CCalenderWnd::OnPaint(){
	CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g
	if(m_pBackDC && ::IsWindow(m_objScV.m_hWnd)){
		int nY = m_objScV.GetScrollPos();
		CRect rect;
		GetClientRect(rect);
		if(m_objScV.IsWindowVisible()){
			rect.right -= 16;
		}
		dc.BitBlt(0, 24, rect.Width(), rect.Height(),
				  m_pBackDC, 0, nY, SRCCOPY);
	}
}

/**
 * @brif WM_SIZE�̃n���h���֐�
 */
void CCalenderWnd::OnSize(UINT nType, int cx, int cy){
	CWnd::OnSize(nType, cx, cy);
	SetCtrlPos();
}

/**
 * @brif WM_ERACEBKGND�̃n���h���֐�
 */
BOOL CCalenderWnd::OnEraseBkgnd(CDC* pDC){
	return CWnd::OnEraseBkgnd(pDC);
}

/**
 * @brif �J�����_�[�̍ĕ`��
 */
void CCalenderWnd::UpdateCalender(){

	if(!m_pBackDC){
		return;
	}
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CCalenderWnd::UpdateCalender : pFrm is null");
	}
	CBrush brush;
	brush.CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
	CFont *pOldFont = (CFont*)m_pBackDC->SelectObject(&m_objFont);
	m_pBackDC->FillRect(m_objCalRect, &brush);
	m_pBackDC->SetBkMode(TRANSPARENT);
	CPWikiDoc* pDoc = (CPWikiDoc*)GetDocument();
	COleDateTime objNow = COleDateTime::GetCurrentTime();

	CAnalisysWiki objAna;
	CString strInfo;
	ANAINFO objAnaInfo;
	objAnaInfo.bUseRetFormat = FALSE;
	objAnaInfo.bUseTBLink = FALSE;
	objAnaInfo.bShowAttach = FALSE;
	objAnaInfo.bUseShowConvTime = FALSE;
	strcpy(objAnaInfo.pszBasePath, "");
	objAna.SetAnaSetting(&objAnaInfo);

	for(int y = 0; y < 31; y++){
		int nSx = 0;
		int nEx = m_obj1DaySize.cx - 1;
		int nSy = m_obj1DaySize.cy * y;
		int nEy = m_obj1DaySize.cy * (y + 1);

		int nY = pFrm->m_objNowDate.GetYear();
		int nM = pFrm->m_objNowDate.GetMonth();

		CEventDate *pDate = NULL;
		pDate = pDoc->FindDate(nY, nM, y + 1);
		
		COleDateTime chkDate;
		chkDate.SetDate(nY, nM, y + 1);
		COLORREF crText = RGB(0x00, 0x00, 0x00);
		COLORREF crBkColor = RGB(0xFF, 0xFF, 0xFF);

		CRect rect(nSx, nSy, nEx, nEy);
		CBrush brush;
		BOOL bToDay = FALSE;
		if(chkDate.GetMonth() == nM){
			CString strDetail = "";
			BOOL bHoliday;
			pDoc->FindFixedDate(nY, nM, y + 1, strDetail, bHoliday);

			CString strWeek[] = {"��", "��", "��", "��", "��", "��", "�y"};
			int nDays = chkDate.GetDayOfWeek();

			//�x���ݒ�m�F
			{
				HOLIDAYINFO objIni;
				pFrm->m_objIniFile.GetHolidayInfoIniData(objIni);
				switch(objIni.eType){
				case HT_NONE:
					break;
				case HT_WEEK2HOLIDAY:
					if((nDays == 1) || (nDays == 7)){
						bHoliday = TRUE;
					}
					break;
				case HT_SEL_WEEKDAY:
					if(objIni.bWeekDays[nDays - 1]){
						bHoliday = TRUE;
					}
					break;
				}
			}

			if(bHoliday){
				crText	  = RGB(0xFF, 0x00, 0x00);
				crBkColor = RGB(0xFF, 0xDD, 0xDD);
			}else{
				switch(nDays){
				case 1:
					crText	  = RGB(0xFF, 0x00, 0x00);
					crBkColor = RGB(0xFF, 0xDD, 0xDD);
					break;
				case 7:
					crText	  = RGB(0x00, 0x00, 0xFF);
					crBkColor = RGB(0xDD, 0xDD, 0xFF);
					break;
				default:
					break;
				}
			}
			if((objNow.GetYear() == chkDate.GetYear())
			&& (objNow.GetMonth() == chkDate.GetMonth())
			&& (objNow.GetDay() == chkDate.GetDay())){
				CRect rectToDay(nSx, nSy + 1, nEx, nEy - 1);
				brush.CreateSolidBrush(RGB(0xFF, 0xFF, 0x88));
				m_pBackDC->FillRect(rectToDay, &brush);
			}else{
				brush.CreateSolidBrush(crBkColor);
				m_pBackDC->FillRect(rect, &brush);
			}
			CString strDate;
			strDate.Format("%2d(%s)", y + 1, strWeek[nDays-1]);
			CSize szDt = m_pBackDC->GetTextExtent(strDate);
			m_pBackDC->SetTextColor(crText);
			m_pBackDC->TextOut(2, 2 + m_obj1DaySize.cy * y, strDate);

			m_pBackDC->SetTextColor(RGB(0x00, 0x00, 0x00));
			if(pDate){
				strDetail += pDate->GetDetail();
			}
			CSize sz = m_pBackDC->GetTextExtent(strDetail);
			CRect rect1(2 + szDt.cx + 4, 2 + m_obj1DaySize.cy * y, rect.right, rect.bottom); 

			CString strBase = GetBasePath();
			WIKIINFO objIni;
			pFrm->m_objIniFile.GetWikiInfoIniData(objIni);
			ANAINFO objAnaInfo;
			objAnaInfo.bUseRetFormat = objIni.bUseRet;
			objAnaInfo.bUseTBLink = objIni.bUseTopBtmLnk;
			objAnaInfo.bShowAttach = objIni.bUseShowAttach;
			objAnaInfo.bUseShowConvTime = objIni.bUseShowConvTime;
			strcpy(objAnaInfo.pszBasePath, strBase);

			CString strInfo;
			objAna.SetAnaSetting(&objAnaInfo);
			objAna.SetMimeType(&pFrm->m_objMimeTypes);
			objAna.Analisys(strDetail, strInfo, NULL, TRUE);
			
			m_pBackDC->DrawText(strInfo, rect1, DT_END_ELLIPSIS /*| DT_NOCLIP*/ );
		}
		CPoint arrLine[5];
		CPen objPen;
		objPen.CreatePen(PS_SOLID, 1, RGB(0xCC, 0xCC, 0xCC));
		CPen *pOldPen = m_pBackDC->SelectObject(&objPen);

		//����
		arrLine[0].x = nSx;
		arrLine[0].y = nSy;
		//�E��
		arrLine[1].x = nEx;
		arrLine[1].y = nSy;
		//�E��
		arrLine[2].x = nEx;
		arrLine[2].y = nEy - 1;
		//����
		arrLine[3].x = nSx;
		arrLine[3].y = nEy - 1;
		//����
		arrLine[4].x = nSx;
		arrLine[4].y = nSy;
		m_pBackDC->Polyline(arrLine, 5);
		m_pBackDC->SelectObject(pOldPen);

	}
	m_pBackDC->SelectObject(pOldFont);
	InvalidateRect(NULL);
}

/**
 * @brif WM_LBUTTONDBLCLK�̃n���h���֐�
 */
void CCalenderWnd::OnLButtonDblClk(UINT nFlags, CPoint point){
	CWnd::OnLButtonDblClk(nFlags, point);
}

/**
 * @brif WM_LBUTTONDOWN�̃n���h���֐�
 */
void CCalenderWnd::OnLButtonDown(UINT nFlags, CPoint point){
	CWnd::OnLButtonDown(nFlags, point);
	//�I���������������`�F�b�N
	int nScVPos = m_objScV.GetScrollPos();
	int nRow = (int)((point.y - 24 + nScVPos)/ m_obj1DaySize.cy);
	if((nRow < 0) || (nRow > 31)){
		return;
	}
	//�I����e��\������
	CMainFrame *pFrm = GetMainFrame(this);
	if(!IsWindowSafe(pFrm)){
		return;
	}
	CInfoTabView *pInfoView = pFrm->GetInfoTabView();
	if(!IsWindowSafe((CWnd*)pInfoView)){
		return;
	}
	COleDateTime objDate;
	m_objDtCtrl.GetTime(objDate);
	int nMonth = objDate.GetMonth();
	objDate.SetDate(objDate.GetYear(), objDate.GetMonth(), nRow + 1);
	if(objDate.GetMonth() == nMonth){
		pInfoView->UpdateInfo(&objDate);
	}
}

/**
 * @brif WM_DESTROY�̃n���h���֐�
 */
void CCalenderWnd::OnDestroy() 
{
//	if(m_pBackDC && m_pBackBmp){
//		m_pBackDC->SelectObject(m_pOldBmp);
//		m_pBackBmp->DeleteObject();
//	}
	KillTimer(m_uTimerID);
	if(m_pBackDC){
		delete m_pBackDC;
		m_pBackDC = NULL;
	}
	if(m_pBackBmp){
		delete m_pBackBmp;
		m_pBackBmp = NULL;
	}
	CWnd::OnDestroy();
}

/**
 * @brif WM_HSCROLL�̃n���h���֐�
 */
void CCalenderWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){
	HScrollFunc(nSBCode, nPos, pScrollBar);
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
	CRect rect;
	GetClientRect(rect);
	rect.right -= 16;
	rect.top += 24;
	rect.bottom -= 16;
	InvalidateRect(rect);
}

/**
 * @brif WM_VSCROLL�̃n���h���֐�
 */
void CCalenderWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){
	VScrollFunc(nSBCode, nPos, pScrollBar);
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
	CRect rect;
	GetClientRect(rect);
	rect.right -= 16;
	rect.top += 24;
//	rect.bottom -= 16;
	InvalidateRect(rect);
}

BOOL CCalenderWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	if(zDelta < 0){
		TRACE("DOWN");

	}else if(zDelta > 0){
		TRACE("UP");
	
	}
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

/**
 * @brif ���փ{�^���̃n���h���֐�
 */
void CCalenderWnd::OnNextBtnClick(){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!IsWindowSafe(pFrm)){
		return;
	}

	CPWikiDoc *pDoc = GetDocument();
	if(!pDoc){
		return;
	}
	int nMonth = pFrm->m_objNowDate.GetMonth();
	int nYear = pFrm->m_objNowDate.GetYear();
	nMonth++;
	if(nMonth > 12){
		nMonth = 1;
		nYear++;
	}
	pFrm->m_objNowDate.SetDate(nYear, nMonth, 1);
	pDoc->m_objScDateData.LoadDate(&pFrm->m_objNowDate);
	
	m_objDtCtrl.SetTime(pFrm->m_objNowDate);
	UpdateCalender();
	InvalidateRect(NULL);
}

/**
 * @brif �O�փ{�^���̃n���h���֐�
 */
void CCalenderWnd::OnPrevBtnClick(){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!IsWindowSafe(pFrm)){
		return;
	}

	CPWikiDoc *pDoc = GetDocument();
	if(!pDoc){
		return;
	}

	int nMonth = pFrm->m_objNowDate.GetMonth();
	int nYear = pFrm->m_objNowDate.GetYear();
	nMonth--;
	if(nMonth < 1){
		nMonth = 12;
		nYear--;
	}
	pFrm->m_objNowDate.SetDate(nYear, nMonth, 1);
	pDoc->m_objScDateData.LoadDate(&pFrm->m_objNowDate);

	m_objDtCtrl.SetTime(pFrm->m_objNowDate);
	UpdateCalender();
	InvalidateRect(NULL);
}

/**
 * @brif �����{�^���̃n���h���֐�
 */
void CCalenderWnd::OnTodayBtnClick(){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!IsWindowSafe(pFrm)){
		return;
	}
	CInfoTabView *pInfoView = pFrm->GetInfoTabView();
	if(!IsWindowSafe((CWnd*)pInfoView)){
		return;
	}

	CPWikiDoc *pDoc = GetDocument();
	if(!pDoc){
		return;
	}
	COleDateTime objCur = COleDateTime::GetCurrentTime();
	int nMonth = objCur.GetMonth();
	int nYear = objCur.GetYear();
	int nDay = objCur.GetDay();

	pFrm->m_objNowDate.SetDate(nYear, nMonth, nDay);
	pDoc->m_objScDateData.LoadDate(&pFrm->m_objNowDate);

	m_objDtCtrl.SetTime(pFrm->m_objNowDate);
	UpdateCalender();
	InvalidateRect(NULL);


	COleDateTime objDate;
	m_objDtCtrl.GetTime(objDate);
	objDate.SetDate(nYear, nMonth, nDay);
	pInfoView->UpdateInfo(&objDate);

}

/**
 * @brif CDateTimeCtrl�̓��t�ύX���̃n���h���֐�
 */
void CCalenderWnd::OnDtChange(NMHDR *pNmHdr, HRESULT *pResult){
	LPNMDATETIMECHANGE lpChange = (LPNMDATETIMECHANGE)pNmHdr ;
	*pResult = 0;

	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CCalenderWnd::OnDtChange : pFrm is null");
	}
	m_objDtCtrl.GetTime(pFrm->m_objNowDate);
	UpdateCalender();
	InvalidateRect(NULL);
}


/**
 * @brif WM_TIMER�n���h���֐�
 */
void CCalenderWnd::OnTimer(UINT nIDEvent) {
	COleDateTime objNow = COleDateTime::GetCurrentTime();
	CPWikiDoc *pDoc = GetDocument();
	if((m_objToDay.GetYear() != objNow.GetYear())
	|| (m_objToDay.GetMonth() != objNow.GetMonth())
	|| (m_objToDay.GetDay() != objNow.GetDay())){
		//�ݒ�
		if(pDoc){
			pDoc->m_objScDateData.GetDate(objNow);
			UpdateInfo();
		}
	}
	
	CWnd::OnTimer(nIDEvent);
}

/**
 * @brif ���o�[�̏����X�V����
 */
void CCalenderWnd::UpdateInfo(){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CCalenderWnd::UpdateInfo : pFrm is null");
	}
	CString strInfo = "";
	CPWikiDoc* pDoc = (CPWikiDoc*)GetDocument();
	if(!pDoc){
		return;
	}
	
	DLGINFO objDlgIni;
	memset(&objDlgIni, 0, sizeof(DLGINFO));
	pFrm->m_objIniFile.GetDlgInfoIniData(objDlgIni);

	COleDateTime objDate = COleDateTime::GetCurrentTime();
	if(objDlgIni.bShowSc){
		CEventDate *pDate = pDoc->m_objScDateData.GetDate(objDate);
		if(pDate){
			strInfo = pDate->GetDetail();
		}
	}	

	if(objDlgIni.bShowFix){
		CString strFixData;
		BOOL bHoliday;
		pDoc->FindFixedDate(objDate.GetYear(), objDate.GetMonth(), objDate.GetDay(), strFixData, bHoliday);
		if(!strFixData.IsEmpty()){
			if(!strInfo.IsEmpty()){
				strInfo += " ";
			}
			strInfo += strFixData;
		}
	}

	if(objDlgIni.bShowToDo){
		CString strToDo;
		pDoc->FindToDoDate(objDate.GetYear(), objDate.GetMonth(), objDate.GetDay(), strToDo, FALSE);
		if(!strToDo.IsEmpty()){
			if(!strInfo.IsEmpty()){
				strInfo += " ";
			}
			strInfo += "�yToDo�z";
			strInfo += strToDo;
		}
	}

	pFrm->SetToDayIinfo(strInfo);
}

/**
 * @brif WM_SHOWWINDOW�̃n���h���֐�
 */
void CCalenderWnd::OnShowWindow(BOOL bShow, UINT nStatus){
	UpdateCalender();
	CWnd::OnShowWindow(bShow, nStatus);
}

void CCalenderWnd::UpdateSetting(){
	if(m_pBackDC){
		m_objFont.DeleteObject();

		FONTINFO objFontInfo;
		CMainFrame *pFrm = GetMainFrame(this);
		pFrm->m_objIniFile.GetFontInfoIniData(objFontInfo);

		MakeFont(m_objFont, m_pBackDC, objFontInfo.szCalFontName, objFontInfo.lCalHeight);

		CreateBuffer();
		
		SetCtrlPos();
		UpdateCalender();
		InvalidateRect(NULL);
	}
}

void CCalenderWnd::CreateBuffer(){
	CDC *pDC = GetDC();
	CFont *pOldFont = (CFont*)pDC->SelectObject(&m_objFont);
	CSize szStr = pDC->GetTextExtent("A");
	pDC->SelectObject(pOldFont);
	int nDispWidth = pDC->GetDeviceCaps(HORZRES);
	m_obj1DaySize.cx = nDispWidth;
	m_obj1DaySize.cy = szStr.cy * 2 + 2 * 2;

	int nWidth = m_obj1DaySize.cx;
	int nHeight = m_obj1DaySize.cy * 32;
	m_objCalRect.SetRect(0, 0, nDispWidth, nHeight);
	if(m_pBackDC){
		delete m_pBackDC;
		m_pBackDC = NULL;
	}
	if(m_pBackBmp){
		m_pBackBmp->DeleteObject();
		delete m_pBackBmp;
		m_pBackBmp = NULL;
	}
	m_pBackDC = new CDC();
	if(!m_pBackDC){
		ASSERT(0);
		SendMessage(WM_CLOSE);
	}
	m_pBackBmp = new CBitmap();
	if(!m_pBackBmp){
		ASSERT(0);
		SendMessage(WM_CLOSE);
	}

	m_pBackDC->CreateCompatibleDC(pDC);
	m_pBackBmp->CreateCompatibleBitmap(pDC, nWidth, nHeight);
	m_pOldBmp = m_pBackDC->SelectObject(m_pBackBmp);
	ReleaseDC(pDC);

}

void CCalenderWnd::SetCtrlPos()
{
	if(::IsWindow(m_objDtCtrl.m_hWnd) && ::IsWindow(m_objScV.m_hWnd) && ::IsWindow(m_hWnd)){
		CLogFile::SaveAppLog("CCalenderWnd::OnSize");
		CRect crRect;
		CRect crHRect;
		CRect crVRect;
		GetClientRect(crRect);
		m_objScV.GetClientRect(crVRect);
		m_objScV.SetWindowPos(&wndTop, 
							  crRect.right - 16,	crRect.top + 24, 
							  16,					crRect.Height() - 24, 
							  SWP_SHOWWINDOW);
		SCROLLINFO objScVInfo;
		SCROLLINFO objScHInfo;
		memset(&objScVInfo, 0, sizeof(SCROLLINFO));
		memset(&objScHInfo, 0, sizeof(SCROLLINFO));

		m_objScV.GetScrollInfo( &objScVInfo,SIF_ALL);
		objScVInfo.cbSize = sizeof(SCROLLINFO);
		objScVInfo.fMask = SIF_ALL;
		objScVInfo.nMin = 0;
		objScVInfo.nMax = m_objCalRect.Height() - (crRect.Height() - 24 + 16);
		objScVInfo.nPage = 10;
		objScVInfo.nTrackPos = 1;
		m_objScV.SetScrollInfo(&objScVInfo);
		if(objScVInfo.nMax <= 0){
			m_objScV.ShowWindow(SW_HIDE);
		}else{
			m_objScV.ShowWindow(SW_SHOW);
		}

		CRect objPrevBtnRect(crRect.left, crRect.top, crRect.left + 24, crRect.top + 24);
		CRect objNextBtnRect(crRect.right - 24 * 2, crRect.top, crRect.right - 24, crRect.top + 24);
		CRect crTodayBtn(crRect.right - 24, crRect.top, crRect.right, crRect.top + 24);
		CRect dtRect(crRect.left + 24, crRect.top, crRect.right - 24 * 2, crRect.top + 24);
		m_objNextMonth.SetWindowPos(&wndTop,
									objNextBtnRect.left, objNextBtnRect.top,
									objNextBtnRect.Width(), objNextBtnRect.Height(),
									SWP_SHOWWINDOW);
		m_objPrevMonth.SetWindowPos(&wndTop,
									objPrevBtnRect.left, objPrevBtnRect.top,
									objPrevBtnRect.Width(), objPrevBtnRect.Height(),
									SWP_SHOWWINDOW);
		m_objBtnToDay.SetWindowPos(&wndTop,
									crTodayBtn.left, crTodayBtn.top,
									crTodayBtn.Width(), crTodayBtn.Height(),
									SWP_SHOWWINDOW);
		m_objDtCtrl.SetWindowPos(&wndTop,
								 dtRect.left, dtRect.top,
								 dtRect.Width(), dtRect.Height(),
								 SWP_SHOWWINDOW);
	}
}

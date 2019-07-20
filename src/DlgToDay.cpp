// DlgToDay.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "personalwiki.h"
#include "DlgToDay.h"
#include "PWikiDoc.h"
#include "MainFrm.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgToDay ダイアログ


CDlgToDay::CDlgToDay(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgToDay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgToDay)
	m_strToDay = _T("");
	m_strNextDay = _T("");
	m_strNextNextDay = _T("");
	//}}AFX_DATA_INIT
}


void CDlgToDay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgToDay)
	DDX_Text(pDX, IDC_ED_TODAY, m_strToDay);
	DDX_Text(pDX, IDC_ED_NEXTDAY, m_strNextDay);
	DDX_Text(pDX, IDC_ED_NEXTNEXTDAY, m_strNextNextDay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgToDay, CDialog)
	//{{AFX_MSG_MAP(CDlgToDay)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgToDay メッセージ ハンドラ

BOOL CDlgToDay::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

int CDlgToDay::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void CDlgToDay::UpdateToDay(){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CDlgToDay::UpdateToDay : pFrm is null");
	}
	CPWikiDoc* pDoc = (CPWikiDoc*)GetDoc();
	if(!pDoc){
		CLogFile::SaveFatalLog("CDlgToDay::UpdateToDay : pDoc is null");
		return;
	}
	
	COleDateTime objCur = COleDateTime::GetCurrentTime();
	COleDateTimeSpan spanAdd;
	spanAdd.SetDateTimeSpan(1, 0, 0, 0);

	for(int i = 0; i < 3; i++){
		int nYear = objCur.GetYear();
		int nMonth = objCur.GetMonth();
		int nDay = objCur.GetDay();
		
		CString strDate = "";
		CString strToDo = "";
		CString strSpDay = "";
		CString strFixDay = "";
		CString strInfo = "";
		BOOL bHoliday;

		CEventDate *pDate = pDoc->FindDate(nYear, nMonth, nDay);
		if(pDate){
			strDate = pDate->GetDetail();
		}
		pDoc->FindToDoDate(nYear, nMonth, nDay, strToDo, FALSE);
		if(strToDo.IsEmpty()){
			strToDo = "なし";
		}
		pDoc->FindSpecialDay(nYear, nMonth, nDay, strSpDay);
		pDoc->FindFixedDate(nYear, nMonth, nDay, strFixDay, bHoliday);

		CString strPlan = strDate + strFixDay;
		if(strPlan.IsEmpty()){
			strPlan = "なし";
		}

		switch(i){
		case 0:
			strInfo.Format(	"■予定\r\n"
							"%s\r\n"
							"■今日は何の日？\r\n"
							"%s\r\n"
							"■ToDo\r\n"
							"%s\r\n",
							strPlan,
							strSpDay,
							strToDo);
			m_strToDay = strInfo;
			break;
		case 1:
			strInfo.Format(	"■予定\r\n"
							"%s\r\n"
							"■ToDo\r\n"
							"%s\r\n",
							strPlan,
							strToDo);
			m_strNextDay = strInfo;
			break;
		case 2:
			strInfo.Format(	"■予定\r\n"
							"%s\r\n"
							"■ToDo\r\n"
							"%s\r\n",
							strPlan,
							strToDo);
			m_strNextNextDay = strInfo;
			break;
		}
		objCur += spanAdd;
	}
	UpdateData(FALSE);
}

BOOL CDlgToDay::PreTranslateMessage(MSG* pMsg){
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgToDay::OnShowWindow(BOOL bShow, UINT nStatus){
	CDialog::OnShowWindow(bShow, nStatus);
/*	
	CDC *pDC = GetDC();
	int nHorz = pDC->GetDeviceCaps(HORZRES);
	int nVert = pDC->GetDeviceCaps(VERTRES);

	CRect clRect;
	GetWindowRect(clRect);

	int nSx = (nHorz / 2) - (clRect.Width() / 2);
	int nSy = (nVert / 2) - (clRect.Height() / 2);

	SetWindowPos(&wndTop, nSx, nSy, clRect.Width(), clRect.Height(), SWP_SHOWWINDOW | SWP_NOSIZE);
*/
}

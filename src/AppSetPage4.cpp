// AppSetPage4.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "AppSetPage4.h"
#include "MainFrm.h"
#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage4 ダイアログ


CAppSetPage4::CAppSetPage4(CWnd* pParent /*=NULL*/)
	: CDialog(CAppSetPage4::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAppSetPage4)
	m_strSample = _T("");
	//}}AFX_DATA_INIT
}


void CAppSetPage4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppSetPage4)
	DDX_Control(pDX, IDC_SET_LIST, m_objSceneList);
	DDX_Control(pDX, IDC_FONT_SIZE_LIST, m_objSizeList);
	DDX_Control(pDX, IDC_FONT_NAME_LIST, m_objNameList);
	DDX_Control(pDX, IDC_ED_SAMPLE, m_objSample);
	DDX_Text(pDX, IDC_ED_SAMPLE, m_strSample);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppSetPage4, CDialog)
	//{{AFX_MSG_MAP(CAppSetPage4)
	ON_WM_DESTROY()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_FONT_SIZE_LIST, OnItemchangedFontSizeList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_FONT_NAME_LIST, OnItemchangedFontNameList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_SET_LIST, OnItemchangedSetList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppSetPage4 メッセージ ハンドラ

BOOL CAppSetPage4::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_objSceneList.InsertColumn(0, "場所");
	m_objSizeList.InsertColumn(0, "名前");
	m_objNameList.InsertColumn(0, "サイズ");

	m_objSceneList.InsertItem(0, "エディタ", 0);
	m_objSceneList.InsertItem(1, "カレンダー", 0);
	m_objSceneList.InsertItem(2, "ToDo", 0);
	m_objSceneList.InsertItem(3, "その他", 0);

	m_strSample = "0123456789 ABCD abcd\r\n"
				  "あいうえお　アイウエオ";
	UpdateData(FALSE);

	LOGFONT lFont;
	memset(&lFont, 0, sizeof(LOGFONT));
	lFont.lfFaceName[0] = '\0';
//	lFont.lfCharSet = DEFAULT_CHARSET;
	lFont.lfCharSet = SHIFTJIS_CHARSET;

	CDC *pDC = GetDC();
	::EnumFontFamiliesEx(pDC->GetSafeHdc(), &lFont, EnumFontFamExProc, (LPARAM)&m_arrFontInfo, 0);

	int nSize = m_arrFontInfo.GetSize();
	for(int i = 0; i < nSize; i++){
		PFONT_DTL_INFO pInfo = m_arrFontInfo.GetAt(i);
		m_objNameList.InsertItem(i, pInfo->lFont.lfFaceName, 0);
	}

	CMainFrame *pFrm = GetMainFrame(this);
	pFrm->m_objIniFile.GetFontInfoIniData(m_objFontInfo);
	
	m_objSizeList.InsertItem(0, "6", 0);
	m_objSizeList.InsertItem(1, "8", 0);
	m_objSizeList.InsertItem(2, "9", 0);
	m_objSizeList.InsertItem(3, "10", 0);
	m_objSizeList.InsertItem(4, "11", 0);
	m_objSizeList.InsertItem(5, "12", 0);
	m_objSizeList.InsertItem(6, "14", 0);
	m_objSizeList.InsertItem(7, "16", 0);
	m_objSizeList.InsertItem(8, "18", 0);
	m_objSizeList.InsertItem(9, "20", 0);

	m_objSceneList.SetItem(0, 0, LVIF_STATE, NULL, 0, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED, NULL);

	int nFontIndex = SelectFontName(m_objFontInfo.szEditFontName);
	int nSizeIndex = SelectFontSize(m_objFontInfo.lEditHeight);

	UpdateFontInfo(nFontIndex, nSizeIndex);

	m_objSceneList.SetColumnWidth(0, LVSCW_AUTOSIZE );
	m_objNameList.SetColumnWidth(0, LVSCW_AUTOSIZE );
	m_objSizeList.SetColumnWidth(0, LVSCW_AUTOSIZE );

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

int CALLBACK CAppSetPage4::EnumFontFamExProc( const LOGFONT *lpelfe, const TEXTMETRIC *lpntme, DWORD FontType, LPARAM lParam ){
	CArray<PFONT_DTL_INFO, PFONT_DTL_INFO>* pArrInfo = (CArray<PFONT_DTL_INFO, PFONT_DTL_INFO>*)lParam;
	PFONT_DTL_INFO pFontInfo = new FONT_DTL_INFO;
	memset(pFontInfo, 0, sizeof(FONT_DTL_INFO));
	pFontInfo->nType = FontType;
	memcpy(&pFontInfo->lFont, lpelfe, sizeof(LOGFONT));

	TEXTMETRIC *pTextMetric = NULL;
	NEWTEXTMETRICEX *pNewTextMetric = NULL;
	if(FontType & TRUETYPE_FONTTYPE){
		//True Type
		memcpy(&pFontInfo->ojbNewTextMatrix, (NEWTEXTMETRICEX*)lpntme, sizeof(NEWTEXTMETRICEX));
	}else{
		memcpy(&pFontInfo->objTextMatrix, (TEXTMETRIC*)lpntme, sizeof(TEXTMETRIC));
	}

	//設定可能なフォントサイズ
	pArrInfo->Add(pFontInfo);
	return 1;
}

void CAppSetPage4::OnDestroy(){
	CDialog::OnDestroy();
	
	while(m_arrFontInfo.GetSize()){
		PFONT_DTL_INFO pFontInfo = m_arrFontInfo.GetAt(0);
		if(pFontInfo){
			delete pFontInfo;
		}
		m_arrFontInfo.RemoveAt(0);
	}
	
}

BOOL CAppSetPage4::UpdateInfo(){
	//UpdateData(TRUE);
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CAppSetPage4::UpdateInfo : pFrm is null");
	}
	pFrm->m_objIniFile.SetFontInfoIniData(&m_objFontInfo);
	
	return TRUE;
}

BOOL CAppSetPage4::PreTranslateMessage(MSG* pMsg) {
	if(DlgKeyCancel(m_hWnd, pMsg)){
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CAppSetPage4::OnItemchangedSetList(NMHDR* pNMHDR, LRESULT* pResult){
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
	
	if((pNMListView->uNewState != pNMListView->uOldState) && (pNMListView->uNewState & LVIS_SELECTED == LVIS_SELECTED)){
		//フォントサイズ一覧変更
		CString strFontName = "ＭＳ ゴシック";
		CString strFontSize = "10";
		int nSelIndex = pNMListView->iItem;
		switch(nSelIndex){
		case 0:
			strFontName = m_objFontInfo.szEditFontName;
			strFontSize.Format("%d", m_objFontInfo.lEditHeight);
			break;
		case 1:
			strFontName = m_objFontInfo.szCalFontName;
			strFontSize.Format("%d", m_objFontInfo.lCalHeight);
			break;
		case 2:
			strFontName = m_objFontInfo.szToDoFontName;
			strFontSize.Format("%d", m_objFontInfo.lToDoHeight);
			break;
		case 3:
			strFontName = m_objFontInfo.szEtcFontName;
			strFontSize.Format("%d", m_objFontInfo.lEtcHeight);
			break;
		}
		int nFontIndex = SelectFontName(strFontName);
		int nSizeIndex = SelectFontSize(atoi(strFontSize));
		UpdateFontInfo(nFontIndex, nSizeIndex);
	}
}

void CAppSetPage4::OnItemchangedFontNameList(NMHDR* pNMHDR, LRESULT* pResult){
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
	if((pNMListView->uNewState != pNMListView->uOldState) && (pNMListView->uNewState & LVIS_SELECTED == LVIS_SELECTED)){
		//フォントサイズ一覧変更
		UpdateFontInfo();
	}
}

void CAppSetPage4::OnItemchangedFontSizeList(NMHDR* pNMHDR, LRESULT* pResult){
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;

	if((pNMListView->uNewState != pNMListView->uOldState) && (pNMListView->uNewState & LVIS_SELECTED == LVIS_SELECTED)){
		UpdateFontInfo();
	}
}

void CAppSetPage4::UpdateFontInfo(int nFontIndex, int nSizeIndex){
	if(nFontIndex < 0){
		nFontIndex = m_objNameList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	}

	if(nSizeIndex < 0){
		nSizeIndex = m_objSizeList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	}

	int nSceneIndex = m_objSceneList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	
	CString strFont = m_objNameList.GetItemText(nFontIndex, 0);
	CString strSize = m_objSizeList.GetItemText(nSizeIndex, 0);
	
	switch(nSceneIndex){
	case 0:
		strcpy(m_objFontInfo.szEditFontName, strFont);
		m_objFontInfo.lEditHeight = atoi(strSize);
		break;
	case 1:
		strcpy(m_objFontInfo.szCalFontName, strFont);
		m_objFontInfo.lCalHeight = atoi(strSize);
		break;
	case 2:
		strcpy(m_objFontInfo.szToDoFontName, strFont);
		m_objFontInfo.lToDoHeight = atoi(strSize);
		break;
	case 3:
		strcpy(m_objFontInfo.szEtcFontName, strFont);
		m_objFontInfo.lEtcHeight = atoi(strSize);
		break;
	}
	
	CDC *pDC = GetDC();
	int nSize = 10;
	if(nSizeIndex != -1){
		CString strSize;
		strSize = m_objSizeList.GetItemText(nSizeIndex, 0);
		nSize = atoi(strSize);
	}
/*
	int nSizeX = -MulDiv(nSize, pDC->GetDeviceCaps(LOGPIXELSX), 72);
	int nSizeY = -MulDiv(nSize, pDC->GetDeviceCaps(LOGPIXELSY), 72);

	if(nFontIndex != -1){
		m_objSmpFont.DeleteObject();
		PFONT_DTL_INFO pInfo = m_arrFontInfo.GetAt(nFontIndex);
		memset(&m_objSmpLFont, 0, sizeof(LOGFONT));
		memcpy(&m_objSmpLFont, &pInfo->lFont, sizeof(LOGFONT));
		m_objSmpLFont.lfHeight = nSizeY;
//		m_objSmpLFont.lfWidth = nSizeX;
		m_objSmpLFont.lfWidth = 0;
		m_objSmpLFont.lfCharSet = DEFAULT_CHARSET;
		m_objSmpFont.CreateFontIndirect(&m_objSmpLFont);
	}
*/
	MakeFont(m_objSmpFont, pDC, strFont, nSize);
	m_objSample.SetFont(&m_objSmpFont);
}


int CAppSetPage4::SelectFontName(LPCTSTR pszFontName){
	if(!pszFontName){
		return -1;
	}

	int nCnt = m_objNameList.GetItemCount();
	CString strName;
	for(int i = 0; i < nCnt; i++){
		strName = m_objNameList.GetItemText(i, 0);
		if(!strName.Compare(pszFontName)){
			m_objNameList.SetItem(i, 0, LVIF_STATE, NULL, 0, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED, NULL);
			return i;
		}
	}
	return -1;
}

int CAppSetPage4::SelectFontSize(int nSize){
	int nCnt = m_objSizeList.GetItemCount();
	CString strSize;
	for(int i = 0; i < nCnt; i++){
		strSize = m_objSizeList.GetItemText(i, 0);
		if(atoi(strSize) == nSize){
			m_objSizeList.SetItem(i, 0, LVIF_STATE, NULL, 0, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED, NULL);
			return i;
		}
	}
	return -1;
}

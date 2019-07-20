// BinderWnd.cpp: CBinderWnd クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BinderPlugin.h"
#include "BinderWnd.h"
#include "devlib.h"
#include "DebugSupport.h"
#include "LogFile.h"
#include "InpBinderNameDlg.h"
#include "StringEncode.h"
#include "BregExpRap.h"
#include <afxinet.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

typedef enum GETRSSRESULT{
	DONT_GET_SERVERNAME = 0,
	DONT_GET_CONNECTION,
	DONT_OPEN_REQUEST,
	DONT_SET_USERID,
	DONT_SET_PASSWORD,
	DONT_SEND_REQUEST,
	FAILD_REQUEST_STATUS,
};

/**
 * @brif
 */
int CALLBACK CBinderWnd::CompareBinder(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){
	CBinder *pBinder1 = (CBinder*)lParam1;
	CBinder *pBinder2 = (CBinder*)lParam2;

	return pBinder1->m_strName.CompareNoCase(pBinder2->m_strName);
}

/**
 * @brif
 */
int CALLBACK CBinderWnd::CompareBinderItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){
	PBINDERITEM pBinder1 = (PBINDERITEM)lParam1;
	PBINDERITEM pBinder2 = (PBINDERITEM)lParam2;
	CString strName1 = pBinder1->pszName;
	CString strName2 = pBinder2->pszName;
	return strName1.CompareNoCase(strName2);
}


//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////
/**
 * @brif
 */
CBinderWnd::CBinderWnd(){

}

/**
 * @brif
 */
CBinderWnd::~CBinderWnd(){

}

BEGIN_MESSAGE_MAP(CBinderWnd, CWnd)
	//{{AFX_MSG_MAP(CBinderWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_DROPFILES()
	ON_COMMAND(IDM_ADDBINDER, OnAddbinder)
	ON_COMMAND(IDM_ADDFILE, OnAddfile)
	ON_COMMAND(IDM_CLIPCOPY, OnClipcopy)
	ON_COMMAND(IDM_FILEDEL, OnFiledel)
	ON_UPDATE_COMMAND_UI(IDM_ADDBINDER, OnUpdateAddbinder)
	ON_UPDATE_COMMAND_UI(IDM_ADDFILE, OnUpdateAddfile)
	ON_UPDATE_COMMAND_UI(IDM_CLIPCOPY, OnUpdateClipcopy)
	ON_UPDATE_COMMAND_UI(IDM_FILEDEL, OnUpdateFiledel)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_DBLCLK, IDC_TREE, OnTreeDBClick)
//	ON_NOTIFY(NM_CLICK, IDC_TREE, OnTreeClick)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchanged)
#if defined(USE_TOOLTIP_BINDER)
    ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotifyEx)
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipNotifyEx)
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipNotifyEx)
#endif

	ON_REGISTERED_MESSAGE(WM_ANALISYS_DROP, OnAnalisys)

	//IDC_TREE
END_MESSAGE_MAP()


/**
 * @brif
 */
BOOL CBinderWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID){
	return CWnd::Create(NULL, NULL, dwStyle, rect, pParentWnd, nID);
}

/**
 * @brif
 */
int CBinderWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//アクセラレータの読み込み
	m_hAccel = ::LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_ACCELERATOR1));


	//ツールバー生成
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | /*WS_BORDER |*/ CBRS_TOOLTIPS | CBRS_SIZE_FIXED | CBRS_FLYBY /*| CBRS_BORDER_BOTTOM*/;
	if(!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle, CRect(0, 0, 0, 0), IDR_TOOLBAR)
	|| !m_wndToolBar.LoadToolBar(IDR_TOOLBAR)){
		CLogFile::SaveAppLog("ツールバーの生成に失敗");
	}else{
		TBIMGINFO objTbInfo;
		memset(&objTbInfo, 0, sizeof(TBIMGINFO));
		objTbInfo.crMask = RGB(0, 128, 128);
		objTbInfo.nBtnHeight = 16;
		objTbInfo.nBtnWidth = 16;
		objTbInfo.nButtons = 6;
		objTbInfo.nColorBit = 8;
		objTbInfo.pToolBar = &m_wndToolBar;
		objTbInfo.uID = IDB_TOOLBAR256;
		SetToolbarImg(&objTbInfo);

		CSize szToolBar = m_wndToolBar.CalcFixedLayout(FALSE,TRUE);
		m_wndToolBar.MoveWindow(0, 0, szToolBar.cx, szToolBar.cy);
		m_objTbRect.SetRect(0, 0, szToolBar.cx, szToolBar.cy);

		CRect rect;
		GetClientRect(rect);
#if defined(USE_TOOLTIP_BINDER)
		m_objToolTip.Create(this);
#endif

		UINT uIDs[] = { IDM_ADDBINDER, IDM_ADDFILE, IDM_FILEDEL};
		int nSize = sizeof(uIDs) / sizeof(UINT);

		for(int i = 0; i < nSize; i++){
			m_wndToolBar.GetToolBarCtrl().GetItemRect(i, rect);
#if defined(USE_TOOLTIP_BINDER)
			m_objToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rect, uIDs[i]);
#endif
		}
#if defined(USE_TOOLTIP_BINDER)
		m_objToolTip.SetDelayTime(TTDT_AUTOPOP, 9999);
		m_objToolTip.SetDelayTime(TTDT_INITIAL, 100);
		m_objToolTip.Activate(TRUE);
		m_wndToolBar.GetToolBarCtrl().SetToolTips(&m_objToolTip);
#endif
	}

	m_objDropTarget.SetBinderWnd(this);

	char pszPath[MAX_PATH];
	memset(pszPath, 0, MAX_PATH);
	::GetModuleFileName(NULL, pszPath, MAX_PATH);

	CRect rect;
	GetClientRect(rect);
	m_objTree.Create(WS_CHILD | WS_BORDER, rect, this, 1);

	char pszDrv[MAX_PATH];
	char pszDir[MAX_PATH];
	char pszName[MAX_PATH];
	char pszExt[MAX_PATH];
	_splitpath(pszPath, pszDrv, pszDir, pszName, pszExt);
	m_strAppPath.Format("%s%s", pszDrv, pszDir);
	m_strIniFile.Format("%s\\plugins\\BinderPlugin.ini", m_strAppPath);

	LoadIni();

	CBinder *pBinder;

	m_objTreeBmp.LoadBitmap(IDB_TREEICON);
	m_arrImg.Create(16, 16, ILC_COLOR16 | ILC_MASK, 10, 1);
	m_arrImg.Add(&m_objTreeBmp, RGB(0xFF, 0xFF, 0xFF));
	m_objTree.SetImageList(&m_arrImg, TVSIL_NORMAL);
	m_hRoot			= m_objTree.InsertItem( "バインダー", IC_ROOT, IC_ROOT);
	m_hHtml			= m_objTree.InsertItem( "HTMLバインダー", IC_CLIP, IC_CLIP, m_hRoot);

	pBinder = new CBinder();
	pBinder->m_strName	= "HTMLバインダー";
	m_objTree.SetItemData(m_hHtml, (LPARAM)pBinder);

	m_objTree.ModifyStyle(0, TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | WS_BORDER);
	m_objTree.ModifyStyleEx(WS_EX_CLIENTEDGE | WS_EX_WINDOWEDGE, 0);
	ModifyStyleEx(0, WS_EX_ACCEPTFILES);

	//データを読み込む
	CString strDataPath;
	strDataPath.Format("%s\\plugins\\BinderPlugin\\*.fbd", m_strAppPath);
	WIN32_FIND_DATA wfd;
	HANDLE hRet = NULL;
	BOOL bFirst = TRUE;
	char szDrv[MAX_PATH];
	char szDir[MAX_PATH];
	char szName[MAX_PATH];
	char szExt[MAX_PATH];
	//ASSERT(0);
	while(TRUE){
		memset(szDrv, 0, MAX_PATH);
		memset(szDir, 0, MAX_PATH);
		memset(szName, 0, MAX_PATH);
		memset(szExt, 0, MAX_PATH);
		if(bFirst){
			hRet = ::FindFirstFile(strDataPath, &wfd);
			if(hRet == INVALID_HANDLE_VALUE){
				break;
			}
			bFirst = FALSE;
			
		}else{
			if(!::FindNextFile(hRet, &wfd)){
				break;
			}
		}

		_splitpath(wfd.cFileName, szDrv, szDir, szName, szExt);
		if(!strcmp(szName, "HTMLバインダー")){
			pBinder = (CBinder*)m_objTree.GetItemData(m_hHtml);
			LoadDataFile(wfd.cFileName, pBinder, m_hHtml);
		}else{
			LoadDataFile(wfd.cFileName);
		}
	}
	m_objTree.Expand(m_hRoot, TVE_EXPAND);
	::FindClose(hRet);

	OleInitialize(NULL);
	if( !m_objDropTarget.Register( this ) ){     // ドロップターゲットへの登録
//	if( !m_objDropTarget.Register( &m_objTree ) ){     // ドロップターゲットへの登録
		CString strMsg;
		
		DWORD dwErr = GetLastError();
		strMsg.Format("D&D不可\n%s", CDebugSupport::GetLastErrorText(dwErr));
		CLogFile::SaveAppLog(strMsg);

		strMsg.Format("ドラッグ & ドロップによるHTMLの取り込みは使用できません。(%d)", dwErr);
		AfxMessageBox(strMsg);
	}
	EnableToolTips();
	return 0;
}

#if defined(USE_TOOLTIP_BINDER)
BOOL CBinderWnd::OnToolTipNotifyEx(UINT id, NMHDR *pTTTStruct, LRESULT *pResult) {
	return OnToolTioNotifyFunc(pTTTStruct, pResult);
}
void CBinderWnd::OnToolTipNotify(NMHDR *pTTTStruct, LRESULT *pResult) {
	OnToolTioNotifyFunc(pTTTStruct, pResult);
}
void CBinderWnd::GetToolTipText(NMHDR *pTTTStruct, CString &strTipText){
	TOOLTIPTEXT *pInfo = (TOOLTIPTEXT*)pTTTStruct;

	switch(pTTTStruct->idFrom){
	case IDM_ADDBINDER:
		strTipText = "バインダーを追加します";
		break;
	case IDM_ADDFILE:
		strTipText = "ファイルを追加します";
		break;
	case IDM_FILEDEL:
		strTipText = "ファイルを削除します";
		break;
	}
}
int CBinderWnd::OnToolHitTest(CPoint point, TOOLINFO* pTI ) const{
//	CRect rect;
//	GetWindowRect(rect);
//	pTI->hwnd		= m_hWnd;
//	pTI->uId		= CDlgInfo::IDD;
//	pTI->lpszText	= LPSTR_TEXTCALLBACK;
//	pTI->rect		= rect;
//	pTI->uFlags		= TTF_NOTBUTTON | TTF_CENTERTIP | TTF_ALWAYSTIP /*| TTF_TRACK*/;
//	pTI->hinst		= AfxGetInstanceHandle();
	return pTI->uId;
}
#endif

/**
 * @brif
 */
void CBinderWnd::LoadIni(){
	char szPath[MAX_PATH];
	memset(szPath, 0, MAX_PATH);
	GetInifileString("BinderPlugin", "RelayTool", "", szPath, MAX_PATH, m_strIniFile);
	m_bIsSecure = GetInifileInt("BinderPlugin", "IsSecure", 1, m_strIniFile);
	m_strToolPath = szPath;
}

/**
 * @brif
 */
void CBinderWnd::SaveIni(){
	WriteInifileString("BinderPlugin", "RelayTool", m_strToolPath, m_strIniFile);
	WriteInifileInt("BinderPlugin", "IsSecure", m_bIsSecure, m_strIniFile);
}

/**
 * @brif
 */
LPCTSTR CBinderWnd::GetFindItem(LPCTSTR pszKey, HTREEITEM hItem){
	HTREEITEM  hChItem = m_objTree.GetChildItem(hItem);
	CString strText;
	while(hChItem){
		strText = m_objTree.GetItemText(hChItem);
		PBINDERITEM pItem = (PBINDERITEM)m_objTree.GetItemData(hChItem);
		if(!strText.Compare(pszKey)){
			//フルパスを返す。
			return pItem->pszFilePath;
		}
		
		if(m_objTree.ItemHasChildren(hChItem)){
			LPCTSTR pszText = GetFindItem(pszKey, hChItem);
			if(pszText){
				return pszText;
			}
		}
		hChItem = m_objTree.GetNextItem(hChItem, TVGN_NEXT);
	}
	return NULL;
}

/**
 * @brif
 */
void CBinderWnd::UpdateTree(){
	CBinder *pBinder = GetActiveBinder();
	//ファイルの一覧を更新する
	if(!pBinder){
		return;
	}
	
	//バインダーを格納するアイテムの検索
	HTREEITEM hParent = m_objTree.GetChildItem(m_hRoot);
	while(hParent){
		if(pBinder == (CBinder*)m_objTree.GetItemData(hParent)){
			break;
		}
		hParent = m_objTree.GetNextSiblingItem(hParent);
	}

	if(hParent == NULL){
		return;
	}
	while(m_objTree.GetChildItem(hParent)){
		m_objTree.DeleteItem(m_objTree.GetChildItem(hParent));
	}

	int nCnt = 0;
	PBINDERITEM pItem = NULL;
	HTREEITEM	hIns  = NULL;
/*
	char szDrv[MAX_PATH];
	char szDir[MAX_PATH];
	char szFile[MAX_PATH];
	char szExt[MAX_PATH];
	POSITION pos;
*/
	//GetBinderItem関数で取得できる情報がNULLになるまで
	while(pItem = pBinder->GetBinderItem(nCnt)){
/*
		memset(szDrv, 0, MAX_PATH);
		memset(szDir, 0, MAX_PATH);
		memset(szFile, 0, MAX_PATH);
		memset(szExt, 0, MAX_PATH);
		_splitpath(pItem->pszFilePath, szDrv, szDir, szFile, szExt);
		pos = m_arrExtList.Find(szExt, NULL);
		int nIndex = 0;
		int nImg = 0;
		if(pos){
			while(m_arrExtList.GetAt(pos).CompareNoCase(szExt)){
				nIndex++;
			}
			nImg = m_arrIconIndex.GetAt(nIndex);
		}else{
			HICON hIcon = pBinder->GetIcon(pItem);
			nImg = m_arrImg.Add(hIcon);
			m_arrIconIndex.Add(nImg);
			m_arrIcon.Add(hIcon);
			m_arrExtList.AddTail(szExt);

		}
*/
		int nImg = GetItemIcon(pBinder, pItem);
		hIns = m_objTree.InsertItem(pItem->pszName, nImg, nImg, hParent);
		m_objTree.SetItemData(hIns, (LPARAM)pItem);
		nCnt++;
	}
	InvalidateRect(NULL);

}

/**
 * @brif
 */
//BOOL CBinderWnd::AnalyzeDropHTML(COleDataObject *pObject){
BOOL CBinderWnd::AnalyzeDropHTML(LPCTSTR pszText){
	CString strData;
	CString strSaveDir;
	strSaveDir.Format("%s\\plugins\\BinderPlugin\\snap", m_strAppPath);
	strSaveDir.Replace("\\\\", "\\");
	if(!::CreateDir(strSaveDir, NULL)){
		return FALSE;
	}
	CStringEncode se;
	char* pszEncText = NULL;
	int nCode = se.CheckCode((char*)pszText);
	switch(nCode){
	case CStringEncode::JIS:
		strData = CStringEncode::jis2sjis((char*)pszText);
		break;
	case CStringEncode::EUC:
		strData = CStringEncode::euc2sjis((char*)pszText);
		break;
	case CStringEncode::UTF8:
		strData = CStringEncode::utf82sjis((char*)pszText);
		break;
	case CStringEncode::SJIS:
		strData = pszText;
		break;
	default:
//		strData = pszText;
//		break;
		AfxMessageBox("文字コードが特定できません。");
		return FALSE;
	}
	if(pszEncText){
		se.ReleaseBuff(pszEncText);
	}

	try{
		CBregExpRap objBregExp;
		CString strPattern;
		
		strPattern="s/^((Version|StartHTML|EndHTML|StartFragment|EndFragment|StartSelection|EndSelection):[^\\r\\n]*\\r\\n)//g";
		while(objBregExp.ReplaceText(strData, strData, strPattern)){
			//ループのみ
		}

		if(m_bIsSecure){
			//JavaScriptやActoiveXの除去
			//<script>または</script>をIEで無意味なタグとして解釈されるようにする
			strPattern="s/<([\\/]?)(script|object)/<$1?/ig";
			while(objBregExp.ReplaceText(strData, strData, strPattern)){
				//ループのみ
			}
		}

		//SourceURL
		CString strSrcURL = "";
#if 1
		strPattern="/SourceURL:([^\\r\\n]*)/";
		if(!objBregExp.GetFindText(strData, strSrcURL, strPattern)){
			//失敗
		}else{
			strSrcURL.Replace("SourceURL:", "");

			//URLパスから保存用にサーバー名のみ取得する
			CString strSaveSubDir = strSrcURL;
			if(!strSaveSubDir.IsEmpty()){
				int pos = strSaveSubDir.Find("://");
				if(pos != -1){
					strSaveSubDir = strSaveSubDir.Mid(pos + 3);
					pos = strSaveSubDir.Find("/");
					if(pos != -1){
						strSaveSubDir = strSaveSubDir.Left(pos);
						CString makeDir = strSaveDir + "\\" + strSaveSubDir;
						if(!::CreateDir(makeDir, NULL)){
							return FALSE;
						}
						strSaveDir = makeDir;
					}
				}
			}
		}

#else
		strPattern="s/(SourceURL:)([^\\r\\n]*)((.*[\\r\\n]*)*)/$2/g";
		if(!objBregExp.ReplaceText(strData, strSrcURL, strPattern)){
			//失敗
		}
#endif

		strPattern="s/(^SourceURL:.*)//g";
		if(!objBregExp.ReplaceText(strData, strData, strPattern)){
			//失敗
		}

		strPattern="s/(\\/|\\\\)[^\\/\\.\\\\]*\\..[^\\r\\n]*//g";
		if(!objBregExp.ReplaceText(strSrcURL, strSrcURL, strPattern)){
			//失敗
		}

		//Body
		strData.Replace("<!--StartFragment-->", "");
		strData.Replace("<!--EndFragment-->", "");

		strPattern="s/(^SourceURL:.*)//g";

		strSrcURL.Replace("\\", "\\\\");
		strSrcURL.Replace("/", "\\/");
		strSrcURL.Replace("?", "\\?");
		strSrcURL.Replace("*", "\\*");
		strSrcURL.Replace(".", "\\.");

	//	strPattern.Format("s/(href=\\\"?|src=\\\"?)(\\/|\\.\\/|..\\/)(\\\"?)/$1%s$2$3/g", strSrcURL);
		
		strPattern.Format("s/((href|src)=\\\"?)(\\/|\\.\\/|\\.\\.\\/)([^\\\" \\t]*)/$1%s$3$4/g", strSrcURL);
		objBregExp.ReplaceText(strData, strData, strPattern);


		//タイトル取得
		CString strTitle = "";
#if 1
		strPattern="/<[Tt][Ii][Tt][Ll][Ee]>(.*[\\r\\n]*.*[\\r\\n]*)<\\/[Tt][Ii][Tt][Ll][Ee]>/$1/mgk";
		if(!objBregExp.ReplaceText(strData, strTitle, strPattern)){
			//失敗
			strTitle = "snap";
		}else{
			strPattern="s/[<>,:;\\\\\\r\\n\\/\\.\\*\\?\\\"\\|]/ /gk";
			objBregExp.ReplaceText(strTitle, strTitle, strPattern);
		}

#else
		strPattern = "s/((.*\\r\\n)*.*<[Tt][Ii][Tt][Ll][Ee]>)(.+)(<\\/[Tt][Ii][Tt][Ll][Ee]>(.*[\\r\\n]*)*)/$3/g";
		if(!objBregExp.ReplaceText(strData, strTitle, strPattern)){
			//失敗
			strTitle = "snap";
		}
#endif
		strTitle.Replace("\t", "");
		strTitle.Replace("　", " ");
		strTitle.TrimLeft();
		strTitle.TrimRight();
		if(strTitle.IsEmpty()){
			strTitle = "snap";
		}

		//イメージの取得
#if 1
		CString arrTag[]  = {"<img", "<link"};
		CString arrAttr[] = {"src", "href"};
		CString strTag;
		CString strAttr;
		int nDLSize = sizeof(arrTag) / sizeof(CString);
		for(int i = 0; i < nDLSize; i++){
			CString strNewData = "";
			CString strChkData;
			int pos = 0;
			strTag = arrTag[i];
			strAttr = arrAttr[i];
			while(TRUE){
				strChkData = strData;
				strChkData.MakeLower();
				pos = strChkData.Find(strTag);
				if(pos == -1){
					strNewData += strData;
					strData = strNewData;
					break;
				}
				strNewData += strData.Left(pos + strlen(strTag));
				strData = strData.Mid(pos + strlen(strTag));
				strChkData = strData;
				strChkData.MakeLower();

				if((i == 1) || (i == 2)){
					//linkタグの場合、typeも調べる
					int nTypePos = strChkData.Find("type");
					int endPos = strChkData.Find(">");
					if((nTypePos == -1) || (endPos < nTypePos)){
						//ダウンロード対象外かつ、セキュリティのためにリンクを無効にする必要がある
						int nPos = strChkData.Find("href");
						int nPos2 = strChkData.Find("=", nPos);
						int nEnd = strChkData.Find(" ", nPos2);
						strNewData += strData.Left(nPos);
						strData = strData.Mid(nEnd);
						strChkData = strData;
						strChkData.MakeLower();
						continue;
					}
					
					
					int nSepPos = strChkData.Find("=", nTypePos + strlen("type"));
					if(nSepPos == -1){
						continue;
					}

					//"で区切られているかをチェックする
					CString strType = "";
					int srcStartPos = nSepPos;
					int srcEndPos = -1;
					//スペースを探す
					srcEndPos = strData.Find(" ", srcStartPos + 1);
					if(srcEndPos != -1){
						//パスを取得する
						strType = strData.Mid(srcStartPos + 1, srcEndPos - srcStartPos);
					}
					strType.TrimLeft();
					strType.TrimRight();
					strType.Replace("\"", "");

					if(strType.CompareNoCase("image/x-icon")
					&& strType.CompareNoCase("text/css")){
						//strNewData += strType;
						continue;
					}
				}	


				int srcPos = strChkData.Find(strAttr);
				int endPos = strChkData.Find(">");

				CString strSrc = "";
				if(endPos > srcPos){
					strNewData += strData.Left(srcPos + strlen(strAttr));
					strData = strData.Mid(srcPos + strlen(strAttr));

					//=を探す
					int nSepPos = strData.Find("=");
					if(nSepPos == -1){
						continue;
					}

					strNewData += strData.Left(nSepPos + 1);
					strData = strData.Mid(nSepPos + 1);
					strChkData = strData;
					strChkData.MakeLower();
					endPos = strChkData.Find(">");


					//"で区切られているかをチェックする
					int srcEndPos = -1;
					if(!strData.Left(1).Compare("\"")){
						//"で区切られていると考える
						strNewData += "\"";
						strData = strData.Mid(1);
						srcEndPos = strData.Find("\"");
						if(srcEndPos != -1){
							//パスを取得する
							strSrc = strData.Left(srcEndPos);
						}
					}else{
						//スペースを探す
						srcEndPos = strData.Find(" ");
						if(srcEndPos != -1){
							//パスを取得する
							strSrc = strData.Left(srcEndPos);
						}
					}
					if(srcEndPos != -1){
						//パスを解析し、置き換える
						if(!strSrc.Left(strlen("http://")).CompareNoCase("http://")
						|| !strSrc.Left(strlen("https://")).CompareNoCase("https://")
						|| !strSrc.Left(strlen("ftp://")).CompareNoCase("ftps://")
						|| !strSrc.Left(strlen("file://")).CompareNoCase("file://")){
							//ダウンロードする(このまま何もしない)
						}else{
							//URLとパスをつなげてダウンロード
							if(!strSrcURL.IsEmpty()){
								strSrc = strSrcURL + "/" + strSrc;
							}else{
								strSrc = "";
							}
						}
						if(!strSrc.IsEmpty()){
							//ファイル名だけにする
							CString strSavePath;
							CString strShortSrc = strSrc;
							int nSepPos = strSrc.ReverseFind('/');
							if(nSepPos != -1){
								strShortSrc = strSrc.Mid(nSepPos + 1);
							}

							int pos = strShortSrc.Find("?");
							if(pos != -1){
								//名前を変える
								strShortSrc = strShortSrc.Left(pos);
							}

							//ダウンロード
							strSavePath = strSaveDir + "\\" + strShortSrc;
							strSavePath.Replace("/", "\\");
							strSavePath.Replace("\\\\", "\\");

							strNewData += "./";
							strNewData += strShortSrc;
							strData = strData.Mid(srcEndPos);

							if(!strShortSrc.IsEmpty()){
								try{
									CString strLog;
									strLog.Format("BinderPlugin : DL %s / Save %s", strSrc, strSavePath);
									CLogFile::SaveAppLog(strLog);
									DownloadFile(strSrc, strSavePath);
								}catch(CException& e){
									SaveExceptLog(&e);
								}
							}				
						}else{
							strNewData += strData;
						}

					}else{
						//何も変えない
					}
					
					
				}else{
					strNewData += strData.Left(endPos);
					strData = strData.Mid(endPos);
				}
			}
		}
#endif

		CString strPath;
		strPath.Format("%s\\%s.html", strSaveDir, strTitle);
		int nCnt = 1;

		while(IsFileExsist(strPath)){
			strPath.Format("%s\\%s(%d).html", strSaveDir, strTitle, nCnt);
			nCnt++;
		}
		strPath.Replace("\\\\", "\\");

		CFile file;
		TRY{
			file.Open(strPath, CFile::modeCreate | CFile::modeWrite);
			file.Write((LPCTSTR)strData, strData.GetLength());
			file.Flush();
			file.Close();
		}CATCH_ALL(e){
			return FALSE;
		}END_CATCH_ALL

		//HTMLバインダーに登録
		CBinder *pBinder = (CBinder*)m_objTree.GetItemData(m_hHtml);
		BINDERITEM objItem;
		memset(&objItem, 0, sizeof(BINDERITEM));

		char szDrv[MAX_PATH];
		char szDir[MAX_PATH];
		char szName[MAX_PATH];
		char szExt[MAX_PATH];
		memset(szDrv, 0, MAX_PATH);
		memset(szDir, 0, MAX_PATH);
		memset(szName, 0, MAX_PATH);
		memset(szExt, 0, MAX_PATH);
		_splitpath(strPath, szDrv, szDir, szName, szExt);
		strcpy(objItem.pszName, szName);
		strcpy(objItem.pszFilePath, strPath);
		pBinder->AddBinderItem(&objItem);
		
		m_objTree.SelectItem(m_hHtml);
		SetActiveBinder(pBinder);
		pBinder->SaveBinderData(m_strAppPath);

		//デストラクタで呼び出されるけど念のため呼び出す。
		objBregExp.RefreshPool();

		UpdateTree();
	}catch(CException &e){
		//e.GetErrorMessage();
	}
	return TRUE;
}

BOOL CBinderWnd::DownloadFile(LPCTSTR pszURL, LPCTSTR pszSavePath){
	CString strURL = pszURL;
	CString strSavePath = pszSavePath;
	CString strErrMsg = "";
	if(::InternetAttemptConnect(0) != ERROR_SUCCESS){
		//ネットワークに接続できていないので何もしない
		strErrMsg = "";
		return FALSE;
	}
	CHttpConnection		*pHttp			= NULL;
	CHttpFile			*pHttpFile		= NULL;
	INTERNET_PORT		nPort			= INTERNET_DEFAULT_HTTP_PORT;
	DWORD				dwServiceType	= 0;
	CString				strServer		= "";
	CString				strObject		= "";
	CInternetSession	objSession("Personal Wiki", 0,
									INTERNET_OPEN_TYPE_PRECONFIG,
									NULL, NULL,
									INTERNET_FLAG_DONT_CACHE);
	BOOL bRet = TRUE;
	BOOL bHttps = FALSE;
	try{
		//---------------------------------------------------------------------------------
		//サーバー名の取得
		bRet = AfxParseURL(strURL, dwServiceType, strServer, strObject, nPort);
		if(!bRet){
			throw(DONT_GET_SERVERNAME);
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);

		//---------------------------------------------------------------------------------
		//
		DWORD dwReqFlag = INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE;
		if(dwServiceType == AFX_INET_SERVICE_HTTPS){
			dwReqFlag |=   INTERNET_FLAG_SECURE 
						 | INTERNET_FLAG_IGNORE_CERT_CN_INVALID
						 | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID;
			nPort = INTERNET_DEFAULT_HTTPS_PORT;
			bHttps = TRUE;
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);

		//---------------------------------------------------------------------------------
		//
		pHttp = objSession.GetHttpConnection(strServer, 
											 nPort, 
											 "", 
											 "");
		if( !pHttp ){
			throw(DONT_GET_CONNECTION);
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);

		//---------------------------------------------------------------------------------
		//
		pHttpFile = pHttp->OpenRequest(CHttpConnection::HTTP_VERB_GET,
									   strObject, 
									   NULL, 
									   1, 
									   NULL, 
									   NULL, 
									   dwReqFlag);
		if( !pHttpFile ){
			throw(DONT_OPEN_REQUEST);
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);
/*
		//---------------------------------------------------------------------------------
		//ユーザーID/パスワードの設定する。
		if(!m_strUser.IsEmpty() || !m_strPass.IsEmpty()){
			//ユーザーID
			bRet = ::InternetSetOption(*pHttpFile, 
									 INTERNET_OPTION_USERNAME, 
									 (LPVOID)(LPCTSTR)m_strUser,  
									 m_strUser.GetLength());

			if(!bRet){
				throw(DONT_SET_USERID);
			}

			//パスワード
			bRet = ::InternetSetOption(*pHttpFile, 
									 INTERNET_OPTION_PASSWORD, 
									 (LPVOID)(LPCTSTR)m_strPass,  
									 m_strPass.GetLength());

			if(!bRet){
				throw(DONT_SET_PASSWORD);
			}
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);
*/
		if(bHttps){
			DWORD dwFlags =
							SECURITY_FLAG_IGNORE_CERT_CN_INVALID 
						  | SECURITY_FLAG_IGNORE_CERT_DATE_INVALID 
						  | SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP 
						  | SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS 
						  | SECURITY_FLAG_IGNORE_UNKNOWN_CA,
			bRet = ::InternetSetOption(*pHttpFile, 
									 INTERNET_OPTION_SECURITY_FLAGS, 
									 &dwFlags,
									 sizeof(dwFlags));

			::PumpMessage(WM_TIMER, WM_TIMER);
			::PumpMessage(WM_PAINT, WM_PAINT);
			if(!bRet){
				throw(DONT_SET_PASSWORD);
			}
		}

		//---------------------------------------------------------------------------------
		//リクエストの送信
		if(!pHttpFile->SendRequest()){
			DWORD dwErr = GetLastError();
			if(dwErr == ERROR_INTERNET_FORCE_RETRY){
				::PumpMessage(WM_TIMER, WM_TIMER);
				::PumpMessage(WM_PAINT, WM_PAINT);
				//やり直し
				if(!pHttpFile->SendRequestEx(0)){
					throw(DONT_SEND_REQUEST);
				}
			}else{
				throw(DONT_SEND_REQUEST);
			}
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);
		DWORD dwErr = GetLastError();
		if(dwErr == 2){
			throw(DONT_SEND_REQUEST);
		}else if(dwErr){
			throw(DONT_SEND_REQUEST);
		}
	
		//---------------------------------------------------------------------------------
		//状態取得
		DWORD dwRc = 0;
		pHttpFile->QueryInfoStatusCode(dwRc);										
		if (dwRc != HTTP_STATUS_OK){
			throw(FAILD_REQUEST_STATUS);
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);

		//---------------------------------------------------------------------------------
		//リクエストの応答受信
		CString strLine;
		DWORD dwSize = pHttpFile->GetLength();
		char* pszBuff = new char[dwSize];
		
		CFile file;
		if(file.Open(strSavePath, CFile::modeCreate | CFile::modeWrite)){
			BOOL bEnd = FALSE;
			while(bEnd == FALSE){
				UINT uReadSize = pHttpFile->Read(pszBuff, dwSize);
				if(dwSize != uReadSize){
					bEnd = TRUE;
				}
				file.Write(pszBuff, uReadSize);
			}
			file.Flush();
			file.Close();
		}
		delete pszBuff;

		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);
	}catch(GETRSSRESULT eErr){
		switch(eErr){
		case DONT_GET_SERVERNAME:
			strErrMsg = "BinderPlugin : サーバー名が取得できません";
			break;
		case DONT_GET_CONNECTION:
			strErrMsg = "BinderPlugin : コネクションの取得に失敗";
			break;
		case DONT_OPEN_REQUEST:
			strErrMsg = "BinderPlugin : リクエストのオープンに失敗";
			break;
		case DONT_SET_USERID:
		case DONT_SET_PASSWORD:
			strErrMsg = "BinderPlugin : ユーザーID/パスワードの設定に失敗しました";
			break;
		case DONT_SEND_REQUEST:
		case FAILD_REQUEST_STATUS:
			strErrMsg = "BinderPlugin : リクエストの送信に失敗しました";
			break;
		}
		CLogFile::SaveExceptionLog(strErrMsg);
	}catch(CInternetException *e){
		CLogFile::SaveExceptionLog(e);
		e->Delete();
	}catch(CInternetException& e){
		CLogFile::SaveExceptionLog(&e);
	}catch(CException& e){
		CLogFile::SaveExceptionLog(&e);
	}
	if(pHttpFile){
		pHttpFile->Close();
		delete pHttpFile;
	}
	if(pHttp){
		pHttp->Close();
		delete pHttp;
	}
	objSession.Close();
	return bRet;
}

/**
 * @brif
 */
int CBinderWnd::GetItemIcon(CBinder *pBinder, PBINDERITEM pItem){
	char szDrv[MAX_PATH];
	char szDir[MAX_PATH];
	char szFile[MAX_PATH];
	char szExt[MAX_PATH];
	POSITION pos;
	_splitpath(pItem->pszFilePath, szDrv, szDir, szFile, szExt);
	pos = m_arrExtList.Find(szExt, NULL);
	int nIndex = 0;
	int nImg = 0;
	if(pos){
		POSITION chkPos = m_arrExtList.GetHeadPosition();
		CString strExt;
		while(chkPos){
			strExt = m_arrExtList.GetNext(chkPos);
			if(!strExt.CompareNoCase(szExt)){
				break;
			}
			nIndex++;
		}
		nImg = m_arrIconIndex.GetAt(nIndex);
	}else{
		HICON hIcon = pBinder->GetIcon(pItem);
		if(!hIcon){
			return 2;
		}
		nImg = m_arrImg.Add(hIcon);
		m_arrIconIndex.Add(nImg);
		m_arrIcon.Add(hIcon);
		m_arrExtList.AddTail(szExt);
	}
	return nImg;
}

/**
 * @brif
 */
void CBinderWnd::LoadDataFile(LPCTSTR pszFileName, CBinder *pStaticBinder /* = NULL */, HTREEITEM hStaticItem /* = NULL*/){
	CString strFilePath;
	strFilePath.Format("%s\\plugins\\BinderPlugin\\%s", m_strAppPath, pszFileName);
	CStdioFile file(strFilePath, CFile::modeRead);
	CString strLine;
	BOOL bFirst = TRUE;
	HTREEITEM hItem = NULL;
	HTREEITEM hIns = NULL;
	CBinder *pBinder = NULL;
	BINDERITEM objBinderItem;
	char szDrv[MAX_PATH];
	char szDir[MAX_PATH];
	char szFile[MAX_PATH];
	char szExt[MAX_PATH];
	CString strName;

	_splitpath(m_strAppPath, szDrv, NULL, NULL, NULL);
	CString strBootDir = szDrv;

	while(file.ReadString(strLine)){
		if(bFirst){
			bFirst = FALSE;
			if(pStaticBinder){
				pBinder = pStaticBinder;
				hItem = hStaticItem;
			}else{
				pBinder = new CBinder();
				hItem = m_objTree.InsertItem(strLine, IC_BINDER, IC_BINDER, m_hRoot);
				m_objTree.SetItemData(hItem, (LPARAM)pBinder);
				pBinder->m_strName = strLine;
			}
		}else{
			memset(&objBinderItem, 0, sizeof(BINDERITEM));
			memset(szDrv, 0, MAX_PATH);
			memset(szDir, 0, MAX_PATH);
			memset(szFile, 0, MAX_PATH);
			memset(szExt, 0, MAX_PATH);
			_splitpath(strLine, szDrv, szDir, szFile, szExt);
			strLine.Format("%s%s%s%s", strBootDir, szDir, szFile, szExt);
//			TRACE("<BinderPlugin>%s\n",strLine);
			strcpy(objBinderItem.pszName, szFile);
			strcpy(objBinderItem.pszFilePath, strLine);
			int nInsPos = pBinder->AddBinderItem(&objBinderItem);
			int nImg = GetItemIcon(pBinder, &objBinderItem);
			//strName.Format("%s.%s", szFile, szExt);
			hIns = m_objTree.InsertItem(szFile, nImg, nImg, hItem);
			PBINDERITEM pBinderItem = pBinder->GetBinderItem(nInsPos);
			m_objTree.SetItemData(hIns, (LPARAM)pBinderItem);
		}
	
	}
	file.Close();

	TVSORTCB tvSort;
	memset(&tvSort, 0, sizeof(TVSORTCB));
	tvSort.hParent = hItem;
	tvSort.lParam  = 0;
	tvSort.lpfnCompare = CompareBinderItem;
	m_objTree.SortChildrenCB(&tvSort);

}

/**
 * @brif
 */
BOOL CBinderWnd::AddBinder(){
	//バインダーを追加する
	CInpBinderNameDlg dlg;
	if(dlg.DoModal() == IDCANCEL){
		return FALSE;
	}

	CBinder *pBinder = new CBinder();
	pBinder->m_strName = dlg.m_strName;

	HTREEITEM hItem = m_objTree.InsertItem(dlg.m_strName, IC_BINDER, IC_BINDER, m_hRoot);
	m_objTree.SetItemData(hItem, (LPARAM)pBinder);	
	pBinder->SaveBinderData(m_strAppPath);

	TVSORTCB tvSort;
	memset(&tvSort, 0, sizeof(TVSORTCB));
	tvSort.hParent = m_hRoot;
	tvSort.lParam  = 0;
	tvSort.lpfnCompare = CompareBinder;
	m_objTree.SortChildrenCB(&tvSort);
	return TRUE;
}

/**
 * @brif
 */
CBinder* CBinderWnd::GetActiveBinder(){
	return m_pActiveBinder;
}

/**
 * @brif
 */
void CBinderWnd::SetActiveBinder(CBinder *pBinder){
	m_pActiveBinder = pBinder;
}

/**
 * @brif
 */
void CBinderWnd::OnDestroy(){
	CBinder *pBinder;
	HTREEITEM hChild = m_objTree.GetChildItem(m_hRoot);
	while(hChild){
		pBinder = (CBinder*)m_objTree.GetItemData(hChild);
		if(pBinder){
			delete pBinder;
		}
		hChild = m_objTree.GetNextSiblingItem(hChild);
	}

	m_objTree.DeleteAllItems();	

//	m_objDropTarget.Revoke();

	CWnd::OnDestroy();

	SaveIni();
}

/**
 * @brif
 */
void CBinderWnd::OnSize(UINT nType, int cx, int cy){
	CWnd::OnSize(nType, cx, cy);
	SetCtrlPos();
}

/**
 * @brif
 */
void CBinderWnd::OnTreeDBClick(NMHDR * pNotifyStruct, LRESULT * result ){
	*result = 0;
	NMTREEVIEW *pList = (NMTREEVIEW*)pNotifyStruct;
	if(pList->itemOld.hItem == NULL){
		return;
	}

	//ダブルクリックされたアイテムを開きます。
//	HTREEITEM hItem = m_objTree.HitTest(point, NULL);
//	HTREEITEM hItem = pList->itemOld.hItem;
	HTREEITEM hItem = m_objTree.GetSelectedItem();
	if(hItem){
		int nImg;
		int nSelImg;
		m_objTree.GetItemImage(hItem, nImg, nSelImg);
		if(nImg >= IC_END){
			PBINDERITEM pItem = (PBINDERITEM)m_objTree.GetItemData(hItem);
			if(pItem){
				CString strOpt = pItem->pszRelayAppOpt;
				CString strAppPath = pItem->pszRelayAppPath;
				char szExt[MAX_PATH];
				memset(szExt, 0, MAX_PATH);
				_splitpath(pItem->pszFilePath, NULL, NULL, NULL, szExt);
				CString strExt = szExt;

				if(pItem->bRelayApp){
					ShellExecute(m_hWnd, "open", strAppPath, pItem->pszFilePath, strOpt, SW_SHOW);
				}else{
					//関連付くアプリケーションを調査
					char szExecPath[MAX_PATH];
					HINSTANCE hRet = FindExecutable(pItem->pszFilePath, NULL, szExecPath);
					CString strPath = szExecPath;
					if(strPath.IsEmpty()){
						ShellExecute(m_hWnd, "open", m_strToolPath, pItem->pszFilePath, NULL, SW_SHOW);
					}else{
						ShellExecute(m_hWnd, "open", pItem->pszFilePath, NULL, NULL, SW_SHOW);
					}
				}
			
			}
		}
	}	

}

/**
 * @brif
 */
void CBinderWnd::OnDropFiles(HDROP hDropInfo) {
	CPoint point;
	if(GetCursorPos(&point)){
		m_objTree.ScreenToClient(&point);
		UINT flags;
		HTREEITEM hTree = m_objTree.HitTest(point, &flags);
		if(hTree){
			m_objTree.SelectItem(hTree);
			int nImg;
			int nSelImg;

			m_objTree.GetItemImage(hTree, nImg, nSelImg);
			if(nImg == IC_BINDER){
				CBinder *pBinder = (CBinder*)m_objTree.GetItemData(hTree);
				SetActiveBinder(pBinder);
				RegistDropFile(hDropInfo);
				UpdateTree();
			}
		}
		TVSORTCB tvSort;
		memset(&tvSort, 0, sizeof(TVSORTCB));
		tvSort.hParent = hTree;
		tvSort.lParam  = 0;
		tvSort.lpfnCompare = CompareBinderItem;
		m_objTree.SortChildrenCB(&tvSort);

	}

	CWnd::OnDropFiles(hDropInfo);
}

/**
 * @brif
 */
void CBinderWnd::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult){
	*pResult = 0;
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	int nImg;
	int nSelImg;
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	m_objTree.GetItemImage(hItem, nImg, nSelImg);
	HTREEITEM hParent = m_objTree.GetParentItem(hItem);

	CBinder *pBinder = NULL;
	PBINDERITEM pItem = NULL;
	if((hParent == m_hClip)
	|| (hParent == m_hRoot)
//	|| (hItem == m_hClipGraph)
//	|| (hItem == m_hClipHtml)
//	|| (hItem == m_hClipText)
//	|| (hItem == m_hHtml)
	){
		pBinder = (CBinder*)m_objTree.GetItemData(hItem);
	}else{
		pItem = (PBINDERITEM)m_objTree.GetItemData(hItem);
		if(hParent){
			pBinder = (CBinder*)m_objTree.GetItemData(hParent);
		}
	}

	SetActiveBinder(pBinder);
}

/**
 * @brif
 */
int CBinderWnd::RegistDropFile(HDROP hDropInfo){
	UINT uSize;
	int nCnt = 0;
	char szPath[MAX_PATH];
	CString strName;

	if(!m_pActiveBinder){
		return -1;
	}

	while(TRUE){
		memset(szPath, 0, MAX_PATH);
		// ドロップされた内容を取得
		uSize = ::DragQueryFile( hDropInfo, 
								 nCnt++,
								 szPath, 
								 MAX_PATH);
		if( uSize <= 0){
			break;
		}

		char szDrive[MAX_PATH];
		char szDir[MAX_PATH];
		char szFname[MAX_PATH];
		char szExt[MAX_PATH];
		_splitpath(szPath, szDrive, szDir, szFname, szExt);

		BINDERITEM objItem;
		memset(&objItem, 0, sizeof(BINDERITEM));
		strcpy(objItem.pszFilePath, szPath);
		strcpy(objItem.pszName, szFname);
		m_pActiveBinder->AddBinderItem(&objItem);
	}
	m_pActiveBinder->SaveBinderData(m_strAppPath);

	return nCnt - 1;
}

/**
 * @brif
 */
void CBinderWnd::SetCtrlPos(){
//	m_wndToolBar
	CRect rect;
	GetClientRect(rect);

	if(::IsWindow(m_wndToolBar.m_hWnd)){
		m_wndToolBar.SetWindowPos(&wndTop, 
								  0, 0, 
								  rect.Width(), m_objTbRect.Height(), 
								  SWP_SHOWWINDOW);
	}	
	
	if(::IsWindow(m_objTree.m_hWnd)){
		m_objTree.SetWindowPos(&wndTop, 
							   0, m_objTbRect.Height(), 
							   rect.Width(), rect.Height() - m_objTbRect.Height(), 
							   SWP_SHOWWINDOW);
	}
}

/**
 * @brif
 */
void CBinderWnd::OnAddbinder(){
	AddBinder();
}

/**
 * @brif
 */
void CBinderWnd::OnAddfile(){
	HTREEITEM hItem = m_objTree.GetSelectedItem();
	if(!hItem){
		return;
	}

	int nImg;
	int nSelImg;
	m_objTree.GetItemImage(hItem, nImg, nSelImg);
	if(nImg == IC_BINDER){
	}else if(nImg >= IC_END){
	}
}

/**
 * @brif
 */
void CBinderWnd::OnClipcopy(){
}

/**
 * @brif
 */
void CBinderWnd::OnFiledel(){
	HTREEITEM hItem = m_objTree.GetSelectedItem();
	if(!hItem){
		return;
	}

	int nImg;
	int nSelImg;
	m_objTree.GetItemImage(hItem, nImg, nSelImg);
	CString strSelLabel = m_objTree.GetItemText(hItem);
	CString strMsg;
	if((nImg == IC_NG) || (nImg >= IC_END)){
		//ファイル削除
		strMsg.Format("選択されたファイル %s の情報をバインダーから削除します。", strSelLabel);
		DWORD dwRet = AfxMessageBox(strMsg, MB_OKCANCEL);
		if(dwRet == IDCANCEL){
			return;
		}

		HTREEITEM hParent = m_objTree.GetParentItem(hItem);
		PBINDERITEM pItem = (PBINDERITEM)m_objTree.GetItemData(hItem);
		CBinder *pBinder = (CBinder*)m_objTree.GetItemData(hParent);
		if(hParent == m_hHtml){
			//ファイルも削除する
			UINT uRet = AfxMessageBox("削除するアイテムの実体ファイルも削除してもよろしいですか？", MB_OKCANCEL);
			if(uRet == IDOK){
				::DeleteFile(pItem->pszFilePath);
			}
		}
		
		pBinder->DeleteBinderItem(pItem);
		pBinder->SaveBinderData(m_strAppPath);

		m_objTree.DeleteItem(hItem);
		
	}else if(nImg == IC_BINDER){
		//バインダー削除
		strMsg.Format("バインダー %s を削除すると、バインダー %s 配下の情報も削除されます。", strSelLabel, strSelLabel);
		DWORD dwRet = AfxMessageBox(strMsg, MB_OKCANCEL);
		if(dwRet == IDCANCEL){
			return;
		}
	
		CBinder *pBinder = (CBinder*)m_objTree.GetItemData(hItem);
		pBinder->DeleteBinder(m_strAppPath);
		if(GetActiveBinder() == pBinder){
			SetActiveBinder(NULL);
		}
		delete pBinder;
		m_objTree.DeleteItem(hItem);
	}
}

/**
 * @brif
 */
void CBinderWnd::OnUpdateAddbinder(CCmdUI* pCmdUI){
}

/**
 * @brif
 */
void CBinderWnd::OnUpdateAddfile(CCmdUI* pCmdUI){
	BOOL bEnable = TRUE;

	HTREEITEM hItem = m_objTree.GetSelectedItem();
	if(!hItem){
		bEnable = FALSE;
	}
//	HTREEITEM hParent = objTree.GetParentItem(hItem);
	int nImg;
	int nSelImg;
	m_objTree.GetItemImage(hItem, nImg, nSelImg);
	switch(nImg){
	case IC_ROOT:
		bEnable = FALSE;
		break;
	case IC_NG:
	case IC_BINDER:
	default:
		bEnable = TRUE;
		break;
	}
	pCmdUI->Enable(bEnable);
/*
	CMainFrame *pFrame = (CMainFrame*)GetParentFrame();
	pFrame->SetButtonEnable(pCmdUI->m_nID, bEnable);
*/
}

/**
 * @brif
 */
void CBinderWnd::OnUpdateClipcopy(CCmdUI* pCmdUI){
}

/**
 * @brif
 */
void CBinderWnd::OnUpdateFiledel(CCmdUI* pCmdUI){
	HTREEITEM hItem = m_objTree.GetSelectedItem();
	if(!hItem){
		pCmdUI->Enable(FALSE);
	}

	int nImg;
	int nSelImg;
	m_objTree.GetItemImage(hItem, nImg, nSelImg);
	switch(nImg){
	case IC_ROOT:
	case IC_CLIP:
		pCmdUI->Enable(FALSE);
		break;
	case IC_NG:
	case IC_BINDER:
	default:
		pCmdUI->Enable(TRUE);
		break;
	}
}

/**
 * @brif
 */
void CBinderWnd::OnContextMenu(CWnd* pWnd, CPoint point){
	CMenu objMenu;
	if(!objMenu.LoadMenu(IDR_POPUP)){
		return;
	}

	HTREEITEM hSelItem = m_objTree.GetSelectedItem();

	CMenu *pMenu;

	pMenu = objMenu.GetSubMenu(0);
	int nImg;
	int nSelImg;
	m_objTree.GetItemImage(hSelItem, nImg, nSelImg);

	switch(nImg){
	case IC_ROOT:
	case IC_CLIP:
		pMenu->EnableMenuItem(IDM_ADDFILE,		MF_BYCOMMAND | MF_GRAYED);
		pMenu->EnableMenuItem(IDM_ADDBINDER,	MF_BYCOMMAND | MF_ENABLED);
		pMenu->EnableMenuItem(IDM_FILEDEL,		MF_BYCOMMAND | MF_GRAYED);
		break;

	case IC_BINDER:
		pMenu->EnableMenuItem(IDM_ADDFILE ,		MF_BYCOMMAND | MF_ENABLED);
		pMenu->EnableMenuItem(IDM_ADDBINDER,	MF_BYCOMMAND | MF_ENABLED);
		pMenu->EnableMenuItem(IDM_FILEDEL,		MF_BYCOMMAND | MF_ENABLED);
		break;

//	case IC_NG:
	default:
		pMenu->EnableMenuItem(IDM_ADDFILE ,		MF_BYCOMMAND | MF_ENABLED);
		pMenu->EnableMenuItem(IDM_ADDBINDER,	MF_BYCOMMAND | MF_ENABLED);
		pMenu->EnableMenuItem(IDM_FILEDEL,		MF_BYCOMMAND | MF_ENABLED);
//		pMenu->EnableMenuItem(IDM_CLIPCOPY,		MF_BYCOMMAND | MF_GRAYED);
//		pMenu->EnableMenuItem(IDM_EXPORT_FILE,  MF_BYCOMMAND | MF_GRAYED);
		break;
	}
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

LRESULT CBinderWnd::OnAnalisys(WPARAM wParam, LPARAM lParam){
	//解析する
	if(!AnalyzeDropHTML(m_strAnalisysData)){
		AfxMessageBox("HTMLの登録に失敗しました");
	}
	return 0;
}

BOOL CBinderWnd::PreTranslateMessage(MSG* pMsg){
	if(::TranslateAccelerator(m_hWnd, m_hAccel, pMsg)){
		return TRUE;
	}
	return CWnd::PreTranslateMessage(pMsg);
}

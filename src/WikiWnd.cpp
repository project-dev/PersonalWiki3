// WikiWnd.cpp: CWikiWnd �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PersonalWiki.h"
#include "WikiWnd.h"
#include "PWikiDoc.h"
#include "Mainfrm.h"
#include "LogFile.h"
#include "InfoTabView.h"
#include "DlgWikiInp.h"
#include "DlgInpWikiPage.h"
#include "FileCtrl.h"
#include "FileDialogEx.h"
#include "FolderDialog.h"
#include "FindFile.h"
#include "devlib.h"
#include "DebugSupport.h"
#include "devlib.h"
#include "DlgImpUrlInp.h"
#include <afxinet.h>
#include "StringEncode.h"
#include "DlgWikiProp.h"
#include "DlgPluginExport.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

/**
 * @brif �R���X�g���N�^
 */
CWikiWnd::CWikiWnd(){

}

/**
 * @brif �f�X�g���N�^
 */
CWikiWnd::~CWikiWnd(){

}

/**
 * @brif ���b�Z�[�W�}�b�v
 */
BEGIN_MESSAGE_MAP(CWikiWnd, CWnd)
	//{{AFX_MSG_MAP(CWikiWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDM_ADDWIKI, OnAddwiki)
	ON_COMMAND(IDM_DELWIKI, OnDelwiki)
	ON_COMMAND(IDM_EDITWIKI, OnEditwiki)
	ON_COMMAND(IDM_EXP_HTML, OnExpHtml)
	ON_COMMAND(IDM_EXP_TEXT, OnExpText)
	ON_COMMAND(IDM_RENAME_WIKI, OnRenameWiki)
	ON_UPDATE_COMMAND_UI(IDM_ADDWIKI, OnUpdateAddwiki)
	ON_UPDATE_COMMAND_UI(IDM_DELWIKI, OnUpdateDelwiki)
	ON_UPDATE_COMMAND_UI(IDM_EDITWIKI, OnUpdateEditwiki)
	ON_UPDATE_COMMAND_UI(IDM_EXP_HTML, OnUpdateExpHtml)
	ON_UPDATE_COMMAND_UI(IDM_EXP_TEXT, OnUpdateExpText)
	ON_UPDATE_COMMAND_UI(IDM_RENAME_WIKI, OnUpdateRenameWiki)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_BTN_TREEREFRESH, OnBtnTreerefresh)
	ON_UPDATE_COMMAND_UI(ID_BTN_TREEREFRESH, OnUpdateBtnTreerefresh)
	ON_COMMAND(IDM_URL_IMPORT, OnUrlImport)
	ON_UPDATE_COMMAND_UI(IDM_URL_IMPORT, OnUpdateUrlImport)
	ON_COMMAND(IDM_PROPERTY, OnProperty)
	ON_UPDATE_COMMAND_UI(IDM_PROPERTY, OnUpdateProperty)
	ON_COMMAND(IDM_PLUGIN_EXPORT, OnPluginExport)
	ON_UPDATE_COMMAND_UI(IDM_PLUGIN_EXPORT, OnUpdatePluginExport)
	//}}AFX_MSG_MAP
	ON_WM_DEVICECHANGE()
	ON_NOTIFY(TVN_SELCHANGED, IDS_WIKITREE, OnSelChanged)
	ON_NOTIFY(NM_CLICK, IDS_WIKITREE, OnClick)
#if defined(USE_TOOLTIP_WIKIWIND)
    ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotifyEx)
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipNotifyEx)
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipNotifyEx)
#endif
	ON_NOTIFY(TCN_SELCHANGE, IDS_MEMOTAB, OnTabChange)

END_MESSAGE_MAP()

#if defined(USE_TOOLTIP_WIKIWIND)
BOOL CWikiWnd::OnToolTipNotifyEx(UINT id, NMHDR *pTTTStruct, LRESULT *pResult) {
	return OnToolTioNotifyFunc(pTTTStruct, pResult);
}
void CWikiWnd::OnToolTipNotify(NMHDR *pTTTStruct, LRESULT *pResult) {
	OnToolTioNotifyFunc(pTTTStruct, pResult);
}
void CWikiWnd::GetToolTipText(NMHDR *pTTTStruct, CString &strTipText){
	TOOLTIPTEXT *pInfo = (TOOLTIPTEXT*)pTTTStruct;

	switch(pTTTStruct->idFrom){
	case IDM_ADDWIKI:
		strTipText = "Wiki�y�[�W��ǉ����܂�";
		break;
	case IDM_EDITWIKI:
		strTipText = "Wiki�y�[�W��ҏW���܂�";
		break;
	case IDM_DELWIKI:
		strTipText = "Wiki�y�[�W���폜���܂�";
		break;
	case IDM_RENAME_WIKI:
		strTipText = "Wiki�y�[�W����ύX���܂�";
		break;
	case IDM_EXP_HTML:
		strTipText = "HTML�`���ŃG�N�X�|�[�g���܂�";
		break;
	case IDM_EXP_TEXT:
		strTipText = "�e�L�X�g�`���ŃG�N�X�|�[�g���܂�";
		break;
	case IDM_PLUGIN_EXPORT:
		strTipText = "�v���O�C�����g���ăG�N�X�|�[�g���܂�";
		break;
	case ID_BTN_TREEREFRESH:
		strTipText = "�c���[���ŐV�̏�Ԃɂ��܂�";
		break;
	}
}
int CWikiWnd::OnToolHitTest(CPoint point, TOOLINFO* pTI ) const{
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
 * @brif �h�L�������g�N���X�̃|�C���^�擾
 */
CPWikiDoc* CWikiWnd::GetDocument(){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CWikiWnd::GetDocument : pFrm is null");
	}
	if(!pFrm){
		return NULL;
	}
	CRect rect;
	CPWikiDoc *pDoc = NULL;
	pDoc = (CPWikiDoc*)GetDoc();
	return pDoc;
}

/**
 * @brif �����֐�
 */ 
BOOL CWikiWnd::Create(DWORD dwStyle, const RECT &rect, CWnd *pParent, UINT uID){
	return CWnd::Create(NULL, NULL, dwStyle, rect, pParent, uID);
}

/**
 * @brif WM_CREATE�̃n���h���֐�
 */
int CWikiWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CLogFile::SaveAppLog("CWikiWnd::OnCreate");
	
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CLogFile::SaveAppLog("CWikiWnd ����");	
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | /*WS_BORDER |*/ CBRS_TOOLTIPS | CBRS_SIZE_FIXED | CBRS_FLYBY /*| CBRS_BORDER_BOTTOM*/;
	if(!m_objToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle, CRect(0, 0, 0, 0), IDR_WIKIWND)
	|| !m_objToolBar.LoadToolBar(IDR_WIKIWND)){
		CLogFile::SaveAppLog("�c�[���o�[�̐����Ɏ��s");
	}else{
		TBIMGINFO objTbInfo;
		memset(&objTbInfo, 0, sizeof(TBIMGINFO));
		objTbInfo.crMask = RGB(0, 128, 128);
		objTbInfo.nBtnHeight = 16;
		objTbInfo.nBtnWidth = 16;
		objTbInfo.nButtons = 8;
		objTbInfo.nColorBit = 8;
		objTbInfo.pToolBar = &m_objToolBar;
		objTbInfo.uID = IDB_WIKITOOLBAR256;
		SetToolbarImg(&objTbInfo);

		CSize szToolBar = m_objToolBar.CalcFixedLayout(FALSE,TRUE);
		m_objToolBar.MoveWindow(0, 0, szToolBar.cx, szToolBar.cy);
		m_objTbRect.SetRect(0, 0, szToolBar.cx, szToolBar.cy);

		CRect rect;
		GetClientRect(rect);

#if defined(USE_TOOLTIP_WIKIWIND)
		m_objToolTip.Create(this);
#endif

		UINT uIDs[] = { IDM_ADDWIKI, IDM_EDITWIKI, IDM_DELWIKI, IDM_RENAME_WIKI, 
						IDM_EXP_HTML, IDM_EXP_TEXT, IDM_PLUGIN_EXPORT, ID_BTN_TREEREFRESH};
		int nSize = sizeof(uIDs) / sizeof(UINT);

		for(int i = 0; i < nSize; i++){
			m_objToolBar.GetToolBarCtrl().GetItemRect(i, rect);
#if defined(USE_TOOLTIP_WIKIWIND)
			m_objToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rect, uIDs[i]);
#endif
		}
#if defined(USE_TOOLTIP_WIKIWIND)
		m_objToolTip.SetDelayTime(TTDT_AUTOPOP, 9999);
		m_objToolTip.SetDelayTime(TTDT_INITIAL, 100);
		m_objToolTip.Activate(TRUE);
		m_objToolBar.GetToolBarCtrl().SetToolTips(&m_objToolTip);
#endif
		m_objToolBar.GetToolBarCtrl().HideButton(IDM_EDITWIKI, TRUE);

	}

	CFont *pFont = GetFont();
	LOGFONT lFont;
	memset(&lFont, 0, sizeof(LOGFONT));
	if(pFont){
		pFont->GetLogFont(&lFont);
	}else{
		strcpy(lFont.lfFaceName, "MS UI Gothic");
		lFont.lfCharSet = DEFAULT_CHARSET;
	}
	lFont.lfHeight = -10;
	m_objFont.CreateFontIndirect(&lFont);
	
	CRect rect;
	GetClientRect(rect);

	m_objTree.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_LINESATROOT | TVS_HASLINES | TVS_HASBUTTONS | TVS_SHOWSELALWAYS, rect, this, IDS_WIKITREE);

	m_objTreeBmp.LoadBitmap(IDB_WIKITREE);
	m_arrImgList.Create(16, 16, ILC_COLOR16, 5, 1);
	m_arrImgList.Add(&m_objTreeBmp, RGB(0xFF, 0xFF, 0xFe));
	m_objTree.SetImageList(&m_arrImgList,TVSIL_NORMAL);

	m_objTab.Create(WS_CHILD | WS_VISIBLE, rect, this, IDS_MEMOTAB);
	m_objTab.SetFont(&m_objFont);
	m_objTab.InsertItem(0, "���C��");
	
	TC_ITEM tcItem;
	memset(&tcItem, 0, sizeof(TC_ITEM));
	tcItem.mask = TCIF_PARAM;
	tcItem.lParam = (LPARAM)&m_objTree;
	m_objTab.SetItem(0, &tcItem);

	m_objTab.SetCurSel(0);

	SetCtrlPos();
//	m_objTree.DeleteAllItems();
	FindWikiDoc();

	//�O�����f�B�A�̌���
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CWikiWnd::OnCreate : pFrm is null");
	}
	pFrm->EnumDevice();

	CLogFile::SaveAppLog("CWikiWnd::OnCreate End");
	return TRUE;
}

/**
 * @brif WM_PAINT�̃n���h���֐�
 */
void CWikiWnd::OnPaint(){
	CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g
}

/**
 * @brif WM_SIZE�̃n���h���֐�
 */
void CWikiWnd::OnSize(UINT nType, int cx, int cy){
	CWnd::OnSize(nType, cx, cy);
	CLogFile::SaveAppLog("CWikiWnd::OnSize");
	SetCtrlPos();
}

/**
 * @brif WM_DESTROY�̃n���h���֐�
 */
void CWikiWnd::OnDestroy() {
	int nCnt = m_objTab.GetItemCount();
	for(int i = 1; i < nCnt; i++){
		CTreeCtrl *pTree = GetTree(i);
		delete pTree;
	}
	m_objTab.DeleteAllItems();
	CWnd::OnDestroy();
}

/**
 * @brif WM_SHOWWINDOW�̃n���h���֐�
 */
void CWikiWnd::OnShowWindow(BOOL bShow, UINT nStatus){
	CWnd::OnShowWindow(bShow, nStatus);
	OnCtrlState();
}

/**
 * @brif �R���g���[���̕\������
 */
void CWikiWnd::SetCtrlPos(){
	CRect rect;
	GetClientRect(rect);
	if(::IsWindow(m_objTree.m_hWnd)){
		rect.top += m_objTbRect.Height();
		m_objTab.SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);

		m_objTab.GetClientRect(rect);
		m_objTab.AdjustRect(FALSE, rect);
		m_objTab.MapWindowPoints(this, rect);
		int nCnt = m_objTab.GetItemCount();
		int nSel = m_objTab.GetCurSel();
		CTreeCtrl* pTree = NULL;
		for(int i = 0; i < nCnt; i++){
			pTree = GetTree(i);
			if(pTree && ::IsWindow(pTree->m_hWnd)){
				pTree->SetWindowPos(&wndTop,
									rect.left,		rect.top, 
									rect.Width(),	rect.Height(), 
									nSel == i ? SWP_SHOWWINDOW : SWP_HIDEWINDOW );
			}
		}

	}
}

/**
 * @brif Wiki�h�L�������g�̌���
 */
void CWikiWnd::FindWikiDoc(LPCTSTR pszDir, HTREEITEM hParent){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CWikiWnd::FindWikiDoc : pFrm is null");
	}
	if(!pszDir && !hParent){
		m_objTree.DeleteAllItems();
	}

	{
		CString strBasePath = GetBasePath();
		if(pszDir){
			strBasePath = pszDir;
		}else{
			strBasePath += "Wiki\\";
		}

		CString strFind;
		strFind.Format("%s*", strBasePath);
		WIN32_FIND_DATA wfd;
		HANDLE hRet = NULL;
		BOOL bFirst = TRUE;
		while(TRUE){
			if(bFirst){
				bFirst = FALSE;
				hRet = ::FindFirstFile(strFind, &wfd);
				if(hRet == INVALID_HANDLE_VALUE){
					break;
				}
			}else{
				if(!::FindNextFile(hRet, &wfd)){
					break;
				}
			}
			CString strFind = wfd.cFileName;
			if(!strFind.CompareNoCase(".") || !strFind.CompareNoCase("..")){
				continue;
			}
			if((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY){
				//�t�H���_
				HTREEITEM hTree = IsAlive(&m_objTree, strFind, hParent);
				if(!hTree){
					hTree = m_objTree.InsertItem(strFind, 2, 3, hParent);
				}
				CString strSubDir;
				strSubDir.Format("%s%s\\", strBasePath, strFind);
				FindWikiDoc(strSubDir, hTree);
			}else{
				char szName[MAX_PATH];
				char szExt[MAX_PATH];
				memset(szName, 0, MAX_PATH);
				memset(szExt, 0, MAX_PATH);
				_splitpath(strFind, NULL, NULL, szName, szExt);
				CString strExt = szExt;
				if(strExt.CompareNoCase(".pwd")){
					continue;
				}
				//�o�^
				HTREEITEM hTree = IsAlive(&m_objTree, szName, hParent);
				if(!hTree){
					hTree = m_objTree.InsertItem(szName, 0, 1, hParent);
				}else{
					m_objTree.SetItemImage(hTree, 0, 1);
				}
			}
		}
		::FindClose(hRet);
	}
}	

void CWikiWnd::FindWikiDocUSB(LPCTSTR pszDir, HTREEITEM hParent){
#if defined(USE_USB_DOC)
	CMainFrame *pFrm = GetMainFrame(this);
	LINKINFO objIni;
	pFrm->m_objIniFile.GetLinkInfoIniData(objIni);
	if(!pFrm){
		CLogFile::SaveFatalLog("CWikiWnd::FindWikiDocUSB : pFrm is null");
	}
	CTreeCtrl *pTree = NULL;
	if(objIni.bUseUSBLink){
		//USB�f�o�C�X�ɑ΂��錟��
		for(int nDrv = 0; nDrv < 27; nDrv++){
			CString strDrvName;
			strDrvName.Format("%c:", CMainFrame::m_arrUsbState[nDrv].szDrv);
			if(!CMainFrame::m_arrUsbState[nDrv].bAlive){
				//�֘A����c���[���폜����
				continue;
			}
			for(int i = 0; i < 4; i++){

				CString strBasePath;
				CString strDir = &CMainFrame::m_arrUsbState[nDrv].szPath[i][0];
				strDir.TrimLeft();
				strDir.TrimRight();
				if(strDir.IsEmpty()){
					continue;
				}
				CString strKeyItem;
				strBasePath.Format("%s\\Wiki", strDir, objIni.szLinkDir[i]);
				strKeyItem.Format("%s", strDir, objIni.szLinkDir[i]);
				strBasePath.Replace("\\\\", "\\");
				if(!strBasePath.Right(1).CompareNoCase("\\")){
					strBasePath = strBasePath.Left(strBasePath.GetLength() - 1);
				}

				if(!::IsDir(strBasePath)){
					continue;
				}
				strBasePath += "\\";

				//�^�u�̑��݊m�F
				int nCnt = m_objTab.GetItemCount();
				char szName[1025];
				TC_ITEM tcItem;
				pTree = NULL;
				for(int j = 1; j < nCnt; j++){
					memset(szName, 0, 1025);
					memset(&tcItem, 0, sizeof(TC_ITEM));
					tcItem.mask = TCIF_TEXT | TCIF_PARAM;
					tcItem.cchTextMax = 1024;
					tcItem.pszText = szName;
					m_objTab.GetItem(j, &tcItem);
					if(!strKeyItem.CompareNoCase(szName)){
						pTree = (CTreeCtrl*)tcItem.lParam;
						break;
					}
				}
				if(!pTree){
					//�^�u�ǉ�
					CRect rect(0,0,0,0);
					pTree = new CTreeCtrl();
					pTree->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_LINESATROOT | TVS_HASLINES | TVS_HASBUTTONS | TVS_SHOWSELALWAYS, rect, this, IDS_WIKITREE);
					pTree->SetImageList(&m_arrImgList,TVSIL_NORMAL);

					int nInsPos = m_objTab.InsertItem(nCnt, strKeyItem);
					memset(&tcItem, 0, sizeof(TC_ITEM));
					tcItem.mask = TCIF_PARAM;
					tcItem.lParam = (LPARAM)pTree;
					m_objTab.SetItem(nInsPos, &tcItem);
				}
				//�h���C�u�̃c���[�̐擪�𐶐�
				if(::IsWindow(pTree->m_hWnd)){
					pTree->DeleteAllItems();
					hParent = pTree->InsertItem(strKeyItem, 0, 0);
					pTree->SetItemData(hParent, (LPARAM)&CMainFrame::m_arrUsbState[nDrv].szPath[i][0]);
					CString strFind;
					strFind.Format("%s*", strBasePath);
					WIN32_FIND_DATA wfd;
					HANDLE hRet = NULL;
					BOOL bFirst = TRUE;
					while(TRUE){
						if(bFirst){
							bFirst = FALSE;
							hRet = ::FindFirstFile(strFind, &wfd);
							if(hRet == INVALID_HANDLE_VALUE){
								break;
							}
						}else{
							if(!::FindNextFile(hRet, &wfd)){
								break;
							}
						}
						CString strFind = wfd.cFileName;
						if(!strFind.CompareNoCase(".") || !strFind.CompareNoCase("..")){
							continue;
						}
						if((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY){
							//�t�H���_
							HTREEITEM hTree = IsAlive(pTree, strFind, hParent);
							if(!hTree){
								hTree = pTree->InsertItem(strFind, 2, 3, hParent);
							}
							CString strSubDir;
							strSubDir.Format("%s%s\\", strBasePath, strFind);
							FindWikiDocUSBFotChild(pTree, strSubDir, hTree, strBasePath);
						}else{
							char szName[MAX_PATH];
							char szExt[MAX_PATH];
							memset(szName, 0, MAX_PATH);
							memset(szExt, 0, MAX_PATH);
							_splitpath(strFind, NULL, NULL, szName, szExt);
							CString strExt = szExt;
							if(strExt.CompareNoCase(".pwd")){
								continue;
							}
							//�o�^
							HTREEITEM hTree = IsAlive(pTree, szName, hParent);
							if(!hTree){
								hTree = pTree->InsertItem(szName, 0, 1, hParent);
							}else{
								pTree->SetItemImage(hTree, 0, 1);
							}
						}
					}
					::FindClose(hRet);
				}

			}
		}
	}

	//�s�v�ȃf�o�C�X���폜����
	int nCnt = m_objTab.GetItemCount();
	char szName[1025];
	TC_ITEM tcItem;
	int nTabSel = m_objTab.GetCurSel();
	for(int j = nCnt - 1; j >= 1; j--){
		memset(szName, 0, 1025);
		memset(&tcItem, 0, sizeof(TC_ITEM));
		tcItem.mask = TCIF_TEXT | TCIF_PARAM;
		tcItem.cchTextMax = 1024;
		tcItem.pszText = szName;

		m_objTab.GetItem(j, &tcItem);
		
		CTreeCtrl* pCtrl = (CTreeCtrl*)tcItem.lParam;
		if(pCtrl){
			CString strDrv = szName;
			strDrv.MakeUpper();

			char szDrv[MAX_PATH];
			memset(szDrv, 0, MAX_PATH);
			_splitpath(strDrv, szDrv, NULL, NULL, NULL);
			if(strlen(szDrv)){
				CString strDrvName;
				int nDrv = (int)(szDrv[0] - 'A');
				strDrvName.Format("%c:", CMainFrame::m_arrUsbState[nDrv].szDrv);
				if(!CMainFrame::m_arrUsbState[nDrv].bAlive || !objIni.bUseUSBLink){
					if(nTabSel == j){
						m_objTab.SetCurSel(0);
						SetCtrlPos();
					}
					m_objTab.DeleteItem(j);
					if(::IsWindow(pCtrl->m_hWnd)){
						pCtrl->SendMessage(WM_CLOSE, 0, 0);
					}
					delete pCtrl;
				}
			}
		}else{
			ASSERT(0);
		}
	}

	
#endif
}

void CWikiWnd::FindWikiDocUSBFotChild(CTreeCtrl* pTree, LPCTSTR pszDir, HTREEITEM hParent, LPCTSTR pszBasePath){
#if defined(USE_USB_DOC)
		CString strFind;
		strFind.Format("%s*", pszDir);
		WIN32_FIND_DATA wfd;
		HANDLE hRet = NULL;
		BOOL bFirst = TRUE;
		while(TRUE){
			if(bFirst){
				bFirst = FALSE;
				hRet = ::FindFirstFile(strFind, &wfd);
				if(hRet == INVALID_HANDLE_VALUE){
					break;
				}
			}else{
				if(!::FindNextFile(hRet, &wfd)){
					break;
				}
			}
			CString strFindName = wfd.cFileName;
			if(!strFindName.CompareNoCase(".") || !strFindName.CompareNoCase("..")){
				continue;
			}
			if((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY){
				//�t�H���_
				HTREEITEM hTree = IsAlive(pTree, strFindName, hParent);
				if(!hTree){
					hTree = pTree->InsertItem(strFindName, 2, 3, hParent);
				}
				CString strSubDir;
				strSubDir.Format("%s%s\\", pszBasePath, strFindName);
				FindWikiDoc(strSubDir, hTree);
			}else{
				char szName[MAX_PATH];
				char szExt[MAX_PATH];
				memset(szName, 0, MAX_PATH);
				memset(szExt, 0, MAX_PATH);
				_splitpath(strFindName, NULL, NULL, szName, szExt);
				CString strExt = szExt;
				if(strExt.CompareNoCase(".pwd")){
					continue;
				}
				//�o�^
				HTREEITEM hTree = IsAlive(pTree, szName, hParent);
				if(!hTree){
					hTree = pTree->InsertItem(szName, 0, 1, hParent);
				}else{
					pTree->SetItemImage(hTree, 0, 1);
				}
			}
		}
		::FindClose(hRet);
#endif
}



/**
 * @brif WM_LBUTTONDBLCLK�̃n���h���֐�
 */
void CWikiWnd::OnLButtonDblClk(UINT nFlags, CPoint point) {
	CWnd::OnLButtonDblClk(nFlags, point);
	OnCtrlState();
}

/**
 * @brif �c���[�̎w��ʒu����Wiki�p�X���擾����
 */
void CWikiWnd::GetWikiPath(CTreeCtrl* pTree, HTREEITEM hItem, CString &strPath){
	
	CString strName;
	strPath = "";
	while(hItem){
		strName = pTree->GetItemText(hItem);
		strPath = "/" + strName + strPath;
		hItem = pTree->GetParentItem(hItem);	
	}
}

/**
 * @brif �c���[�̑I��ύX���̏���
 */
void CWikiWnd::OnSelChanged(NMHDR * pNotifyStruct, LRESULT * result ){
	*result = 0;
/*
	OnCtrlState();
	HTREEITEM hItem = m_objTree.GetSelectedItem();
	CMainFrame *pFrm = GetMainFrame(this);
	CInfoView *pInfo = pFrm->GetInfoView();
	CString strWikiPath = "";
	if(hItem){
		GetWikiPath(hItem, strWikiPath);
		CString strPath;
		GetWikiPath(hItem, strPath);
		if(!strPath.IsEmpty()){
			pInfo->UpdateInfo(strPath);
		}
	}
*/
}

/**
 * @brif ���b�Z�[�W����������O�̃t�B���^�֐�
 */
BOOL CWikiWnd::PreTranslateMessage(MSG* pMsg) {
/*
	if(::IsWindow(m_objToolTip.m_hWnd)){
		switch(pMsg->message){
		case WM_MOUSEMOVE:
			m_objToolTip.RelayEvent(pMsg);
			break;
		}
	}
*/
/*
	CToolTipCtrl *pTip = m_objToolBar.GetToolBarCtrl().GetToolTips();
	if(pTip && ::IsWindow(pTip->m_hWnd)){
		switch(pMsg->message){
		case WM_MOUSEMOVE:
			pTip->RelayEvent(pMsg);
			break;
		}
	}
*/
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CWikiWnd::PreTranslateMessage : pFrm is null");
	}

	CString strBasePath = GetBasePath(TRUE);
	strBasePath += "Wiki\\";

	CTreeCtrl* pTree = GetTree(-1);
	if(pMsg->hwnd == pTree->m_hWnd){
		HTREEITEM hItem = NULL;
		CString strWikiPath = "";
		UINT uFlags = 0;
		switch(pMsg->message){
		case WM_LBUTTONDBLCLK:
			{
				OnCtrlState();
				POINT pos;
				pos.y = HIWORD(pMsg->lParam);
				pos.x = LOWORD(pMsg->lParam);
				hItem = pTree->HitTest(pos, &uFlags);
				if(hItem && (uFlags & TVHT_ONITEMLABEL)){
					OnClickWikiEdit();
				}
				return TRUE;
			}
			break;
		}
	}

	return CWnd::PreTranslateMessage(pMsg);
}

void CWikiWnd::OnClick(NMHDR * pNotifyStruct, LRESULT * result ){
	POINT pos;
	::GetCursorPos(&pos);
	CTreeCtrl* pTree = GetTree(-1);

	pTree->ScreenToClient(&pos);
	OnCtrlState();

	TVHITTESTINFO hTest;
	memset(&hTest, 0, sizeof(TVHITTESTINFO));
	hTest.pt = pos;
	
	HTREEITEM hItem = pTree->HitTest(&hTest);
	
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CWikiWnd::OnClick : pFrm is null");
	}
	CInfoTabView *pInfo = pFrm->GetInfoTabView();
	CString strWikiPath = "";
	if(hItem && (hTest.flags == TVHT_ONITEMLABEL) ){
		GetWikiPath(pTree, hItem, strWikiPath);
		CString strPath;
		GetWikiPath(pTree, hItem, strPath);

		CString strRealPath1;
		CString strRealPath2;

		CString strChkPath = strWikiPath;
		CString strBasePath = GetBasePath(TRUE);
		BOOL bUSB = GetUSBPath(strChkPath, strBasePath);

		strPath = strChkPath;
		strRealPath1.Format("%sWiki\\%s", strBasePath, strPath);
		strRealPath1.Replace("/", "\\");
		strRealPath1.Replace("\\\\", "\\");
		strRealPath2.Format("%sWiki\\%s.pwd", strBasePath, strPath);
		strRealPath2.Replace("/", "\\");
		strRealPath2.Replace("\\\\", "\\");

		
		if(!strPath.IsEmpty() && ::IsFileExsist(strRealPath2)){
			if(bUSB){
				pInfo->UpdateInfoUSB(strPath, strBasePath);
			}else{
				pInfo->UpdateInfo(strPath);
			}
		}
	}
}

/**
 * @brif �ǉ��{�^���������̏���
 */
void CWikiWnd::OnClickWikiAdd(){
	//�y�[�W�̐V�K�쐬
	CDlgInpWikiPage objDlgWikiName;
	if(objDlgWikiName.DoModal() != IDOK){
		return;
	}
	
	CString strWikiPath = objDlgWikiName.m_strWikiName;
	if(strWikiPath.Left(1).Compare("/")){
		strWikiPath = "/" + strWikiPath;
	}
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CWikiWnd::OnClickWikiAdd : pFrm is null");
	}
	CInfoTabView *pInfo = pFrm->GetInfoTabView();
	CCalView *pCalView = pFrm->GetCalView();
	CPWikiDoc *pDoc = GetDocument();
/*
	CDlgWikiInp dlg;
	dlg.m_strSetText = "";
	dlg.m_strWikiPath = strWikiPath;
*/
	CString strCreDir;
	CString strCreDirAtt;
	CString strFilePath;
	CString strData = "";
	pDoc->CreateWikiDir(strWikiPath, NULL, strFilePath, strCreDir, strCreDirAtt);
/*
	if(dlg.DoModal() == IDOK){
		CString strData = dlg.m_strSetText;
		if(!strData.IsEmpty()){
			if(CFileCtrl::CreateDirectory(strCreDir)){
			}
			if(CFileCtrl::CreateDirectory(strCreDirAtt)){
			}

			CFile file;
			file.Open(strFilePath, CFile::modeCreate | CFile::modeNoInherit | CFile::modeReadWrite);
			file.Write(strData.GetBuffer(0), strData.GetLength());
			file.Flush();
			file.Close();
			if(!strWikiPath.IsEmpty()){
				pInfo->UpdateInfo(strWikiPath);
				FindWikiDoc();
				ActiveTreeItem(strWikiPath);
//				pInfo->UpdateInfo(strWikiPath);
			}
		}
	}
*/

	if(CFileCtrl::CreateDirectory(strCreDir)){
	}
	if(CFileCtrl::CreateDirectory(strCreDirAtt)){
	}

	CFile file;
	file.Open(strFilePath, CFile::modeCreate | CFile::modeNoInherit | CFile::modeReadWrite);
	file.Write(strData.GetBuffer(0), strData.GetLength());
	file.Flush();
	file.Close();
	if(!strWikiPath.IsEmpty()){
		pInfo->UpdateInfo(strWikiPath);
		FindWikiDoc();
		ActiveTreeItem(strWikiPath);
//		pInfo->UpdateInfo(strWikiPath);
	}
}

/**
 * @brif �ҏW�{�^���������̏���
 */
void CWikiWnd::OnClickWikiEdit(){
}

/**
 * @brif �폜�{�^���������̏���
 */
void CWikiWnd::OnClickWikiDel(){
	CTreeCtrl *pTree = GetTree(-1);
	HTREEITEM hItem = pTree->GetSelectedItem();
	if(!hItem){
		return;
	}
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		CLogFile::SaveFatalLog("CWikiWnd::OnClickWikiDel : pFrm is null");
	}
	CInfoTabView *pInfo = pFrm->GetInfoTabView();
	CString strBasePath = GetBasePath(TRUE);

	CString strWikiPath;
	GetWikiPath(pTree, hItem, strWikiPath);

	//�O�����f�B�A�Ή�
	BOOL bUSB = GetUSBPath(strWikiPath, strBasePath);
	
	CString strMsg;
	strMsg.Format("%s ���폜���܂�", strWikiPath);
	if(AfxMessageBox(strMsg, MB_OKCANCEL) == IDCANCEL){
		return;
	}
	CString strDelDir = strBasePath + "Wiki\\" + strWikiPath;
	CString strDelFile = strBasePath + "Wiki\\" + strWikiPath + ".pwd";
	CString strDelAttachDir = strBasePath + "attach\\" + strWikiPath;
	strDelDir.Replace("/", "\\");
	strDelAttachDir.Replace("/", "\\");
	strDelFile.Replace("/", "\\");
	strDelDir.Replace("\\\\", "\\");
	strDelAttachDir.Replace("\\\\", "\\");
	strDelFile.Replace("\\\\", "\\");

	if(::IsFileExsist(strDelFile) && !::DeleteFile(strDelFile)){
		DWORD dwErr = ::GetLastError();
	}
	if(::IsFileExsist(strDelDir) && !::RemoveDirectoryEx(strDelDir, TRUE)){
		DWORD dwErr = ::GetLastError();
		CString strError = CDebugSupport::GetLastErrorText(dwErr);
		AfxMessageBox(strError);

	}
	if(::IsFileExsist(strDelAttachDir) && !::RemoveDirectoryEx(strDelAttachDir, TRUE)){
		DWORD dwErr = ::GetLastError();
		CString strError = CDebugSupport::GetLastErrorText(dwErr);
		AfxMessageBox(strError);

	}
	FindWikiDoc();
	FindWikiDocUSB();
}

/**
 * @brif �w��Wiki�y�[�W���������Ă��邩�`�F�b�N
 */
HTREEITEM CWikiWnd::IsAlive(CTreeCtrl *pTree, LPCTSTR pszText, HTREEITEM hParent){

	HTREEITEM hItem = pTree->GetChildItem(hParent);
	while(hItem){
		CString strItem = pTree->GetItemText(hItem);
		if(!strItem.CompareNoCase(pszText)){
			return hItem;
		}
		hItem = pTree->GetNextItem(hItem, TVGN_NEXT);
	}
	return NULL;
}

/**
 * @brif �R���g���[���̏�Ԑ���
 */
void CWikiWnd::OnCtrlState(){
}

/**
 * @brif �|�b�v�A�b�v���j���[
 */
void CWikiWnd::OnContextMenu(CWnd* pWnd, CPoint point) {
	CTreeCtrl *pTree = GetTree(-1);
	UINT uFlags = 0;
	CPoint htPos = point;
	pTree->ScreenToClient(&htPos);
	HTREEITEM hItem = pTree->HitTest(htPos, &uFlags);
	if(hItem && (uFlags & TVHT_ONITEMLABEL)){
		pTree->Select(hItem, TVGN_CARET);
	}
	
	hItem = pTree->GetSelectedItem();

	CMenu menu;
	menu.LoadMenu(IDR_WIKIMENU);
	CMenu *pMenu = menu.GetSubMenu(0);

	CMenu *pExpMenu = pMenu->GetSubMenu(6);
	if(hItem){
		pMenu->EnableMenuItem(IDM_EDITWIKI, MF_BYCOMMAND | MF_ENABLED) ; 
		pMenu->EnableMenuItem(IDM_DELWIKI, MF_BYCOMMAND | MF_ENABLED) ; 
		pMenu->EnableMenuItem(IDM_RENAME_WIKI, MF_BYCOMMAND | MF_ENABLED) ; 
		pExpMenu->EnableMenuItem(IDM_EXP_HTML, MF_BYCOMMAND | MF_ENABLED) ; 
		pExpMenu->EnableMenuItem(IDM_EXP_TEXT, MF_BYCOMMAND | MF_ENABLED) ; 
	}else{
		pMenu->EnableMenuItem(IDM_EDITWIKI, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED) ; 
		pMenu->EnableMenuItem(IDM_DELWIKI, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED) ; 
		pMenu->EnableMenuItem(IDM_RENAME_WIKI, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED) ; 
		pExpMenu->EnableMenuItem(IDM_EXP_HTML, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED) ; 
		pExpMenu->EnableMenuItem(IDM_EXP_TEXT, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED) ; 
	}
	
	pMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}

/**
 * @brif �ǉ����j���[�I��������
 */
void CWikiWnd::OnAddwiki(){
	OnClickWikiAdd();
}

/**
 * @brif �폜���j���[�I��������
 */
void CWikiWnd::OnDelwiki(){
	OnClickWikiDel();
}

/**
 * @brif �ҏW���j���[�I��������
 */
void CWikiWnd::OnEditwiki(){
	OnClickWikiEdit();
}

/**
 * @brif HTML�փG�N�X�|�[�g���j���[�I��������
 */
void CWikiWnd::OnExpHtml(){
	Export(EXP_HTML);
}

/**
 * @brif �e�L�X�g�t�@�C���փG�N�X�|�[�g���j���[�I��������
 */
void CWikiWnd::OnExpText(){
	Export(EXP_TEXT);
}

/**
 * @brif �G�N�X�|�[�g�֐�
 */
BOOL CWikiWnd::Export(EXP_TYPE eExpType){
	CTreeCtrl *pTree = GetTree(-1);
	BOOL bRet = TRUE;
	HTREEITEM hItem = pTree->GetSelectedItem();
	CString strWikipath;
	CString strFileName;
	CString strBase = GetBasePath(TRUE);
	GetWikiPath(pTree, hItem, strWikipath);

	//�O�����f�B�A�Ή�
	BOOL bUSB = GetUSBPath(strWikipath, strBase);
	
	strFileName.Format("%sWiki\\%s.pwd", strBase, strWikipath);
	strFileName.Replace("/", "\\");
	strFileName.Replace("\\\\", "\\");

	CString strText;
	CFile file;
	CFileStatus status;
	char *pszBuff = NULL;
	try{
#if 1
		if(LoadWikiText(strWikipath, strBase, strText) != LD_OK){
			throw(0);
		}
#else	
		if(file.Open(strFileName, CFile::modeRead)){
			file.GetStatus(status);
			if(status.m_size <= 0){
				file.Close();
				throw(0);
			}
			pszBuff = new char[status.m_size + 1];
			memset(pszBuff, 0, status.m_size + 1);
			file.Read(pszBuff, status.m_size);
			strText = pszBuff;
			file.Close();
		}
#endif
	}catch(CFileException &fe){
		SaveExceptLog(&fe);
		bRet = FALSE;
	}catch(...){
		bRet = FALSE;
	}
	if(pszBuff){
		delete pszBuff;
	}
	if(bRet){
		CAnalisysWiki objAna;
		CMainFrame *pFrm = GetMainFrame(this);
		if(!pFrm){
			CLogFile::SaveFatalLog("CWikiWnd::Export : pFrm is null");
		}
		WIKIINFO objIni;
		pFrm->m_objIniFile.GetWikiInfoIniData(objIni);
		ANAINFO objAnaInfo;
		memset(&objAnaInfo, 0, sizeof(objAnaInfo));
		objAnaInfo.bUseRetFormat = objIni.bUseRet;
		objAnaInfo.bUseTBLink = objIni.bUseTopBtmLnk;
		objAnaInfo.bShowAttach = objIni.bUseShowAttach;
		objAnaInfo.bUseShowConvTime = objIni.bUseShowConvTime;
		strcpy(objAnaInfo.pszBasePath, strBase);
		strcpy(objAnaInfo.pszBaseWikiPath, strFileName);
		objAna.SetAnaSetting(&objAnaInfo);

		CString strOut;
		CString strExt;
		CString strBody;
		CFile objOutFile;
		switch(eExpType){
		case EXP_HTML:
			{
				CString strWikiExportDir;
				CString strAttachExportDir;
				CString strHtmlExportFile;
				CString strAttachDir;
				CString strCSSDir;
				CString strCSSExportDir;
				CString strImgDir;
				CString strImgExportDir;
				strWikiExportDir = "Wiki\\" + strWikipath;
				strAttachExportDir = "Attach\\" + strWikipath;
				strAttachDir.Format("%sAttach\\%s", strBase, strWikipath);
				strCSSDir.Format("%sCSS", strBase);
				strCSSExportDir = "CSS";
				strImgDir.Format("%sImg\\Face", strBase);
				strImgExportDir = "Img\\Face";

				strAttachDir.Replace("/", "\\");
				strAttachDir.Replace("\\\\", "\\");

				strWikiExportDir.Replace("/", "\\");
				strWikiExportDir.Replace("\\\\", "\\");
				
				strAttachExportDir.Replace("/", "\\");
				strAttachExportDir.Replace("\\\\", "\\");
				
				strCSSDir.Replace("/", "\\");
				strCSSDir.Replace("\\\\", "\\");
				
				strImgDir.Replace("/", "\\");
				strImgDir.Replace("\\\\", "\\");
				
				strImgExportDir.Replace("/", "\\");
				strImgExportDir.Replace("\\\\", "\\");
				
				strHtmlExportFile = strWikiExportDir + ".html";
				int nPos = strWikiExportDir.ReverseFind('\\');
				strWikiExportDir = strWikiExportDir.Left(nPos);

				WIKIINFO objInfo;
				memset(&objInfo, 0, sizeof(WIKIINFO));
				pFrm->m_objIniFile.GetWikiInfoIniData(objInfo);
				objAna.SetMimeType(&pFrm->m_objMimeTypes);
				objAna.Analisys(strText, strBody, strWikipath, FALSE, TRUE);
				objAna.CreateHTML(strOut, objInfo.szCss, strWikipath, strBody);
				CFolderDialog dlg(m_hWnd, "HTML�̃G�N�X�|�[�g");
				if(dlg.DoModal()){
					CString strDir = dlg.GetFolder();
					strWikiExportDir = strDir + "\\" + strWikiExportDir;
					strAttachExportDir = strDir + "\\" + strAttachExportDir;
					strHtmlExportFile = strDir + "\\" + strHtmlExportFile;
					strCSSExportDir = strDir + "\\" + strCSSExportDir;
					strImgExportDir = strDir + "\\" + strImgExportDir;
					
					
					::CreateDir(strWikiExportDir, NULL);
					::CreateDir(strAttachExportDir, NULL);
					::CreateDir(strCSSExportDir, NULL);
					::CreateDir(strImgExportDir, NULL);
					if(objOutFile.Open(strHtmlExportFile, CFile::modeCreate /*| CFile::modeNoTruncate*/ | CFile::modeWrite)){
						objOutFile.Write(strOut, strOut.GetLength());
						objOutFile.Flush();
						objOutFile.Close();
					}

					//�Y�t�t�@�C���R�s�[
					CopyFiles(strAttachDir, strAttachExportDir);
					CopyFiles(strCSSDir, strCSSExportDir);
					CopyFiles(strImgDir, strImgExportDir);
				}
			}
			break;
		case EXP_TEXT:
			{
				objAna.SetMimeType(NULL);
				objAna.Analisys(strText, strOut, strWikipath, TRUE);
				strExt = "*.txt";

				
				CFileDialogEx objDlg(m_hWnd, 
									 NULL, 
									 strExt.GetBuffer(0), 
									 "�G�N�X�|�[�g", 
									 "", 
									 0, 
									 NULL, 
									 "�G�N�X�|�[�g", 
									 strExt.GetBuffer(0));
				if(objDlg.DoModal() == IDOK){
					strFileName = objDlg.GetFileName();
					if(objOutFile.Open(strFileName, CFile::modeCreate /*| CFile::modeNoTruncate*/ | CFile::modeWrite)){
						objOutFile.Write(strOut, strOut.GetLength());
						objOutFile.Flush();
						objOutFile.Close();
					}
				}
			}
			break;
		}
	}
	return bRet;
}

BOOL CWikiWnd::CopyFiles(LPCTSTR pszFrom, LPCTSTR pszTo){
	CString strFind;
	strFind.Format("%s\\*.*", pszFrom);
	CString strFrom = pszFrom;
	CString strTo = pszTo;
	WIN32_FIND_DATA wfd;
	HANDLE hRet = NULL;
	BOOL bFirst = TRUE;
	while(TRUE){
		if(bFirst){
			hRet = ::FindFirstFile(strFind, &wfd);
			if(hRet == INVALID_HANDLE_VALUE){
				break;
			}
			bFirst = FALSE;
		}else{
			if(!::FindNextFile(hRet, &wfd)){
				break;
			}
		}
		CString strCopyFrom = strFrom + "\\" + wfd.cFileName;
		CString strCopyTo = strTo + "\\" + wfd.cFileName;
		::CopyFile(strCopyFrom, strCopyTo, FALSE);
	}
	::FindClose(hRet);
	return TRUE;
}

/**
 * @brif ���l�[������
 */
void CWikiWnd::OnRenameWiki(){
	CTreeCtrl* pTree = GetTree(-1);
	HTREEITEM hTree = pTree->GetSelectedItem();
	if(!hTree){
		return;
	}
	CString strName;
	GetWikiPath(pTree, hTree, strName);
	CString strBasePath = GetBasePath(TRUE);

	//�O�����f�B�A�Ή�
	BOOL bUSB = GetUSBPath(strName, strBasePath);

	CString strOldPath;
	CString strOldAttPath;
	strOldPath.Format("%sWiki\\%s", strBasePath, strName);
	strOldPath.Replace("/", "\\");
	strOldPath.Replace("\\\\", "\\");

	strOldAttPath.Format("%sAttach\\%s", strBasePath, strName);
	strOldAttPath.Replace("/", "\\");
	strOldAttPath.Replace("\\\\", "\\");

	CDlgInpWikiPage dlg;
	dlg.m_strWikiName = strName;
	if(dlg.DoModal() == IDCANCEL){
		return;
	}
	if(dlg.m_strWikiName.IsEmpty()){
		return;
	}
	strName = dlg.m_strWikiName;
	CString strPath;
	CString strAttPath;
	strPath.Format("%sWiki\\%s", strBasePath, strName);
	strPath.Replace("/", "\\");
	strPath.Replace("\\\\", "\\");

	strAttPath.Format("%sAttach\\%s", strBasePath, strName);
	strAttPath.Replace("/", "\\");
	strAttPath.Replace("\\\\", "\\");

	//�f�B���N�g�����l�[��
	if(CFileCtrl::IsExistDir(strOldPath)){
		if(!::MoveFile(strOldPath, strPath)){
			AfxMessageBox("���l�[���Ɏ��s���܂���");
			return;
		}
	}
	strOldPath += ".pwd";
	strPath += ".pwd";

	//�t�@�C�����l�[��
	if(CFindFile::IsExistFile(strOldPath)){
		if(!::MoveFile(strOldPath, strPath)){
			AfxMessageBox("���l�[���Ɏ��s���܂���");
		}
	}

	//�Y�t�f�B���N�g�����l�[��
	if(CFileCtrl::IsExistDir(strOldAttPath)){
		if(!::MoveFile(strOldAttPath, strAttPath)){
			AfxMessageBox("���l�[���Ɏ��s���܂���");
			return;
		}
	}
	
//	pTree->DeleteAllItems();
	FindWikiDoc();
	FindWikiDocUSB();
}

void CWikiWnd::OnProperty(){
	CTreeCtrl* pTree = GetTree(-1);
	HTREEITEM hTree = pTree->GetSelectedItem();
	if(!hTree){
		return;
	}
	CString strName;
	GetWikiPath(pTree, hTree, strName);
	CString strBasePath = GetBasePath(TRUE);
	CString strPath;
	strPath.Format("%sWiki\\%s.pwd", strBasePath, strName);
	strPath.Replace("/", "\\");
	strPath.Replace("\\\\", "\\");

	CDlgWikiProp dlg;
	dlg.m_strRealPath = strPath;
	dlg.m_strWikiPath = strName;
	if(dlg.DoModal() == IDOK){
	
	}
}


void CWikiWnd::OnUpdateAddwiki(CCmdUI* pCmdUI){
	pCmdUI->Enable(TRUE);
}

void CWikiWnd::OnUpdateEditwiki(CCmdUI* pCmdUI){
	CTreeCtrl* pTree = GetTree(-1);
	HTREEITEM hItem = pTree->GetSelectedItem();
	pCmdUI->Enable(hItem ? TRUE : FALSE);
}

void CWikiWnd::OnUpdateDelwiki(CCmdUI* pCmdUI){
	CTreeCtrl* pTree = GetTree(-1);
	HTREEITEM hItem = pTree->GetSelectedItem();
	pCmdUI->Enable(hItem ? TRUE : FALSE);
}

void CWikiWnd::OnUpdateExpHtml(CCmdUI* pCmdUI){
	CTreeCtrl* pTree = GetTree(-1);
	HTREEITEM hItem = pTree->GetSelectedItem();
	pCmdUI->Enable(hItem ? TRUE : FALSE);
}

void CWikiWnd::OnUpdateExpText(CCmdUI* pCmdUI){
	CTreeCtrl* pTree = GetTree(-1);
	HTREEITEM hItem = pTree->GetSelectedItem();
	pCmdUI->Enable(hItem ? TRUE : FALSE);
}

void CWikiWnd::OnUpdateRenameWiki(CCmdUI* pCmdUI){
	CTreeCtrl* pTree = GetTree(-1);
	HTREEITEM hItem = pTree->GetSelectedItem();
	pCmdUI->Enable(hItem ? TRUE : FALSE);
}

void CWikiWnd::OnUpdateProperty(CCmdUI* pCmdUI){
	CTreeCtrl* pTree = GetTree(-1);
	HTREEITEM hItem = pTree->GetSelectedItem();
	pCmdUI->Enable(hItem ? TRUE : FALSE);
}

BOOL CWikiWnd::OnEraseBkgnd(CDC* pDC){
	CBrush brush;
	brush.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));
	CRect rect;
	GetClientRect(rect);
	rect.bottom = m_objTbRect.bottom;
	pDC->FillRect(rect, &brush);
	return FALSE;
//	return CWnd::OnEraseBkgnd(pDC);
}

void CWikiWnd::ActiveTreeItem(LPCTSTR pszWikipath)
{
	CTreeCtrl* pTree = GetTree(-1);
	CString strWikiPath = pszWikipath;
	strWikiPath.TrimLeft();
	strWikiPath.TrimRight();
	if(strWikiPath.IsEmpty()){
		return;
	}

	//��������
	CStringArray arrPath;
	CString strSplitPath;
	while(!strWikiPath.IsEmpty()){
		int nPos = strWikiPath.Find("/");
		if(nPos == -1){
			arrPath.Add(strWikiPath);
			strWikiPath = "";
		}else{
			strSplitPath = strWikiPath.Left(nPos);
			if(!strSplitPath.IsEmpty()){
				arrPath.Add(strSplitPath);
			}
			strWikiPath = strWikiPath.Mid(nPos + 1);
		}
	}
	HTREEITEM htItem = pTree->GetNextItem(NULL, TVGN_CHILD);
	if(htItem == NULL){
		return;
	}

	int nIndex = 0;
	while(TRUE){
		CString strPath = arrPath.GetAt(nIndex);
		CString strName = pTree->GetItemText(htItem);
		if(strName.CollateNoCase(strPath)){
			htItem = pTree->GetNextItem(htItem, TVGN_NEXT);
		}else{
			//��v
			nIndex++;
			if(nIndex == arrPath.GetSize()){
				pTree->Select(htItem, TVGN_CARET);
				break;
			}
			if(!pTree->ItemHasChildren(htItem)){
				break;
			}
			pTree->Expand(htItem, TVE_EXPAND);
			htItem = pTree->GetNextItem(htItem, TVGN_CHILD);
		}
		if(htItem == NULL){
			break;
		}
	}
}

BOOL CWikiWnd::OnDeviceChange( UINT nEventType, DWORD dwData ){
	return CWnd::OnDeviceChange(nEventType, dwData);
}


BOOL CWikiWnd::GetUSBPath(CString &strWikiPath, CString &strBasePath){
	CString strChkPath = strWikiPath;
	BOOL bUSB = FALSE;
	if(strChkPath.Left(0).Compare("/")){
		//�O�����f�B�A�`�F�b�N
		strChkPath = strChkPath.Mid(1);
		strChkPath.Replace("/", "\\");
		strChkPath.MakeUpper();
		char szDrv[MAX_PATH];
		memset(szDrv, 0, MAX_PATH);
		_splitpath(strChkPath, szDrv, NULL, NULL, NULL);
		if(strlen(szDrv)){
			int nDrv = szDrv[0] - 'A';
			for(int i = 0; i < 4; i++){
				CString strBase = CMainFrame::m_arrUsbState[nDrv].szPath[i];
				if(strBase.IsEmpty()){
					continue;
				}
				strBase.MakeUpper();
				int nBaseLen = strBase.GetLength();
				int nChkLen = strChkPath.GetLength();
				if(nBaseLen > nChkLen){
					continue;
				}
				if(strChkPath.Left(nBaseLen).CompareNoCase(strBase)){
					continue;
				}
				strBasePath = CMainFrame::m_arrUsbState[nDrv].szPath[i];
				strWikiPath = strWikiPath.Mid(1);
				CString strRepPath = strBasePath;
				strRepPath.Replace("/", "\\");
				strWikiPath.Replace(strRepPath, "");
				strBasePath += "\\";
				strBasePath.Replace("\\\\", "\\");
				bUSB = TRUE;
				break;
			}
		}
	}
	return bUSB;
}

CTreeCtrl* CWikiWnd::GetTree(int nSel){
	if(nSel < 0){
		nSel = m_objTab.GetCurSel();
	}
	if(nSel < 0){
		return NULL;
	}
	CTreeCtrl *pTree = NULL;
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TC_ITEM));
	tcItem.mask = TCIF_PARAM;
	m_objTab.GetItem(nSel, &tcItem);
	pTree = (CTreeCtrl*)tcItem.lParam;
	return pTree;
}
void CWikiWnd::OnTabChange(LPNMHDR pNmhdr, HRESULT *pResult){
	*pResult = 0;
	SetCtrlPos();
}

/**
 * @brif
 * @param bActiveTree TRUE�̏ꍇ�A�A�N�e�B�u�ȃc���[�̃x�[�X�p�X���擾���܂��BFALSE�̏ꍇ�APersonalWiki�̃p�X���擾���܂�
 */
CString CWikiWnd::GetBasePath(BOOL bActiveTree /*= FALSE*/){
	CTreeCtrl* pTree = GetTree(-1);
	CString strPath = "";
	if(!bActiveTree || (pTree->m_hWnd == m_objTree.m_hWnd)){
		strPath = CAbstractBaseWnd::GetBasePath();
	}else if(::IsWindow(pTree->m_hWnd)){
		HTREEITEM hItem = pTree->GetChildItem(NULL);
		strPath = pTree->GetItemText(hItem);
		strPath += "\\";
	}
	return strPath;
	
}

void CWikiWnd::OnBtnTreerefresh() {
	FindWikiDoc();
	FindWikiDocUSB();
}

void CWikiWnd::OnUpdateBtnTreerefresh(CCmdUI* pCmdUI) {
}

void CWikiWnd::OnUrlImport(){
	CDlgImpUrlInp dlg;
	if(dlg.DoModal() == IDCANCEL){
		return;
	}
	
	CString strPage = dlg.m_strPage;
	strPage.TrimLeft();
	strPage.TrimRight();

	const char szTarget[] = {'%', '\\', '/', ':', '?', '<', '>', '|'};
	int nLen = sizeof(szTarget) / sizeof(char);
	for(int i = 0; i < nLen; i++){
		CString strRepText;
		CString strRepFrom;
		strRepFrom.Format("%c", szTarget[i]);
		strRepText.Format("%%%0X", szTarget[i]);
		strPage.Replace(strRepFrom, strRepText);
	}

	CString strURL;
	strURL.Format("%s?cmd=edit&page=%s", dlg.m_strUrl, strPage);

	//�y�[�W���_�E�����[�h
	CString strPageData;
	if(!DownloadFile(strURL, strPageData, dlg.m_strID, dlg.m_strPass)){
		return;
	}


	CStringEncode se;
	char* pszEncText = NULL;
	char* pszText = strPageData.GetBuffer(strPageData.GetLength());
	CString strData;
	int nCode = se.CheckCode(pszText);
	switch(nCode){
	case CStringEncode::JIS:
		strData = CStringEncode::jis2sjis(pszText);
		break;
	case CStringEncode::EUC:
		strData = CStringEncode::euc2sjis(pszText);
		break;
	case CStringEncode::UTF8:
		strData = CStringEncode::utf82sjis(pszText);
		break;
	case CStringEncode::SJIS:
		strData = pszText;
		break;
	default:
		AfxMessageBox("�����R�[�h������ł��܂���B");
		strPageData.ReleaseBuffer();
		return;
	}
	if(pszEncText){
		se.ReleaseBuff(pszEncText);
	}
	strPageData.ReleaseBuffer();
	strPageData = strData;


	//TextArea������
	CString strFindData = strPageData;
	strFindData.MakeLower();

	int nPos = strFindData.Find("<textarea");
	if(nPos == -1){
		return;
	}

	//name������msg
	int nStPos = strFindData.Find("name=\"msg\"", nPos);
	if(nStPos == -1){
		return;
	}

	//TextArea�̏I�[���擾
	int nEndPos = strFindData.Find("</textarea", nPos);
	if(nEndPos == -1){
		return;
	}

	//�e�L�X�g��ۑ�����
	nStPos = strFindData.Find(">", nStPos);
	if(nStPos == -1){
		return;
	}
	nStPos++;

	strPageData = strPageData.Mid(nStPos, nEndPos - nStPos);

	//�f�B���N�g���𐶐�
	CString strSavePath = GetBasePath();
	strSavePath += "\\Wiki\\" + dlg.m_strPage;
	strSavePath.Replace("/", "\\");
	strSavePath.Replace("\\\\", "\\");
	if(!::CreateDir(strSavePath, NULL)){
		return;
	}

	//�t�@�C���ۑ�
	strSavePath += ".pwd";
	CFile file;
	try{
		file.Open(strSavePath, CFile::modeCreate | CFile::modeWrite);
		file.Write(strPageData.GetBuffer(strPageData.GetLength()), strPageData.GetLength());
		file.Flush();
		file.Close();
	}catch(CException *e){
		e->Delete();
	}

	FindWikiDoc();

}

void CWikiWnd::OnUpdateUrlImport(CCmdUI* pCmdUI){
#if defined(_DEBUG)
	pCmdUI->Enable(TRUE);
#else
	pCmdUI->Enable(FALSE);
#endif
}


BOOL CWikiWnd::DownloadFile(LPCTSTR pszURL, CString& strRetData, LPCTSTR pszUserID, LPCTSTR pszPass){
typedef enum GETRSSRESULT{
	DONT_GET_SERVERNAME = 0,
	DONT_GET_CONNECTION,
	DONT_OPEN_REQUEST,
	DONT_SET_USERID,
	DONT_SET_PASSWORD,
	DONT_SEND_REQUEST,
	FAILD_REQUEST_STATUS,
};

	CString strUser = pszUserID;
	CString strPass = pszPass;
	CString strURL = pszURL;
	CString strErrMsg = "";
	strRetData = "";
	if(::InternetAttemptConnect(0) != ERROR_SUCCESS){
		//�l�b�g���[�N�ɐڑ��ł��Ă��Ȃ��̂ŉ������Ȃ�
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
		//�T�[�o�[���̎擾
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
											 strUser, 
											 strPass);
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

		//---------------------------------------------------------------------------------
		//���[�U�[ID/�p�X���[�h�̐ݒ肷��B
		if(!strUser.IsEmpty() || !strPass.IsEmpty()){
			//���[�U�[ID
			bRet = ::InternetSetOption(*pHttpFile, 
									 INTERNET_OPTION_USERNAME, 
									 (LPVOID)(LPCTSTR)strUser,  
									 strUser.GetLength());

			if(!bRet){
				throw(DONT_SET_USERID);
			}

			//�p�X���[�h
			bRet = ::InternetSetOption(*pHttpFile, 
									 INTERNET_OPTION_PASSWORD, 
									 (LPVOID)(LPCTSTR)strPass,  
									 strPass.GetLength());

			if(!bRet){
				throw(DONT_SET_PASSWORD);
			}
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);
		if(bHttps){
			DWORD dwFlags =
//							SECURITY_FLAG_128BIT
//						  | SECURITY_FLAG_40BIT 
//						  | SECURITY_FLAG_56BIT 
//						  | SECURITY_FLAG_FORTEZZA						//�Ȃ��Ƃ���ꂽ
//						  | SECURITY_FLAG_IETFSSL4 
							SECURITY_FLAG_IGNORE_CERT_CN_INVALID 
						  | SECURITY_FLAG_IGNORE_CERT_DATE_INVALID 
						  | SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTP 
						  | SECURITY_FLAG_IGNORE_REDIRECT_TO_HTTPS 
//						  | SECURITY_FLAG_IGNORE_REVOCATION 
						  | SECURITY_FLAG_IGNORE_UNKNOWN_CA
//						  | SECURITY_FLAG_IGNORE_WRONG_USAGE 
//						  | SECURITY_FLAG_NORMALBITNESS 
//						  | SECURITY_FLAG_PCT 
//						  | SECURITY_FLAG_PCT4 
//						  | SECURITY_FLAG_SECURE 
//						  | SECURITY_FLAG_SSL 
//						  | SECURITY_FLAG_SSL3 
//						  | SECURITY_FLAG_STRENGTH_MEDIUM 
//						  | SECURITY_FLAG_STRENGTH_STRONG 
//						  | SECURITY_FLAG_STRENGTH_WEAK 
//						  | SECURITY_FLAG_UNKNOWNBIT 
							,
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
		//���N�G�X�g�̑��M
		if(!pHttpFile->SendRequest()){
			DWORD dwErr = GetLastError();
			if(dwErr == ERROR_INTERNET_FORCE_RETRY){
				::PumpMessage(WM_TIMER, WM_TIMER);
				::PumpMessage(WM_PAINT, WM_PAINT);
				//��蒼��
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
		//��Ԏ擾
		DWORD dwRc = 0;
		pHttpFile->QueryInfoStatusCode(dwRc);										
		if (dwRc != HTTP_STATUS_OK){
			throw(FAILD_REQUEST_STATUS);
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);

		//---------------------------------------------------------------------------------
		//���N�G�X�g�̉�����M
		CString strLine;
		while(pHttpFile->ReadString(strLine)){
			strRetData += strLine;
			strRetData += "\r\n";
			::PumpMessage(WM_TIMER, WM_TIMER);
			::PumpMessage(WM_PAINT, WM_PAINT);
		}

		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);
	}catch(GETRSSRESULT eErr){
		switch(eErr){
		case DONT_GET_SERVERNAME:
			strErrMsg = "URL�C���|�[�g : �T�[�o�[�����擾�ł��܂���";
			break;
		case DONT_GET_CONNECTION:
			strErrMsg = "URL�C���|�[�g : �R�l�N�V�����̎擾�Ɏ��s";
			break;
		case DONT_OPEN_REQUEST:
			strErrMsg = "URL�C���|�[�g : ���N�G�X�g�̃I�[�v���Ɏ��s";
			break;
		case DONT_SET_USERID:
		case DONT_SET_PASSWORD:
			strErrMsg = "URL�C���|�[�g : ���[�U�[ID/�p�X���[�h�̐ݒ�Ɏ��s���܂���";
			break;
		case DONT_SEND_REQUEST:
		case FAILD_REQUEST_STATUS:
			strErrMsg = "URL�C���|�[�g : ���N�G�X�g�̑��M�Ɏ��s���܂���";
			break;
		}
		CLogFile::SaveExceptionLog(strErrMsg);
		bRet = FALSE;
	}catch(CInternetException *e){
		CLogFile::SaveExceptionLog(e);
		e->Delete();
		bRet = FALSE;
	}catch(CInternetException& e){
		CLogFile::SaveExceptionLog(&e);
		bRet = FALSE;
	}catch(CException& e){
		CLogFile::SaveExceptionLog(&e);
		bRet = FALSE;
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

void CWikiWnd::UpdateSetting(){
	OnBtnTreerefresh();
}

void CWikiWnd::OnPluginExport(){
	CMainFrame *pFrm = GetMainFrame(this);
	if(!pFrm){
		return;
	}
	
	
	CTreeCtrl *pTree = GetTree(-1);
	BOOL bRet = TRUE;
	HTREEITEM hItem = pTree->GetSelectedItem();
	CString strWikipath;
	CString strFileName;
	CString strBase = GetBasePath(TRUE);
	GetWikiPath(pTree, hItem, strWikipath);

	//�O�����f�B�A�Ή�
	BOOL bUSB = GetUSBPath(strWikipath, strBase);
	
	strFileName.Format("%sWiki\\%s.pwd", strBase, strWikipath);
	strFileName.Replace("/", "\\");
	strFileName.Replace("\\\\", "\\");

	CDlgPluginExport dlg;

	int nSize = pFrm->m_objPlugins.GetSize();
	CPWikiPlugin* pPlugin;
	for(int i = 0; i < nSize; i++){
		pPlugin = pFrm->m_objPlugins.GetPlugin(i);
		if(pPlugin && (pPlugin->GetUse() && pPlugin->m_objInfo.arrType[eTypeExportExtend])){
			dlg.m_arrPluginName.Add(pPlugin->m_objInfo.szName);
		}
	}

	CString strBuff;
	if(LD_OK != LoadWikiText(strWikipath, strBase, strBuff)){
		strBuff = "";
	}

	dlg.m_strWikiPath = strWikipath;
	
	if(dlg.DoModal() != IDOK){
		return;
	}

	CString strSelPlugin = dlg.m_strSelPlugin;
	nSize = pFrm->m_objPlugins.GetSize();
//	CString strBase = GetBasePath();
	CString strTmp;
	strTmp.Format("%sexptmp.html", strBase);
	for(i = 0; i < nSize; i++){
		pPlugin = pFrm->m_objPlugins.GetPlugin(i);
		if(pPlugin && (pPlugin->GetUse() && pPlugin->m_objInfo.arrType[eTypeExportExtend])){
			if(!strSelPlugin.Compare(pPlugin->m_objInfo.szName)){
				LPCTSTR pszBuff = NULL;
				//�G�N�X�|�[�g������
				switch(pPlugin->ReqDataType()){
				case EXP_WIKITEXT:
					pszBuff = strBuff;
					break;

				case EXP_WIKIFILE:
					pszBuff = strFileName;
					break;
	
				case EXP_HTMLFILE:
					{
						CStdioFile file;
						WIKIINFO objIni;
						CAnalisysWiki objAnalisys;
						CString strDetail = strBuff;
						CString strDetail2 = "";
						CString strHtml = "";
						
						pFrm->m_objIniFile.GetWikiInfoIniData(objIni);
						ANAINFO objAnaInfo;
						memset(&objAnaInfo, 0, sizeof(ANAINFO));
						objAnaInfo.bUseRetFormat = objIni.bUseRet;
						objAnaInfo.bUseTBLink = objIni.bUseTopBtmLnk;
						objAnaInfo.bShowAttach = objIni.bUseShowAttach;
						objAnaInfo.bUseShowConvTime = objIni.bUseShowConvTime;
						strcpy(objAnaInfo.pszBasePath, strBase);
						strcpy(objAnaInfo.pszAppendPath, "");
						objAnalisys.SetAnaSetting(&objAnaInfo);
						objAnalisys.SetMimeType(&pFrm->m_objMimeTypes);
						objAnalisys.Analisys(strDetail, strDetail2, strWikipath, FALSE);
						CString strTitle = strWikipath;

						CString strHead;
						objAnalisys.CreateHTML(strHtml, objIni.szCss, strTitle, strDetail2);
						try{						
							if(!file.Open(strTmp, CFile::modeCreate | CFile::modeReadWrite)){
								throw(0);
							}
							file.WriteString(strHtml);
							file.Close();
						}catch(CFileException* fe){
						}catch(int ne){
						}
						pszBuff = strTmp;
					}
					break;
				}

				if(pPlugin->Export((char*)pszBuff)){
					AfxMessageBox("�G�N�X�|�[�g���������܂���");
				}else{
					AfxMessageBox("�G�N�X�|�[�g�Ɏ��s���܂���");
				}

				if(pPlugin->ReqDataType() == EXP_HTMLFILE){
					::DeleteFile(strTmp);
				}
				break;
			}
		}
	}

}

void CWikiWnd::OnUpdatePluginExport(CCmdUI* pCmdUI){
	CMainFrame *pFrm = GetMainFrame(this);
	BOOL bEnable = FALSE;
	if(pFrm){
		int nSize = pFrm->m_objPlugins.GetSize();
		CPWikiPlugin* pPlugin;
		for(int i = 0; i < nSize; i++){
			pPlugin = pFrm->m_objPlugins.GetPlugin(i);
			if(pPlugin && (pPlugin->GetUse() && pPlugin->m_objInfo.arrType[eTypeExportExtend])){
				bEnable = TRUE;
				break;
			}
		}
	}
	pCmdUI->Enable(bEnable);
}

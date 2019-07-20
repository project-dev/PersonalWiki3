// RSSList.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "rssplugin.h"
#include "RSSList.h"
#include "RssWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSSList

CRSSList::CRSSList()
{
}

CRSSList::~CRSSList()
{
}


BEGIN_MESSAGE_MAP(CRSSList, CListCtrl)
	//{{AFX_MSG_MAP(CRSSList)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDM_READRSS, OnReadrss)
	ON_UPDATE_COMMAND_UI(IDM_READRSS, OnUpdateReadrss)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRSSList ���b�Z�[�W �n���h��

void CRSSList::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult){
	*pResult = 0;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	if((pNMListView->uChanged & LVIF_STATE == 0) || (pNMListView->uNewState == pNMListView->uOldState)){
		return;
	}
	
	m_pRssWnd->OnUpdateRSS(pNMListView->iItem);
}

void CRSSList::OnContextMenu(CWnd* pWnd, CPoint point) {
	ShowPopupMenu(point, IDR_RSSMENU, this);
	
}

void CRSSList::OnReadrss(){
}

void CRSSList::OnUpdateReadrss(CCmdUI* pCmdUI){
}

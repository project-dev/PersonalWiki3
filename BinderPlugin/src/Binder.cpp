// Binder.cpp: CBinder クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BinderPlugin.h"
#include "Binder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CBinder::CBinder(){
	m_strName = "";
}

CBinder::~CBinder(){
	POSITION pos = m_arrBinderItem.GetHeadPosition();
	PBINDERITEM pBinder;
	while(pos != NULL){
		pBinder = m_arrBinderItem.GetNext(pos);
		DeleteItem(pBinder);
	}
}

int CBinder::AddBinderItem(PBINDERITEM pItem){
	PBINDERITEM pBinder = new BINDERITEM;
	memcpy(pBinder, pItem, sizeof(BINDERITEM));
	POSITION pos = m_arrBinderItem.AddTail(pBinder);
	int nInsIndex = m_arrBinderItem.GetCount() - 1;
	if(pos == NULL){
		return -1;
	}
	return nInsIndex;
}

BOOL CBinder::SetBinderItem(int nIndex, PBINDERITEM pItem){
	POSITION pos = m_arrBinderItem.FindIndex(nIndex);
	if(pos == NULL){
		return FALSE;
	}

	PBINDERITEM pBinder = m_arrBinderItem.GetAt(pos);
	DeleteItem(pBinder);

	m_arrBinderItem.SetAt(pos, pItem);
	return TRUE;
}

BOOL CBinder::DeleteBinderItem(int nIndex){
	POSITION pos = m_arrBinderItem.FindIndex(nIndex);
	if(pos == NULL){
		return FALSE;
	}
	PBINDERITEM pBinder = m_arrBinderItem.GetAt(pos);
	DeleteItem(pBinder);

	m_arrBinderItem.RemoveAt(pos);
	return TRUE;

}

BOOL CBinder::DeleteBinderItem(PBINDERITEM pItem){
	POSITION pos = m_arrBinderItem.Find(pItem, NULL);
	
	if(pos == NULL){
		return FALSE;
	}
	DeleteItem(pItem);

	m_arrBinderItem.RemoveAt(pos);
	return TRUE;

}

PBINDERITEM CBinder::GetBinderItem(int nIndex){
	if(!m_arrBinderItem.GetCount()){
		return NULL;
	}
	POSITION pos = m_arrBinderItem.FindIndex(nIndex);
	if(pos == NULL){
		return NULL;
	}

	PBINDERITEM pItem = m_arrBinderItem.GetAt(pos);
	return pItem;
}

BOOL CBinder::SaveBinderData(LPCTSTR pszRoot){
	CString strSavePath;
	strSavePath.Format("%s\\plugins\\BinderPlugin\\%s.fbd", pszRoot, m_strName);
	CStdioFile file(strSavePath, CFile::modeCreate | CFile::modeReadWrite);
	CString strLine;
	TRY{
		strLine.Format("%s\n", m_strName);
		file.WriteString(strLine);	
		POSITION pos = m_arrBinderItem.GetHeadPosition();
		PBINDERITEM pItem;
		while(pos){
			pItem = m_arrBinderItem.GetNext(pos);
			strLine.Format("%s\n", pItem->pszFilePath);
			file.WriteString(strLine);
		}
		file.Flush();
		file.Close();
	}CATCH_ALL(e){
		file.Flush();
		file.Close();
		return FALSE;
	}END_CATCH_ALL
	return TRUE;
}

HICON CBinder::GetIcon(PBINDERITEM pItem){
	WIN32_FIND_DATA wfd;
	HANDLE hRet = ::FindFirstFile(pItem->pszFilePath, &wfd);
	if(hRet == INVALID_HANDLE_VALUE){
		return NULL;
	}
	::FindClose(hRet);
	SHFILEINFO shfi;
	SHGetFileInfo( pItem->pszFilePath, 0, &shfi, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_SMALLICON );
	return shfi.hIcon;
}

void CBinder::DeleteBinder(LPCTSTR pszRootPath){
	CString strDelPath;
	strDelPath.Format("%s\\plugins\\BinderPlugin\\%s.fbd", pszRootPath, m_strName);
	::DeleteFile(strDelPath);

}

void CBinder::DeleteItem(PBINDERITEM pItem){
	if(!pItem){
		return;
	}

	delete pItem;

}

int CBinder::GetSize(){
	return m_arrBinderItem.GetCount();
}

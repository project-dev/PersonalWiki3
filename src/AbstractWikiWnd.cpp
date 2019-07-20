// AbstractWikiWnd.cpp: CAbstractWikiWnd クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "personalwiki.h"
#include "AbstractWikiWnd.h"
#include "PWikiDoc.h"
#include "MainFrm.h"
#include "LogFile.h"
#include "FindFile.h"
#include "DlgWikiInp.h"
#include "CalView.h"
#include "FileCtrl.h"
#include "EventDate.h"
#include "InfoView.h"
#include "WikiEditWnd.h"
#include "Cryptography.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
CString CAbstractWikiWnd::m_strDataBasePath = "";
CString CAbstractWikiWnd::m_strWikiPath = "";
CMainFrame* CAbstractWikiWnd::m_pFrm = NULL;
CPWikiDoc* CAbstractWikiWnd::m_pDoc = NULL;
CInfoView* CAbstractWikiWnd::m_pInfo = NULL;
CWikiEditWnd* CAbstractWikiWnd::m_pEdit = NULL;

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CAbstractWikiWnd::CAbstractWikiWnd()
{

}

CAbstractWikiWnd::~CAbstractWikiWnd(){

}

void CAbstractWikiWnd::GetHtmlHead(CString &strHtml, LPCTSTR pszTitle){
}
void CAbstractWikiWnd::UpdateInfoSc(COleDateTime *pTargetDate){
	CString strTmp;
	CString strBase = GetBasePath();
	strTmp.Format("%stmp.html", strBase);
	CStdioFile file;
	CString strHtml = "";
	CPWikiDoc* pDoc = m_pDoc;
	CString strImg = strBase + "Img\\";

	CEventDate *pDate = pDoc->FindDate(pTargetDate->GetYear(), pTargetDate->GetMonth(), pTargetDate->GetDay());
	CString strFixData = "";
	CString strToDo = "";
	CString strSpDay = "";

	//定期データ検索
	BOOL bHoliday;
	pDoc->FindFixedDate(pTargetDate->GetYear(), pTargetDate->GetMonth(), pTargetDate->GetDay(), strFixData, bHoliday);
	if(strFixData.IsEmpty()){
		strFixData = "なし";
	}

	//関連ToDo検索
	pDoc->FindToDoDate(pTargetDate->GetYear(), pTargetDate->GetMonth(), pTargetDate->GetDay(), strToDo, TRUE);
	if(strToDo.IsEmpty()){
		strToDo = "なし";
	}

	//記念日
	pDoc->FindSpecialDay(pTargetDate->GetYear(), pTargetDate->GetMonth(), pTargetDate->GetDay(), strSpDay);
	if(strSpDay.IsEmpty()){
		strSpDay = "なし";
	}
	try{
		if(!file.Open(strTmp, CFile::modeCreate | CFile::modeReadWrite)){
			throw(0);
		}

	
		CString strDetail2 = "";
		int nPos = 0;
		CString strDetail = "";
		CString strSCData = "";
		if(pDate){
			strSCData = pDate->GetDetail();
			m_pEdit->SetText(strSCData, pTargetDate->Format("%Y/%m/%d"), OP_DATE);
		}else{
			m_pEdit->SetText("", pTargetDate->Format("%Y/%m/%d"), OP_DATE);
		}
		if(strSCData.IsEmpty()){
			strSCData = "なし";
		}

		strDetail.Format("**スケジュール\r\n"
						 "%s\r\n"
						 "**定期データ\r\n"
						 "%s\r\n"
						 "**今日は何の日？\r\n"
						 "%s\r\n"
						 "**関連ToDo\r\n"
						 "%s\r\n"
						 ,strSCData
						 ,strFixData
						 ,strSpDay
						 ,strToDo);
		
		CMainFrame *pFrm = m_pFrm;

		WIKIINFO objIni;
		pFrm->m_objIniFile.GetWikiInfoIniData(objIni);
		ANAINFO objAnaInfo;
		memset(&objAnaInfo, 0, sizeof(ANAINFO));
		
		objAnaInfo.bUseRetFormat = objIni.bUseRet;
		objAnaInfo.bUseTBLink = objIni.bUseTopBtmLnk;
		objAnaInfo.bShowAttach = objIni.bUseShowAttach;
		objAnaInfo.bUseShowConvTime = objIni.bUseShowConvTime;
		strcpy(objAnaInfo.pszBasePath, strBase);
		strcpy(objAnaInfo.pszAppendPath, "");
		m_objAnalisys.SetAnaSetting(&objAnaInfo);
		m_objAnalisys.SetMimeType(&pFrm->m_objMimeTypes);
		m_objAnalisys.Analisys(strDetail, strDetail2, NULL, FALSE);

		CString strTitle = pTargetDate->Format("%Y/%m/%dのスケジュール");

		CString strHead;
		m_objAnalisys.CreateHTML(strHtml, objIni.szCss, strTitle, strDetail2);
		file.WriteString(strHtml);
		file.Close();
		m_pInfo->Navigate2(strTmp,NULL,NULL);
	}catch(CFileException &fe){
		CLogFile::SaveExceptionLog(&fe, "CInfoView::UpdateInfo (DateTime)");
	}catch(...){
		CLogFile::SaveExceptionLog("CInfoView::UpdateInfo (DateTime)");
	}
}
void CAbstractWikiWnd::UpdateInfo(CString &strWikiPath){
	CString strTmp;
	CString strBase = GetBasePath();
	strTmp.Format("%stmp.html", strBase);
	CStdioFile file;
	CString strHtml = "";
	CPWikiDoc* pDoc = m_pDoc;
	CString strImg = strBase + "Img\\";
	CString strDetail = "";

	while(!strWikiPath.Right(1).Compare("/")){
		strWikiPath = strWikiPath.Left(strWikiPath.GetLength() - 1);
	}


	CString strWikiDataPath;
	strWikiDataPath.Format("%sWiki\\%s.pwd", strBase, strWikiPath);
	strWikiDataPath.Replace("/", "\\");

	CString strPropFile = strWikiDataPath;
	strPropFile.Replace(".pwd", "\\.property");
	BOOL bCryp = (BOOL)GetInifileInt("Status", "Cryptography", 0, strPropFile);
	

	if(CFindFile::IsExistFile(strWikiDataPath)){
		try{
			if(!file.Open(strWikiDataPath, CFile::modeRead)){
				throw(0);
			}
			CString strLine = "";
			while(file.ReadString(strLine)){
				strDetail += strLine;
				if(!bCryp){
					strDetail += "\r\n";
				}
			}
			file.Close();
			if(bCryp){
				//復号化する
				CCryptography cryp;
				int nLen = strDetail.GetLength();
				byte *pBuff = NULL;
				char *pszFrom = strDetail.GetBuffer(strDetail.GetLength());
				cryp.DecodeData((byte*)pszFrom, nLen, "PersonalWiki", pBuff);
				strDetail.ReleaseBuffer();
				if(pBuff){
					strDetail = pBuff;
				}else{
					strDetail.Empty();
				}
			}

		}catch(CFileException &fe){
			CLogFile::SaveExceptionLog(&fe, "CInfoView::UpdateInfo (WikiPage)");
		}
		m_pEdit->SetText(strDetail, strWikiDataPath, OP_WIKI);
	}else{
		//ページの新規作成
		CMainFrame *pFrm = m_pFrm;
		CInfoTabView *pInfo = pFrm->GetInfoTabView();
		CCalView *pCalView = pFrm->GetCalView();
#if 1
		m_strWikiPath = strWikiPath;
		CString strCreDir;
		CString strCreDirAtt;
		CString strFilePath;
		pDoc->CreateWikiDir(strWikiPath, NULL, strFilePath, strCreDir, strCreDirAtt);

		if(CFileCtrl::CreateDirectory(strCreDir)){
		}
		if(CFileCtrl::CreateDirectory(strCreDirAtt)){
		}

		CString strData = "";
		file.Open(strFilePath, CFile::modeCreate | CFile::modeNoInherit | CFile::modeReadWrite);
		file.Write(strData.GetBuffer(0), strData.GetLength());
		file.Flush();
		file.Close();
		if(!strWikiPath.IsEmpty()){
			pCalView->UpdateWikiTree();
			pCalView->UpdateWikiTree(TRUE);
			pCalView->ActiveWikiPage(strWikiPath);
			//新規ページの読み込み
			UpdateInfo(strWikiPath);
			return;
		}
#else
		CDlgWikiInp dlg;
		dlg.m_strSetText = "";
		dlg.m_strWikiPath = strWikiPath;

		CString strCreDir;
		CString strCreDirAtt;
		CString strFilePath;
		pDoc->CreateWikiDir(strWikiPath, NULL, strFilePath, strCreDir, strCreDirAtt);
	

		if(dlg.DoModal() == IDOK){
			CString strData = dlg.m_strSetText;
			if(!strData.IsEmpty()){
				if(CFileCtrl::CreateDirectory(strCreDir)){
				}
				if(CFileCtrl::CreateDirectory(strCreDirAtt)){
				}
				file.Open(strFilePath, CFile::modeCreate | CFile::modeNoInherit | CFile::modeReadWrite);
				file.Write(strData.GetBuffer(0), strData.GetLength());
				file.Flush();
				file.Close();
				if(!strWikiPath.IsEmpty()){
					pCalView->UpdateWikiTree();
					pCalView->UpdateWikiTree(TRUE);
					pCalView->ActiveWikiPage(strWikiPath);
					//新規ページの読み込み
					UpdateInfo(strWikiPath);
					return;
				}
			}
		}
#endif
	}
	CString strFixData = "";
	CString strToDo = "";

	try{
		if(!file.Open(strTmp, CFile::modeCreate | CFile::modeReadWrite)){
			throw(0);
		}

	
		CString strDetail2 = "";
		int nPos = 0;

		CMainFrame *pFrm = m_pFrm;
		WIKIINFO objIni;
		pFrm->m_objIniFile.GetWikiInfoIniData(objIni);
		ANAINFO objAnaInfo;
		memset(&objAnaInfo, 0, sizeof(ANAINFO));
		objAnaInfo.bUseRetFormat = objIni.bUseRet;
		objAnaInfo.bUseTBLink = objIni.bUseTopBtmLnk;
		objAnaInfo.bShowAttach = objIni.bUseShowAttach;
		objAnaInfo.bUseShowConvTime = objIni.bUseShowConvTime;
		strcpy(objAnaInfo.pszBasePath, strBase);
		strcpy(objAnaInfo.pszAppendPath, "");
		m_objAnalisys.SetAnaSetting(&objAnaInfo);
		m_objAnalisys.SetMimeType(&pFrm->m_objMimeTypes);
		m_objAnalisys.Analisys(strDetail, strDetail2, strWikiPath, FALSE);

		CString strTitle = strWikiPath;

		CString strHead;
		m_objAnalisys.CreateHTML(strHtml, objIni.szCss, strTitle, strDetail2);

		file.WriteString(strHtml);
		file.Close();
		m_pInfo->Navigate2(strTmp,NULL,NULL);
	}catch(CFileException &fe){
		CLogFile::SaveExceptionLog(&fe, "CInfoView::UpdateInfo (WikiPage)");
	}catch(...){
		CLogFile::SaveExceptionLog("CInfoView::UpdateInfo (WikiPage)");
	}
}
void CAbstractWikiWnd::UpdateInfoUSB(CString &strWikiPath, LPCTSTR pszBasePath){
	CString strTmp;
	CString strBase = pszBasePath;
	strTmp.Format("%stmp.html", strBase);
	CStdioFile file;
	CString strHtml = "";
	CPWikiDoc* pDoc = m_pDoc;
	CString strImg = strBase + "Img\\";
	CString strDetail = "";

	CString strWikiDataPath;
	strWikiDataPath.Format("%sWiki\\%s.pwd", strBase, strWikiPath);
	strWikiDataPath.Replace("/", "\\");

	CString strPropFile = strWikiDataPath;
	strPropFile.Replace(".pwd", "\\.property");
	BOOL bCryp = (BOOL)GetInifileInt("Status", "Cryptography", 0, strPropFile);

	if(CFindFile::IsExistFile(strWikiDataPath)){
		try{
			if(!file.Open(strWikiDataPath, CFile::modeRead)){
				throw(0);
			}
			CString strLine = "";
			while(file.ReadString(strLine)){
				strDetail += strLine;
				if(!bCryp){
					strDetail += "\r\n";
				}
			}
			file.Close();
			if(bCryp){
				//復号化する
				CCryptography cryp;
				int nLen = strDetail.GetLength();
				byte *pBuff = NULL;
				char *pszFrom = strDetail.GetBuffer(strDetail.GetLength());
				cryp.DecodeData((byte*)pszFrom, nLen, "PersonalWiki", pBuff);
				strDetail.ReleaseBuffer();
				if(pBuff){
					strDetail = pBuff;
				}else{
					strDetail.Empty();
				}
			}
			m_pEdit->SetText(strDetail, strWikiDataPath, OP_USB);
		}catch(CFileException &fe){
			CLogFile::SaveExceptionLog(&fe, "CInfoView::UpdateInfo (WikiPage)");
		}
	}else{
		//ページの新規作成
		CMainFrame *pFrm = m_pFrm;
		CInfoTabView *pInfo = pFrm->GetInfoTabView();
		CCalView *pCalView = pFrm->GetCalView();
#if 1
		m_strWikiPath = strWikiPath;
		CString strCreDir;
		CString strCreDirAtt;
		CString strFilePath;
		pDoc->CreateWikiDir(strWikiPath, pszBasePath, strFilePath, strCreDir, strCreDirAtt);

		if(CFileCtrl::CreateDirectory(strCreDir)){
		}
		if(CFileCtrl::CreateDirectory(strCreDirAtt)){
		}
		CString strData = "";
		file.Open(strFilePath, CFile::modeCreate | CFile::modeNoInherit | CFile::modeReadWrite);
		file.Write(strData.GetBuffer(0), strData.GetLength());
		file.Flush();
		file.Close();
		if(!strWikiPath.IsEmpty()){
			pCalView->UpdateWikiTree();
			pCalView->UpdateWikiTree(TRUE);
			CString strWikiPath2;
			strWikiPath2.Format("%s%s", pszBasePath, strWikiPath);
			strWikiPath2.Replace("\\/", "/");
			pCalView->ActiveWikiPage(strWikiPath2);
			//新規ページの読み込み
			UpdateInfoUSB(strWikiPath, pszBasePath);
			return;
		}
#else
		CDlgWikiInp dlg;
		dlg.m_strSetText = "";
		dlg.m_strWikiPath = strWikiPath;

		CString strCreDir;
		CString strCreDirAtt;
		CString strFilePath;
		pDoc->CreateWikiDir(strWikiPath, pszBasePath, strFilePath, strCreDir, strCreDirAtt);
	

		if(dlg.DoModal() == IDOK){
			CString strData = dlg.m_strSetText;
			if(!strData.IsEmpty()){
				if(CFileCtrl::CreateDirectory(strCreDir)){
				}
				if(CFileCtrl::CreateDirectory(strCreDirAtt)){
				}
				file.Open(strFilePath, CFile::modeCreate | CFile::modeNoInherit | CFile::modeReadWrite);
				file.Write(strData.GetBuffer(0), strData.GetLength());
				file.Flush();
				file.Close();
				if(!strWikiPath.IsEmpty()){
					pCalView->UpdateWikiTree();
					pCalView->UpdateWikiTree(TRUE);
					CString strWikiPath2;
					strWikiPath2.Format("%s%s", pszBasePath, strWikiPath);
					strWikiPath2.Replace("\\/", "/");
					pCalView->ActiveWikiPage(strWikiPath2);
					//新規ページの読み込み
					UpdateInfoUSB(strWikiPath, pszBasePath);
					return;
				}
			}
		}
#endif
	}
	CString strFixData = "";
	CString strToDo = "";

	try{
		if(!file.Open(strTmp, CFile::modeCreate | CFile::modeReadWrite)){
			throw(0);
		}

	
		CString strDetail2 = "";
		int nPos = 0;

		CMainFrame *pFrm = m_pFrm;
		WIKIINFO objIni;
		pFrm->m_objIniFile.GetWikiInfoIniData(objIni);
		ANAINFO objAnaInfo;
		memset(&objAnaInfo, 0, sizeof(ANAINFO));
		objAnaInfo.bUseRetFormat = objIni.bUseRet;
		objAnaInfo.bUseTBLink = objIni.bUseTopBtmLnk;
		objAnaInfo.bShowAttach = objIni.bUseShowAttach;
		objAnaInfo.bUseShowConvTime = objIni.bUseShowConvTime;
		strcpy(objAnaInfo.pszBasePath, strBase);
		CString strAppendPath = "";
		strAppendPath = strBase;
		strAppendPath += "\\Wiki\\";
		strAppendPath.Replace("\\\\", "\\");
		if(!strAppendPath.Right(1).Compare("\\")){
			strAppendPath = strAppendPath.Left(strAppendPath.GetLength() - 1);
		}
//		nPos = strAppendPath.ReverseFind('\\');
//		if((nPos != -1) && (nPos == strAppendPath.GetLength() - 1)){
//			strAppendPath = strAppendPath.Mid(nPos);
//		}
		strcpy(	objAnaInfo.pszAppendPath, strAppendPath);

		m_objAnalisys.SetAnaSetting(&objAnaInfo);
		m_objAnalisys.SetMimeType(&pFrm->m_objMimeTypes);
		m_objAnalisys.Analisys(strDetail, strDetail2, strWikiPath, FALSE);

		CString strTitle = strWikiPath;

		CString strHead;
		m_objAnalisys.CreateHTML(strHtml, objIni.szCss, strTitle, strDetail2);

		file.WriteString(strHtml);
		file.Close();
		m_pInfo->Navigate2(strTmp,NULL,NULL);
	}catch(CFileException &fe){
		CLogFile::SaveExceptionLog(&fe, "CInfoView::UpdateInfo (WikiPage)");
	}catch(...){
		CLogFile::SaveExceptionLog("CInfoView::UpdateInfo (WikiPage)");
	}
}


eLOADSTATE CAbstractWikiWnd::LoadWikiText(LPCTSTR pszWikiPath, LPCTSTR pszBasePath, CString &strBuff){
	strBuff = "";
	
	CStdioFile file;
	CString strBase = pszBasePath;
	CString strWikiDataPath;
	strWikiDataPath.Format("%sWiki\\%s.pwd", strBase, pszWikiPath);
	strWikiDataPath.Replace("/", "\\");

	CString strPropFile = strWikiDataPath;
	strPropFile.Replace(".pwd", "\\.property");
	BOOL bCryp = (BOOL)GetInifileInt("Status", "Cryptography", 0, strPropFile);

	if(CFindFile::IsExistFile(strWikiDataPath)){
		try{
			if(!file.Open(strWikiDataPath, CFile::modeRead)){
				throw(0);
			}
			CString strLine = "";
			while(file.ReadString(strLine)){
				strBuff += strLine;
				if(!bCryp){
					strBuff += "\r\n";
				}
			}
			file.Close();
			if(bCryp){
				//復号化する
				CCryptography cryp;
				int nLen = strBuff.GetLength();
				byte *pBuff = NULL;
				char *pszFrom = strBuff.GetBuffer(strBuff.GetLength());
				cryp.DecodeData((byte*)pszFrom, nLen, "PersonalWiki", pBuff);
				strBuff.ReleaseBuffer();
				if(pBuff){
					strBuff = pBuff;
				}else{
					strBuff.Empty();
				}
			}
			return LD_OK;
		}catch(CFileException &fe){
			CLogFile::SaveExceptionLog(&fe, "CInfoView::UpdateInfo (WikiPage)");
		}
	}else{
		//ページの新規作成
		return LD_NEW;
	}
	return LD_NG;
}

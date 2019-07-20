// PWikiPlgList.cpp: CPWikiPlgList �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "personalwiki.h"
#include "PWikiPlgList.h"
#include "devlib.h"
#include "LogFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CPWikiPlgList::CPWikiPlgList()
{

}

CPWikiPlgList::~CPWikiPlgList()
{

}

BOOL CPWikiPlgList::Create(LPCTSTR pszPluginDir){
	m_strPluginPath = pszPluginDir;
	return TRUE;
}

void CPWikiPlgList::EnumPlugins(BOOL bLogOut, BOOL bAppLog, BOOL bExceptLog, BOOL bFatalLog){
	CString strLog;
	CLogFile::SaveAppLog("EnumPlugin Start");
	WIN32_FIND_DATA wfd;
	HANDLE hRet = NULL;
	BOOL isFirst = TRUE;
	CString strPath = m_strPluginPath + "*.pwp";

	while(TRUE){
		CPWikiPlugin* pPlug = NULL;
		CString strPluginPath;
//		::PumpMessage(WM_PAINT, WM_PAINT);

		if(isFirst){
			hRet = ::FindFirstFile(strPath, &wfd);
			isFirst = FALSE;
			if(hRet == INVALID_HANDLE_VALUE){
				return;
			}
		}else{
			if(!::FindNextFile(hRet, &wfd)){
				//��������
				break;
			}
		}
		pPlug = new CPWikiPlugin();
		
		strPluginPath.Format("%s%s", m_strPluginPath, wfd.cFileName); 

		try{
			strLog.Format("%s ��ǂݍ��݂܂�", strPluginPath);
			CLogFile::SaveAppLog(strLog);
			
			if(!pPlug->LoadPlugin(strPluginPath)){
				strLog.Format("%s �͓ǂݍ��߂܂���ł���", strPluginPath);
				CLogFile::SaveAppLog(strLog);
				delete pPlug;
				continue;
			}
			if(!pPlug->GetPluginInfo()){
				pPlug->ExitPlugin();
				pPlug->ReleasePlugin();
				strLog.Format("%s �̓v���O�C���Ƃ��ĔF���ł��܂���ł���", strPluginPath);
				CLogFile::SaveAppLog(strLog);
				delete pPlug;
				continue;
			}
			LPVOID pVal;
			if(m_mapPlugin.Lookup(pPlug->m_objInfo.szName, pVal)){
				pPlug->ExitPlugin();
				pPlug->ReleasePlugin();
				delete pPlug;
				continue;
			}
			try{
				//�f�o�b�O���ݒ�
				pPlug->SetLogFlag(bLogOut, bAppLog, bExceptLog, bFatalLog);
			}catch(CPWikiPluginException *pe){
				pe->Delete();
			}
			m_mapPlugin.SetAt(pPlug->m_objInfo.szName, pPlug);
			strLog.Format("%s ���v���O�C���Ƃ��ĔF�����܂���", strPluginPath);
			CLogFile::SaveAppLog(strLog);
		}catch(CException *e){
			if(pPlug){
				m_mapPlugin.RemoveKey(pPlug->m_objInfo.szName);
				delete pPlug;
				pPlug = NULL;
			}
			strLog.Format("%s ��ǂݍ��ݒ��ɗ�O����", strPluginPath);
			CLogFile::SaveExceptionLog(e, strLog);
			e->Delete();
		}
	}
	::FindClose(hRet);
	CLogFile::SaveAppLog("EnumPlugin End");
}

void CPWikiPlgList::ReleasePlugins(){
	CLogFile::SaveAppLog("ReleasePlugins Start");
	POSITION pos = m_mapPlugin.GetStartPosition();
	LPVOID pVal;
	CString strKey;
	while(pos){
		m_mapPlugin.GetNextAssoc(pos, strKey, pVal);
		CPWikiPlugin* pPlug = (CPWikiPlugin*)pVal;
		if(pPlug){
			
			DWORD dwStart = ::GetTickCount();
			while(!pPlug->ExitPlugin()){
				//�I���ł���܂ő҂�
				DWORD dwSpan = ::GetTickCount() - dwStart;
				if(dwSpan > 1000 * 30){
					//30�b�߂�����^�C���A�E�g
					CString strErr;
					strErr.Format("�v���O�C�� %s �͏I�����^�C���A�E�g(30�b)�ɂȂ�܂����B�����I�����܂��B", pPlug->m_objInfo.szName);
					CLogFile::SaveAppLog(strErr);
					AfxMessageBox(strErr);
				}
			}
			pPlug->ReleasePlugin();
			delete pPlug;
		}
		pVal = NULL;
		m_mapPlugin.SetAt(strKey, pVal);

	}
	m_mapPlugin.RemoveAll();
	CLogFile::SaveAppLog("ReleasePlugins End");
}


CPWikiPlugin* CPWikiPlgList::GetPlugin(int nIndex){
	POSITION pos = m_mapPlugin.GetStartPosition();
	LPVOID pVal;
	CString strKey;
	int nCnt = 0;
	while(pos){
		m_mapPlugin.GetNextAssoc(pos, strKey, pVal);
		CPWikiPlugin* pPlug = (CPWikiPlugin*)pVal;
		if(nCnt == nIndex){
			return pPlug;
		}
		nCnt++;
	}
	return NULL;
}

int CPWikiPlgList::GetSize(){
	return m_mapPlugin.GetCount();
}

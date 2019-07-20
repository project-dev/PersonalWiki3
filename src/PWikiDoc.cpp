// PWikiDoc.cpp : CPWikiDoc �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "PersonalWiki.h"
#include "devlib.h"

#include "PWikiDoc.h"
#include "LogFile.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPWikiDoc

IMPLEMENT_DYNCREATE(CPWikiDoc, CDocument)

BEGIN_MESSAGE_MAP(CPWikiDoc, CDocument)
	//{{AFX_MSG_MAP(CPWikiDoc)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPWikiDoc �N���X�̍\�z/����

CPWikiDoc::CPWikiDoc()
{
	// TODO: ���̈ʒu�ɂP�x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CPWikiDoc::~CPWikiDoc(){
}

BOOL CPWikiDoc::OnNewDocument(){
	if (!CDocument::OnNewDocument())
		return FALSE;

	CLogFile::SaveAppLog("CPWikiDoc::OnNewDocument");

	CWaitCursor objCur;

	//�t�H���_�̑��݊m�F
	CString strDir[] = {
		"ToDo",		//ToDo
		"Date",		//�X�P�W���[��
		"Img",		//�C���[�W
		"Wiki",		//Wiki
		"FixPlan",	//����f�[�^
		"Log",		//���O
		"CSS",		//�X�^�C���V�[�g
	};
	int nSize = sizeof(strDir) / sizeof(CString);
	CString strDataPath = GetBasePath();
	for(int i = 0; i < nSize; i++){
		CString strChk;
		strChk.Format("%s%s\\", strDataPath, strDir[i]);
		if(::CreateDirectory(strChk, NULL)){
			CString strLog;
			strLog.Format("%s �쐬", strChk);
			CLogFile::SaveAppLog(strLog);
		}
		::PumpMessage(WM_TIMER, WM_TIMER);
		::PumpMessage(WM_PAINT, WM_PAINT);
 	}

	CLogFile::SaveAppLog("ToDo�f�[�^�̓ǂݍ���");
	strDataPath = GetBasePath();
	strDataPath += "ToDo\\";
	m_objToDoData.SetDataDir(strDataPath);
	if(!m_objToDoData.LoadToDo()){
		CLogFile::SaveAppLog("ToDo�f�[�^�̓ǂݍ��ݎ��s");
		AfxMessageBox("ToDo�f�[�^�̓ǂݍ��݂Ɏ��s���܂���");
	}

	strDataPath = GetBasePath();
	strDataPath += "FixPlan\\";
	m_objFixedData.SetDataDir(strDataPath);
	if(!m_objFixedData.LoadFixedData()){
		CLogFile::SaveAppLog("����f�[�^�̓ǂݍ��ݎ��s");
		AfxMessageBox("����f�[�^�̓ǂݍ��݂Ɏ��s���܂���");
	}

	CLogFile::SaveAppLog("�X�P�W���[���f�[�^�̓ǂݍ���");
	COleDateTime objCurrent = COleDateTime::GetCurrentTime();
	strDataPath = GetBasePath();
	strDataPath += "Date\\";
	m_objScDateData.SetDataDir(strDataPath);
	m_objScDateData.SetDataDir(strDataPath);
	if(!m_objScDateData.LoadDate(&objCurrent)){
		CLogFile::SaveAppLog("�X�P�W���[���f�[�^�̓ǂݍ��ݎ��s");
		AfxMessageBox("�X�P�W���[���f�[�^�̓ǂݍ��݂Ɏ��s���܂���");
	}
	SetTitle("Personal Wiki");

	CFile file;
	strDataPath = GetBasePath();
	strDataPath += "Category.txt";
	try{
		if(file.Open(strDataPath, CFile::modeReadWrite)){
			CFileStatus status;
			file.GetStatus(status);
			char *pszCategory = new char[status.m_size + 1];
			memset(pszCategory, 0, status.m_size + 1);
			file.Read(pszCategory, status.m_size);
			file.Close();
			CString strCategory = pszCategory;
			delete pszCategory;
			CString strLine;
			int nPos;
			while(!strCategory.IsEmpty()){
				nPos = strCategory.Find("\r\n");
				if(nPos == -1){
					strLine = strCategory;
					strCategory = "";
				}else{
					strLine = strCategory.Left(nPos);
					strCategory = strCategory.Right(strCategory.GetLength() - nPos - 2);
				}
				m_arrCategory.Add(strLine);
				::PumpMessage(WM_TIMER, WM_TIMER);
				::PumpMessage(WM_PAINT, WM_PAINT);
			}
		}
	}catch(CFileException &fe){
		CLogFile::SaveExceptionLog(&fe, "OnNewDocument");
	}catch(CMemoryException &me){
		CLogFile::SaveExceptionLog(&me, "OnNewDocument");
	}

	CLogFile::SaveAppLog("CPWikiDoc::OnNewDocument End");

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPWikiDoc �V���A���C�[�[�V����

void CPWikiDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���̈ʒu�ɕۑ��p�̃R�[�h��ǉ����Ă��������B
	}
	else
	{
		// TODO: ���̈ʒu�ɓǂݍ��ݗp�̃R�[�h��ǉ����Ă��������B
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPWikiDoc �N���X�̐f�f

#ifdef _DEBUG
void CPWikiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPWikiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPWikiDoc �R�}���h


void CPWikiDoc::OnCloseDocument() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CLogFile::SaveAppLog("ToDo�f�[�^��������");
	m_objToDoData.SaveToDo();

	CLogFile::SaveAppLog("����f�[�^��������");
	m_objFixedData.SaveFixedData();

	CLogFile::SaveAppLog("�X�P�W���[���f�[�^��������");
	m_objScDateData.SaveDate();

	CFile file;
	CString strDataPath = GetBasePath();
	strDataPath += "Category.txt";
	try{
		CString strLine = "";
		int nCnt = m_arrCategory.GetSize();
		for(int i = 0; i < nCnt; i++){
			strLine += m_arrCategory.GetAt(i);
			strLine += "\r\n";
		}
		file.Open(strDataPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
		file.Write(strLine, strLine.GetLength());
		file.Close();
	}catch(CFileException &fe){
		CLogFile::SaveExceptionLog(&fe, "OnCloseDocument");
	}catch(CMemoryException &me){
		CLogFile::SaveExceptionLog(&me, "OnCloseDocument");
	}

	CDocument::OnCloseDocument();
}

CEventDate* CPWikiDoc::FindDate(int nYear, int nMonth, int nDay){
	COleDateTime objDate;
	objDate.SetDate(nYear, nMonth, nDay);
	return m_objScDateData.GetDate(objDate);
}

void CPWikiDoc::FindFixedDate(int nYear, int nMonth, int nDay, CString &strDetail, BOOL &bHoliday){
	int nSize = m_objFixedData.GetSize();
	CEventDate *pData;
	COleDateTime objDate;
	eSCTYPE eType;
	bHoliday = FALSE;
	for(int i = 0; i < nSize; i++){
		pData = m_objFixedData.GetFixedData(i);
		if(!pData){
			continue;
		}
		eType = pData->GetType();
		switch(eType){
		case SC_FIX_YEAR:
			{
				int nChkMonth;
				int nChkDay;
				pData->GetMonthDay(nChkMonth, nChkDay);
#if 1
				if((nChkMonth == nMonth)
				&& (nChkDay == nDay)){
					strDetail += pData->GetName();
					strDetail += "�@\r\n";
					if(!bHoliday){
						bHoliday = pData->GetHoliday();
					}
				}
#else
				if(pDate->IsHolyDay(nYear, nChkMonth, nChkDay)){
					if((nChkMonth == nMonth)
					&& (nChkDay == nDay)){
						strDetail += pData->GetName();
						strDetail += "\r\n";
					}else{
						int nSiftYear = nYear;
						int nSiftMonth;
						int nSiftDay;
						if((abs(nMonth - nChkMonth) <= 1)
						&& (abs(nDay - nChkDay) <= 1)){
							if(pData->ChkShiftPlan(nSiftYear, nSiftMonth, nSiftDay)){
							}
						}
					
					}
				}
#endif
			}
			break;
		case SC_FIX_MONTH1:
			{
				int nChkMonth;
				int nChkDay;
				pData->GetMonthDay(nChkMonth, nChkDay);
				if(nChkDay == nDay){
					strDetail += pData->GetName();
					strDetail += "�@\r\n";
				}
			}
			break;
		case SC_FIX_MONTH2:
			{
				int nWeek = GetDayOfWeekNum(nDay);
				if((pData->GetSpan() + 1) == nWeek){
					//��n�T����v
					COleDateTime objDate(nYear, nMonth, nDay, 0, 0, 0);
					int nChkWeekDay = objDate.GetDayOfWeek();
					if(nChkWeekDay == (pData->GetWeekDay() + 1)){
						strDetail += pData->GetName();
						strDetail += "�@\r\n";
					}
				}
			}
			break;
		case SC_FIX_WEEK:
			{
				COleDateTime objDate(nYear, nMonth, nDay, 0, 0, 0);
				int nWeekDay = objDate.GetDayOfWeek() - 1;
				if(pData->GetWeekDay(nWeekDay)){
					strDetail += pData->GetName();
					strDetail += "�@\r\n";
				}
			}
			break;
		}
	}
}

void CPWikiDoc::FindSpecialDay(int nYear, int nMonth, int nDay, CString &strDetail){
	CString strBase = GetBasePath();
	CString strSpDir = strBase + "SpDay";
	CString strFind = strSpDir + "\\*.spd";
	BOOL bFirst = TRUE;
	WIN32_FIND_DATA wfd;
	HANDLE hRet = NULL;
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
		CString strIni;
		char szVal[MAX_PATH + 1];
		memset(szVal, 0, MAX_PATH + 1);
		strIni = strSpDir + "\\" + wfd.cFileName;
		int nUse = ::GetPrivateProfileInt("Setting", "Use", 1, strIni);
		if(nUse != 0){
			CString strSec;
			CString strKey;
			strSec.Format("Month%02d", nMonth);
			strKey.Format("Day%02d", nDay);
			char szValue[1025];
			memset(szValue, 0, 1025);
			::GetPrivateProfileString(strSec, strKey, "", szValue, 1024, strIni);
			CString strVal = szValue;
			strVal.TrimLeft();
			strVal.TrimRight();
			strDetail += strVal;
		}

	}
	::FindClose(hRet);
}


void CPWikiDoc::FindToDoDate(int nYear, int nMonth, int nDay, CString &strDetail, BOOL bGetDetail){
	int nSize = m_objToDoData.GetSize();
	CEventDate *pData;
	COleDateTime objStDate;
	COleDateTime objEdDate;
	COleDateTime objStPlDate;
	COleDateTime objEdPlDate;
	COleDateTime objDate;
	objDate.SetDateTime(nYear, nMonth, nDay, 0, 0, 0);
	for(int i = 0; i < nSize; i++){
		pData = m_objToDoData.GetToDo(i);
		if(!pData){
			continue;
		}
		pData->GetProgress(&objStDate, &objEdDate);
		pData->GetPlan(&objStPlDate, &objEdPlDate);
		
		int nY = objStDate.GetYear();
		int nM = objStDate.GetMonth();
		int nD = objStDate.GetDay();
		objStDate.SetDateTime(nY, nM, nD, 0, 0, 0);

		nY = objEdDate.GetYear();
		nM = objEdDate.GetMonth();
		nD = objEdDate.GetDay();
		objEdDate.SetDateTime(nY, nM, nD, 0, 0, 0);

		nY = objStPlDate.GetYear();
		nM = objStPlDate.GetMonth();
		nD = objStPlDate.GetDay();
		objStPlDate.SetDateTime(nY, nM, nD, 0, 0, 0);

		nY = objEdPlDate.GetYear();
		nM = objEdPlDate.GetMonth();
		nD = objEdPlDate.GetDay();
		objEdPlDate.SetDateTime(nY, nM, nD, 0, 0, 0);
		if(((objStDate   <= objDate) && (objEdDate   >= objDate) && (pData->GetState() == 4))
		|| ((objStPlDate <= objDate) && (objEdPlDate >= objDate))
		){
			if(bGetDetail){
				CString strText;
				CString strDet = pData->GetDetail();
				if(strDet.IsEmpty()){
					strDet = "�Ȃ�";
				}
				strText.Format("***%s �y%6.2f%% - %s�z\r\n"
							   "''�ڍׁF''\r\n"
							   "%s\r\n"
							   ,pData->GetName()
							   ,pData->GetProcess()
							   ,pData->GetStateString()
							   ,strDet);
				strDetail += strText;
			}else{
				if(!strDetail.IsEmpty()){
					strDetail += " ";
				}
				strDetail += pData->GetName();
				strDetail +="(";
				strDetail += pData->GetStateString();
				strDetail +=")";
			}
			strDetail += "\r\n";
		}
	}
}

int CPWikiDoc::GetWeek(int nYear, int nMonth, int nDay){
	COleDateTime objDate;
	COleDateTime objChkDate;
	objDate.SetDate(nYear, nMonth, 1);
	objChkDate.SetDate(nYear, nMonth, nDay);
	//������n�T�������߂��遫��
	int nStart = objDate.GetDayOfWeek();
	double dDay2 = (double)nDay + (double)nStart + 1.0;
	int nWeek = (int)(dDay2 / 7.0 + 0.5);
	return nWeek;
}

int CPWikiDoc::GetDayOfWeekNum(int nDay){
	int nMod = nDay % 7;
	int nWeek = (nDay - nMod) / 7;
	if(nMod){
		nWeek++;
	}
	return nWeek;
}

BOOL CPWikiDoc::CreateWikiDir(LPCTSTR pszWikiPage, LPCTSTR pszBasePath, CString &strWikiPage, CString &strWikiDir, CString &strWikiAttDir){
	CString strBasePath = GetBasePath();
	if(pszBasePath){
		strBasePath = pszBasePath;
	}
	strWikiPage.Format("%sWiki\\%s.pwd", strBasePath, pszWikiPage);
	strWikiDir.Format("%sWiki\\%s", strBasePath, pszWikiPage);
	strWikiAttDir.Format("%sAttach\\%s", strBasePath, pszWikiPage);
		
	strWikiPage.Replace("/", "\\");
	strWikiDir.Replace("/", "\\");
	strWikiAttDir.Replace("/", "\\");

	strWikiPage.Replace("\\\\", "\\");
	strWikiDir.Replace("\\\\", "\\");
	strWikiAttDir.Replace("\\\\", "\\");
	return TRUE;
}

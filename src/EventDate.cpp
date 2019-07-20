// EventDate.cpp: CEventDate �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PersonalWiki.h"
#include "EventDate.h"
#include "LogFile.h"
#include "devlib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
static const char* g_pszState[] = {
		"������",
		"�Ή���",
		"�m�F��",
		"�҂�",
		"����",
		"�ۗ�",
};

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

/**
 * @brif �R���X�g���N�^
 */
CEventDate::CEventDate(){
	m_strName			= "";
	m_strDetail			= "";
	m_objDate			= COleDateTime::GetCurrentTime();
	m_objPlan[0]		= COleDateTime::GetCurrentTime();
	m_objPlan[1]		= COleDateTime::GetCurrentTime();
	m_objProgress[0]	= COleDateTime::GetCurrentTime();
	m_objProgress[1]	= COleDateTime::GetCurrentTime();
	m_dProcessPar		= 0;
	m_strEventID		= "";
	m_eType				= SC_NORMAL;
	m_nSpan				= 0;
	m_nWeekDays			= 0;
	m_nFixMonth			= 0;
	m_nFixDay			= 0;
	m_strEventID		= "";
	m_bModify			= FALSE;
	m_bHolyday			= FALSE;
	m_ePlanHolyday		= HO_NONE;
	memset(m_arrWeekDays, 0, sizeof(BOOL) * 7);
	m_nState = 0;
}

/**
 *@brif �f�X�g���N�^
 */
CEventDate::~CEventDate(){

}

/**
 * @brif ������Z�q
 */
CEventDate& CEventDate::operator =(CEventDate &pData){
	m_strName			= pData.m_strName;
	m_strDetail			= pData.m_strDetail;
	m_objDate			= pData.m_objDate;
	m_objPlan[0]		= pData.m_objPlan[0];
	m_objPlan[1]		= pData.m_objPlan[1];
	m_objProgress[0]	= pData.m_objProgress[0];
	m_objProgress[1]	= pData.m_objProgress[1];
	m_dProcessPar		= pData.m_dProcessPar;
	m_strEventID		= pData.m_strEventID;
	m_eType				= pData.m_eType;
	m_nFixMonth			= pData.m_nFixMonth;
	m_nFixDay			= pData.m_nFixDay;
	
	m_strCategory		= pData.m_strCategory;

	m_bHolyday			= pData.m_bHolyday;
	m_ePlanHolyday		= pData.m_ePlanHolyday;

	m_nSpan				= pData.m_nSpan;
	m_nWeekDays			= pData.m_nWeekDays;
	m_nState			= pData.m_nState;
	for(int i = 0; i < 7; i++){
		m_arrWeekDays[i] = pData.m_arrWeekDays[i];
	}


	m_bModify			= TRUE;
	return *this;
}

/**
 * @brif ��r���Z�q
 */
BOOL CEventDate::operator ==(CEventDate &pData){
	switch(m_eType){
	case SC_NORMAL:
		if(!m_strName.Compare(pData.m_strName)
		&& !m_strDetail.Compare(pData.m_strDetail)
		&& m_objDate == pData.m_objDate
		&& !m_strEventID.Compare(pData.m_strEventID)
		&& m_eType == pData.m_eType
		){
			return TRUE;
		}else{
			return FALSE;
		}
		break;
	case SC_TODO:
		if(!m_strName.Compare(pData.m_strName)
		&& !m_strDetail.Compare(pData.m_strDetail)
		&& m_objPlan[0]	== pData.m_objPlan[0]
		&& m_objPlan[1]	== pData.m_objPlan[1]
		&& m_objProgress[0]	== pData.m_objProgress[0]
		&& m_objProgress[1] == pData.m_objProgress[1]
		&& m_dProcessPar == pData.m_dProcessPar
		&& m_strEventID == pData.m_strEventID
		&& m_eType == pData.m_eType
		&& !m_strCategory.Compare(pData.m_strCategory)
		&& m_nState == pData.m_nState
		){
			return TRUE;
		}else{
			return FALSE;
		}
		break;
	case SC_FIX_YEAR:
		if(!m_strName.Compare(pData.m_strName)
		&& m_eType == pData.m_eType
		&& m_nFixMonth == pData.m_nFixMonth
		&& m_nFixDay == pData.m_nFixDay
		){
			return TRUE;
		}else{
			return FALSE;
		}
		break;
	case SC_FIX_MONTH1:
		if(!m_strName.Compare(pData.m_strName)
		&& m_eType == pData.m_eType
		&& m_nFixDay == pData.m_nFixDay
		){
			return TRUE;
		}else{
			return FALSE;
		}
		break;
	case SC_FIX_MONTH2:
		if(!m_strName.Compare(pData.m_strName)
		&& m_eType == pData.m_eType
		&& m_nSpan == pData.m_nSpan
		&& m_nWeekDays == pData.m_nWeekDays
		&& !m_strEventID.Compare(pData.m_strEventID)
		){
			return TRUE;
		}else{
			return FALSE;
		}
		break;
	case SC_FIX_WEEK:
		if(!m_strName.Compare(pData.m_strName)
		&& m_eType == pData.m_eType
		&& m_arrWeekDays[0] == pData.m_arrWeekDays[0]
		&& m_arrWeekDays[1] == pData.m_arrWeekDays[1]
		&& m_arrWeekDays[2] == pData.m_arrWeekDays[2]
		&& m_arrWeekDays[3] == pData.m_arrWeekDays[3]
		&& m_arrWeekDays[4] == pData.m_arrWeekDays[4]
		&& m_arrWeekDays[5] == pData.m_arrWeekDays[5]
		&& m_arrWeekDays[6] == pData.m_arrWeekDays[6]
		&& !m_strEventID.Compare(pData.m_strEventID)
		){
			return TRUE;
		}else{
			return FALSE;
		}
		break;
	}
	return FALSE;
}

/**
 * @brif ��r���Z�q
 */
BOOL CEventDate::operator !=(CEventDate &pData){
	switch(m_eType){
	case SC_NORMAL:
		if(!m_strName.Compare(pData.m_strName)
		&& !m_strDetail.Compare(pData.m_strDetail)
		&& m_objDate == pData.m_objDate
		&& m_strEventID == pData.m_strEventID
		&& m_eType == pData.m_eType
		){
			return FALSE;
		}else{
			return TRUE;
		}
		break;
	case SC_TODO:
		if(!m_strName.Compare(pData.m_strName)
		&& !m_strDetail.Compare(pData.m_strDetail)
		&& m_objPlan[0]	== pData.m_objPlan[0]
		&& m_objPlan[1]	== pData.m_objPlan[1]
		&& m_objProgress[0]	== pData.m_objProgress[0]
		&& m_objProgress[1] == pData.m_objProgress[1]
		&& m_dProcessPar == pData.m_dProcessPar
		&& m_strEventID == pData.m_strEventID
		&& m_eType == pData.m_eType
		&& !m_strCategory.Compare(pData.m_strCategory)
		&& m_nState == pData.m_nState
		){
			return FALSE;
		}else{
			return TRUE;
		}
		break;
	case SC_FIX_YEAR:
		if(!m_strName.Compare(pData.m_strName)
		&& m_eType == pData.m_eType
		&& m_nFixMonth == pData.m_nFixMonth
		&& m_nFixDay == pData.m_nFixDay
		){
			return FALSE;
		}else{
			return TRUE;
		}
		break;
	case SC_FIX_MONTH1:
		if(!m_strName.Compare(pData.m_strName)
		&& m_eType == pData.m_eType
		&& m_nFixDay == pData.m_nFixDay
		){
			return FALSE;
		}else{
			return TRUE;
		}
		break;
	case SC_FIX_MONTH2:
		if(!m_strName.Compare(pData.m_strName)
		&& m_eType == pData.m_eType
		&& m_nSpan == pData.m_nSpan
		&& m_nWeekDays == pData.m_nWeekDays
		&& !m_strEventID.Compare(pData.m_strEventID)
		){
			return FALSE;
		}else{
			return TRUE;
		}
		break;
	case SC_FIX_WEEK:
		if(!m_strName.Compare(pData.m_strName)
		&& m_eType == pData.m_eType
		&& m_arrWeekDays[0] == pData.m_arrWeekDays[0]
		&& m_arrWeekDays[1] == pData.m_arrWeekDays[1]
		&& m_arrWeekDays[2] == pData.m_arrWeekDays[2]
		&& m_arrWeekDays[3] == pData.m_arrWeekDays[3]
		&& m_arrWeekDays[4] == pData.m_arrWeekDays[4]
		&& m_arrWeekDays[5] == pData.m_arrWeekDays[5]
		&& m_arrWeekDays[6] == pData.m_arrWeekDays[6]
		&& !m_strEventID.Compare(pData.m_strEventID)
		){
			return FALSE;
		}else{
			return TRUE;
		}
		break;
	}
	return FALSE;

}

/**
 * @brif �����֐�
 * @param LPCTSTR pszName ���O/�T�v
 * @param LPCTSTR pszDetail �ڍ�
 * @param COleDateTime *pDat ����(NULL��)
 * @param eSCTYPE eType
 * @return ����ɐ����ł����TRUE
 */
BOOL CEventDate::Create(LPCTSTR pszName, LPCTSTR pszDetail, COleDateTime *pDate, eSCTYPE eType/*= SC_NORMAL*/){
	if(!pszName && !pszDetail){
		return FALSE;
	}
	if(pszName){
		m_strName = pszName;
	}
	if(pszDetail){
		m_strDetail = pszDetail;
	}
	if(pDate){
		m_objDate = *pDate;
	}
/*
	COleDateTime objDateTime = COleDateTime::GetCurrentTime();
	CString strID;
	strID.Format("%d", objDateTime.m_dt * 100000);
*/
	CString strID;
	strID.Format("%d", GetTickCount());
	while(strID.GetLength() < 12){
		strID = "0" + strID;
	}
	m_strEventID = strID;
	m_eType = eType;
	m_bModify = TRUE;

	return TRUE;
}

/**
 * @brif �C�x���g���̓ǂݍ���
 * @param LPCTSTR pszFile �t�@�C����
 * @param BOOL bToDo ToDo�f�[�^���ǂ����H
 */
BOOL CEventDate::LoadEvent(LPCTSTR pszFile, BOOL bToDo /*= FALSE*/){
	CString strLog;
	CFile file;
	char *pszBuff = NULL;
	try{
		file.Open(pszFile, CFile::modeRead | CFile::shareExclusive);
		CFileStatus status;
		file.GetStatus(status);
		CLogFile::SaveAppLog("--------------------------------");
		strLog.Format("%s�ǂݍ���(%d)", pszFile, status.m_size);
		CLogFile::SaveAppLog(strLog);
		if(bToDo){
			BOOL bEnd = FALSE;
			int nSize = 0;
			char *pszBuff =  NULL;
			while(!bEnd){
				::PumpMessage(WM_TIMER, WM_TIMER);
				::PumpMessage(WM_PAINT, WM_PAINT);
				int nSize = sizeof(EVENTDATA);
				if(nSize <= 0){
					throw(0);
				}
				pszBuff =  new char[nSize + 1];
				memset(pszBuff, 0, nSize + 1);
				int nRet = file.Read(pszBuff, nSize);
				if(nRet <= 0){
					bEnd = TRUE;
					nRet = -1;
				}else if(nSize > nRet){
					strLog.Format("%d : %d EVENTDATA �ǂݍ��݃T�C�Y�s��", nSize, nRet);
					CLogFile::SaveAppLog(strLog);
					break;
				}
				EVENTDATA objData = *(PEVENTDATA)pszBuff;
				delete pszBuff;
				pszBuff = NULL;
				pszBuff = new char[objData.nSize + 1];
				memset(pszBuff, 0, objData.nSize + 1);
				nRet = file.Read(pszBuff, objData.nSize);
				if(objData.nSize > nRet){
					CLogFile::SaveAppLog("�f�[�^�t�@�C���s��");
					break;
				}
				char szKey[6];
				memset(szKey, 0, 6);
				memcpy(szKey, objData.szKey, 5);
				CLogFile::SaveAppLog(szKey);

				if      (!memcmp(szKey, "EVNID", 5)){
					//ID
					m_strEventID = pszBuff;
				}else if(!memcmp(szKey, "TITLE", 5)){
					//�^�C�g��
					m_strName = pszBuff;
				}else if(!memcmp(szKey, "DETAI", 5)){
					//�ڍ�
					m_strDetail = pszBuff;
				}else if(!memcmp(szKey, "DATE_", 5)){
					//���t
					m_objDate.ParseDateTime(pszBuff, LOCALE_NOUSEROVERRIDE   );
				}else if(!memcmp(szKey, "PLNST", 5)){
					//�\��J�n��
					m_objPlan[0].ParseDateTime(pszBuff, LOCALE_NOUSEROVERRIDE   );
				}else if(!memcmp(szKey, "PLNED", 5)){
					//�\��I����
					m_objPlan[1].ParseDateTime(pszBuff, LOCALE_NOUSEROVERRIDE   );
				}else if(!memcmp(szKey, "PRSST", 5)){
					//�J�n��
					m_objProgress[0].ParseDateTime(pszBuff, LOCALE_NOUSEROVERRIDE   );
				}else if(!memcmp(szKey, "PRSED", 5)){
					//�I����
					m_objProgress[1].ParseDateTime(pszBuff, LOCALE_NOUSEROVERRIDE   );
				}else if(!memcmp(szKey, "PROCE", 5)){
					//�i����
					m_dProcessPar = atof(pszBuff);
				}else if(!memcmp(szKey, "FIX_M", 5)){
					//�i����
					m_nFixMonth = atoi(pszBuff);
				}else if(!memcmp(szKey, "FIX_D", 5)){
					//�i����
					m_nFixDay = atoi(pszBuff);
				}else if(!memcmp(szKey, "TYPE", 4)){
					switch(atoi(pszBuff)){
					case SC_NORMAL:
						m_eType = SC_NORMAL;
						break;
					case SC_TODO:
						m_eType = SC_TODO;
						break;
					case SC_FIX_YEAR:
						m_eType = SC_FIX_YEAR;
						break;
					case SC_FIX_MONTH1:
						m_eType = SC_FIX_MONTH1;
						break;
					case SC_FIX_MONTH2:
						m_eType = SC_FIX_MONTH2;
						break;
					case SC_FIX_WEEK:
						m_eType = SC_FIX_WEEK;
						break;
					default:
						break;
					}
				}else if(!memcmp(szKey, "HOLYD", 5)){
					m_bHolyday = atoi(pszBuff);
				}else if(!memcmp(szKey, "PL_HD", 5)){
					switch(atoi(pszBuff)){
					case HO_NONE:
						m_ePlanHolyday = HO_NONE;
						break;
					case HO_PREV:
						m_ePlanHolyday = HO_PREV;
						break;
					case HO_NEXT:
						m_ePlanHolyday = HO_NEXT;
						break;
					}
				}else if(!memcmp(szKey, "CATEG", 5)){
					m_strCategory = pszBuff;
				}else if(!memcmp(szKey, "SPAN", 4)){
					m_nSpan = atoi(pszBuff);
				}else if(!memcmp(szKey, "WDAYS", 5)){
					m_nWeekDays = atoi(pszBuff);
				}else if(!memcmp(szKey, "W_SUN", 5)){
					m_arrWeekDays[0] = atoi(pszBuff);
				}else if(!memcmp(szKey, "W_MON", 5)){
					m_arrWeekDays[1] = atoi(pszBuff);
				}else if(!memcmp(szKey, "W_TUE", 5)){
					m_arrWeekDays[2] = atoi(pszBuff);
				}else if(!memcmp(szKey, "W_WED", 5)){
					m_arrWeekDays[3] = atoi(pszBuff);
				}else if(!memcmp(szKey, "W_THU", 5)){
					m_arrWeekDays[4] = atoi(pszBuff);
				}else if(!memcmp(szKey, "W_FRI", 5)){
					m_arrWeekDays[5] = atoi(pszBuff);
				}else if(!memcmp(szKey, "W_SAT", 5)){
					m_arrWeekDays[6] = atoi(pszBuff);
				}else if(!memcmp(szKey, "STATE", 5)){
					m_nState = atoi(pszBuff);
				}else{
					CLogFile::SaveAppLog("�s���ȃf�[�^");
					CLogFile::SaveAppLog(pszBuff);
					bEnd = TRUE;
					nRet = -1;
				}

				if(pszBuff){
					delete pszBuff;
					pszBuff = NULL;
				}
				if(nRet == -1){
					strLog.Format("EVENTDATA �ǂݍ��݊���");
					CLogFile::SaveAppLog(strLog);
					CLogFile::SaveAppLog("--------------------------------\r\n");
				}
			}
			if(pszBuff){
				delete pszBuff;
				pszBuff = NULL;
			}

		}else{
			CFileStatus status;
			file.GetStatus(status);
			char *pBuff =  new char[status.m_size + 1];
			memset(pBuff, 0, status.m_size + 1);
			file.Read(pBuff, status.m_size);
			m_strDetail = pBuff;
			
			char szFile[MAX_PATH];
			memset(szFile, 0, MAX_PATH);
			_splitpath(pszFile, NULL, NULL, szFile, NULL);
			char szYear[5];
			char szMonth[3];
			char szDay[3];
			memset(szYear, 0, 5);
			memset(szMonth, 0, 3);
			memset(szDay, 0, 3);
			strncpy(szYear, &szFile[0], 4);
			strncpy(szMonth, &szFile[4], 2);
			strncpy(szDay, &szFile[6], 2);

			m_objDate.SetDate(atoi(szYear), atoi(szMonth), atoi(szDay)); 
			delete pBuff;
			strLog.Format("EVENTDATA �ǂݍ��݊���");
			CLogFile::SaveAppLog(strLog);
			CLogFile::SaveAppLog("--------------------------------\r\n");
		}
	}catch(CFileException &fe){
		char szErr[1025];
		memset(szErr, 0, 1025);
		fe.GetErrorMessage(szErr, 1024);
		AfxMessageBox(szErr);
		if(pszBuff){
			delete pszBuff;
		}
		CLogFile::SaveExceptionLog(&fe, "CEventDate::LoadEvent");
	}catch(...){
		if(pszBuff){
			delete pszBuff;
		}
		CLogFile::SaveExceptionLog("CEventDate::LoadEvent");
	}
	file.Close();
	m_bModify = FALSE;
	return TRUE;
}

/**
 * @param �C�x���g�f�[�^�̍폜
 * @param LPCTSTR pszFile �t�@�C����
 * @return �폜�ɐ��������TRUE
 */
BOOL CEventDate::DeleteEvent(LPCTSTR pszFile){
	CString strFile;
	strFile.Format("%s%s.dat", pszFile, m_objDate.Format("%Y%m%d"));
	return ::DeleteFile(strFile);
}

/**
 * @brif ���̕ۑ�
 * @param LPCTSTR pszFile �t�@�C����
 * @param BOOL bToDo ToDo�`�����ǂ����H
 */
BOOL CEventDate::SaveEvent(LPCTSTR pszFile, BOOL bToDo /*= FALSE*/){
	if(!m_bModify){
		return TRUE;
	}
	
	CFile file;
	char *pszBuff = NULL;
	try{
		file.Open(pszFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	
		EVENTDATA data;
		memset(&data, 0, sizeof(EVENTDATA));
		CString strDate;
		if(bToDo){
			//ID
			memcpy(data.szKey, "EVNID", 5);
			data.nSize = m_strEventID.GetLength();
			file.Write(&data, sizeof(EVENTDATA));
			char *pszID = m_strEventID.GetBuffer(m_strEventID.GetLength());
			file.Write(pszID, m_strEventID.GetLength());
			m_strEventID.ReleaseBuffer();

			// �^�C�v
			memcpy(data.szKey, "TYPE", 4);
			strDate.Format("%2d", m_eType);
			data.nSize = strDate.GetLength();
			file.Write(&data, sizeof(EVENTDATA));
			file.Write(strDate, strDate.GetLength());

			// �^�C�g��
			memcpy(data.szKey, "TITLE", 5);
			data.nSize = m_strName.GetLength();
			file.Write(&data, sizeof(EVENTDATA));
			char *pszName = m_strName.GetBuffer(m_strName.GetLength());
			file.Write(pszName, m_strName.GetLength());
			m_strName.ReleaseBuffer();

			if(m_eType == SC_TODO){
				// �ڍ�
				memcpy(data.szKey, "DETAI", 5);
				data.nSize = m_strDetail.GetLength();
				file.Write(&data, sizeof(EVENTDATA));
				file.Write(m_strDetail, m_strDetail.GetLength());

				// ���t
				memcpy(data.szKey, "DATE_", 5);
				strDate = m_objDate.Format("%m/%d/%Y %H:%M:%S");
				data.nSize = strDate.GetLength();
				file.Write(&data, sizeof(EVENTDATA));
				file.Write(strDate, strDate.GetLength());

				// �\��J�n��
				memcpy(data.szKey, "PLNST", 5);
				strDate = m_objPlan[0].Format("%m/%d/%Y %H:%M:%S");
				data.nSize = strDate.GetLength();
				file.Write(&data, sizeof(EVENTDATA));
				file.Write(strDate, strDate.GetLength());
				
				// �\��I����
				memcpy(data.szKey, "PLNED", 5);
				strDate = m_objPlan[1].Format("%m/%d/%Y %H:%M:%S");
				data.nSize = strDate.GetLength();
				file.Write(&data, sizeof(EVENTDATA));
				file.Write(strDate, strDate.GetLength());
				
				// �J�n��
				memcpy(data.szKey, "PRSST", 5);
				strDate = m_objProgress[0].Format("%m/%d/%Y %H:%M:%S");
				data.nSize = strDate.GetLength();
				file.Write(&data, sizeof(EVENTDATA));
				file.Write(strDate, strDate.GetLength());
				
				// �I����
				memcpy(data.szKey, "PRSED", 5);
				strDate = m_objProgress[1].Format("%m/%d/%Y %H:%M:%S");
				data.nSize = strDate.GetLength();
				file.Write(&data, sizeof(EVENTDATA));
				file.Write(strDate, strDate.GetLength());

				// �i����
				memcpy(data.szKey, "PROCE", 5);
				strDate.Format("%08.3f", m_dProcessPar);
				data.nSize = strDate.GetLength();
				file.Write(&data, sizeof(EVENTDATA));
				file.Write(strDate, strDate.GetLength());

				//�J�e�S��
				memcpy(data.szKey, "CATEG", 5);
				strDate = m_strCategory;
				data.nSize = strDate.GetLength();
				file.Write(&data, sizeof(EVENTDATA));
				file.Write(strDate, strDate.GetLength());

				// ���
				memcpy(data.szKey, "STATE", 5);
				strDate.Format("%d", m_nState);
				data.nSize = strDate.GetLength();
				file.Write(&data, sizeof(EVENTDATA));
				file.Write(strDate, strDate.GetLength());
			}

			if(m_eType == SC_FIX_YEAR){
				// ����f�[�^:��
				memcpy(data.szKey, "FIX_M", 5);
				strDate.Format("%0d", m_nFixMonth);
				data.nSize = strDate.GetLength();
				file.Write(&data, sizeof(EVENTDATA));
				file.Write(strDate, strDate.GetLength());
			}

			if((m_eType == SC_FIX_YEAR)
			|| (m_eType == SC_FIX_MONTH1)){
				// ����f�[�^:��
				memcpy(data.szKey, "FIX_D", 5);
				strDate.Format("%0d", m_nFixDay);
				data.nSize = strDate.GetLength();
				file.Write(&data, sizeof(EVENTDATA));
				file.Write(strDate, strDate.GetLength());
			}

			if(m_eType == SC_FIX_YEAR){
				//�x������
				memcpy(data.szKey, "HOLYD", 5);
				strDate.Format("%0d", m_bHolyday ? 1 : 0);
				data.nSize = strDate.GetLength();
				file.Write(&data, sizeof(EVENTDATA));
				file.Write(strDate, strDate.GetLength());

				//�\�肪�x���̏ꍇ
				memcpy(data.szKey, "PL_HD", 5);
				strDate.Format("%d", (int)m_ePlanHolyday);
				data.nSize = strDate.GetLength();
				file.Write(&data, sizeof(EVENTDATA));
				file.Write(strDate, strDate.GetLength());
			}

			if(m_eType == SC_FIX_MONTH2){
				// ��n
				memcpy(data.szKey, "SPAN", 4);
				strDate.Format("%0d", m_nSpan);
				data.nSize = strDate.GetLength();
				file.Write(&data, sizeof(EVENTDATA));
				file.Write(strDate, strDate.GetLength());

				// �j��
				memcpy(data.szKey, "WDAYS", 5);
				strDate.Format("%0d", m_nWeekDays);
				data.nSize = strDate.GetLength();
				file.Write(&data, sizeof(EVENTDATA));
				file.Write(strDate, strDate.GetLength());
			}

			if(m_eType == SC_FIX_WEEK){
				// ���j��
				char* pszWeek[] = {"W_SUN", "W_MON", "W_TUE", "W_WED", "W_THU", "W_FRI", "W_SAT"};
				for(int i = 0; i < 7; i++){
					memcpy(data.szKey, pszWeek[i], 5);
					strDate.Format("%0d", m_arrWeekDays[i]);
					data.nSize = strDate.GetLength();
					file.Write(&data, sizeof(EVENTDATA));
					file.Write(strDate, strDate.GetLength());
				}
			}
		}else{
			file.Write((LPCTSTR)m_strDetail, m_strDetail.GetLength());
		}
		file.Flush();
		file.Close();
		m_bModify = FALSE;
	}catch(CFileException &fe){
		char szErr[1025];
		memset(szErr, 0, 1025);
		fe.GetErrorMessage(szErr, 1024);
		AfxMessageBox(szErr);
		if(pszBuff){
			delete pszBuff;
		}
		CLogFile::SaveExceptionLog(&fe, "CEventDate::SaveEvent");
	}catch(...){
		if(pszBuff){
			delete pszBuff;
		}
		CLogFile::SaveExceptionLog("CEventDate::SaveEvent");
	}
	return TRUE;
}

/**
 * @brif ���O/�T�v�ݒ�
 * @param LPCTSTR pszName ���O/�T�v
 */
void CEventDate::SetName(LPCTSTR pszName){
	m_strName = pszName;
	m_bModify = TRUE;
}

/**
 * @brif �ڍאݒ�
 * @param LPCTSTR pszDetail �ڍ�
 */
void CEventDate::SetDetail(LPCTSTR pszDetail){
	m_strDetail = pszDetail;
	m_bModify = TRUE;
}

/**
 * @brif �����ݒ�
 * @param COleDateTime *pDate ����
 */
void CEventDate::SetDate(COleDateTime *pDate){
	m_objDate = *pDate;
	m_bModify = TRUE;
}

/**
 * @brif �\��ݒ�
 * @param COleDateTime *pStart �J�n�\���
 * @param COleDateTime *pEnd   �I���\���
 */
void CEventDate::SetPlan(COleDateTime *pStart, COleDateTime *pEnd){
	m_objPlan[0] = *pStart;
	m_objPlan[1] = *pEnd;
	m_bModify = TRUE;
}

/**
 * @brif ���ѐݒ�
 * @param COleDateTime *pStart �J�n��
 * @param COleDateTime *pEnd   �I����
 */
void CEventDate::SetProgress(COleDateTime *pStart, COleDateTime *pEnd){
	m_objProgress[0] = *pStart;
	m_objProgress[1] = *pEnd;
	m_bModify = TRUE;
}

/**
 * @brif �i���ݒ�
 * @param double dPar �i����
 */
void CEventDate::SetProcess(double dPar){
	if(dPar > 0){
		m_dProcessPar = dPar;
		m_bModify = TRUE;
	}
}

/**
 * @brif ���O/�T�v�擾
 * @return ���O/�T�v
 */
LPCTSTR CEventDate::GetName(){
	return m_strName;
}

/**
 * @brif �ڍ׎擾
 * @return �ڍ�
 */
LPCTSTR CEventDate::GetDetail(){
	return m_strDetail;
}

/**
 * @brif �����擾
 * @param COleDateTime *pDate
 */
void CEventDate::GetDate(COleDateTime *pDate){
	*pDate = m_objDate;
}

/**
 * @brif �\��̎擾
 * @param COleDateTime *pStart �J�n�\���
 * @param COleDateTime *pEnd   �I���\���
 */
void CEventDate::GetPlan(COleDateTime *pStart, COleDateTime *pEnd){
	*pStart = m_objPlan[0];
	*pEnd = m_objPlan[1];
}

/**
 * @brif ���т̎擾
 * @param COleDateTime *pStart �J�n��
 * @param COleDateTime *pEnd   �I����
 */
void CEventDate::GetProgress(COleDateTime *pStart, COleDateTime *pEnd){
	*pStart = m_objProgress[0];
	*pEnd = m_objProgress[1];
}

/**
 * @brif �i�����擾
 * @return �i����
 */
double CEventDate::GetProcess(){
	return m_dProcessPar;
}

/**
 * @beif ID�ݒ�
 */
void CEventDate::SetEventID(LPCTSTR pszID){
	m_strEventID = pszID;
	m_bModify = TRUE;
}

/**
 * @brif ID�擾
 * @return ID
 */
LPCTSTR CEventDate::GetEventID(){
	return m_strEventID;
}

/**
 * @brif �������ǂ����`�F�b�N
 */
BOOL CEventDate::IsToDay(){
	COleDateTime objNow = COleDateTime::GetCurrentTime();
	COleDateTime objDate = m_objDate;
	TRACE("Now %s Data %s\n", objNow.Format("%Y/%m/%d"), objDate.Format("%Y/%m/%d"));
	if((objNow.GetYear() == objDate.GetYear())
	&& (objNow.GetMonth() == objDate.GetMonth())
	&& (objNow.GetDay() == objDate.GetDay())){
		return TRUE;
	}else{
		return FALSE;
	}
}

/**
 * @brif �^�C�v�擾
 */
eSCTYPE CEventDate::GetType(){
	return m_eType;
}

/**
 * @brif ������ݒ肷��(����f�[�^�p)
 *@param int nMonth
 *@param int nDay
 */
void CEventDate::SetMonthDay(int nMonth, int nDay){
	m_nFixMonth = nMonth;
	m_nFixDay = nDay;
	m_bModify = TRUE;
}

/**
 * @brif �������擾����(����f�[�^�p)
 *@param int nMonth
 *@param int nDay
 */
void CEventDate::GetMonthDay(int &nMonth, int &nDay){
	nMonth = m_nFixMonth;
	nDay = m_nFixDay;
	m_bModify = TRUE;
}

/**
 * @brif �ύX�̗L�����擾����
 */
BOOL CEventDate::IsModify(){
	return m_bModify;
}

/**
 * @brif �ύX�̗L����ݒ肷��
 */
void CEventDate::SetModify(BOOL bModify){
	m_bModify = bModify;
}

/**
 * @brif ���炷
 */
BOOL CEventDate::ChkShiftPlan(int& nYear, int& nMonth, int& nDay){
	if(m_eType != SC_FIX_YEAR){
		return FALSE;
	}
	COleDateTime objDate;
	objDate.SetDate(nYear, m_nFixMonth, m_nFixDay);
	int nDayOfWeek = objDate.GetDayOfWeek();
	BOOL bShift = FALSE;
	while(TRUE){
		if((nDayOfWeek == 0)
		|| (nDayOfWeek == 6)){
			//���炷�B
			COleDateTimeSpan span;
			span.SetDateTimeSpan(1, 0, 0, 0);
			objDate += span;
			bShift = TRUE;
			nMonth = objDate.GetMonth();
			nDay   = objDate.GetDay();
		}else{
			break;
		}
	}
	return bShift;
}

/**
 * @brif �x�����`�F�b�N
 */
BOOL CEventDate::IsHolyDay(int nYear, int nMonth, int nDay){
	COleDateTime objDate;
	objDate.SetDate(nYear, m_nFixMonth, m_nFixDay);
	int nDayOfWeek = objDate.GetDayOfWeek();
	if((nDayOfWeek == 0)
	|| (nDayOfWeek == 6)){
		//�Ƃ肠�����y���͋x��
		return TRUE;
	}
	return FALSE;
}

/**
 * @brif �J�e�S���̐ݒ�
 * @param LPCTSTR pszCategor �J�e�S��
 */
void CEventDate::SetCategory(LPCTSTR pszCategory){
	m_strCategory = pszCategory;
	m_bModify = TRUE;
}

/**
 * @brif �J�e�S���̎擾
 */
LPCTSTR CEventDate::GetCategory(){
	return m_strCategory;
}

/**
 * @brif �j���̐ݒ�
 * @param int nWeekDays �j��
 */
void CEventDate::SetWeekDay(int nWeekDays){
	m_nWeekDays = nWeekDays;
	m_bModify = TRUE;
}

/**
 * @brif ��n�̐ݒ�
 * @param int nSpan ��n
 */
void CEventDate::SetSpan(int nSpan){
	m_nSpan = nSpan;
	m_bModify = TRUE;
}

/**
 * @brif �j���̎擾
 */
int CEventDate::GetWeekDay(){
	return m_nWeekDays;
}

/**
 * @brif ��n�̎擾
 */
int CEventDate::GetSpan(){
	return m_nSpan;
}

/**
 * @brif n�j���̐ݒ�
 * @param int nDays �j��
 * @param BOOL bUse �g��/�g��Ȃ�
 */
void CEventDate::SetWeekDay(int nDays, BOOL bUse){
	m_arrWeekDays[nDays] = bUse;
	m_bModify = TRUE;
}

/**
 * @brif n�j���̎擾
 */
BOOL CEventDate::GetWeekDay(int nDays){
	return m_arrWeekDays[nDays];
}

/**
 * ��Ԃ̐ݒ�
 */
void CEventDate::SetState(int nState){
	m_nState = nState;
	m_bModify = TRUE;
}

/**
 * @brif ��Ԃ̎擾
 */
int CEventDate::GetState(){
	return m_nState;
}

/**
 * @brif ��Ԃ̕�����擾
 */
LPCTSTR CEventDate::GetStateString(){
	return g_pszState[m_nState];
}

/**
 * @brif �x���ݒ�
 */
void CEventDate::SetHoliday(BOOL bHoliday){
	m_bHolyday = bHoliday;
	m_bModify = TRUE;
}

/**
 * @brif �x���ݒ�擾
 */
BOOL CEventDate::GetHoliday(){
	return m_bHolyday;
}

/**
 * @brif �I�v�V����(�x���̎��̈���)�ݒ�
 */
void CEventDate::SetOption(ePLAN_HOLYDAY eOption){
	m_ePlanHolyday = eOption;
	m_bModify = TRUE;
}

/**
 * @brif �I�v�V����(�x���̎��̈���)�擾
 */
ePLAN_HOLYDAY CEventDate::GetOption(){
	return m_ePlanHolyday;
}

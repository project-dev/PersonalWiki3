// FixedData.h: CFixedData クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIXEDDATA_H__EC74CB1E_C47E_493C_9D85_65D540DA50FF__INCLUDED_)
#define AFX_FIXEDDATA_H__EC74CB1E_C47E_493C_9D85_65D540DA50FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <AfxTempl.h>
#include "EvDatBase.h"
class CEventDate;

class CFixedData : public CEvDatBase{
public:
	CFixedData();
	virtual ~CFixedData();
	BOOL LoadFixedData();
	BOOL SaveFixedData();
	int AddFixedData(CEventDate *pDate);
	BOOL DelFixedData(CEventDate *pDate);
	BOOL DelFixedData(int i);
	int GetSize();
	CEventDate* GetFixedData(int nIndex);
	BOOL UpdateFixedData(CEventDate* pToDo);
private:
	BOOL ReleaseFixedData();
	CArray<CEventDate*, CEventDate* > m_arrFixedData;
};

#endif // !defined(AFX_FIXEDDATA_H__EC74CB1E_C47E_493C_9D85_65D540DA50FF__INCLUDED_)

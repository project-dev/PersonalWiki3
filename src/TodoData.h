// TodoData.h: CTodoData クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TODODATA_H__7B4BA3F7_DE7E_4058_B91B_4D77AC746BA0__INCLUDED_)
#define AFX_TODODATA_H__7B4BA3F7_DE7E_4058_B91B_4D77AC746BA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "EventDate.h"
#include <AfxTempl.h>
#include "EvDatBase.h"
class CTodoData : public CEvDatBase{
public:
	CTodoData();
	virtual ~CTodoData();
	BOOL LoadToDo();
	BOOL SaveToDo();
	BOOL AddToDo(CEventDate *pDate);
	BOOL DelToDo(CEventDate *pDate);
	BOOL DelToDo(int nIndex);
	int GetSize();
	CEventDate* GetToDo(int nIndex);
	BOOL UpdateToDo(CEventDate* pToDo);
private:
	BOOL ReleaseToDo();
	CArray<CEventDate*, CEventDate* > m_arrToDo;
};

#endif // !defined(AFX_TODODATA_H__7B4BA3F7_DE7E_4058_B91B_4D77AC746BA0__INCLUDED_)

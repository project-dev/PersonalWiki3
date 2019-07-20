// ScDateData.h: CScDateData クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCDATEDATA_H__3DBC0974_ACC7_44DB_80BC_A92B7E168420__INCLUDED_)
#define AFX_SCDATEDATA_H__3DBC0974_ACC7_44DB_80BC_A92B7E168420__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <AfxTempl.h>
#include "EvDatBase.h"
class CEventDate;
class CScDateData : public CEvDatBase{
public:
	CScDateData();
	virtual ~CScDateData();
	BOOL LoadDate(COleDateTime *pDate = NULL, BOOL bDateOny = FALSE);
	BOOL SaveDate();
	BOOL AddDate(CEventDate *pDate);
	BOOL DelDate(CEventDate *pDate);
	int GetSize();
	CEventDate* GetDate(COleDateTime &objDate);
	BOOL UpdateDate(CEventDate* pDate);
private:
	BOOL ReleaseDate();
	CMapStringToPtr m_mapDate;
};

#endif // !defined(AFX_SCDATEDATA_H__3DBC0974_ACC7_44DB_80BC_A92B7E168420__INCLUDED_)

// EvDatBase.h: CEvDatBase �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVDATBASE_H__0EC5F901_03A3_415A_8CE2_2001F05AD13D__INCLUDED_)
#define AFX_EVDATBASE_H__0EC5F901_03A3_415A_8CE2_2001F05AD13D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CEventDate;

class CEvDatBase {
public:
	CEvDatBase();
	virtual ~CEvDatBase();
	void SetDataDir(LPCTSTR pszDir);
private:
protected:
	CString m_strDataDir;
};

#endif // !defined(AFX_EVDATBASE_H__0EC5F901_03A3_415A_8CE2_2001F05AD13D__INCLUDED_)

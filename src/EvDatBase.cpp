// EvDatBase.cpp: CEvDatBase クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PersonalWiki.h"
#include "EvDatBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CEvDatBase::CEvDatBase()
{

}

CEvDatBase::~CEvDatBase()
{

}
void CEvDatBase::SetDataDir(LPCTSTR pszDir){
	m_strDataDir = pszDir;
}

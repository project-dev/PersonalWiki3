// BregExpRap.cpp: CBregExpRap ƒNƒ‰ƒX‚ÌƒCƒ“ƒvƒŠƒƒ“ƒe[ƒVƒ‡ƒ“
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BinderPlugin.h"
#include "BregExpRap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// \’z/Á–Å
//////////////////////////////////////////////////////////////////////

CBregExpRap::CBregExpRap(){

}

CBregExpRap::~CBregExpRap(){
	RefreshPool();

}

/*-------------------------------------------------------------------*/
// ³‹K•\Œ»‚É‚æ‚é•¶Žš‚ÌŒŸõ
// ˆø” strTarget
//      strPattern
/*-------------------------------------------------------------------*/
BOOL CBregExpRap::FindText(CString &strTarget, CString &strPattern){
	BREGEXP *rxp = NULL;
	char msg[80];
	int nTargetLen = strTarget.GetLength();
	LPTSTR pszTarget = strTarget.GetBuffer(nTargetLen);
	LPTSTR pszPattern = strPattern.GetBuffer(strPattern.GetLength());

	CObject *pDummy = NULL;
	m_mapStruct.Lookup(pszPattern, pDummy);
	if(pDummy){
		//“¯‚¶ŒŸõðŒ‚ð”­Œ©
		rxp = (BREGEXP*)pDummy;
	}

	int ret = BMatch(pszPattern,
					 pszTarget,
					 pszTarget + nTargetLen,
					 &rxp,
					 msg);

	strTarget.ReleaseBuffer(strTarget.GetLength());
	strPattern.ReleaseBuffer(strPattern.GetLength());
	if(!ret){
		if(rxp && !pDummy){
			BRegfree(rxp);
			rxp = NULL;
		}
		return FALSE;
	}

	if(rxp == NULL){
		return FALSE;
	}

	if(!pDummy){
		//“o˜^
		m_mapStruct.SetAt(pszPattern, (CObject*)rxp);
	}

	CString strMsg = msg;
	if(!strMsg.IsEmpty()){
#if OUTRESULT		
		TRACE("FindText : %s\n", strMsg);
		TRACE("Statment : %s\n", strPattern);
#endif
	}

	return TRUE;
}

/*-------------------------------------------------------------------*/
// ³‹K•\Œ»‚É‚æ‚é•¶Žš‚ÌŒŸõ
// ˆø” strTarget
//      strPattern
/*-------------------------------------------------------------------*/
BOOL CBregExpRap::GetFindText(CString &strTarget, CString &strRet, CString &strPattern){
	BREGEXP *rxp = NULL;
	char msg[80];
	int nTargetLen = strTarget.GetLength();
	LPTSTR pszTarget = strTarget.GetBuffer(nTargetLen);
	LPTSTR pszPattern = strPattern.GetBuffer(strPattern.GetLength());

	CObject *pDummy = NULL;
	m_mapStruct.Lookup(pszPattern, pDummy);
	if(pDummy){
		//“¯‚¶ŒŸõðŒ‚ð”­Œ©
		rxp = (BREGEXP*)pDummy;
	}

	int ret = BMatch(pszPattern,
					 pszTarget,
					 pszTarget + nTargetLen,
					 &rxp,
					 msg);
	strTarget.ReleaseBuffer(strTarget.GetLength());
	strPattern.ReleaseBuffer(strPattern.GetLength());
	if(!ret){
		if(rxp && !pDummy){
			BRegfree(rxp);
			rxp = NULL;
		}
		return FALSE;
	}
	if(rxp == NULL){
		return FALSE;
	}

	if(!pDummy){
		//“o˜^
		m_mapStruct.SetAt(pszPattern, (CObject*)rxp);
	}

	int nLen = rxp->outendp - rxp->outp;
	char *pBuff = new char[nLen + 1];
	memset(pBuff, 0, nLen + 1);
//	memcpy(pBuff, *rxp->outp, nLen);
	memcpy(pBuff, rxp->outp, nLen);
	strRet = pBuff;
	delete[] pBuff;

	CString strMsg = msg;
	if(!strMsg.IsEmpty()){
#if OUTRESULT		
		TRACE("FindText : %s\n", strMsg);
		TRACE("Statment : %s\n", strPattern);
#endif
	}

	return TRUE;
}

/*-------------------------------------------------------------------*/
// ³‹K•\Œ»‚É‚æ‚é•¶Žš‚Ì’u‚«Š·‚¦
// ˆø” strTarget
//      strReturn
//      strPattern
/*-------------------------------------------------------------------*/
BOOL CBregExpRap::ReplaceText(CString &strTarget, CString &strReturn, CString &strPattern){
	BREGEXP *rxp = NULL;
	char msg[80];
	int nTargetLen = strTarget.GetLength();
	LPTSTR pszTarget = strTarget.GetBuffer(nTargetLen);
	LPTSTR pszPattern = strPattern.GetBuffer(strPattern.GetLength());

	int nRet;

	CObject *pDummy = NULL;
	m_mapStruct.Lookup(pszPattern, pDummy);
	if(pDummy){
		//“¯‚¶ŒŸõðŒ‚ð”­Œ©
		rxp = (BREGEXP*)pDummy;
	}

	nRet = BSubst(pszPattern,
				   pszTarget,
				   pszTarget + nTargetLen,
				   &rxp,
				   msg);

	strTarget.ReleaseBuffer(strTarget.GetLength());
	strPattern.ReleaseBuffer(strPattern.GetLength());
	if(!nRet){
		if(rxp && !pDummy){
			BRegfree(rxp);
			rxp = NULL;
		}
		strReturn = strTarget;
		return FALSE;
	}

	CString strMsg = msg;
	if(!strMsg.IsEmpty()){
#if OUTRESULT		
		TRACE("ReplaceText : %s\n", strMsg);
		TRACE("Statment : %s\n", strPattern);
#endif
	}

	if(rxp == NULL){
		strReturn = strTarget;
		return FALSE;
	}

	if(!pDummy){
		//“o˜^
		m_mapStruct.SetAt(pszPattern, (CObject*)rxp);
	}

	strReturn = rxp->outp;
	return TRUE;

}

void CBregExpRap::GetVersionString(CString &strVersion){
	strVersion = BRegexpVersion();
}

/*-------------------------------------------------------------------*/
// ³‹K•\Œ»‚É‚æ‚éŽw’è•¶Žš—ñ‚Ì’Šo
// ˆø” strTarget
//      strReturn
//      strPattern
/*-------------------------------------------------------------------*/
BOOL CBregExpRap::GetFindStrList(CString &strTarget, CString &strPattern, CStringArray &arrText){
	arrText.RemoveAll();

	BREGEXP *rxp = NULL;
	char msg[80];
	int ret;
	int nTargetLen = strTarget.GetLength();
	LPTSTR pszTarget = strTarget.GetBuffer(nTargetLen);
	LPTSTR pszPattern = strPattern.GetBuffer(strPattern.GetLength());
	CString strMsg;
	CString strResult;

	CObject *pDummy = NULL;
	m_mapStruct.Lookup(pszPattern, pDummy);
	if(pDummy){
		//“¯‚¶ŒŸõðŒ‚ð”­Œ©
		rxp = (BREGEXP*)pDummy;
	}

	while(TRUE){
		ret = BMatch(pszPattern,
					 pszTarget,
					 pszTarget + nTargetLen,
					 &rxp,
					 msg);
		if(!ret){
			if(rxp && !pDummy){
				BRegfree(rxp);
				rxp = NULL;
			}
			break;
		}
		if(!rxp){
			break;
		}
		int nBuffLen = (rxp->outendp) - (rxp->outp);
		char *pszBuff = new char[nBuffLen + 1];
		memset(pszBuff, 0, nBuffLen + 1);
		memcpy(pszBuff, rxp->outp, nBuffLen);
		pszBuff[nBuffLen] = '\0';
		strResult = pszBuff;
		delete[] pszBuff;
		//’Ç‰Á
		arrText.Add(strResult);
		//TRACE("ADD : %s\n", strResult);
		
		//ƒ^[ƒQƒbƒg‚Ìƒ|ƒCƒ“ƒ^‚ð‚¸‚ç‚·
		pszTarget = (char*)rxp->outendp;
		nTargetLen = strlen(pszTarget);
		strMsg = msg;
		if(!strMsg.IsEmpty()){
#if OUTRESULT
			TRACE("GetFindStrList : %s\n", strMsg);
			TRACE("Statment : %s\n", strPattern);
#endif
			break;
		}
	}

	if(!pDummy){
		//“o˜^
		m_mapStruct.SetAt(pszPattern, (CObject*)rxp);
	}

	strTarget.ReleaseBuffer(strTarget.GetLength());
	strPattern.ReleaseBuffer(strPattern.GetLength());

	return TRUE;
}

void CBregExpRap::RefreshPool(){
	POSITION pos = m_mapStruct.GetStartPosition();

	CString strKey;
	CObject *pData;
	while(pos){
		m_mapStruct.GetNextAssoc(pos, strKey, pData);
		BRegfree((BREGEXP*)pData);
	}
	m_mapStruct.RemoveAll();
}

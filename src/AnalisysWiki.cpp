// AnalisysWiki.cpp: CAnalisysWiki �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PersonalWiki.h"
#include "AnalisysWiki.h"
#include "FindFile.h"
#include "LogFile.h"
#include "devlib.h"
#include "Cryptography.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define CMP_AMP
//#define USE_IMG

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CAnalisysWiki::CAnalisysWiki(){
	memset(&m_objAnaInfo, 0, sizeof(ANAINFO));
	m_bExport = FALSE;
	m_strWikiRealPath = "";

}

CAnalisysWiki::~CAnalisysWiki(){

}

/**
 * @brif ��͊֐�
 * @param LPCTSTR pszText ��͑Ώە�����
 * @param CString &strHtml ��͌㕶����i�[�p
 * @param LPCTSTR pszWikiPathBase ��̓t�@�C����Wiki�x�[�X�p�X(�J�����_�[�̏ꍇ�̂�NULL���w�肷�邱�ƁI)
 * @param BOOL    bPlainText �e�L�X�g�`���ŕϊ����邩�ǂ���
 * @return ��͂ɐ�������� TRUE
 */
BOOL CAnalisysWiki::Analisys(LPCTSTR pszText, CString &strHtml, LPCTSTR pszWikiPathBase, BOOL bPlainText, BOOL bExport /*= FALSE*/, BOOL bInclude /*= FALSE*/){
	m_bExport = bExport;

	//�J�����_�[�y�[�W�����ׂ�
	DWORD dwStart = ::GetTickCount();
	
	//���(�b���)
	CStringArray arrStockLI;		//<UL><OL>
	BOOL bMarge = FALSE;
	CString strLine = "";
	CString strDetail2 = "";
	int nPos = 0;
	CString strDetail = pszText;
	strDetail += "\r\n";
	CString strBase = m_objAnaInfo.pszBasePath;
	CString strImg = pszWikiPathBase ? strBase + "Attach\\" : strBase + "Img\\";;
	CStringArray arrContents;
	CStringArray arrTable;
	CStringArray arrComment;
	CString strTbLink =  "\n<DIV ALIGN=\"right\" CLASS=\"TBLINK\">[<A HREF=\"#__PWIKI_TOP__\">��</A>"
						 "/<A HREF=\"#__PWIKI_BOTTOM__\">��</A>]</DIV>";

	m_strWikiRealPath = m_objAnaInfo.pszBaseWikiPath;
	if(bPlainText){
//		TRACE("TEXT\n");
	}else{
//		TRACE("HTML\n");
		strDetail2 = "<A NAME=\"__PWIKI_TOP__\">\n";
	}

	strHtml = "";
	BOOL bNoBrTag = FALSE;
	BOOL bInPre = FALSE;
	while(nPos != -1){
		BOOL bRet = FALSE;
		bNoBrTag = FALSE;
		nPos = strDetail.Find("\r\n");

		if(!strDetail.Left(2).Compare("//")){
			strDetail = strDetail.Right(strDetail.GetLength() - nPos - 2);
			continue;
		}
		
		if(strDetail.Left(1).Compare("-") 
		&& strDetail.Left(1).Compare("+") 
		&& arrStockLI.GetSize()){
			//���ڕ\��
			GetLiText(strLine, arrStockLI, bPlainText);
			strDetail2 += strLine;
			strLine = "";
			arrStockLI.RemoveAll();
		}
		if(strDetail.Left(1).Compare("|")
		&& arrTable.GetSize()){
			//�e�[�u���\��
			GetTableText(strLine, arrTable, bPlainText);
			strDetail2 += strLine;
			strLine = "";
			arrTable.RemoveAll();
		}

		if(!strDetail.Left(1).Compare(" ")){
			if(!bInPre){
				bInPre = TRUE;
				if(!bPlainText){
					strDetail2 += "<PRE>\n";
				}
			}
			strLine = strDetail.Left(nPos);
//			strLine.TrimLeft();
			CString strPreText;
			ReplaceHTMLText(strLine, strPreText);
			strDetail2 += strPreText;
			strDetail2 += "\n";
			strDetail = strDetail.Right(strDetail.GetLength() - nPos - 2);
			continue;
		}else if(bInPre){
			bInPre = FALSE;
			if(!bPlainText){
				strDetail2 += "</PRE>\n";
			}
			strLine = "";
		}

		if(!m_objAnaInfo.bUseRetFormat){
			bRet = TRUE;
			if(nPos != -1){
				strLine = strDetail.Left(nPos);
			}else{
				strLine = strDetail;
			}
			strDetail = strDetail.Right(strDetail.GetLength() - nPos - 2);
			strLine.TrimLeft();
			strLine.TrimRight();
			if(!strLine.Right(1).Compare("~")){
				strLine = strLine.Left(strLine.GetLength() - 1);
			}
		}else{
			BOOL bForceRet = FALSE;
			if(nPos != -1){
				CString strChk = strDetail.Left(nPos);
				if(!strChk.Left(1).Compare("*")
				|| !strChk.Left(1).Compare(" ")
				|| (!strChk.Left(1).Compare("-") && strChk.Left(4).Compare("----"))
				|| !strChk.Left(1).Compare("+")
				|| !strChk.Left(1).Compare("#")
				|| (!strChk.Left(1).Compare("|") && (!strChk.Right(1).Compare("|") || !strChk.Right(2).Compare("|h")))
				){
					//�������s
					bForceRet = TRUE;
					bNoBrTag = TRUE;
				}
				if(bMarge){
					if(!bForceRet){
						//�A��(�������s����)
						strLine += strDetail.Left(nPos);
					}
				}else{
					strLine = strDetail.Left(nPos);
					if(bForceRet){
						//�A�����Ȃ��ꍇ�̋������s�͎擾�����������؂����Ă����B
						strDetail = strDetail.Right(strDetail.GetLength() - nPos - 2);
					}
				}
				if(!bForceRet){
					//�������s�łȂ��ꍇ�͎擾������؂����Ă���
					strDetail = strDetail.Right(strDetail.GetLength() - nPos - 2);
				}
			}else{
				if(bMarge){
					strLine += strDetail;
				}else{
					strLine = strDetail;
				}
			}
			strLine.TrimLeft();
			strLine.TrimRight();
			if((nPos == -1) || bForceRet){
			}else if(!strLine.Right(1).Compare("~")){
				strLine = strLine.Left(strLine.GetLength() -1);
				bRet = TRUE;
			}else{
				bMarge = TRUE;
				continue;
			}
			bMarge = FALSE;
		}

		if(!bPlainText){
			//URL�������N�ɕύX����
			CString arrURLHead[] = {
				"http:",
				"https:",
				"file:",
				"ftp:",
				"mk:@",
				"mailto:",
			};
			int nURLs = sizeof(arrURLHead) / sizeof(CString);

			for(int nChkURL = 0; nChkURL < nURLs; nChkURL++){
				CString strChkUrl = strLine;
	//			CString strLeft = "";
				strLine = "";
				while(TRUE){
					int nPos = strChkUrl.Find(arrURLHead[nChkURL], 0);
					if(nPos == -1){
						//URL���Ȃ�
						strLine += strChkUrl;
						break;
					}
					
					//[[]]�͂�
					int nStPos = strChkUrl.Find("[[");
					//#or&xx()�͂�
					int nStPosIn = strChkUrl.Find("&");
					int nStPosOt = strChkUrl.Find("#");
					int nStPosPlgSt = strChkUrl.Find("(");
					int nStPosPlgEd = strChkUrl.Find(")");

					if((nStPosOt != -1) && (nStPosPlgSt != -1) && (nStPosPlgEd != -1)
					&& (nStPosOt < nStPosPlgSt) && (nStPosPlgSt < nPos) && (nPos < nStPosPlgEd)){
						//�ΏۊO
						strLine += strChkUrl.Left(nStPosPlgEd + 1);
						strChkUrl = strChkUrl.Mid(nStPosPlgEd + 1);

					}else if((nStPosIn != -1) && (nStPosPlgSt != -1) && (nStPosPlgEd != -1)
						  && (nStPosIn < nStPosPlgSt) && (nStPosPlgSt < nPos) && (nPos < nStPosPlgEd)){
						//�ΏۊO
						strLine += strChkUrl.Left(nStPosPlgEd + 1);
						strChkUrl = strChkUrl.Mid(nStPosPlgEd + 1);
					}else if(nStPos == -1){
						//�ϊ��Ώ�
						strLine += strChkUrl.Left(nPos);
						strChkUrl = strChkUrl.Mid(nPos);
					}else{
						int nEdPos = strChkUrl.Find("]]", nStPos);
						int nStPos2 = strChkUrl.Find("[[", nStPos);
						if(nEdPos != -1){
							//[[...]]�w�肳��Ă���
							if((nStPos2 != -1) || (nStPos2 > nEdPos)){
								//[[�Ώ�]]
								//�ϊ��ΏۊO
								strLine += strChkUrl.Left(nEdPos + 1);
								strChkUrl = strChkUrl.Mid(nEdPos + 1);
								continue;
							}else if((nStPos2 != -1) && (nStPos2 < nEdPos)){
								//[[�Ώ�[[...]]
								//�ϊ��Ώ�
								strLine += strChkUrl.Left(nStPos + 1);
								strChkUrl = strChkUrl.Mid(nStPos + 1);
							}
						}else{
							//�ϊ��Ώ�
							//[[�Ώ�...
							strLine += strChkUrl.Left(nStPos + 1);
							strChkUrl = strChkUrl.Mid(nStPos + 1);
						}
					}
					int nLen = strChkUrl.GetLength();
					for(int chIndex = 0; chIndex < nLen; chIndex++){
						TCHAR ch = strChkUrl.GetAt(chIndex);
						if(((ch >= 'a') && (ch <= 'z'))	//
						|| ((ch >= '?') && (ch <= 'Z'))	// ?@ABCDEFGHIJKLMNOPQRSTUVWXYZ
						|| ((ch >= '/') && (ch <= ':'))	// /0123456789:
						|| (ch == '-') || (ch == '~')	// -~+*._=&#$%
						|| (ch == '+') || (ch == '*')
						|| (ch == '.') || (ch == '_')
						|| (ch == '=') || (ch == '&')
						|| (ch == '#') || (ch == '$')
						|| (ch == '%')
						){
						}else{
							CString strURL = strChkUrl.Left(chIndex);
							strLine += "[[";
							strLine += strURL;
							strLine += "]]";
							strLine += strChkUrl.Mid(chIndex);
							strChkUrl = "";
							break;
						}
					}
					if(!strChkUrl.IsEmpty()){
						strLine += "[[";
						strLine += strChkUrl;
						strLine += "]]";
						strChkUrl = "";
					}
				}
			}
		}

		if(!bPlainText){
			int nChkPosST = 0;
			int nChkPosED = 0;
			CString strBuff = "";
			CString strFirst;
			CString strMid;
			CString strRight;
			while(!strLine.IsEmpty()){
				strFirst = "";
				strMid = "";
				strRight = "";
				nChkPosST = strLine.Find("[[", 0);
				nChkPosED = strLine.Find("]]", nChkPosST);
				if((nChkPosST == -1) || (nChkPosED == -1)){
					strFirst = strLine;
				}else{
					strFirst = strLine.Left(nChkPosST);
					strMid = strLine.Mid(nChkPosST, nChkPosED - nChkPosST + 2);
					strRight = strLine.Right(strLine.GetLength() - nChkPosED - 2);
				}
				strLine = strRight;
#if defined(CMP_AMP)				
				strFirst.Replace("&", "&amp;");
#endif
				strFirst.Replace(" ", "&nbsp;");
				strFirst.Replace("<", "&lt;");
				strFirst.Replace(">", "&gt;");
				strBuff += strFirst;
				strBuff += strMid;
			}
			strLine = strBuff;
		}

		//��
		if(!strLine.Left(strlen("CENTER:")).Compare("CENTER:")){
			strLine = strLine.Mid(strlen("CENTER:"));
			if(!bPlainText){
				strLine = "<div style=\"text-align:center\">" + strLine + "</div>";
			}
		}else if(!strLine.Left(strlen("LEFT:")).Compare("LEFT:")){
			strLine = strLine.Mid(strlen("LEFT:"));
			if(!bPlainText){
				strLine = "<div style=\"text-align:left\">" + strLine + "</div>";
			}
		}else if(!strLine.Left(strlen("RIGHT:")).Compare("RIGHT:")){
			strLine = strLine.Mid(strlen("RIGHT:"));
			if(!bPlainText){
				strLine = "<div style=\"text-align:right\">" + strLine + "</div>";
			}
		}

		//�W���ϊ�
		typedef struct tagCNVDATA{
			const char *pszKey;
			const char *pszStTag;
			const char *pszEndtag;
		}CNVDATA, *PCNVDATA;
		CNVDATA arrDat[] = {
			{"\'\'\'",	"<I>",		"</I>"}
			,{"\'\'",	"<B>",		"</B>"}
			,{"%%%",	"<U>",		"</U>"}
			,{"%%",		"<S>",		"</S>"}
		};
		int nSize = sizeof(arrDat) / sizeof(CNVDATA);

		if(!strLine.Left(4).Compare("----")){
			strLine = "";
			strDetail2 += "<HR>\r\n";
			continue;
		}

		int nChkStartPos = 0;
		int nChkEndPos = 0;
		for(int i = 0; i < nSize; i++){
			nChkStartPos = 0;
			nChkEndPos = 0;
			int nKeyLen = strlen(arrDat[i].pszKey);
			while(strLine.Find(arrDat[i].pszKey) != -1){
				nChkStartPos = strLine.Find(arrDat[i].pszKey, 0);
				nChkEndPos   = strLine.Find(arrDat[i].pszKey, nChkStartPos + nKeyLen);
				if((nChkStartPos != -1) && (nChkEndPos != -1)){
					CString strLeft = strLine.Left(nChkStartPos);
					CString strMid = strLine.Mid(nChkStartPos + nKeyLen, nChkEndPos - nChkStartPos - nKeyLen);
					CString strEnd = strLine.Right(strLine.GetLength() - nChkEndPos - nKeyLen);
					if(bPlainText){
						strLine.Format("%s%s%s", strLeft, strMid, strEnd);
					}else{
						strLine.Format("%s%s%s%s%s", strLeft, arrDat[i].pszStTag, strMid, arrDat[i].pszEndtag, strEnd);
					}
				}else{
					break;
				}
			}
		}
		//&�v���O�C���ϊ�
		GetInlinePlugin(strLine, pszWikiPathBase, strImg, bPlainText);

		//Link���
		LinkAna(strLine, pszWikiPathBase, bPlainText);
	
		int nPos = 0;
		while(strLine.Find("((", nPos) != -1){
			int nStPos = strLine.Find("((", nPos);
			int nEdPos = strLine.Find("))", nStPos);
			if((nStPos != -1) && (nEdPos != -1)){
				nPos = nEdPos + 2;
				CString strLeft = strLine.Left(nStPos);
				CString strMid = strLine.Mid(nStPos + 2, nEdPos - nStPos - 2);
				CString strRight = strLine.Mid(nEdPos + 2);
				arrComment.Add(strMid);
				if(bPlainText){
					strLine.Format("%s(*%d)%s", strLeft, arrComment.GetSize(), strRight);
				}else{
					strLine.Format("%s<a href=\"#comment_%04d\">*%d</a>%s", strLeft, arrComment.GetSize(), arrComment.GetSize(), strRight);
				}
			}else{
				break;
			}
		}

		//�C���f�b�N�X
		CString strIndex;
		if(!strLine.Left(3).Compare("***")){
			arrContents.Add(strLine);
			strLine = strLine.Right(strLine.GetLength() - 3);
			strLine.TrimLeft();
			strLine.TrimRight();
			if(bPlainText){
				strIndex.Format("�� %s ��", strLine);
			}else{
				strIndex.Format("<A Name=\"%s\"><H3>%s</H3>", strLine, strLine);
			}
			if(!bPlainText && m_objAnaInfo.bUseTBLink){
				strIndex += strTbLink;
			}
			strLine = strIndex;
		}else if(!strLine.Left(2).Compare("**")){
			arrContents.Add(strLine);
			strLine = strLine.Right(strLine.GetLength() - 2);
			strLine.TrimLeft();
			strLine.TrimRight();
			if(bPlainText){
				strIndex.Format("�y %s �z", strLine);
			}else{
				strIndex.Format("<A Name=\"%s\"><H2>%s</H2>", strLine, strLine);
			}
			if(!bPlainText && m_objAnaInfo.bUseTBLink){
				strIndex += strTbLink;
			}
			strLine = strIndex;
		}else if(!strLine.Left(1).Compare("*")){
			arrContents.Add(strLine);
			strLine = strLine.Right(strLine.GetLength() - 1);

			CString strHref = strLine;
			while(TRUE){
				int stPos = strHref.Find("<");
				int edPos = strHref.Find(">");
				if(((stPos != -1) && (edPos != -1))
				&& (stPos < edPos)){
					CString strDel = strHref.Mid(stPos, edPos - stPos + 1);
					strHref.Replace(strDel, "");
				}else{
					break;
				}
			}
			ReplaceHTMLText(strHref, strHref);
			
			strHref.TrimLeft();
			strHref.TrimRight();
			if(bPlainText){
				strIndex.Format("��%s", strHref);
			}else{
				strIndex.Format("<A Name=\"%s\"><H1>%s</H1>", strHref, strLine);
			}
			if(!bPlainText && m_objAnaInfo.bUseTBLink){
				strIndex += strTbLink;
			}
			strLine = strIndex;

		}else if(!strLine.Left(1).Compare("-")
		      || !strLine.Left(1).Compare("+")){
			//strLine = strLine.Right(strLine.GetLength() - 3);
			arrStockLI.Add(strLine);
			strLine = "";
		}else if(!strLine.Left(1).Compare("|")
			&&(!strLine.Right(1).Compare("|") || !strLine.Right(2).Compare("|h"))){
			arrTable.Add(strLine);
			strLine = "";
		}else{
			if(!bPlainText){
				if(bNoBrTag){
					strLine += "\n";
				}else{
					strLine += "<BR>\n";
				}
			}
		}
/*
		int nPos = 0;
		while(strLine.Find("((", nPos) != -1){
			int nStPos = strLine.Find("((", nPos);
			int nEdPos = strLine.Find("))", nStPos);
			if((nStPos != -1) && (nEdPos != -1)){
				nPos = nEdPos + 2;
				CString strLeft = strLine.Left(nStPos);
				CString strMid = strLine.Mid(nStPos + 2, nEdPos - nStPos - 2);
				CString strRight = strLine.Mid(nEdPos + 2);
				arrComment.Add(strMid);
				if(bPlainText){
					strLine.Format("%s(*%d)%s", strLeft, arrComment.GetSize(), strRight);
				}else{
					strLine.Format("%s<a href=\"#comment_%04d\">*%d</a>%s", strLeft, arrComment.GetSize(), arrComment.GetSize(), strRight);
				}
			}else{
				break;
			}
		}
*/
		if(!strLine.IsEmpty()){
			strDetail2 += strLine;
			strDetail2 += "\n";
		}
	}

	//���ߒǉ�
	int nCnt = arrComment.GetSize();
	if(nCnt > 0){
		if(bPlainText){
			strDetail2 += "----------------------------------------\n";
		}else{
			strDetail2 += "<HR>\n";
		}
	}
	for(int nCmt = 0; nCmt < nCnt; nCmt++){
		CString strComment = arrComment.GetAt(nCmt);
		CString strLine;
		if(bPlainText){
			strLine.Format("*%d:%s\n", nCmt + 1, strComment);
		}else{
			strLine.Format("<a name=\"comment_%04d\">*%d:%s<br>\n", nCmt + 1, nCmt + 1, strComment);
		}
		strDetail2 += strLine;
	}

	//#�v���O�C�����
	GetOutlinePlugin(strDetail2, strHtml, arrContents, pszWikiPathBase, strImg, bPlainText);

	//�t�b�^����
	if(!bPlainText && !bInclude){
		if(m_objAnaInfo.bShowAttach && pszWikiPathBase){
			CStringArray arrAttach;
			GetAttachFiles(pszWikiPathBase, strBase, arrAttach);
			CString strAttr = "";
			for(int i = 0; i < arrAttach.GetSize(); i++){
				CString strAttach = arrAttach.GetAt(i);
				char szFile[MAX_PATH];
				char szExt[MAX_PATH];
				memset(szFile, 0, MAX_PATH);
				memset(szExt, 0, MAX_PATH);
				_splitpath(strAttach, NULL, NULL, szFile, szExt);

				CString strAttFile;
				CFileStatus state;
				CFile::GetStatus(strAttach, state);
				COleDateTime objLastWriteTime(state.m_mtime.GetTime());
				COleDateTime objCurrent = COleDateTime::GetCurrentTime();
				COleDateTimeSpan objSpan = objCurrent - objLastWriteTime;
				CString strSpan;
				if(objSpan.GetDays()){
					strSpan.Format("%dd", objSpan.GetDays());
				}else if(objSpan.GetHours()){
					strSpan.Format("%dh", objSpan.GetHours());
				}else if(objSpan.GetMinutes()){
					strSpan.Format("%dm", objSpan.GetMinutes());
				}				
				strAttFile.Format("%s%s\\%s%s", strImg, pszWikiPathBase, szFile, szExt);
				if(m_bExport){
					CString strFrom = strBase + "Wiki\\" + pszWikiPathBase;
					CString strToPath;
					strToPath.Format("%s%s", strImg, pszWikiPathBase);
//					strToPath.Format("%s", strImg);
					if(!strToPath.Right(1).Compare("\\")){
						strToPath = strToPath.Left(strToPath.GetLength() - 1);
					}
					CString strAbsPath;
					strToPath.Replace("/", "\\");
					strToPath.Replace("\\\\", "\\");
					strFrom.Replace("/", "\\");
					strFrom.Replace("\\\\", "\\");
					int nPos = strFrom.ReverseFind('\\');
					strFrom = strFrom.Left(nPos);
					FullToAbstractPath(strFrom, strToPath, strAbsPath);
					strAbsPath.Replace("\\", "/");
					strAttFile.Format("%s\\%s%s", strAbsPath, szFile, szExt);
				}
				strLine.Format("<A HREF=\"%s\" target=\"_blank\">%s%s(%s)</a>&nbsp;", strAttFile, szFile, szExt, strSpan);
				strAttr += strLine;
			}
			if(!strAttr.IsEmpty()){
				strHtml += "<HR>\n";
				strHtml += strAttr;
				strHtml += "\n";
			}
		}
		DWORD dwEnd = ::GetTickCount();
		DWORD dwSpan = dwEnd - dwStart;
		double dSpan = (double)dwSpan / 1000.0;
		CString strSpan = "";
		if(m_objAnaInfo.bUseShowConvTime){
			strSpan.Format("Convert time %f sec.<br>", dSpan);
		}

		CString strFooter;
		strFooter.Format("<HR>\n"
						 "%s\n"
						 "Personal Wiki - Copyright <A href=\"http://aquaspac.hp.infoseek.co.jp/\" target=\"_blank\">Project D.E.V</a>\n",
						 strSpan);
		strHtml += strFooter;
		strHtml += "<A NAME=\"__PWIKI_BOTTOM__\">\n";
	}
	return TRUE;
}

/**
 * @brif �A�E�g���C���v���O�C���֐�
 */
void CAnalisysWiki::GetOutlinePlugin(CString &strDetail2, CString &strHtml, CStringArray &arrContents, LPCTSTR pszWikiPathBase, LPCTSTR pszImgPath, BOOL bPlainText){
	CString strLine;
	//#�v���O�C�����
	while(!strDetail2.IsEmpty()){
		int nPos = strDetail2.Find("\n");
		if(nPos != -1){
			strLine = strDetail2.Left(nPos);
			strDetail2 = strDetail2.Right(strDetail2.GetLength() - nPos - 1);
		}else{
			strLine = strDetail2;
			strDetail2 = "";
		}
		
		if(!strLine.Left(strlen("#contents")).Compare("#contents")){
			ContentsAna(strLine, arrContents, bPlainText);

		}else if(!strLine.Left(strlen("#include")).Compare("#include")){
			int nStart = strLine.Find("(");
			int nEnd = strLine.Find(")");
			CString strPath = strLine.Mid(nStart + 1, nEnd - nStart - 1);
			IncludeAna(strLine, strPath, bPlainText);
		}else if(!strLine.Left(strlen("#hr")).Compare("#hr")){
			if(bPlainText){
				strLine = "----------------------------------------\n";
			}else{
				strLine = "<HR>\n";
			}

		}else if(!strLine.Left(strlen("#ref")).Compare("#ref")){
			int nPlugEnd = strLine.Find(");");
			CString strMid = strLine.Mid(strlen("#ref("), nPlugEnd - strlen("#ref("));
			strMid.Replace("&nbsp;", " ");
			//�p�����^
			CStringArray arrParam;
			while(!strMid.IsEmpty()){
				int nPos = strMid.Find(",");
				if(nPos == -1){
					arrParam.Add(strMid);
					strMid = "";
				}else{
					arrParam.Add(strMid.Left(nPos));
					strMid = strMid.Mid(nPos + 1);
				}
			}
			strMid = arrParam.GetAt(0);
			arrParam.RemoveAt(0);

			CString strEnd = strLine.Right(strLine.GetLength() - nPlugEnd - strlen(");"));
			if(bPlainText){
				strLine = strEnd;
			}else{
				AnalisysRef(strLine, strMid, &arrParam, pszWikiPathBase, pszImgPath, bPlainText);
				strLine = strLine + "<BR>\n" + strEnd;
			}
		}else if(!strLine.Left(strlen("#youtube")).Compare("#youtube")){
			if(bPlainText){
				strLine = "";
			}else{
				int nPlugEnd = strLine.Find(")");
				CString strMid = strLine.Mid(strlen("#youtube("), nPlugEnd - strlen("#youtube("));
				strLine.Format(	"<P><object width=\"425\" height=\"350\">"
								"<param name=\"movie\" value=\"http://www.youtube.com/v/%s\"></param>"
								"<param name=\"wmode\" value=\"transparent\"></param>"
								"<embed src=\"http://www.youtube.com/v/%s\" type=\"application/x-shockwave-flash\" wmode=\"transparent\" width=\"425\" height=\"350\">"
								"</embed></object></P>\n",
								strMid, strMid);
			}
		}else if(!strLine.Left(strlen("#br")).Compare("#br")){
			//���s
			if(bPlainText){
				strLine = "\n";
			}else{
				strLine = strLine.Mid(strlen("#br"));
				strLine = "<BR>\n" + strLine;
			}
/*
		}else if(!strLine.Left(strlen("#rss")).Compare("#rss")){
			int nPlugEnd = strLine.Find(")");
			CString strMid = strLine.Mid(strlen("#rss("), nPlugEnd - strlen("#rss("));
			
			CString strURL;
			CString strUser;
			CString strPass;
			
			if(strMid.Find(",", 0) == -1){
				strURL = strMid;
			}else{
				int nSepPos = strMid.Find(",", 0);
				if(nSepPos > 0){
					strURL = strMid.Left(nSepPos);
					strMid = strMid.Mid(nSepPos + 1);
				}
				nSepPos = strMid.Find(",", 0);
				if(nSepPos > 0){
					strUser = strMid.Left(nSepPos);
					strMid = strMid.Mid(nSepPos + 1);
				}
				strPass = strMid;
			}
			
			//RSS���擾���AHTML�ɕϊ�����
			CRssCtrl objRss;
			objRss.Create(strURL, strUser, strPass);
			CString strRss;
			objRss.GetRSS(strRss);
			CString strOut = "";
			objRss.ConvertHTML(strRss, strOut);
			if(strOut.IsEmpty()){
			}else{
				strLine.Format("<TABLE class=\"rss\">\r\n%s\r\n</TABLE>", strOut);
			}
*/
		}
		strHtml += strLine;
		strHtml += "\n";
	}
}

/**
 * @brif �C�����C���v���O�C���֐�
 */
void CAnalisysWiki::GetInlinePlugin(CString &strLine, LPCTSTR pszWikiPathBase, LPCTSTR pszImgPath, BOOL bPlainText){
	typedef struct tagPLGINFO{
		const char* pszName;	//�v���O�C������
		int nType;				//�^�C�v 0:�p�����^�Ȃ� 1:�p�����^���� 2:�p�����^���� 9:�G�X�P�[�v����
	}PLGINFO, *PPLGINFO;
	PLGINFO arrPlgName[] ={
#if defined(USE_IMG)
		{"img",		1},		//&img(URL);
#endif
		{"ref",		1},		//&ref(URL,Name);
		{"color",	2},		//&color(Color){TEXT};
		{"size",	2},		//&size(Size){TEXT};
		{"heart",	0},		//&heart;
		{"smile",	0},		//&smile;
		{"bigsmile",0},		//&bigsmile;
		{"huh",		0},		//&huh;
		{"oh",		0},		//&oh;
		{"wink",	0},		//&wink;
		{"sad",		0},		//&sad;
		{"worried",	0},		//&worried;
		{"br",		0},		//&br;
		{"ruby",	2},		//&ruby(���r){������};
		{"aname",	1},		//&aname(�A���J�[��);
		{"youtube",	1},		//&youtube(ID);
		{"#x",		9},		//&#xnnn(�G�X�P�[�v����);
		{"#",		9},		//&#nnnn(�G�X�P�[�v����);
	};
	typedef enum INLINE_PLG{
#if defined(USE_IMG)
		IP_IMG,
#endif
		IP_REF,
		IP_COLOR,
		IP_SIZE,
		IP_HEART,
		IP_SMILE,
		IP_BIGSMILE,
		IP_HUH,
		IP_OH,
		IP_WINK,
		IP_SAD,
		IP_WORRIED,
		IP_BR,
		IP_RUBY,
		IP_ANAME,
		IP_YOUTUBE,
		IP_END,
	};
	
	if(!bPlainText){
		TRACE("");
	}

	int nPlgSize = sizeof(arrPlgName) / sizeof(PLGINFO);
	CString strPlugin = "";
	int nPlugStart = 0;
	int nPlugEnd = 0;
	int nPlugSep;
	CString strLeft = "";
	CString strMid = "";
	CString strEnd = "";
	CString strSep = "";
	BOOL bPlgMatch = FALSE;
	while(TRUE){
		bPlgMatch = FALSE;
		for(int nCnt = 0; nCnt < nPlgSize; nCnt++){
			nPlugStart = -1;
			if(arrPlgName[nCnt].nType == 0){
				//����q���Ȃ��ꍇ
#if defined(CMP_AMP)
				strPlugin.Format("&amp;%s;", arrPlgName[nCnt].pszName);
#else
				strPlugin.Format("&%s;", arrPlgName[nCnt].pszName);
#endif
				nPlugStart = strLine.Find(strPlugin);
				nPlugEnd = nPlugStart + strPlugin.GetLength();
				if(nPlugStart == -1){
					continue;
				}
				switch(nCnt){
				case IP_HEART:		//heart
				case IP_SMILE:		//smile
				case IP_BIGSMILE:	//bigsmile
				case IP_HUH:		//huh
				case IP_OH:			//oh
				case IP_WINK:		//wink
				case IP_SAD:		//sad
				case IP_WORRIED:	//worried
					strLeft = strLine.Left(nPlugStart);
					strEnd = strLine.Mid(nPlugEnd);
					if(bPlainText){
						strLine.Format("%s%s", strLeft, strEnd);
					}else{
						CString strFacePath;
//						strFacePath.Format("%s\\Img\\Face\\%s.png", m_objAnaInfo.pszBasePath, arrPlgName[nCnt].pszName);
						if(m_bExport){
							strFacePath.Format("%s\\Img\\Face", m_objAnaInfo.pszBasePath);
							CString strAbsPath = "";
							CString strFromPath = m_strWikiRealPath;
							int nPos = strFromPath.ReverseFind('\\');
							strFromPath = strFromPath.Left(nPos);
							FullToAbstractPath(strFromPath, strFacePath, strAbsPath);
							strAbsPath.Replace("\\\\", "\\");
							strAbsPath.Replace("\\", "/");
							strFacePath.Format("%s\\%s.png", strAbsPath, arrPlgName[nCnt].pszName);
						}else{
							strFacePath.Format("./Img/Face/%s.png", arrPlgName[nCnt].pszName);
						}
						strFacePath.Replace("\\\\", "\\");
						strLine.Format("%s<img src=\"%s\">%s", strLeft, strFacePath, strEnd);
					}
					bPlgMatch = TRUE;
					break;
				case IP_BR:			//br
					strLeft = strLine.Left(nPlugStart);
					strEnd = strLine.Mid(nPlugEnd);
					if(bPlainText){
						strLine.Format("%s%s", strLeft, strEnd);
					}else{
						strLine.Format("%s<BR>\n%s", strLeft, strEnd);
					}
					bPlgMatch = TRUE;
					break;
				default:
					ASSERT(0);
					break;
				}
#if defined(CMP_AMP)
			}else if(arrPlgName[nCnt].nType == 9 && !bPlainText){
				//�G�X�P�[�v����(�v���[���e�L�X�g�̏ꍇ�͂��̂܂܏o��)
				strPlugin.Format("&amp;%s", arrPlgName[nCnt].pszName);
				//�J�n�𒲂ׂ�
				nPlugStart = strLine.Find(strPlugin);
				CString strLine2;
				
				if(nPlugStart == -1){
					continue;
				}
				strLeft = strLine.Left(nPlugStart);
				strLine2 = strLine.Mid(nPlugStart);

				//�I���𒲂ׂ�
				nPlugEnd = strLine2.Find(";");
				if(nPlugEnd == -1){
					continue;
				}
				nPlugEnd += 4;
				strMid = strLine2.Mid(0, nPlugEnd + 1);
				strEnd = strLine2.Mid(nPlugEnd + 1);
				strMid.Replace("&amp;", "&");
				strLine = strLeft + strMid + strEnd;

				bPlgMatch = TRUE;
#endif
			}else{
#if defined(CMP_AMP)
				strPlugin.Format("&amp;%s(", arrPlgName[nCnt].pszName);
#else
				strPlugin.Format("&%s(", arrPlgName[nCnt].pszName);
#endif
				//�J�n�𒲂ׂ�
				nPlugStart = strLine.Find(strPlugin);
				if(nPlugStart == -1){
					continue;
				}
				//�I���𒲂ׂ�
				if(arrPlgName[nCnt].nType == 1){
					nPlugEnd = strLine.Find(");");
				}else{
					nPlugEnd = strLine.Find("};");
					//�؂�ڂ𒲂ׂ�
					nPlugSep = strLine.Find("){", nPlugStart);
					if(nPlugSep == -1){
						continue;
					}
				}
				if(nPlugEnd == -1){
					continue;
				}

				CString strInPlg = "";
				int nPlugStEtc = 0;
				for(int nInCnt = 0; nInCnt < nPlgSize; nInCnt++){
					if(arrPlgName[nCnt].nType == 0){
						continue;
					}
#if defined(CMP_AMP)
					strInPlg.Format("&amp;%s(", arrPlgName[nInCnt].pszName);
#else
					strInPlg.Format("&%s(", arrPlgName[nInCnt].pszName);
#endif
					nPlugStEtc = strLine.Find(strInPlg, nPlugStart + 1);
					//���̃v���O�C���J�n�𒲂ׂ�
					if((nPlugStEtc != -1) && (nPlugEnd != -1) && (nPlugStEtc < nPlugEnd)){
						//�ق��̃v���O�C�����A�I�����O�ɂ���ꍇ�A����q�Ƃ݂Ȃ��̂�
						//�I��̈ʒu���X�V����
						//�ʒu���X�V������A�ق��̃v���O�C���̈ʒu���A�v���O�C���̊J�n�𒲂ׂ�
						if(arrPlgName[nCnt].nType == 1){
							nPlugEnd = strLine.Find(");", nPlugEnd + 1);
						}else{
							nPlugEnd = strLine.Find("};", nPlugEnd + 1);
						}
					}
				}

				//�ϊ�
				strLeft = strLine.Left(nPlugStart);
#if defined(CMP_AMP)
				strInPlg.Format("&amp;%s(", arrPlgName[nCnt].pszName);
#else
				strInPlg.Format("&%s(", arrPlgName[nCnt].pszName);
#endif
				strMid = strLine.Mid(nPlugStart + strlen(strInPlg), nPlugEnd - (nPlugStart + strlen(strInPlg)));
				if((arrPlgName[nCnt].nType == 1) || (arrPlgName[nCnt].nType == 2)){
					strEnd = strLine.Mid(nPlugEnd + 2);
				}

				//(...){...}��{...}�̏����擾����
				if(arrPlgName[nCnt].nType == 2){
					strSep = strLine.Mid(nPlugSep + 2, nPlugEnd - nPlugSep - 2);
					strMid = strLine.Mid(nPlugStart + strInPlg.GetLength(), nPlugSep - nPlugStart - strInPlg.GetLength());
				}

				//�p�����^
				CStringArray arrParam;
				while(!strMid.IsEmpty()){
					int nPos = strMid.Find(",");
					if(nPos == -1){
						arrParam.Add(strMid);
						strMid = "";
					}else{
						arrParam.Add(strMid.Left(nPos));
						strMid = strMid.Mid(nPos + 1);
					}
				}
				strMid = arrParam.GetAt(0);
				arrParam.RemoveAt(0);

				switch(nCnt){ // <<<< switch start <<<<<<<<<<<<<<<<
#if defined(USE_IMG)
				//----------img----------------------------------------
				case IP_IMG:
					{
						CString strPrm = "";
						int nPar = -1;
						if(arrParam.GetSize()){
							strPrm = arrParam.GetAt(0);
						}
						if(bPlainText){
							strLine.Format("%s%s", strLeft, strEnd);
						}else{
							CString strWikiBase = pszWikiPathBase;
							AbstractToFullWikiPath(strMid, strWikiBase);
							CString strPath;
							strPath.Format("%s\\%s", pszImgPath, strMid);
							strPath.Replace("/", "\\");
							strPath.Replace("\\\\", "\\");
							if(strPrm.IsEmpty()){
								strLine.Format("%s<IMG SRC=\"%s\" ALT=\"%s\">%s", strLeft, strPath, strMid, strEnd);
							}else{
								strLine.Format("%s<IMG SRC=\"%s\" ALT=\"%s\" width=\"%s\" height=\"%s\">%s", strLeft, strPath, strMid, strPrm, strPrm, strEnd);
							}
						}
					}
					bPlgMatch = TRUE;
					break;
#endif
				//----------ref----------------------------------------
				case IP_REF:
					{
						strMid.Replace("&nbsp;", " ");
						if(bPlainText){
							strLine.Format("%s%s", strLeft, strEnd);
						}else{
							AnalisysRef(strLine, strMid, &arrParam, pszWikiPathBase, pszImgPath, bPlainText);
							strLine = strLeft + strLine + strEnd;
						}
						bPlgMatch = TRUE;
					}
					break;
				//----------color----------------------------------------
				case IP_COLOR:
					if(bPlainText){
						strLine.Format("%s%s", strLeft, strEnd);
					}else{
						strLine.Format("%s<div style=\"color:%s;\">%s</div>%s", strLeft, strMid, strSep, strEnd);
					}
					bPlgMatch = TRUE;
					break;
				//----------size----------------------------------------
				case IP_SIZE:
					if(bPlainText){
						strLine.Format("%s%s", strLeft, strEnd);
					}else{
						strLine.Format("%s<div style=\"font-size:%s;\">%s</div>%s", strLeft, strMid, strSep, strEnd);
					}
					bPlgMatch = TRUE;
					break;
				//----------ruby----------------------------------------
				case IP_RUBY:
					if(bPlainText){
						strLine.Format("%s%s(%s)%s", strLeft, strSep, strMid, strEnd);
					}else{
						strLine.Format("%s<RUBY><RB>%s<RP>(</RP><RT>%s</RT><RP>)</RP></RUBY>%s", 
										strLeft, strSep, strMid, strEnd);
					}
					bPlgMatch = TRUE;
					break;
				//----------aname----------------------------------------
				case IP_ANAME:
					if(bPlainText){
						strLine.Format("%s%s", strLeft, strEnd);
					}else{
						strLine = strLeft + "<A NAME=\"%s\">" + strMid + strEnd;
					}
					bPlgMatch = TRUE;
					break;
				//----------aname----------------------------------------
				case IP_YOUTUBE:
					strLine.Format("%s"
									"<object width=\"425\" height=\"350\">"
									"<param name=\"movie\" value=\"http://www.youtube.com/v/%s\"></param>"
									"<param name=\"wmode\" value=\"transparent\"></param>"
									"<embed src=\"http://www.youtube.com/v/%s\" type=\"application/x-shockwave-flash\" wmode=\"transparent\" width=\"425\" height=\"350\">"
									"</embed></object><br>"
									"%s",
									strLeft,
									strMid, strMid,
									strEnd);
					
					
					if(bPlainText){
						strLine.Format("%s%s", strLeft, strEnd);
					}else{
						strLine = strLeft + "<A NAME=\"%s\">" + strMid + strEnd;
					}
					bPlgMatch = TRUE;
					break;
				} // <<<< switch end <<<<<<<<<<<<<<<<
			}
		}
		if(!bPlgMatch){
			break;
		}
	}
}

/**
 * @brif #ref or &ref�p��͊֐�
 */
//void CAnalisysWiki::AnalisysRef(CString &strHtml, LPCTSTR pszURL, LPCTSTR pszPrm, LPCTSTR pszWikiPathBase, LPCTSTR pszImgPath, BOOL bPlainText){
void CAnalisysWiki::AnalisysRef(CString &strHtml, LPCTSTR pszURL, CStringArray *parrPrm, LPCTSTR pszWikiPathBase, LPCTSTR pszImgPath, BOOL bPlainText){
	CString strURL = pszURL;
	if(bPlainText){
		return;
	}else{
		CString strWikiBase = pszWikiPathBase;
		AbstractToFullWikiPath(strURL, strWikiBase);
		CString strPath;
		strPath.Format("%s\\%s", pszImgPath, strURL);
		strPath.Replace("/", "\\");
		strPath.Replace("\\\\", "\\");

		CString strAbsPath;
		CString strBase = m_objAnaInfo.pszBasePath;
		CString strWikiPath = strBase + "Wiki\\" + pszWikiPathBase;
		strWikiPath.Replace("/", "\\");
		strWikiPath.Replace("\\\\", "\\");
		int nPos = strWikiPath.ReverseFind('\\');
		strWikiPath = strWikiPath.Left(nPos);
		CString strToPath = strPath;
		nPos = strToPath.ReverseFind('\\');
		strToPath = strToPath.Left(nPos);
		strToPath.Replace("/", "\\");
		strToPath.Replace("\\\\", "\\");

		FullToAbstractPath(strWikiPath, strToPath, strAbsPath);
		if(m_bExport){
			strPath = strAbsPath + strURL;
			strPath.Replace("/", "\\");
			strPath.Replace("\\\\", "\\");
			strPath.Replace("\\", "/");
		}

		char szExt[MAX_PATH];
		memset(szExt, 0, MAX_PATH);
		_splitpath(strPath, NULL, NULL, NULL, szExt);
		CString strExt = szExt;

		BOOL bMatch = FALSE;
		CString strMime;
		int nMimeSize = m_objMime.GetDataSize();
		for(int nMime = 0; nMime < nMimeSize; nMime++){
			if(!m_objMime.GetUse(nMime)){
				continue;
			}
			CString strExts = m_objMime.GetExt(nMime);
			strMime = m_objMime.GetMimeType(nMime);
			int nSplPos = strMime.Find("/", 0);
			CString strType = strMime.Left(nSplPos);
			while(!strExts.IsEmpty() && (nSplPos != -1)){
				int nExtPos = strExts.Find(";", 0);
				CString strSingleExt;
				if(nExtPos != -1){
					strSingleExt = strExts.Left(nExtPos);
					strExts = strExts.Mid(nExtPos + 1);

				}else{
					strSingleExt = strExts;
					strExts = "";
				}
				strSingleExt = "." + strSingleExt;
				if(strExt.CompareNoCase(strSingleExt)){
					continue;
				}
				if(!strType.CompareNoCase("IMAGE")){
					//�摜(width, height, �^�C�g��)
					CString strTitle = strURL;
					CString strPrm = "";
					if(parrPrm){
						int nSize = parrPrm->GetSize();
						for(int i = 0; i < nSize; i++){
							if(i == (nSize - 1)){
								//�Ō�̓^�C�g���Ƃ݂Ȃ�
								strTitle = parrPrm->GetAt(i);
							}else{
								if(i == 0){
									strPrm += "WIDTH=\"";
								}else if(i == 1){
									strPrm += "HEIGHT=\"";
								}else{
									continue;
								}
								strPrm += parrPrm->GetAt(i);
								strPrm += "\" ";
							
							}
						}

					}
					strHtml.Format("<IMG SRC=\"%s\" ALT=\"%s\"", strPath, strTitle);
					if(!strPrm.IsEmpty()){
						strHtml += strPrm;
					}
					strHtml += ">";
					bMatch = TRUE;
					break;
				}else{
					//����
					strHtml.Format("<EMBED "
										"width=\"176\" "
										"height=\"48\" "
										"showcontrols=\"1\" "
										"autoplay=\"false\" "
										"autostart=\"false\" "
										"type=\"%s\" "
										"src=\"%s\"></EMBED>",
										strMime, 
										strPath);
					bMatch = TRUE;
					break;
				}
			}
		}

		if(!bMatch){
			CString strTitle = strURL;
			if(parrPrm && (parrPrm->GetSize() > 0)){
				strTitle = parrPrm->GetAt(0);
			}

			strHtml.Format("<A HREF=\"%s\" TARGET=\"_blank\">%s</a>", strPath, strTitle);
		}
	}
}

/**
 * @brif �����N���
 * @param CString &strLine ��͑Ώە�����B���ʂ����̈����Ɋi�[�����
 * @param LPCTSTR pszWikiPathBase ��̓t�@�C����Wiki�x�[�X�p�X
 * @param BOOL    bPlainText �e�L�X�g�`���ŕϊ����邩�ǂ���
 * @return �Ȃ�
 */
void CAnalisysWiki::LinkAna(CString &strLine, LPCTSTR pszWikiPathBase, BOOL bPlainText){
	CString strAppendPath =	m_objAnaInfo.pszAppendPath;
	while(TRUE){
		int nChkStartPos = strLine.Find("[[");
		int nChkEndPos = strLine.Find("]]", nChkStartPos);
		if((nChkStartPos == -1) || (nChkEndPos == -1)){
			break;
		}
		//�����N�u������
		CString strLeft = strLine.Left(nChkStartPos);
		CString strMid = strLine.Mid(nChkStartPos + strlen("[["), nChkEndPos - nChkStartPos - strlen("[["));
		CString strEnd = strLine.Right(strLine.GetLength() - nChkEndPos - strlen("]]"));

		CString strURL = strMid;
		CString strName = strMid;
		
		int nSep1 = strMid.Find(":");
		int nSep2 = strMid.Find(">");
		if(nSep2 != -1){
			nChkStartPos = nSep2;
			strName = strMid.Left(nChkStartPos);
			strURL = strMid.Right(strMid.GetLength() - nChkStartPos - 1);
		}else{
			nChkStartPos = nSep1;
			nChkEndPos = strMid.Find(":", nChkStartPos + 1);
			if(nChkEndPos != -1){
				strName = strMid.Left(nChkStartPos);
				strURL = strMid.Right(strMid.GetLength() - nChkStartPos - 1);
			}
		}

		if(bPlainText){
			strLine.Format("%s%s%s", strLeft, strName, strEnd);
		}else{
			if(!strURL.Left(5).CompareNoCase("http:")
			|| !strURL.Left(6).CompareNoCase("https:")
			|| !strURL.Left(5).CompareNoCase("file:")
			|| !strURL.Left(4).CompareNoCase("ftp:")
			|| !strURL.Left(4).CompareNoCase("mk:@")
			|| !strURL.Left(7).CompareNoCase("mailto:")
			){
				strLine.Format("%s<A HREF=\"%s\" target=\"_blank\">%s</A>%s", strLeft, strURL, strName, strEnd);
			}else{

				CString strWikiPath = strURL;
				CString strWikiPathBase = pszWikiPathBase;

				CString strReal;
				AbstractToFullWikiPath(strWikiPath, strWikiPathBase);

				if(strWikiPathBase.IsEmpty()){
					//�t����񂪂���Εt������
					if(!strAppendPath.IsEmpty()){
						if(strWikiPath.GetLength() >= strAppendPath.GetLength()){
							if(strWikiPath.Left(strAppendPath.GetLength()).CompareNoCase(strAppendPath)){
								strWikiPath = strAppendPath + strWikiPath;
							}
						}else{
							strWikiPath = strAppendPath + strWikiPath;
						}

					}

					strLine.Format("%s<A HREF=\"wiki://%s\">%s</A>%s", strLeft, strWikiPath, strName, strEnd);
				}else if(strWikiPath.IsEmpty()){
					strLine.Format("%s%s<font color=\"red\">!�p�X������������܂���</a>%s", strLeft, strName, strEnd);
				}else{
					strWikiPath.TrimLeft();
					strWikiPath.TrimRight();
					CheckURLValue(strWikiPath);

					//�y�[�W�̑��݃`�F�b�N
					CString strChkPath;
					strChkPath.Format("%sWiki\\%s.pwd", m_objAnaInfo.pszBasePath, strWikiPath);
					strChkPath.Replace("/", "\\");

					if(m_bExport){
						CString strToPath;
						CString strFromPath;
						strToPath.Format("%s\\Wiki\\%s", m_objAnaInfo.pszBasePath, strWikiPath);
						strFromPath.Format("%s\\Wiki\\%s", m_objAnaInfo.pszBasePath, pszWikiPathBase);
						strToPath.Replace("/", "\\");
						strToPath.Replace("\\\\", "\\");
						strFromPath.Replace("/", "\\");
						strFromPath.Replace("\\\\", "\\");
						int nPos = strFromPath.ReverseFind('\\');
						strFromPath = strFromPath.Left(nPos);
						CString strAbsPath;
						FullToAbstractPath(strFromPath, strToPath, strAbsPath);
						strWikiPath = strAbsPath + ".html";
						strWikiPath.Replace("\\", "/");
					}else{
						//�t����񂪂���Εt������
						if(!strAppendPath.IsEmpty()){
							if(strWikiPath.GetLength() >= strAppendPath.GetLength()){
								if(strWikiPath.Left(strAppendPath.GetLength()).CompareNoCase(strAppendPath)){
									if(strWikiPath.Left(1).Compare("/")){
										strWikiPath = strAppendPath + "/" + strWikiPath;
									}else{
										strWikiPath = strAppendPath + strWikiPath;
									}
								}
							}else{
								if(strWikiPath.Left(1).Compare("/")){
									strWikiPath = strAppendPath + "/" + strWikiPath;
								}else{
									strWikiPath = strAppendPath + strWikiPath;
								}
							}

						}
						strWikiPath = "wiki://" + strWikiPath;
						strWikiPath.Replace("\\/", "/");
					}
					if(CFindFile::IsExistFile(strChkPath)){
						strLine.Format("%s<A HREF=\"%s\">%s</A>%s", strLeft, strWikiPath, strName, strEnd);
					}else{
						strLine.Format("%s%s<A HREF=\"%s\">?</A>%s", strLeft, strName, strWikiPath, strEnd);
					}
				}
			}
		}
	}
}

/**
 * @brif #contents���
 * @param CString &strLine ���ʂ��i�[����
 * @param LPCTSTR pszWikiPathBase ��̓t�@�C����Wiki�x�[�X�p�X
 * @param BOOL    bPlainText �e�L�X�g�`���ŕϊ����邩�ǂ���
 * @return �Ȃ�
 */
void CAnalisysWiki::ContentsAna(CString &strLine, CStringArray &arrContents, BOOL bPlainText){
	//�C���f�b�N�X�}��
	int nSize = arrContents.GetSize();
	CString strURL;
	CString strIndex;
	int nIndent[3];
	memset(nIndent, 0, sizeof(int) * 3);
	int nCurIndent = 0;
	int nOldIndent = -1;
	strLine = "";
	for(int nIndex = 0; nIndex < nSize; nIndex++){
		strURL = arrContents.GetAt(nIndex);
		if(!strURL.Left(3).Compare("***")){
			strURL = strURL.Right(strURL.GetLength() - 3);
			nCurIndent = 2;
		}else if(!strURL.Left(2).Compare("**")){
			strURL = strURL.Right(strURL.GetLength() - 2);
			nCurIndent = 1;
		}else if(!strURL.Left(1).Compare("*")){
			strURL = strURL.Right(strURL.GetLength() - 1);
			nCurIndent = 0;
		}
		if(bPlainText){
			for(int i = 0; i < nCurIndent; i++){
				strLine += "    ";
			}
			strLine += strURL;
			strLine += "\n";
		}else{
			if(nCurIndent != nOldIndent){
				int nSpan = abs(nOldIndent - nCurIndent);
				if(nOldIndent < nCurIndent){
					for(int i = 0 ;i < nSpan; i++){
						if(!nIndent[i + nCurIndent]){
							CString strTabs = "";
							for(int nTabs = 0; nTabs < nCurIndent - i; nTabs++){
								strTabs += "\t";
							}
							strLine += strTabs;
							strLine += "<UL>\n";
							nIndent[nCurIndent - i] = 1;
						}
					}
				}else{
					for(int i = 0 ;i < nSpan; i++){
						if(nIndent[nOldIndent - i]){
							CString strTabs = "";
							for(int nTabs = 0; nTabs < nOldIndent - i; nTabs++){
								strTabs += "\t";
							}
							strLine += strTabs;
							strLine += "</UL>\n";
							nIndent[nOldIndent - i] = 0;
						}
					}
				}
			}
			nOldIndent = nCurIndent;
			CString strTabs = "";
			for(int nTabs = 0; nTabs < nCurIndent + 1; nTabs++){
				strTabs += "\t";
			}
		
			CString strHref = strURL;
			while(TRUE){
				int stPos = strHref.Find("<");
				int edPos = strHref.Find(">");
				if(((stPos != -1) && (edPos != -1))
				&& (stPos < edPos)){
					CString strDel = strHref.Mid(stPos, edPos - stPos + 1);
					strHref.Replace(strDel, "");
				}else{
					break;
				}
			}
			CString strName = strHref;
			ReplaceHTMLText(strHref, strHref);

			strIndex.Format("%s<LI><A HREF=\"#%s\">%s</A></LI>\n", strTabs, strHref, strName);
			strLine += strIndex;
		}
	}
	if(!bPlainText){
		for(int i = 2; i >= 0; i--){
			if(nIndent[i]){
				CString strTabs = "";
				for(int nTabs = 0; nTabs < i; nTabs++){
					strTabs += "\t";
				}
				strLine += strTabs;
				strLine += "</UL>\n";
			}
		}
		strLine += "<BR>";
	}
}

/**
 * @brif #include���
 * @param CString &strLine ���ʂ��i�[����
 * @param LPCTSTR pszWikiPage �C���N���[�h����Wiki�y�[�W��
 * @param BOOL    bPlainText �e�L�X�g�`���ŕϊ����邩�ǂ���
 * @return �Ȃ�
 */
void CAnalisysWiki::IncludeAna(CString &strLine, LPCTSTR pszWikiPage, BOOL bPlainText){
	CString strIncFile;
	strIncFile.Format("%sWiki\\%s.pwd", m_objAnaInfo.pszBasePath, pszWikiPage);
	strIncFile.Replace("/", "\\");
	CFile file;
	char *pChar = NULL;

	CString strPropFile = strIncFile;
	strPropFile.Replace(".pwd", "\\.property");
	BOOL bCryp = (BOOL)GetInifileInt("Status", "Cryptography", 0, strPropFile);

	
	try{
		CFileStatus state;
		if(!file.Open(strIncFile, CFile::modeReadWrite)){
			throw(0);
		}
		file.GetStatus(state);
		pChar = new char[state.m_size + 1];
		if(!pChar){
			throw(0);
		}
		memset(pChar, 0, state.m_size + 1);
		file.Read(pChar, state.m_size);

		CString strDetail = pChar;


		if(bCryp){
			//����������
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

		Analisys(strDetail, strLine, pszWikiPage, bPlainText, FALSE, TRUE);
		strLine = "</h1>\r\n" + strLine;
		strLine =  pszWikiPage + strLine;
		strLine = "<h1>" + strLine;
	}catch(CFileException &fe){
		char szErr[1024];
		memset(szErr, 0, 1024);
		fe.GetErrorMessage(szErr, 1024);
		strLine = "\n<FONT COLOR=\"red\">#include�̃p�����^���s���ł��I</FONT>\n";
		CLogFile::SaveExceptionLog(&fe, "CAnalisysWiki::IncludeAna");
	}catch(...){
		strLine = "\n<FONT COLOR=\"red\">#include�̃p�����^���s���ł��I</FONT>\n";
		CLogFile::SaveExceptionLog("CAnalisysWiki::IncludeAna");
	}
	if(pChar){
		delete pChar;
	}
}

/**
 * @brif ��͐ݒ��ݒ肷��
 * @param PANAINFO pAnaInfo �ݒ���
 * @return �Ȃ�
 */
void CAnalisysWiki::SetAnaSetting(PANAINFO pAnaInfo){
	memcpy(&m_objAnaInfo, pAnaInfo, sizeof(ANAINFO));
}

/**
 * @brif HTML�𐶐�����
 * @param CString &strHtml ���ʂ̊i�[��
 * @param LPCTSTR pszCSSPath CSS�t�@�C��
 * @param LPCTSTR pszTitle �^�C�g��
 * @param LPCTSTR pszBody �{�f�B�[������HTML
 * @return �Ȃ�
 */
void CAnalisysWiki::CreateHTML2(CString &strHtml, LPCTSTR pszCSSPath, LPCTSTR pszTitle, LPCTSTR pszBody){
	CAnalisysWiki objAna;
	objAna.CreateHTML(strHtml, pszCSSPath, pszTitle, pszBody);
}
void CAnalisysWiki::CreateHTML(CString &strHtml, LPCTSTR pszCSSPath, LPCTSTR pszTitle, LPCTSTR pszBody){
	CString strHead;
	CString strTitle = pszTitle;
	if(!strTitle.Left(1).Compare("/")){
		strTitle = strTitle.Mid(1);
	}
	GetHtmlHeadLocal(strHead, pszCSSPath, pszTitle);
	strHtml.Format( "<HTML lang=\"ja\">\n"
					"%s\n"
//					"<BODY onContextMenu=\"return false;\">\n"
					"<BODY>\n"
					"<H1 class=\"page_title\">%s</H1>\n"
					"<TABLE class=\"body\"><TR><TD class=\"body\">\n"
					"%s\n"
					"</TD></TR></TABLE></BODY>\n"
					"</HTML>\n"
					,strHead
					,strTitle
					,pszBody
					);
}

/**
 * @brif HTML�̃w�b�_���擾����
 * @param CString &strHtml ���ʂ̊i�[��
 * @param LPCTSTR pszCSSPath CSS�t�@�C��
 * @param LPCTSTR pszTitle �^�C�g��
 * @return �Ȃ�
 */
void CAnalisysWiki::GetHtmlHead(CString &strHtml, LPCTSTR pszCSSPath, LPCTSTR pszTitle){
	CAnalisysWiki objAna;
	objAna.GetHtmlHeadLocal(strHtml, pszCSSPath, pszTitle);
}

/**
 * @brif HTML�̃w�b�_���擾����
 * @param CString &strHtml ���ʂ̊i�[��
 * @param LPCTSTR pszCSSPath CSS�t�@�C��
 * @param LPCTSTR pszTitle �^�C�g��
 * @return �Ȃ�
 */

void CAnalisysWiki::GetHtmlHeadLocal(CString &strHtml, LPCTSTR pszCSSPath, LPCTSTR pszTitle){
	CString strCSS;
	CString strBase = m_objAnaInfo.pszBasePath;
	CString strTitle = pszTitle;
	if(!strTitle.Left(1).Compare("/")){
		strTitle = strTitle.Mid(1);
	}
	if(m_bExport){
		//���݂̃y�[�W�̈ʒu����CSS�̈ʒu�����߂�
		strCSS.Format("%s\\CSS", m_objAnaInfo.pszBasePath);
		strCSS.Replace("/", "\\");
		strCSS.Replace("\\\\", "\\");
		CString strAbsPath;
		CString strFrom = m_strWikiRealPath;
		int nPos = strFrom.ReverseFind('\\');
		strFrom = strFrom.Left(nPos);
		
		FullToAbstractPath(strFrom, strCSS, strAbsPath);
		strCSS.Format("%s\\%s", strAbsPath, pszCSSPath);
		strCSS.Replace("/", "\\");
		strCSS.Replace("\\\\", "\\");
		strCSS.Replace("\\", "/");

	}else{
		strCSS.Format("./CSS/%s", pszCSSPath);
	}
	strHtml.Format( "<HEAD>\n"
					"<META http-equiv=\"Content-Style-Type\" content=\"text/css\">\n"
					"<META http-equiv=\"Content-Type\" content=\"text/html; charset=Shift_JIS\">\n"
					"<link rel=\"Stylesheet\" href=\"%s\">\n"
					"<TITLE>%s</TITLE>\n"
					"</HEAD>\n"
					,strCSS
					,pszTitle
	);
}
/**
 * @brif HTML�ɓK����������ɒu��������
 * @param LPCTSTR pszFrom �u�������Ώ�
 * @param CString &strEnd �u���������ʂ��i�[����
 * @return �Ȃ�
 */
void CAnalisysWiki::ReplaceHTMLText(LPCTSTR pszFrom, CString &strEnd){
	strEnd = pszFrom;
	strEnd.Replace("&", "&amp;");
	strEnd.Replace("<", "&lt;");
	strEnd.Replace(">", "&gt;");
	strEnd.Replace(" ", "&nbsp;");
}

/**
 * @brif URL�ɓK����������ɕύX����
 * @param CString &strValue �`�F�b�N�ΏہB�`�F�b�N���A�ϊ��������ʂ������Ɋi�[
 * @return �Ȃ�
 */
void CAnalisysWiki::CheckURLValue(CString &strValue){
	char arrText[] = {'.',  ':',  ',',  '*', 
					  '?',  /*'/',*/  '\'', '\"',
					  '<',  '>',  '|',  '$',
					  '#',  '\\', '&'};
	int nLen = sizeof(arrText);
	CString strRep;
	CString strCh;
	for(int i = 0; i < nLen; i++){
		strRep.Format("%%%d", arrText[i]);
		strCh = arrText[i];
		strValue.Replace(strCh, strRep);
	}
}

/**
 * @brif �e�[�u�����
 * @param CString &strLine ��͌��ʂ��i�[����
 * @param CStringArray &arrTable ��͑Ώ�
 * @return �Ȃ�
 */
void CAnalisysWiki::GetTableText(CString &strLine, CStringArray &arrTable, BOOL bPlainText){
	int nSize = arrTable.GetSize();
	CString strData;
	if(!bPlainText){
		strLine = "<TABLE class=\"normal\">\n";
	}
	for(int i = 0; i < nSize; i++){
		strData = arrTable.GetAt(i);
		strData = strData.Right(strData.GetLength() - 1);
		BOOL bHead = FALSE;
		if(!strData.Right(1).Compare("h")){
			strData = strData.Left(strData.GetLength() - 1);
			bHead = TRUE;
		}
		if(!bPlainText){
			strLine += "<TR>\n";
		}
		int nUnionH = 1;
		while(!strData.IsEmpty()){
			int nPos = strData.Find("|", 0);
			if(!bPlainText && (nUnionH == 1)){
				if(bHead){
					strLine += "<TD class=\"head\"";
				}else{
					strLine += "<TD class=\"normal\"";
				}
			}
			if(nPos != -1){
//				strLine += strData.Left(nPos);
				if(!strData.Left(4).Compare("&gt;")){
					//�A���Ώۂ��`�F�b�N
					if(!strData.Mid(4, 1).Compare("|")){
						nUnionH++;
						strData = strData.Right(strData.GetLength() - nPos - 1);
						continue;
					}else{
						//�A���Ώ�
						strData = strData.Right(strData.GetLength() - nPos - 1);
					}
				}else{
					if(nUnionH > 1){
						CString strCols;
						strCols.Format(" colspan=\"%d\"", nUnionH);
						nUnionH = 1;
						strLine += strCols;
					}
					CString strCell = strData.Left(nPos);;
					strData = strData.Right(strData.GetLength() - nPos - 1);
					
					if(!strCell.Left(strlen("CENTER:")).Compare("CENTER:")){
						strCell = strCell.Mid(strlen("CENTER:"));
						strLine += " style=\"text-align:center;\"";
					}else if(!strCell.Left(strlen("LEFT:")).Compare("LEFT:")){
						strCell = strCell.Mid(strlen("LEFT:"));
						strLine += " style=\"text-align:left;\"";
					}else if(!strCell.Left(strlen("RIGHT:")).Compare("RIGHT:")){
						strCell = strCell.Mid(strlen("RIGHT:"));
						strLine += " style=\"text-align:right;\"";
					}
					strLine += ">";
					strLine += strCell;
				}
			}else{
				strLine += strData;
				strData = "";
			}
			if(bPlainText){
				strLine += ", ";
			}else{
				strLine += "</TD>";
			}
		}
		if(bPlainText){
			strLine += "\n";
		}else{
			strLine += "</TR>\n";
		}
	}
	if(!bPlainText){
		strLine += "</TABLE>\n";
	}
}

/**
 * @brif �ӏ��������
 * @param CString &strLiText ��͌��ʂ��i�[����
 * @param CStringArray &arrStockLI ��͑Ώ�
 * @return �Ȃ�
 */
void CAnalisysWiki::GetLiText(CString &strLiText, CStringArray &arrStockLI, BOOL bPlainText){
	int nSize = arrStockLI.GetSize();
	CString strURL;
	CString strIndex;
	int nIndent[3];
	int nType[3];
	memset(nIndent, 0, sizeof(int) * 3);
	memset(nType, 0, sizeof(int) * 3);
	int nCurIndent = 0;
	int nCurType = 0;
	int nOldIndent = -1;
	int nOldType = -1;
	CString strLine = "";
	int nNumCnt[3];
	memset(nNumCnt, 0, sizeof(int) * 3);
	for(int nIndex = 0; nIndex < nSize; nIndex++){
		strURL = arrStockLI.GetAt(nIndex);
		if(!strURL.Left(3).Compare("+++")){
			strURL = strURL.Right(strURL.GetLength() - 3);
			nCurIndent = 2;
			nCurType = 1;
			nNumCnt[2]++;
		}else if(!strURL.Left(2).Compare("++")){
			strURL = strURL.Right(strURL.GetLength() - 2);
			nCurIndent = 1;
			nCurType = 1;
			nNumCnt[1]++;
		}else if(!strURL.Left(1).Compare("+")){
			strURL = strURL.Right(strURL.GetLength() - 1);
			nCurIndent = 0;
			nCurType = 1;
			nNumCnt[0]++;
		}else if(!strURL.Left(3).Compare("---")){
			strURL = strURL.Right(strURL.GetLength() - 3);
			nCurIndent = 2;
			nCurType = 0;
		}else if(!strURL.Left(2).Compare("--")){
			strURL = strURL.Right(strURL.GetLength() - 2);
			nCurIndent = 1;
			nCurType = 0;
		}else if(!strURL.Left(1).Compare("-")){
			strURL = strURL.Right(strURL.GetLength() - 1);
			nCurIndent = 0;
			nCurType = 0;
		}
		if(nCurIndent != nOldIndent){
			int nSpan = abs(nOldIndent - nCurIndent);
			if(nOldIndent < nCurIndent){
				for(int i = 0 ;i < nSpan; i++){
					if(!nIndent[i + nCurIndent]){
						CString strTabs = "";
						if(!bPlainText){
							for(int nTabs = 0; nTabs < nCurIndent - i; nTabs++){
								strTabs += "\t";
							}
							strLine += strTabs;
							if(!nCurType){
								strLine += "<UL>\n";
							}else{
								strLine += "<OL>\n";
							}
						}
						nIndent[nCurIndent - i] = 1;
						nType[nCurIndent - i] = nCurType;
					}
				}
			}else{
				for(int i = 0 ;i < nSpan; i++){
					if(nIndent[nOldIndent - i]){
						CString strTabs = "";
						if(!bPlainText){
							for(int nTabs = 0; nTabs < nOldIndent - i; nTabs++){
								strTabs += "\t";
							}
							strLine += strTabs;
							if(!nType[nOldIndent - i]){
								strLine += "</UL>\n";
							}else{
								strLine += "</OL>\n";
							}
						}
						nIndent[nOldIndent - i] = 0;
						nType[nOldIndent - i] = 0;
						nNumCnt[nOldIndent - i ] = 0;
					}
				}
			}
		}
		nOldIndent = nCurIndent;
		CString strTabs = "";
		for(int nTabs = 0; nTabs < nCurIndent + 1; nTabs++){
			if(bPlainText){
				strTabs += "    ";
			}else{
				strTabs += "\t";
			}
		}
		if(bPlainText){
			if(nCurType == 0){
				strIndex.Format("%s�E%s\n", strTabs, strURL);
			}else{
				strIndex.Format("%s%d�D%s\n", strTabs, nNumCnt[nCurIndent], strURL);
			}
		}else{
			strIndex.Format("%s<LI>%s</LI>\n", strTabs, strURL);
		}
		strLine += strIndex;
	}
	if(!bPlainText){
		for(int i = 2; i >= 0; i--){
			if(nIndent[i]){
				CString strTabs = "";
				for(int nTabs = 0; nTabs < i; nTabs++){
					strTabs += "\t";
				}
				strLine += strTabs;
				if(!nType[i]){
					strLine += "</UL>\n";
				}else{
					strLine += "</OL>\n";
				}
			}
		}
	}
	strLiText = strLine;
}


void CAnalisysWiki::GetAttachFiles(LPCTSTR pszWikiPath, LPCTSTR pszBasePath, CStringArray &arrAttach){
	arrAttach.RemoveAll();
	if(!pszWikiPath || !pszBasePath){
		return;
	}

	CString strAttachPath;
	strAttachPath.Format("%s\\Attach\\%s\\", pszBasePath, pszWikiPath);
	strAttachPath.Replace("/", "\\");
	strAttachPath.Replace("\\\\", "\\");
	CString strFindPath;
	strFindPath.Format("%s*.*", strAttachPath);
	HANDLE hRet = NULL;
	WIN32_FIND_DATA wfd;
	BOOL bFirst = TRUE;
	while(TRUE){
		if(bFirst){
			bFirst = FALSE;
			hRet = ::FindFirstFile(strFindPath, &wfd);
			if(hRet == INVALID_HANDLE_VALUE){
				break;
			}
		}else{
			if(!::FindNextFile(hRet, &wfd)){
				break;
			}
		}

		CString strFile = wfd.cFileName;
		if(!strFile.Compare(".") || !strFile.Compare("..") || !strFile.CompareNoCase(".properties")){
			continue;	
		}
		if((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY){
			continue;
		}
		CString strFilePath;
//		if(m_bExport){
//			strFilePath.Format("%s%s", strAttachPath, wfd.cFileName);
//		}else{
//			strFilePath.Format("%s%s", strAttachPath, wfd.cFileName);
//		}
		strFilePath.Format("%s%s", strAttachPath, wfd.cFileName);
		arrAttach.Add(strFilePath);
	}
	::FindClose(hRet);
	return;
}

/**
 * @brif ���ۃp�X���t���p�X�ɕϊ�����
 */
void CAnalisysWiki::AbstractToFullWikiPath(CString &strWikiPath, CString &strWikiPathBase){
	if(strWikiPathBase.IsEmpty()){
	}else if(!strWikiPath.Left(1).Compare("#")){
		//�y�[�W���A���J�[(Base#Ancer");
		strWikiPath = strWikiPathBase + strWikiPath;
	}else if(strWikiPath.Left(1).Compare("/") && strWikiPath.Left(1).Compare(".")){
		//���΃p�X�ł͂Ȃ�
	}else if(!strWikiPath.Left(1).Compare("/") && strWikiPath.Left(1).Compare(".")){
		//���΃p�X�ł͂Ȃ�
	}else{
		//���΃p�X
		while(TRUE){
			if(!strWikiPath.Left(2).Compare("./")){
				//�J�����g
				strWikiPath = strWikiPath.Right(strWikiPath.GetLength() - 2);
			}else if(!strWikiPath.Left(3).Compare("../")){
				//�ЂƂ�
				if(!strWikiPathBase.Right(1).Compare("/")){
					strWikiPathBase = strWikiPathBase.Left(strWikiPathBase.GetLength() - 1);
				}
				int nPos = strWikiPathBase.ReverseFind('/');
				if(nPos -1){
					strWikiPath.Empty(); 
					break;
				}
				strWikiPathBase = strWikiPathBase.Left(nPos - 1);
				strWikiPath = strWikiPath.Right(strWikiPath.GetLength() - 3);
			}else{
				break;
			}
		}
		if(!strWikiPath.IsEmpty()){
			strWikiPath = strWikiPathBase + "/" + strWikiPath;
		}
/*
		CString strAppendPath = m_objAnaInfo.pszAppendPath;
		if(!strAppendPath.IsEmpty()){
			strWikiPath = strAppendPath + strWikiPath;
		}
*/
	}

}

/**
 * @brif �t���p�X�𒊏ۃp�X�ɕϊ�����
 */
void CAnalisysWiki::FullToAbstractPath(LPCTSTR pszFromPath, LPCTSTR pszToPath, CString& strAbstractPath){
	strAbstractPath = "";
	//From����To���Q�Ƃ����ꍇ�̑��΃p�X
	CString strFrmPath = pszFromPath;
	CString strToPath = pszToPath;
	strFrmPath.Replace("/", "\\");
	strFrmPath.Replace("\\\\", "\\");
	strToPath.Replace("/", "\\");
	strToPath.Replace("\\\\", "\\");
	char szFrmDrv[MAX_PATH];
	char szToDrv[MAX_PATH];
	char szFrmDir[MAX_PATH];
	char szToDir[MAX_PATH];
	memset(szFrmDrv, 0, MAX_PATH);
	memset(szToDrv, 0, MAX_PATH);
	memset(szFrmDir, 0, MAX_PATH);
	memset(szToDir, 0, MAX_PATH);
	_splitpath(strFrmPath, szFrmDrv, szFrmDir, NULL, NULL);
	_splitpath(strToPath, szToDrv, szToDir, NULL, NULL);
	CString strFrmDrv = szFrmDrv;
	CString strToDrv = szToDrv;
	if(strFrmDrv.CompareNoCase(strToDrv)){
		strAbstractPath = pszToPath;
		return;
	}
	if(!strFrmPath.CompareNoCase(strToPath)){
		strAbstractPath = ".\\";
		return;
	}

	//�p�X�𕪉�����
	CStringArray arrFrom;
	CStringArray arrTo;
	SplitString(pszFromPath, "\\", arrFrom);
	SplitString(pszToPath, "\\", arrTo);

	int nFrmSize = arrFrom.GetSize();
	int nToSize = arrTo.GetSize();
	int nCnt = 0;
	if(nFrmSize > nToSize){
		nCnt = nToSize;
	}else{
		nCnt = nFrmSize;
	}
	BOOL bMatch = TRUE;
	int nUnMatchPos = 0;
	for(int i = 0; i < nCnt; i++){
		if(bMatch){
			CString strFrm = arrFrom[i];
			CString strTo = arrTo[i];
			if(strFrm.CompareNoCase(strTo)){
				//�Ⴄ�ꍇ
				strAbstractPath += "..\\";
				bMatch = FALSE;
				nUnMatchPos = i;
			}
		}else{
			strAbstractPath += "..\\";
		}
	}
	if(!bMatch){
		for(int i = nCnt; i < nFrmSize; i++){
			strAbstractPath += "..\\";
		}
		for(int j = nUnMatchPos; j < nToSize; j++){
			strAbstractPath += arrTo[j];
			if(j != (nToSize - 1)){
				strAbstractPath += "\\";
			}
		}
	}else{
		for(int j = nFrmSize ; j < nToSize; j++){
			strAbstractPath += arrTo[j];
			if(j != (nToSize - 1)){
				strAbstractPath += "\\";
			}
		}
	}
	strAbstractPath.Replace("/", "\\");
	strAbstractPath.Replace("\\\\", "\\");
}
void CAnalisysWiki::SplitString(LPCTSTR pszText, LPCTSTR pszSplit, CStringArray &arrResult){
	arrResult.RemoveAll();

	CString strText = pszText;
	CString strSplit = pszSplit;
	while(!strText.IsEmpty()){
		int nPos = strText.Find(strSplit, 0);
		if(nPos == -1){
			arrResult.Add(strText);
			strText = "";
		}else{
			arrResult.Add(strText.Left(nPos));
			strText = strText.Mid(nPos + 1);
		}
	}
	return;
}


void CAnalisysWiki::SetMimeType(CMimeType *pMime){
	CMimeType::Copy(pMime, &m_objMime);
}
